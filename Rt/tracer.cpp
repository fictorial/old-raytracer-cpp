//-----------------------------------------------------------------------------
// File:        tracer.cpp
// Repository:  $Source$
// Created:     Thu Sep 11 10:44:46 2003
// Last Change: Wed Oct 01 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/tracer.h"
#include "Rt/config.h"
#include "Rt/color.h"
#include "Rt/iworld.h"
#include "Rt/iprimitive.h"
#include "Rt/material.h"
#include "Rt/material.h"
#include "Rt/surfacepoint.h"
#include "Rt/light.h"
#include "Rt/camera.h"
#include "Rt/ray.h"

#include <cassert>
#include <cstdio>
#include <cmath>

namespace Rt 
{
  tracer::statmap tracer::stats_;

  const char* KEY_PRIMARY_SAMPLES = "primary samples (eyerays)";
  const char* KEY_ISECT_TESTS_TOTAL = "total intersection tests";
  const char* KEY_ISECT_TESTS_PASSED = "intersection tests passed";
  const char* KEY_SHADOW_TESTS = "shadow tests";
  const char* KEY_SHADOW_TESTS_PASSED = "shadow tests passed";
  const char* KEY_REFLECTION_RAYS = "reflection rays";
  const char* KEY_TRANSMISSION_RAYS = "transmission rays";
  //TODO
  const char* KEY_AVG_RAY_DEPTH = "avg ray depth";
  const char* KEY_MAX_RAY_DEPTH = "max ray depth";

  tracer::tracer(int iw, int ih, iworld* w)
    : iw_(iw)
    , ih_(ih)
    , maxdepth_(DEFAULT_MAX_DEPTH)
    , minweight_(DEFAULT_MIN_WEIGHT)
    , world_(w)
  {
    assert(w);
  }

  void tracer::maxdepth(int d)
  {
    assert(d > 0);
    maxdepth_ = d;
  }

  void tracer::minweight(scalar w)
  {
    assert(w > 0);
    minweight_ = w;
  }
  
  tracer::~tracer() 
  {
    delete world_;
  }
  
  colormap* tracer::trace()
  {
    camera* cam = world_->active_camera();
    assert(cam);
    cam->image_size(iw_, ih_);
    
    colormap* cm = new colormap(iw_, ih_);
    assert(cm);
    
    for (int y = 0; y < ih_; ++y) 
    {
      for (int x = 0; x < iw_; ++x) 
      {
        ++stats_[KEY_PRIMARY_SAMPLES];

        ray er(cam->eyeray(x, y)); 
        cm->set(x, y, shade(er));
      }
      
      if (y > 0 && y % 10 == 0) 
      {
        if (y % 100 == 0)
          printf("[%d]", y);
        
        fflush(stdout);
      }
    }
    
    printf("[Done]\n");

    // Get summary of primitive stats.
    
    for (Rt::iprimitive::statmap::const_iterator it = 
         Rt::iprimitive::stats_begin();
         it != Rt::iprimitive::stats_end(); ++it)
    {
      const Rt::prim_stats& s = (*it).second;

      stats_[KEY_ISECT_TESTS_TOTAL] += s.tests;
      stats_[KEY_ISECT_TESTS_PASSED] += s.tests_passed;
    }
    
    return cm;
  }
  
  bool tracer::closest_hit(const ray& r, surfacepoint* sp) 
  {
    assert(sp);

    surfacepoint closest;
    closest.t = SCALAR_MAX;
    
    bool any = false;
    surfacepoint curr;
    
    for (int i = 0; i < world_->num_primitives(); ++i) 
    {
      iprimitive* p = world_->get_primitive(i);
      assert(p);
      
      if (p->intersect(r, &curr)) 
      {
        if (curr.t > 0.0 && curr.t < closest.t) 
        {
          closest = curr;
          any = true;
        }
      }
    }
    
    if (any) 
    {
      *sp = closest;
      return true;
    }
    
    if (sp)
    {
      sp->t = -1;
    }

    return false;
  }

  scalar tracer::shadow(const ray& r, const v3& lpos, color* outcolor) 
  {
    ++stats_[KEY_SHADOW_TESTS];
    
    scalar s = 1.0;
    
    //TODO implement jitter for soft-shadows.

    surfacepoint sp;
    
    if (!closest_hit(r, &sp))
    {
      // Didn't hit anything at all; hence not in shadow.
      
      return s;
    }

    // TODO transparent surfaces
   
    if (sp.mat->Kt() > 0)
    {
      // Hit a transparent surface.  Refract the shadow
      // ray and recurse.
      //
      // TODO for now, just scale shadow factor down by transparency factor
    
      s *= sp.mat->Kt();
    }
    
    // Hit an object.  Is light (at 'p') closer?
    
    v3 vp = sp.P - r.o;
    v3 vl = lpos - r.o;
    
    if (length_sqr(vl) > length_sqr(vp))
    {
      // Hit object first; in shadow.

      ++stats_[KEY_SHADOW_TESTS_PASSED];

      // TODO seems like a hack to get colored transparent shadows.

      if (sp.mat->Kt() > 0)
      {
        if (outcolor)
        {
          *outcolor = sp.mat->diffuse();
        }

        return s;
      }
      
      return 0;
    }

    // Not in shadow.
    
    return s;
  }
  
  color tracer::shade(const ray& r, int depth, scalar weight) 
  {
    assert(depth > 0);
    assert(weight >= minweight_);

    if (depth > stats_[KEY_MAX_RAY_DEPTH])
    {
      stats_[KEY_MAX_RAY_DEPTH] = depth;
    }

    // This is a scaling factor to ensure we do not self-intersect
    // when spawning rays whose origin is a surface point.
    
    const scalar SURFACE_OFFSET = 1.0001;
    
    // Find closest primitive hit if anything.
    
    surfacepoint sp;
    
    if (!closest_hit(r, &sp))
    {
      return world_->bgcolor();
    }
    
    // Shade the surface point hit.
    
    assert(sp.prim);
    material* m = sp.mat;
    assert(m);

    // Ambient term.
    
    color Ia = world_->ambient() * m->diffuse();

    color Itotal(Ia);
    
    // light source contributions.
      
    for (int j=0; j < world_->num_lights(); ++j) 
    {
      light* Lj = world_->get_light(j);
    
      if (Lj->type() == light::AMBIENT)
      {
        // Ambient lights just add illumination without respect to 
        // incident angle, light parameters, etc.

        Itotal += Lj->spectrum() * m->Kd() * m->diffuse();
        continue;
      }

      v3 L;
     
      switch (Lj->type())
      {
      case light::AMBIENT:
        break;
      
      case light::POINT:
      case light::SPOT:
        L = Lj->position() - sp.P;
        break;
        
      case light::DIRECTIONAL:
        L = -Lj->direction();
        break;

      default:
        assert(false);
      }
      
      normalize(L); 
      
      // light's attenuation w.r.t. surface point. 
      
      scalar Ljatt = Lj->attenuation(sp.P);    
      
      // Determine spotlight factor. [0,1] 0=outside cone, 1=inside
      
      scalar cspot = 1;

      if (Lj->type() == light::SPOT)
      {
        scalar IdotL = Lj->direction() * -L;

        if (IdotL < 0.0 || IdotL > Lj->cutoff()*2.0)
        {
          cspot = 0.0;
        }
        else
        {
          cspot = ::pow(Rt::max(IdotL, 0.0), Lj->dropoff());
        }
      }

      // Determine how much of this point is in shadow w.r.t. light j.
      // [0,1] 0=in shadow, 1=not
      
      scalar S;
      color shadow_color(0,0,0);

      if (!Lj->castshadows())
      {
        S = 1.0;
      } 
      else
      {
        S = this->shadow(ray(sp.P + L * SURFACE_OFFSET, L), Lj->position(),
          &shadow_color);
      }
      
      if (S < EPS) 
      {
        // Surface point is in shadow.  Do not add diffuse nor specular terms.
        continue;
      
        /*
        color c(world_->ambient());
        normalize(c);
        S = sqrt(c.r*c.r+c.g*c.g+c.b*c.b);
        */
      }
      
      // Not 100% in shadow, determine this light's contribution to 
      // the illumination of the surface point.
    
      color ILj;
      m->local_illum(sp, L, *Lj, &ILj);

      // Add to total contribution.
     
      // TODO shadow_color * S ...
      Itotal += S * cspot * Ljatt * ILj;
    }
    
    if (depth + 1 < maxdepth_) 
    {
      // Recurse on specular reflection.
  
      if (m->Kr() * weight > minweight_) 
      {
        ++stats_[KEY_REFLECTION_RAYS];
      
        Itotal += m->Kr() * shade(
          ray(sp.P + sp.N * SURFACE_OFFSET, reflect(sp.I, sp.N)), 
          depth+1, m->Kr() * weight);
      }

      // Recurse on specular transmission.

      //TODO should use a stack for IORs
      //TODO when entering, push target IOR
      //TODO when exiting, pop target IOR
      //
      //This will allow transparent surfaces inside each other
      
      if (m->Kt() * weight > minweight_) 
      {
        scalar n1, n2;
       
        //TODO should not check on vacuum IOR to see if ray is entering
        //TODO should use dot product of normal and ray dir
        //TODO dp won't work as we flip normals when inside prims!
        
        if (r.IOR == 1.0)
        //if (sp.N * r.d < 0)
        {
          // ray is in vacuum. must be entering the inside 
          // of the hit primitive.
          
          n1 = 1.0;
          n2 = sp.mat->IOR();
        }
        else
        {
          // ray is not in a vacuum, must be inside a primitive
          // exiting back into the vacuum.

          n1 = sp.mat->IOR();
          n2 = 1.0;
        }

        v3 Td;
        
        if (Rt::refract(sp.I, sp.N, n1, n2, &Td))
        {
          ray T(sp.P + sp.N * -SURFACE_OFFSET, Td);
          
          T.IOR = n2;        // ray in new medium.
          
          Itotal += m->Kt() * shade(T, depth+1, m->Kt() * weight); 
      
          ++stats_[KEY_TRANSMISSION_RAYS];
        }
      }
    }

    bool visualize_normals = false;

    if (visualize_normals) 
    {
      // Return normal as color.
      
      color c(sp.N.x, sp.N.y, sp.N.z);
      normalize(c);
      return c;
    }
    else
    {
      // Combine all contributions and normalize output color.
    
      Rt::normalize(Itotal);
      return Itotal;
    }
  }
    
  tracer::statmap::const_iterator tracer::stats_begin()
  {
    return stats_.begin();
  }
  
  tracer::statmap::const_iterator tracer::stats_end()
  {
    return stats_.end();
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

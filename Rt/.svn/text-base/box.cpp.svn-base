//-----------------------------------------------------------------------------
// File:        box.cpp
// Repository:  $Source$
// Created:     Thu Sep 11 03:26:54 2003
// Last Change: Tue Sep 30 10:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/box.h"
#include "Rt/ray.h"
#include "Rt/surfacepoint.h"
#include "Rt/material.h"

#include <cassert>

namespace Rt 
{
  box::box(const v3& pta, const v3& ptb)
    : min_(Rt::min(pta.x, ptb.x), Rt::min(pta.y, ptb.y), Rt::min(pta.z, ptb.z))
    , max_(Rt::max(pta.x, ptb.x), Rt::max(pta.y, ptb.y), Rt::max(pta.z, ptb.z))
  {}
  
  box::box(const v3& center, scalar len) 
  {
    scalar half_len = len * 0.5;
    min_ = v3(center.x-half_len, center.y-half_len, center.z-half_len);
    max_ = v3(center.x+half_len, center.y+half_len, center.z+half_len);
  }
  
  box::box(const v3& center, scalar xlen, scalar ylen, scalar zlen)
    : min_(center.x-xlen*0.5, center.y-ylen*0.5, center.z-zlen*0.5)
    , max_(center.x+xlen*0.5, center.y+ylen*0.5, center.z+zlen*0.5) 
  {}
 
  namespace 
  {
    enum PLANE { NOPLANE=-1, XP, YP, ZP };
  }

  bool box::intersect(const ray& r, surfacepoint* isect)
  {
    ++iprimitive::stats_["box"].tests;
    
    scalar tn = -SCALAR_MAX;
    scalar tf =  SCALAR_MAX;
    
    scalar sign = 1.0;         // TODO -- Yes?
    PLANE which = NOPLANE;
    
    // X slabs
    
    if (fabs(r.d.x) < EPS) 
    {
      // Ray parallel to X plane. Is the origin in the X slab?
      
      if (r.o.x < min_.x || r.o.x > max_.x)
        return false;
    } 
    else 
    {
      // Not parallel to X axis.
      //
      // Find when the ray intersects the X slabs.  A slab is
      // 2 planes distinct only by distance, not normal.
      //
      // Ro(x) + t * Rd(x) = Xs
      // t * Rd(x) = Xs - Ro(x)
      // t = ( Xs - Ro(x) ) / Rd(x)

      scalar t1 = (min_.x - r.o.x) / r.d.x;
      scalar t2 = (max_.x - r.o.x) / r.d.x;

      // Want t1 as intersection with nearest plane in slab,
      // t2 with furthest.
      
      if (t1 > t2) 
      {
        Rt::swap(t1,t2);
      }
      
      // Keep track of furthest "near" hit and closest "far" hit.
      
      if (t1 > tn) 
      {
        tn = t1;
        which = XP;
        sign = -Rt::sgn(r.d.x);
      }
      
      if (t2 < tf) 
        tf = t2;
      
      // Ray misses box or box behind ray?
      
      if (tn > tf || tf < 0) 
        return false;
    }

    // Do the same for the Y slabs... 
    
    if (fabs(r.d.y) < EPS) 
    {
      if (r.o.y < min_.y || r.o.y > max_.y)
        return false;
    } 
    else 
    {
      scalar t1 = (min_.y - r.o.y) / r.d.y;
      scalar t2 = (max_.y - r.o.y) / r.d.y;
      
      if (t1 > t2) 
        Rt::swap(t1,t2);
      
      if (t1 > tn) 
      {
        tn = t1;
        which = YP;
        sign = -Rt::sgn(r.d.y);
      }
      
      if (t2 < tf)
        tf = t2;
      
      if (tn > tf || tf < 0)
        return false;
    }
    
    // Do the same for the Z slabs... 

    if (fabs(r.d.z) < EPS) 
    {
      if (r.o.z < min_.z || r.o.z > max_.z)
        return false;
    } 
    else 
    {
      scalar t1 = (min_.z - r.o.z) / r.d.z;
      scalar t2 = (max_.z - r.o.z) / r.d.z;
      
      if (t1 > t2) 
        Rt::swap(t1,t2);
      
      if (t1 > tn) 
      {
        tn = t1;
        which = ZP;
        sign = -Rt::sgn(r.d.z);
      }
      
      if (t2 < tf)
        tf = t2;
      
      if (tn > tf || tf < 0)
        return false;
    }

    // Record intersection info if requested.
    
    if (isect) 
    {
      isect->t = tn;
      isect->P = r.o + tn * r.d;
      isect->I = r.d;
      isect->prim = this;
      isect->mat = this->mat;
      
      // Check to see if ray origin is inside box.  If yes
      // then flip normal at intersection point.  We only
      // care about this for transparent boxes.
      
      if (mat->Kt() > 0) 
      {
        if (r.o.x > min_.x-EPS && r.o.x < max_.x+EPS &&
            r.o.y > min_.y-EPS && r.o.y < max_.y+EPS &&
            r.o.z > min_.z-EPS && r.o.z < max_.z+EPS) 
        {
          sign = -sign;
        }
      }

      // Set normal and texture coordinates based on which plane was hit.
      
      //TODO texcoords
      
      switch (which) 
      {
      case XP: 
        isect->N = v3(sign,0,0);
        break;
      
      case YP: 
        isect->N = v3(0,sign,0); 
        break;
      
      case ZP: 
        isect->N = v3(0,0,sign); 
        break;
      
      default:
        assert(false && "internal error in box intersect");
      }
    }
    
    ++iprimitive::stats_["box"].tests_passed;
    
    return true;
  }
  
  bool box::inside(const v3& p)
  {
    return
      p.x > min_.x-EPS && p.x < max_.x+EPS &&
      p.y > min_.y-EPS && p.y < max_.y+EPS &&
      p.z > min_.z-EPS && p.z < max_.z+EPS;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

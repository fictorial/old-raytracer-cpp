//-----------------------------------------------------------------------------
// File:        material.cpp
// Repository:  $Source$
// Created:     Thu Sep 18 13:36:03 2003
// Last Change: Sun Oct 05 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/material.h"
#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/colors.h"
#include "Rt/colormap.h"
#include "Rt/surfacepoint.h"
#include "Rt/light.h"
#include "Rt/colormap.h"

#include <cassert>
#include <cmath>

namespace Rt 
{
  material::material()
    : Kd_(1.0)
    , diffuse_(1,1,1)
    , Ks_(0.5)
    , roughness_(8.0)
    , specular_(colors::white)
    , Kr_(0.0)
    , Kt_(0.0)
    , IOR_(1.0)
    , diffmap_(0)
  {}

  material::material(scalar Kd, const color& diff, scalar Ks, scalar roughness, 
    const color& spec, scalar Kr, scalar Kt, scalar IOR)
    : Kd_(Kd)
    , diffuse_(diff)
    , Ks_(Ks)
    , roughness_(roughness)
    , specular_(spec)
    , Kr_(Kr)
    , Kt_(Kt)
    , IOR_(IOR) 
    , diffmap_(0)
  {
    assert(Kd_ >= 0 && Kd_ <= 1);
    assert(Ks_ >= 0 && Ks_ <= 1);
    assert(Kt_ >= 0 && Kt_ <= 1);
  }
  
  void material::local_illum(const surfacepoint& p, const v3& L, 
    const light& Lj, color* Io) 
  {
    assert(Io);

    scalar NdotL = p.N*L;
    
    if (NdotL <= 0) 
    {
      Io->set(0,0,0);
      return;
    }

    v3 V(-p.I);

    // Use diffuse map over flat color if we have such a map.

    color diffuse_color;
    
    if (diffmap_)
    {
      //TODO bilinear... 

      unsigned ix = unsigned((p.u - floor(p.u)) * diffmap_->w());
      unsigned iy = unsigned((p.v - floor(p.v)) * diffmap_->h());
      
      diffmap_->get(ix, iy, &diffuse_color);
    }
    else
    {
      diffuse_color = diffuse_;
    }

    if (blinn_) 
    {
      // Use Blinn's approximation.
      
      v3 H(L + V);
      normalize(H);
      
      *Io = 
        // diffuse term
        Lj.spectrum() * (Kd_ * diffuse_color) * NdotL
        
        // specular term
        + Lj.spectrum() * (Ks_ * specular_) * 
        ::pow(Rt::max(p.N * H, 0.0), roughness_);
    } 
    else 
    {
      // straightforward material.
      
      v3 R = Rt::reflect(L, p.N);
      
      *Io = 
        // diffuse term
        Lj.spectrum() * (Kd_ * diffuse_color) * NdotL
        
        // specular term
        + Lj.spectrum() * (Ks_ * specular_) * ::pow(R * V, roughness_);
    }
  }

  void material::diffuse_map(colormap* cm)
  {
    diffmap_ = cm;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

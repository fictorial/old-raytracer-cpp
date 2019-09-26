#ifndef INCLUDED_RT_RAY_H
#define INCLUDED_RT_RAY_H

//-----------------------------------------------------------------------------
// File:        ray.h
// Repository:  $Source$
// Created:     Thu Sep 11 03:07:15 2003
// Last Change: Mon Sep 22 06:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Ray has a starting position (origin) and direction.
//-----------------------------------------------------------------------------

#include "Rt/v3.h"

namespace Rt 
{
  class iprimitive;
  
  struct ray 
  {
    v3 o;                    // origin
    v3 d;                    // direction
    scalar IOR;                // index of refraction of primitive ray is "in"
    
    ray() 
      : IOR(1.0)             // by default in a vacuum.
    {}
    
    // donorm - if true will normalize/unitize dir.
    
    ray(const v3& origin, const v3& dir, bool donorm=false, scalar IOR=1.0)
      : o(origin)
      , d(dir)
      , IOR(IOR) 
    {
      if (donorm) 
        normalize(d);
    }

    // Sample a point along the ray at time t.
    
    v3 sample(scalar t) const { return o + t * d; } 
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

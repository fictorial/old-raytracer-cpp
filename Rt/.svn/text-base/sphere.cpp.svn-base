//-----------------------------------------------------------------------------
// File:        sphere.cpp
// Repository:  $Source$
// Created:     Thu Sep 11 03:26:54 2003
// Last Change: Tue Sep 30 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/sphere.h"
#include "Rt/ray.h"
#include "Rt/surfacepoint.h"
#include "Rt/material.h"
#include "Rt/uvmapping.h"
#include "Rt/spherical_mapping.h"

#include <cstdio>
#include <cmath>

namespace Rt 
{
  sphere::sphere(const v3& center, scalar radius) 
    : c_(center)
    , r_(radius)
    , r2_(radius*radius)
  {
    this->inverse_mapping(new spherical_mapping());
  }

  bool sphere::intersect(const ray& r, surfacepoint* isect) 
  {
    ++iprimitive::stats_["sphere"].tests;
    
    // Geometric method.
    
    v3 L(c_ - r.o);
    scalar D = L * r.d;
    scalar L2 = L*L;
    
    if (D < 0 && L2 > r2_) 
    {
      return false;
    }
    
    scalar M2 = L2 - D*D;
    
    if (M2 > r2_) 
    {
      return false;
    }

    // Does the ray start from inside the sphere?
    
    bool inside = length_sqr(c_ - r.o) < r2_;
    
    // Early out if query is a boolean query since we now know that the ray
    // intersects the sphere.
    //
    // This is an acceptable intersection iff the ray origin is outside the
    // sphere or if the ray is inside the sphere _and_ the sphere is at least 
    // partially transparent.
    
    if (!isect)
    {
      if (!inside || mat->Kt() > 0)
      {
        ++iprimitive::stats_["sphere"].tests_passed;
        return true;
      }

      return false;
    }
    
    scalar Q = ::sqrt(r2_ - M2);
    
    if (L2 > r2_) 
    {
      isect->t = D - Q;
    }
    else 
    {
      isect->t = D + Q;
    }

    // Incident direction, intersection point and normal at intersection point.
    // Note: for intersections with the inside surface of the sphere, the 
    // normal points back to the center of the sphere, else outwards away from
    // the center.
    
    isect->I = r.d;
    isect->P = r.o + r.d * isect->t;
    isect->N = normalized(inside ? c_ - isect->P : isect->P - c_);
    isect->mat = this->mat;
    isect->prim = this;
    
    // Calculate texture coordinates.
    
    inverse_mapping().map(isect);

    ++iprimitive::stats_["sphere"].tests_passed;
    
    return true;
  }

  bool sphere::inside(const v3& pt)
  {
    return length_sqr(pt - c_) < r2_;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

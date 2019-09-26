//-----------------------------------------------------------------------------
// File:        plane
// Repository:  $Source$
// Created:     Thu Sep 11 03:31:28 2003
// Last Change: Tue Sep 30 10:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/plane.h"
#include "Rt/config.h"
#include "Rt/ray.h"
#include "Rt/surfacepoint.h"
#include "Rt/planar_mapping.h"

#include <cmath>

namespace Rt 
{
  plane::plane(const v3& n, const scalar d) 
    : n_(n)
    , d_(d) 
  {
    this->inverse_mapping(new planar_mapping());
  }
  
  bool plane::intersect(const ray& r, surfacepoint* isect) 
  {
    ++iprimitive::stats_["plane"].tests;
    
    scalar D = n_ * r.d;
    
    if (::fabs(D) < EPS) 
    {
      return false;  
    }
    
    scalar t = -(n_ * r.o + d_) / D; 
    
    if (t < 0.0) 
    {
      return false;  
    }

    if (isect) 
    {
      isect->t = t;
      isect->I = r.d;
      isect->P = r.o + t * r.d;
      isect->prim = this;
      isect->mat = this->mat;
    
      bool two_sided = false;
      isect->N = two_sided && r.d * n_ > 0 ? -n_ : n_;
      
      inverse_mapping().map(isect);
    }

    ++iprimitive::stats_["plane"].tests_passed;

    return true;
  }

  bool plane::inside(const v3& pt)
  {
    return (n_ * pt) - d_ > 0;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

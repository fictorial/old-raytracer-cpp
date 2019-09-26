#ifndef INCLUDED_RT_SPHERE_H
#define INCLUDED_RT_SPHERE_H

//-----------------------------------------------------------------------------
// File:        sphere.h
// Repository:  $Source$
// Created:     Thu Sep 11 03:26:30 2003
// Last Change: Tue Sep 30 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A sphere.
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/iprimitive.h"

namespace Rt 
{
  class ray;
  class surfacepoint;
  
  class sphere : public iprimitive 
  {
  public:
    sphere(const v3& center, scalar radius);
    
    virtual bool intersect(const ray& r, surfacepoint* isect=0);
    virtual bool inside(const v3& pt);
    
    void c(const v3& v) { c_ = v; }
    void c(scalar x, scalar y, scalar z) { c_.x=x; c_.y=y; c_.z=z; }
    void r(scalar radius) { r_=radius; r2_ = radius*radius; }
    v3 c() const { return c_; }
    scalar r() const { return r_; }
    
  private:
    v3 c_;
    scalar r_;
    scalar r2_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

//-----------------------------------------------------------------------------
// File:        light.cpp
// Repository:  $Source$
// Created:     Thu Sep 11 10:37:48 2003
// Last Change: Wed Oct 01 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/light.h"
#include "Rt/config.h"

#include <cmath>
#include <cassert>

namespace Rt 
{
  light::light()
    : type_(light::POINT)
    , atten_(light::LINEAR)
    , spectrum_(1.0, 1.0, 1.0)
    , r_(1.0)
    , pos_()
    , dir_()
    , cutoff_(180.0)
    , dropoff_(0.0)
    , shadows_(true)
  {}
  
  light::light(const color& color, scalar radius, atten_type at)
    : type_(light::POINT)
    , atten_(at)
    , spectrum_(color)
    , r_(radius)
    , pos_()
    , dir_()
    , cutoff_(180.0)
    , dropoff_(0.0)
    , shadows_(true)
  {}
  
  void light::spectrum(const color& s) 
  {
    spectrum_ = s;
  }

  void light::radius(scalar r)
  {
    assert(r > 0);
    r_ = r;
  }

  void light::attenuation(atten_type at)
  {
    atten_ = at;
  }

  void light::castshadows(bool s)
  {
    shadows_ = s;
  }
  
  void light::make_ambient(const color& s) 
  {
    type_ = light::AMBIENT;
    spectrum_ = s;
  }
  
  void light::make_point(const v3& pos) 
  {
    type_ = light::POINT;
    pos_ = pos;
  }
  
  void light::make_directional(const v3& dir) 
  {
    type_ = light::DIRECTIONAL;
    dir_ = dir;
    normalize(dir_);
  }

  void light::make_spot(const v3& pos, const v3& target, scalar cutoff, 
    scalar dropoff)
  {
    assert(cutoff > 0);
    assert(dropoff > 0);
    
    type_ = light::SPOT;
    pos_ = pos;
    dir_ = target - pos;
    normalize(dir_);
    cutoff_ = Rt::radians(cutoff);
    dropoff_ = dropoff;
  }

  scalar light::attenuation(const v3& pt) const
  {
    switch (type_)
    {
    case light::POINT:
    case light::SPOT:
    {
      // Point lights and spotlights have the same attenuation factors.
     
      v3 L(pos_ - pt);
      scalar d2 = L*L;
      
      switch (atten_)
      {
      case light::NONE:      return 1.0;
      case light::LINEAR:    return Rt::max(0.0, (r_ - ::sqrt(d2)) / r_);
      case light::REALISTIC: return (r_ * r_) / d2;
      default:               assert(false);
      }
    }
    
    case light::DIRECTIONAL:
    case light::AMBIENT:
      // Directional lights have no attenuation; they are infinitely far away.
      // Ambient lights by definition have no attenuation since they have no
      // position in space.

      return 1.0;
    
    default:
      assert(false);
    }
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

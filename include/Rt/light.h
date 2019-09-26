#ifndef INCLUDED_RT_LIGHT_H
#define INCLUDED_RT_LIGHT_H

//-----------------------------------------------------------------------------
// File:        light.h
// Repository:  $Source$
// Created:     Thu Sep 11 10:33:41 2003
// Last Change: Wed Oct 01 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Base class for light sources. This is a point light.
//-----------------------------------------------------------------------------

#include "Rt/v3.h"
#include "Rt/color.h"
#include "Rt/config.h"

namespace Rt 
{
  class light 
  {
  public:
    enum light_type
    {
      AMBIENT,
      POINT,
      DIRECTIONAL,
      SPOT
    };

    // How light attenuates in intensity as a function of distance and 
    // sphere of influence.
    
    enum atten_type
    {
      NONE,
      LINEAR,      // (r-d) / r
      REALISTIC    // r^2 / d^2
    };
    
    light();
    light(const color& color, scalar radius = 1.0, atten_type at = LINEAR);
    
    void make_ambient(const color& color);
    void make_point(const v3& pos);
    void make_directional(const v3& dir);
    
    // cutoff - half the angle (in degrees) of spotlight cone.
    //   anything outside this cone is in shadow with respect to this light.
    // dropoff - [0,inf) controls how quickly intensity drops/falls off 
    //   from the center of spotlight. higher values create a more focused beam.
    //   a nice default may be 10.0
    
    void make_spot(const v3& pos, const v3& target, scalar cutoff, 
      scalar dropoff);
    
    void spectrum(const color& c);
    void radius(scalar r);
    void attenuation(atten_type at);
    void castshadows(bool s);
    
    // Determines attenuation factor for this light w.r.t. point PT.
    // Returns [0,1] where 0 = full attenuation 1 = no attenuation.
    
    scalar attenuation(const v3& pt) const;
    
    atten_type attenuation() { return atten_; } 
    light_type type() const { return type_; }
    color spectrum() const { return spectrum_; }
    scalar radius() const { return r_; }
    v3 position() const { return pos_; }
    v3 direction() const { return dir_; }
    scalar dropoff() const { return dropoff_; }
    scalar cutoff() const { return Rt::degrees(cutoff_); }
    bool castshadows() const { return shadows_; }
    
  protected:
    light_type type_;
    atten_type atten_;
    color spectrum_;
    scalar r_;
    v3 pos_;
    v3 dir_;
    scalar cutoff_;
    scalar dropoff_;
    bool shadows_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

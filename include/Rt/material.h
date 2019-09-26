#ifndef INCLUDED_RT_MATERIAL_H
#define INCLUDED_RT_MATERIAL_H

//-----------------------------------------------------------------------------
// File:        material.h
// Repository:  $Source$
// Created:     Thu Sep 18 16:55:03 2003
// Last Change: Sun Oct 05 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Basic material-based material with support for reflectance and transmission.
// Your typical basic raytracer material. 
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/color.h"

#include <cassert>

namespace Rt 
{ 
  class surfacepoint;
  class light;
  class v3;
  class colormap;
  
  class material 
  {
  public:
    material();

    // Kd - Diffuse component.  How diffuse the material is. [0,1]
    // diff - Diffuse reflectance color.  What color the material diffusely
    //   reflects.
    // Ks - Specular coefficient.  How specular the material is. [0,1]
    //   Controls intensity of specular highlight and also controls how
    //   specularly reflective the material is.
    // roughness - How rough the material is.  Controls spread of specular
    //   highlight.
    // spec - Color of the specular highlight.
    // Kr - Reflection coefficient. Controls how reflective the material is.
    //   [0,1]
    // Kt - Transmission coefficient.  Determines how transparent the 
    //   material is. [0,1]
    // IOR - Index of refraction of the transparent material (implies that
    //   Kt>0) w.r.t. IOR of a vacuum.  IOR of water is 1.33 for instance.
    //
    // As an example a perfect mirror has Kd=0, Ks=1, roughness=1

    material(scalar Kd, const color& diff, scalar Ks, scalar roughness, 
      const color& spec, scalar Kr, scalar Kt, scalar IOR);
    
    virtual ~material() {}
    
    // Calculate local illumination for a surface point with this material.
    // 
    // p  - surface point to illuminate
    // L  - normalized vector from P to light source position
    // Lj - light source (1 <= j <= n total sources)
    // Io - output intensity (resultant color)
    
    virtual void local_illum(const surfacepoint& p, const v3& L, 
      const light& Lj, color* Io);
    
    bool reflective() const { return Ks_ > 0.0; }
    bool transmissive() const { return Kt_ > 0.0; }
    
    void Kd(scalar f) { assert(f >= 0 && f <= 1); Kd_ = f; }
    void diffuse(const color& c) { diffuse_ = c; }
    void Ks(scalar f) { assert(f >= 0 && f <= 1); Ks_ = f; }
    void roughness(scalar f) { roughness_ = f; }
    void specular(const color& c) { specular_ = c; }
    void Kt(scalar f) { assert(f >=0 && f <= 1); Kt_ = f; }
    void Kr(scalar f) { assert(f >=0 && f <= 1); Kr_ = f; }
    void IOR(scalar f) { assert(f >= 1); IOR_ = f; }

    void diffuse_map(colormap* cm);
    void reflection_map(colormap* cm);
    void transparency_map(colormap* cm);
    void bump_map(colormap* cm);
    void specular_map(colormap* cm);
    
    scalar Kd() const { return Kd_; }
    color diffuse() const { return diffuse_; }
    scalar Ks() const { return Ks_; }
    scalar roughness() const { return roughness_; }
    color specular() const { return specular_; }
    scalar Kr() const { return Kr_; }
    scalar Kt() const { return Kt_; }
    scalar IOR() const { return IOR_; }

    const colormap* diffuse_map() const { return diffmap_; } 
    
    // Use Blinn's approximation to material.
    
    void use_blinn(bool use) { blinn_ = use; }
    bool using_blinn() const { return blinn_; }
    
  private:
    scalar Kd_;
    color diffuse_;
    scalar Ks_;
    scalar roughness_;
    color specular_;
    scalar Kr_;
    scalar Kt_;
    scalar IOR_;
    bool blinn_;
    colormap* diffmap_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

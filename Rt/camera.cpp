//-----------------------------------------------------------------------------
// File:        camera
// Repository:  $Source$
// Created:     Thu Sep 11 03:13:33 2003
// Last Change: Fri Sep 26 12:00 AM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/camera.h"
#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/ray.h"

#include <cmath>
#include <cassert>
#include <cstdio>

namespace Rt 
{
  camera::camera() 
    : VRP_(0,0,0)
    , U_(1,0,0)
    , V_(0,1,0)
    , N_(0,0,-1)
    , filmw_(32)
    , filmh_(24)
    , vpw_(400)
    , vph_(300) 
  {
    hfov(60.);
  }
  
  void camera::image_size(int w, int h) 
  {
    assert(w>0 && h>0);
  
    vpw_ = w;
    vph_ = h;
    setup();
  }
  
  void camera::lookat(const v3& eye, const v3& at, const v3& up) 
  {
    v3 real_up(up);
    
    //if (fabs(up.x) < EPS && fabs(up.z) < EPS)
    //  real_up.set(0,0,1);
    
    VRP_ = eye;
    N_ = normalized(at - eye);
    U_ = normalized(N_ ^ real_up);
    V_ = U_ ^ N_;
  }
  
  void camera::filmsize(scalar w, scalar h) 
  {
    filmw_ = w;
    filmh_ = h;
    hfov_ = 2. * ::atan((filmw_ * .5) / focal_);
    setup();
  }
  
  void camera::hfov(scalar ang) 
  {
    hfov_ = radians(ang);
    focal_ = (filmw_ * .5) / ::tan(hfov_ * .5);
    setup();
  }
  
  void camera::focallength(scalar d) 
  {
    focal_ = d;
    hfov_ = 2. * ::atan((filmw_ * .5) / focal_);
    setup();
  }
  
  ray camera::eyeray(int x, int y) const 
  {
    scalar u = x * pw_;
    scalar v = y * ph_;
    v3 p = VPO_ + U_ * u + 0.5 - V_ * v + 0.5;
  
    return ray(VRP_, normalized(p - VRP_));
  }  
  
  scalar camera::vfov() const 
  { 
    return degrees(2. * ::atan((filmw_ * .5) / focal_)); 
  }
  
  void camera::dump() 
  {
    printf("camera VRP=<%4.2f %4.2f %4.2f>\nU=<%4.2f %4.2f %4.2f>\nV=<%4.2f %4.2f %4.2f>\n", 
      VRP_.x, VRP_.y, VRP_.z, U_.x, U_.y, U_.z, V_.x, V_.y, V_.z);
    printf("N=<%4.2f %4.2f %4.2f>\nVPO=<%4.2f %4.2f %4.2f>\n",
      N_.x, N_.y, N_.z, VPO_.x, VPO_.y, VPO_.z); 
    printf("Focal=%.2fmm HFOV=%.2f deg. Image=(%.2f x %.2f) Film=(%.2f x %.2f)\n",
      focal_, hfov(), vpw_, vph_, filmw_, filmh_);
  }
  
  void camera::setup() 
  {
    pw_  = filmw_ / vpw_;
    ph_  = filmh_ / vph_;
    COP_ = VRP_ + N_ * focal_;
    VPO_ = COP_ - U_ * filmw_ * .5 + V_ * filmh_ * .5;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

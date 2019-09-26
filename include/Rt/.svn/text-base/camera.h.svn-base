#ifndef INCLUDED__H
#define INCLUDED__H

//-----------------------------------------------------------------------------
// File:        camera.h
// Repository:  $Source$
// Created:     Thu Sep 11 03:11:36 2003
// Last Change: Mon Sep 22 12:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A pinhole camera that knows how to sample the focal plane to generate
// "eyerays."  Cameras can be oriented using the familiar lookat transform.
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/ray.h"

namespace Rt 
{
  class camera 
  {
  public:
    camera(); 
    
    void image_size(int w, int h);
    void lookat(const v3& eye, const v3& at, const v3& up);
    void filmsize(scalar w, scalar h);
    void focallength(scalar d);
    ray eyeray(int x, int y) const;
    
    scalar filmaspect() const { return filmw_ / filmh_; }
    scalar focallength() const { return focal_; }
    void hfov(scalar rads);
    scalar hfov() const { return degrees(hfov_); }
    scalar vfov() const;
    v3 VRP() const { return VRP_; }
    v3 U() const { return U_; }
    v3 V() const { return V_; }
    v3 N() const { return N_; }
    void dump();
  
  protected:
    void setup();
  
  private:
    v3 VRP_, COP_, U_, V_, N_, VPO_;
    scalar filmw_, filmh_;
    scalar vpw_, vph_;
    scalar focal_;
    scalar hfov_;
    scalar pw_, ph_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

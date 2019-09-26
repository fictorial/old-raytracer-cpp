#ifndef INCLUDED_RT_PLANE_H
#define INCLUDED_RT_PLANE_H

//-----------------------------------------------------------------------------
// File:        plane.h
// Repository:  $Source$
// Created:     Thu Sep 11 03:30:57 2003
// Last Change: Mon Sep 29 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// 
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/iprimitive.h"
#include "Rt/v3.h"

namespace Rt 
{
  class ray;
  class surfacepoint;
  class v3;

  class plane : public iprimitive 
  {
  public:
    plane(const v3& n, const scalar d);
    virtual bool intersect(const ray& r, surfacepoint* isect = 0);
    virtual bool inside(const v3& pt);

  private:
    v3 n_;
    scalar d_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

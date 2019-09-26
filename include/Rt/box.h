#ifndef INCLUDED_RT_BOX_H
#define INCLUDED_RT_BOX_H

//-----------------------------------------------------------------------------
// File:        box.h
// Repository:  $Source$
// Created:     Thu Sep 11 03:26:30 2003
// Last Change: Mon Sep 29 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Axially aligned box.
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/iprimitive.h"

namespace Rt 
{
  class ray;
  class surfacepoint;
  
  class box : public iprimitive 
  {
  public:
    box(const v3& minpt, const v3& maxpt);
    
    // Create cube from center point and a length along each of XYZ axes.
    // The final width, height, and breadth of the cube will each be 'len';
    // The cube extends len/2 in each of X, Y, and Z.

    box(const v3& center, scalar len);
    
    // Create a parallelipiped from a center point and length along
    // each of XYZ axes.  The box will extend xlen/2 in X, ylen/2 in Y,
    // and zlen/2 in Z.

    box(const v3& center, scalar xlen, scalar ylen, scalar zlen);

    v3 center() const { return (min_ + max_) * 0.5; }
    
    virtual bool intersect(const ray& r, surfacepoint* isect=0);
    virtual bool inside(const v3& pt);
    
    v3 min_, max_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

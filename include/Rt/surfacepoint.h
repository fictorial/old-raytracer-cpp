#ifndef INCLUDED_RT_SURFACEPOINT_H
#define INCLUDED_RT_SURFACEPOINT_H

//-----------------------------------------------------------------------------
// File:        surfacepoint
// Repository:  $Source$
// Created:     Thu Sep 18 16:56:53 2003
// Last Change: Mon Sep 22 02:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A point on surface hit by a ray. 
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/v3.h"

#include <cassert>

namespace Rt 
{
  class material;
  class iprimitive;
  
  // Describes a point on a surface to be shaded.
  // t - "time" of intersection of I with surface that results in P.
  // I - incident direction vector (normalized)
  // P - point on surface
  // N - normal to surface at P
  // u,v - 2D texture coordinates
  // mat - material at surface point.
  // entering - if true, ray is outside primitive and intersecting given surface
  //   point from the outside in. if false, from the inside out.
  // prim - primitive the surface point belongs to
  
  class surfacepoint 
  {
  public:
    scalar t;
    v3 I, P, N;
    scalar u, v;
    material* mat;
    bool entering;
    iprimitive* prim;

    surfacepoint()
      : mat(0)
      , entering(true)
      , prim(0)
    {}
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

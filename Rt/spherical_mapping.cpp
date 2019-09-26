//-----------------------------------------------------------------------------
// File:        spherical_mapping.cpp
// Repository:  $Source$
// Created:     Fri Sep 26 20:05:38 2003
// Last Change: Tue Sep 30 08:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/spherical_mapping.h"
#include "Rt/v3.h"
#include "Rt/config.h"
#include "Rt/surfacepoint.h"

#include <cmath>
#include <cassert>
#include <cstdio>

namespace
{
  const scalar INV_PI = 1.0 / M_PI;
  const scalar INV_2PI = 1.0 / (2.0 * M_PI);
}

namespace Rt 
{
  spherical_mapping::spherical_mapping(const v3& p, const v3& e)
    : pole_(p)
    , equator_(e)
  {
    normalize(pole_);
    normalize(equator_);
    pole_cross_eq_ = cross(pole_, equator_);
  }
  
  spherical_mapping::spherical_mapping()
    : pole_(0,1,0)
    , equator_(1,0,0)
    , pole_cross_eq_(0,0,-1)
  {
  }

  void spherical_mapping::map(surfacepoint* p)
  {
    assert(p);
    
    // This method is based on Haines' method in _Intro to Raytracing_
    //
    // My derivation:
    //
    // Conversion from spherical coordinates to cartesian coordinates:
    //
    // x = sin phi cos theta
    // y = sin phi sin theta
    // z = cos phi
    //
    // with X,Y,Z as cartesian basis vectors and X out, Y right, Z up.
    //
    // From this we map our north pole to Z and equator to X but this will
    // work for any orthogonal unit vectors chosen for the north pole (Sp) and
    // the equator (Se).
    // 
    // We solve for theta to find the longitude (u) value:
    // x = sin phi cos theta
    // x / sin phi = cos theta
    // cos^-1(x / sin phi) = theta
    //
    // x is the projection of the normal onto the equator.  
    // x = N . Se (Note: Sp, Se are unit vectors).
    //
    // Thus, theta = longitude = cos^-1((N . Se) / sin phi)
    //
    // We want u in [0,1].  The range of arccosine is [0, Pi] but longitude is
    // of course in the range [0, 2 Pi] (extends all the way around the sphere)
    // (i.e. theta = [0, 2 Pi]).  
    //
    // u = theta / (2 Pi)       Normalize u to [0,1]
    //
    // Now since cos^-1(theta) = [0, Pi], the returned theta is only valid for
    // the first two quadrants.  We need a valid theta for all four quadrants.
    // Thus, we need to check to see which side of the equator the normal
    // is on.  
    //
    // If it is on the same side as the equator, the original theta is valid 
    // (think of equator as X; if N and X are not facing away from each other, 
    // N is in quadrants I or II).  
    //
    // If it is on the opposite side (faces away), N is in Q III or IV.
    // 1 - u brings it back into the correct range. (u is already normalized
    // to [0,1]).
    //
    // For the latitudinal part, v, we recall:
    // z = cos phi
    // phi = cos^-1(z)
    //
    // We don't have z directly but it is just the projection of the normal
    // onto the north pole vector:
    // 
    // z = N . Sp
    // phi = cos^-1(N . Sp)
    // 
    // We want v in the range [0,1] and phi is in the range of [0,Pi].
    // Thus, v = phi / Pi
    
    scalar phi = acos(dot(p->N, pole_));
    p->v = phi * INV_PI;

    scalar theta = acos(dot(equator_, p->N) / sin(phi)) * INV_2PI;
    p->u = dot(pole_cross_eq_, p->N) > 0 ? theta : 1 - theta;
    
    assert(p->u >= 0 && p->u <= 1.0);
    assert(p->v >= 0 && p->v <= 1.0);
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

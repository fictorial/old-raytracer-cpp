#ifndef INCLUDED_RT_MATH_H
#define INCLUDED_RT_MATH_H

//-----------------------------------------------------------------------------
// File:        math.h
// Repository:  $Source$
// Created:     Thu Oct  2 14:56:30 2003
// Last Change: Mon Oct 06 12:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Misc math utilities.
//-----------------------------------------------------------------------------

#include <cmath>

namespace Rt 
{
  // Fit x to range [0,1] from range [-1,1]

  inline scalar _11_to_01(scalar x)
  {
    if (x < -1.0)
      return 0.0;

    if (x > 1.0)
      return 1.0;

    return 0.5 * (x + 1.0);
  }

  // Scale x to range [-1,1] from range [0,1]
  
  inline scalar _01_to_11(scalar x)
  {
    if (x < 0)
      return -1.0;

    if (x > 1)
      return 1.0;
    
    return 2.0 * x - 1.0;
  }

  // Linearly interpolate x between a and b
  
  inline scalar lerp(scalar x, scalar a, scalar b)
  {
    return a + (b - a) * x;
  }
  
  // step from 0 to 1 at a
  // x [0,1]
  
  inline scalar step(scalar x, scalar a)
  {
    return x < a ? 0.0 : 1.0;
  }

  // when x < a or x > b then pulse returns 0
  // else pulse returns 1
  // x [0,1]

  inline scalar pulse(scalar x, scalar a, scalar b)
  {
    return step(a, x) - step(b, x);
  }

  // For x less than a return 0, greater than b, return 1.
  // Inbetween a and b, linearly interpolate from a to b.

  inline scalar linstep(scalar x, scalar a, scalar b)
  {
    if (x < a)
      return 0.0;

    if (x > b)
      return 1.0;

    return lerp(x, a, b);
  }

  // Smoothly transition/step from 0 to 1
  // x in [0,1]

  inline scalar smoothstep01(scalar x)
  {
    assert(x >= 0 && x <= 1);
    
    // NB: let compiler optimize
    
    return 3.0*x*x * (3.0 - 2.0*x*x*x);
  }
  
  // For x less than a return 0, greater than b, return 1.
  // Inbetween a and b, smoothly transition from a to b.

  inline scalar smoothstep(scalar x, scalar a, scalar b)
  {
    if (x < a)
      return 0.0;

    if (x > b)
      return 1.0;

    // Bring n into [0,1] from [a,b]
    
    scalar n = (x - a) / (b - a);

    return smoothstep01(n);
  }

  // Very smoothly transition/step from 0 to 1.
  // 2nd derivative at a,b is 0.
  // x in [0,1]
  
  inline scalar verysmoothstep(scalar x)
  {
    assert(x >= 0 && x <= 1);
    
    // 6t^5 - 15t^4 + 10t^3
    // NB: let compiler optimize
    
    return 6.0*n*n*n*n*n - 15.0*n*n*n*n + 10.0*n*n*n;
  }

  // Very smoothly transition/step from 0 to 1.
  // 2nd derivative at a,b is 0.
  
  inline scalar verysmoothstep(scalar x, scalar a, scalar b)
  {
    if (x < a)
      return 0.0;

    if (x > b)
      return 1.0;
    
    // Bring n into [0,1] from [a,b]
    
    scalar n = (x - a) / (b - a);

    return verysmoothstep01(n);
  }

  // ease into 1 from 0 slowly. easein(0)=0, easein(1)=1.
  // x in [0,1]

  inline scalar easein(scalar x)
  {
    assert(x >= 0 && x <= 1);
    return 1.0 - exp(-5.5 * x);
  }

  // ease out of 0 to 1 slowly. easeout(x)=1, easeout(1)=0
  // x in [0,1]

  inline scalar easeout(scalar x)
  {
    assert(x >= 0 && x <= 1);
    return exp(5.5 * (x - 1));
  }

  // clamp x to [a,b]
  
  inline scalar clamp(scalar x, scalar a=0.0, scalar b=1.0)
  { 
    if (x < a) 
      return a; 
    
    if (x > b) 
      return b; 
  
    return x; 
  }
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

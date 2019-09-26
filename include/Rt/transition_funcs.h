@INCLUDE_GUARD@

//-----------------------------------------------------------------------------
// File:        transition_funcs
// Repository:  $Source$
// Created:     Thu Oct  2 11:51:32 2003
// Last Change: Thu Oct 02 02:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// 
//-----------------------------------------------------------------------------

namespace Rt 
{

  scalar step(float a, float x)
  {
    return x < a ? 0.0 : 1.0;
  }

  scalar smoothstep(float a, float b, float x)
  {
    if (x < a)
      return 0;

    if (x > b)
      return 1;

    scalar n = (x - a) / (b - a);
    return 3.0*n*n * (3-2*n*n*n);
  }

  // much smoother than smoothstep. 2nd derivative at a,b is 0.
  // 6t^5 -15t^4 + 10t^3
  
  scalar verysmoothstep(scalar a, scalar b, scalar x)
  {
    if (x < a)
      return 0;

    if (x > b)
      return 1;
    
    scalar n = (x - a) / (b - a);
    return 6.0*n*n*n*n*n - 15.0*n*n*n*n + 10.0*n*n*n;
  }

  // ease into 1
  // x in [0,1]

  scalar easein(scalar x)
  {
    assert(x >= 0 && x <= 1);
    return 1.0 - exp(-5.5 * x);
  }

  // ease out of 1
  // x in [0,1]

  scalar easeout(scalar x)
  {
    assert(x >= 0 && x <= 1);
    return exp(5.5 * (x - 1));
  }
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

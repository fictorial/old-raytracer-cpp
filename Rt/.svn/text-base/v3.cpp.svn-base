//-----------------------------------------------------------------------------
// File:        v3.cpp
// Repository:  $Source$
// Created:     Mon Sep 22 12:35:56 2003
// Last Change: Tue Sep 23 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/v3.h"

#include <cstdio>

namespace Rt 
{
  v3 reflect(const v3& I, const v3& N) 
  { 
    return I - 2.0 * (N * I) * N; 
  }
  
  bool refract(const v3& I, const v3& N, scalar n1, scalar n2, v3* out) 
  {
    assert(out);

    // Heckbert's method.

    scalar eta = n1 / n2;
    scalar c1  = -dot(I,N);
    scalar c2  = 1 - eta*eta * (1 - c1*c1);

    if (c2 < 0)
    {
      return false;
    }

    *out = eta*I + (eta * c1 - sqrt(c2))*N;
    return true;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

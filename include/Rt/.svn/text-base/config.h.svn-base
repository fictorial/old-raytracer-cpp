#ifndef INCLUDED_RT_CONFIG_H
#define INCLUDED_RT_CONFIG_H

//-----------------------------------------------------------------------------
// File:        config.h
// Repository:  $Source$
// Created:     Thu Sep 11 02:52:46 2003
// Last Change: Mon Sep 29 12:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Global configuration.
//-----------------------------------------------------------------------------

#include <cfloat>
#include <cmath>

#ifdef SCALAR_DOUBLE
  typedef double scalar;
  const double SCALAR_MAX = DBL_MAX;
#elif SCALAR_FLOAT
  typedef float scalar;
  const float SCALAR_MAX = FLT_MAX;
#else
#warning "Using double for scalar type. Define SCALAR_DOUBLE or SCALAR_FLOAT"
  typedef double scalar;
  const double SCALAR_MAX = DBL_MAX;
#endif

namespace Rt 
{
  const int DEFAULT_MAX_DEPTH = 8;
  const scalar DEFAULT_MIN_WEIGHT = 0.01;
  
  const scalar EPS = 1e-7;

  inline scalar radians(scalar n) { return M_PI/180.*n; }
  inline scalar degrees(scalar n) { return 180./M_PI*n; }

  inline bool nearly_equal(scalar n, scalar to)
  {
    return n > to-EPS && n < to+EPS;
  }

  inline bool nearly_zero(scalar n)
  {
    return n > -EPS && n < EPS;
  }

  template<typename T> void swap(T& a, T& b) 
  {
    T tmp(a);
    a = b;
    b = tmp;
  }

  template<typename T> T min(T a, T b) 
  {
    return a < b ? a : b;
  }

  template<typename T> T max(T a, T b) 
  {
    return a > b ? a : b;
  }

  template<typename T> T sgn(T n) 
  {
    return n < T(0) ? T(-1) : T(1);
  }
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

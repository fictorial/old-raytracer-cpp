//-----------------------------------------------------------------------------
// File:        checker.cpp
// Repository:  $Source$
// Created:     Wed Oct  1 14:03:35 2003
// Last Change: Wed Oct 01 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/checker.h"
#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/color.h"
#include "Rt/surfacepoint.h"
#include "Rt/light.h"

#include <cmath>

namespace Rt 
{
  checker::checker()
    : c1_(0,0,0)
    , c2_(1,1,1)
  {}
  
  checker::checker(const color& c1, const color& c2)
    : c1_(c1)
    , c2_(c2)
  {}

  void checker::local_illum(const surfacepoint& p, const v3& L, 
    const light& Lj, color* Io)
  {
    material::local_illum(p, L, Lj, Io);
    
    scalar u = p.u - floor(p.u);
    scalar v = p.v - floor(p.v);
      
    if ((u < .5 && v < .5) || (u >= .5 && v >= .5))
    {
      *Io = c1_;
    }
    else
    {
      *Io = c2_;
    }
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

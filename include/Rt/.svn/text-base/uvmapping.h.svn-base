#ifndef INCLUDED_RT_UVMAPPING_H
#define INCLUDED_RT_UVMAPPING_H

//-----------------------------------------------------------------------------
// File:        uvmapping.h
// Repository:  $Source$
// Created:     Fri Sep 26 15:40:12 2003
// Last Change: Mon Sep 29 12:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Inverse mappings from 3-space to texture space.  This is used to generate
// texture coordinates for primitive surface points.
//-----------------------------------------------------------------------------

#include "Rt/config.h"

namespace Rt 
{
  class v3;
  class surfacepoint;

  //TODO finish me
  
  class uvmapping
  {
  public:
    // Calculate (u,v) for pt.
    
    virtual void map(surfacepoint* pt) = 0;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

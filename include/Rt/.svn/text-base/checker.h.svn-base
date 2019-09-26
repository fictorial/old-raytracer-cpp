#ifndef INCLUDED_RT_CHECKER_H
#define INCLUDED_RT_CHECKER_H

//-----------------------------------------------------------------------------
// File:        checker.h
// Repository:  $Source$
// Created:     Wed Oct  1 14:01:08 2003
// Last Change: Wed Oct 01 02:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A simple checkerboard shader/material.
//-----------------------------------------------------------------------------

#include "Rt/color.h"
#include "Rt/material.h"

namespace Rt 
{
  class surfacepoint;
  class v3;
  class light;
  class color;
  
  class checker : public material 
  {
  public:
    checker();
    checker(const color& c1, const color& c2);

    virtual void local_illum(const surfacepoint& p, const v3& L, 
      const light& Lj, color* Io);

  protected:
    color c1_, c2_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

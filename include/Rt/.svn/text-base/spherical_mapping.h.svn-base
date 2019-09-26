#ifndef INCLUDED_RT_SPHERICAL_MAPPING_H
#define INCLUDED_RT_SPHERICAL_MAPPING_H

//-----------------------------------------------------------------------------
// File:        spherical_mapping.h
// Repository:  $Source$
// Created:     Fri Sep 26 20:03:08 2003
// Last Change: Tue Sep 30 03:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// U,V mapper that uses spherical projection to map (x,y,z) -> (u,v).
//-----------------------------------------------------------------------------

#include "Rt/uvmapping.h"
#include "Rt/v3.h"

namespace Rt 
{  
  class surfacepoint;
  
  class spherical_mapping : public uvmapping
  {
  public:
    spherical_mapping();
    spherical_mapping(const v3& north_pole, const v3& equator);
    virtual void map(surfacepoint* pt);

  protected:
    v3 pole_;
    v3 equator_;
    v3 pole_cross_eq_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl


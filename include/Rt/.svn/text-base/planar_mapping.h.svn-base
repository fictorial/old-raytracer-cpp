#ifndef INCLUDED_RT_PLANAR_MAPPING_H
#define INCLUDED_RT_PLANAR_MAPPING_H

//-----------------------------------------------------------------------------
// File:        planar_mapping.h
// Repository:  $Source$
// Created:     Tue Sep 30 15:55:45 2003
// Last Change: Tue Sep 30 09:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Inverse mapping using planar projection.  (x, y, z) -> (u, v)
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/uvmapping.h"

namespace Rt 
{
  class surfacepoint;

  class planar_mapping : public uvmapping 
  {
  public:
    enum axis_type
    {
      X,                        // Map onto -ZY plane
      Y,                        // Map onto X-Z plane
      Z,                        // Map onto XY plane
      MAXIMIZE_PROJECTION       // Map onto whatever plane maximizes normal
    };

    // Maps the plane with a tiling using a 1:1 world unit to mapping unit.
    // The default plane to map onto is the XY plane (axis is Z).
    // Thus 1 unit in X will represent 1 unit in U.
    
    planar_mapping();

    // Map the plane with a tiling. 
    //
    // axis - The normal of the target mapping plane. Currently, only a set
    //   of fixed planes can be used.  Perhaps a future version will allow
    //   for arbitrary planar mappings.
    //
    //   axis  |   U   |   V
    //   ------|-------|--------
    //   X     |  -Z   |   Y
    //   Y     |   X   |  -Z
    //   Z     |   X   |   Y
    //   MAX.. |   **  |   **
    //
    //   ** For MAXIMIZE_PROJECTION axis, the axis chosen is that which will 
    //   maximize the projected normal at the given surface point.
    //
    // sizes - a 3-tuple whose elements represent the number of world units 
    //   that are mapped per unit of texture space.  In other words, this
    //   controls how the tiling repeats in each direction.
    //   e.g. if axis is X and sizes.y = 5 then the value of v at 
    //   (0,5) (-Z,Y) in world space would be v=1.  at (0,2.5), v=0.5, etc.
    
    planar_mapping(const v3& sizes, axis_type axis = MAXIMIZE_PROJECTION);
    
    virtual void map(surfacepoint* p);

  protected:
    v3 sizes_;
    axis_type axis_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

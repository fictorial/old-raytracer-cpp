//-----------------------------------------------------------------------------
// File:        planar_mapping.cpp
// Repository:  $Source$
// Created:     Tue Sep 30 16:04:34 2003
// Last Change: Tue Sep 30 09:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/planar_mapping.h"
#include "Rt/config.h"
#include "Rt/v3.h"
#include "Rt/surfacepoint.h"

namespace Rt 
{
  planar_mapping::planar_mapping()
    : sizes_(1.0, 1.0, 1.0)
    , axis_(Y)
  {}
    
  planar_mapping::planar_mapping(const v3& sizes, axis_type axis)
    : sizes_(sizes)
    , axis_(axis)
  {
    // Ensure size components are > 0.

    sizes_.x = fabs(sizes_.x);
    sizes_.y = fabs(sizes_.y);
    sizes_.z = fabs(sizes_.z);
  }
    
  void planar_mapping::map(surfacepoint* p)
  {
    axis_type axis = axis_;
    
    if (axis == MAXIMIZE_PROJECTION)
    {
      scalar& Nx = p->N.x;
      scalar& Ny = p->N.y;
      scalar& Nz = p->N.z;

      if (Nx > Ny && Nx > Nz) 
      {
        axis = X;
      }
      else if (Ny > Nx && Ny > Nz) 
      {
        axis = Y;
      }
      else 
      {
        axis = Z;
      }
    }
    
    scalar& x = p->P.x;
    scalar& y = p->P.y;
    scalar& z = p->P.z;
    
    switch (axis)
    {
    case X:
      p->u = -z / sizes_.z + 0.5;
      p->v =  y / sizes_.y + 0.5;
      break;

    case Y:
      p->u =  x / sizes_.x + 0.5;
      p->v = -z / sizes_.z + 0.5;
      break;

    case Z:
      p->u = x / sizes_.x + 0.5;
      p->v = y / sizes_.y + 0.5;
      break;

    case MAXIMIZE_PROJECTION:
    default:
      assert(false && "internal error");
    }
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

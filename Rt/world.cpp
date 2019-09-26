//-----------------------------------------------------------------------------
// File:        world.cpp
// Repository:  $Source$
// Created:     Thu Sep 11 10:43:32 2003
// Last Change: Thu Sep 25 11:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/world.h"
#include "Rt/light.h"
#include "Rt/iprimitive.h"
#include "Rt/camera.h"
#include "Rt/material.h"
#include "Rt/color.h"
#include "Rt/colors.h"

namespace Rt 
{
  world::world() 
    : iworld()
    , active_camera_(99999999)
    , amb_(colors::gray5)
    , bg_(colors::black) 
  { }
  
  world::~world() 
  {
    for (lightvec::iterator i=lights_.begin(); i != lights_.end(); ++i)
      delete *i;
    
    for (primvec::iterator i=prims_.begin(); i != prims_.end(); ++i)
      delete *i;
    
    for (cameravec::iterator i=cameras_.begin(); i != cameras_.end(); ++i)
      delete *i;
    
    for (materialvec::iterator i=materials_.begin(); i != materials_.end(); ++i)
      delete *i;
  }
  
  void world::finalize() 
  {
    if (num_cameras() == 0)
      assert(false && "no cameras defined");

    if (num_lights() == 0)
      assert(false && "no lights defined");

    if (num_primitives() == 0)
      assert(false && "no primitives defined");
    
    // Assign an active camera if one was not set but we have >= 1 cameras
    // in the world.  Just pick the first one.

    if (active_camera_ == -1)
      active_camera_ = 0;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

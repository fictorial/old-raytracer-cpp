#ifndef INCLUDED_RT_IWORLD_H
#define INCLUDED_RT_IWORLD_H

//-----------------------------------------------------------------------------
// File:        world.h
// Repository:  $Source$
// Created:     Thu Sep 11 10:39:52 2003
// Last Change: Wed Oct 01 01:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// An interface for a collection of entities that comprise a virtual world.
//-----------------------------------------------------------------------------

#include "Rt/color.h"

namespace Rt 
{
  class light;
  class iprimitive;
  class camera;
  class material;
  
  class iworld 
  {
  public:
    virtual void add_light(light* l) = 0;          
    virtual void add_primitive(iprimitive* p) = 0;
    virtual void add_camera(camera* c, bool make_default = true) = 0;
    virtual void active_camera(unsigned idx) = 0;
    virtual camera* active_camera() const = 0;
    virtual void add_material(material* m) = 0;

    // Gives the world implementation a chance to perform any 
    // optimizations for ray queries later.  After calling this,
    // no call to add_*() should be performed.
    
    virtual void finalize() {};
    
    virtual void ambient(const color& a) = 0;
    virtual void bgcolor(const color& b) = 0;

    virtual color ambient() const = 0;
    virtual color bgcolor() const = 0;
    
    // Random access.

    virtual int num_lights() const = 0;
    virtual light* get_light(int idx) = 0;

    virtual int num_primitives() const = 0;
    virtual iprimitive* get_primitive(int idx) = 0;
    
    virtual int num_cameras() const = 0;
    virtual camera* get_camera(int idx) = 0;
    
    virtual int num_materials() const = 0;
    virtual material* get_material(int idx) = 0;
  };  
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

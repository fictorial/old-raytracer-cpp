#ifndef INCLUDED_RT_WORLD_H
#define INCLUDED_RT_WORLD_H

//-----------------------------------------------------------------------------
// File:        world.h
// Repository:  $Source$
// Created:     Thu Sep 11 10:39:52 2003
// Last Change: Fri Sep 26 12:00 AM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Very simple world class. This has no spatial partitioning, etc. This 
// implementation is just a simple list of world entities (lights, cameras,
// primitives, etc).
//-----------------------------------------------------------------------------

#include "Rt/iworld.h"
#include "Rt/color.h"

#include <vector>
#include <cassert>

namespace Rt 
{
  class light;
  class iprimitive;
  class camera;
  class material;
  
  class world : public iworld 
  {
  public:
    world();
    virtual ~world();
    
    virtual void bgcolor(const color& c) { bg_ = c; }
    virtual void ambient(const color& c) { amb_ = c; }

    virtual color bgcolor() const { return bg_; }
    virtual color ambient() const { return amb_; }
    
    virtual void add_light(light* l)         
    { assert(l); lights_.push_back(l); }
    
    virtual void add_primitive(iprimitive* p) 
    { assert(p); prims_.push_back(p); }
    
    virtual void add_camera(camera* c, bool make_default = true) 
    { 
      assert(c); 
      cameras_.push_back(c);
      
      if (make_default)
        active_camera_ = cameras_.size() - 1;
    }

    virtual void active_camera(unsigned idx) 
    {
      assert(idx > 0 && idx < cameras_.size());
      active_camera_ = idx;
    }

    virtual camera* active_camera() const 
    {
      return cameras_[active_camera_];
    }
    
    virtual void add_material(material* m)   
    { assert(m); materials_.push_back(m); }
  
    virtual int num_lights() const { return lights_.size(); }
    virtual light* get_light(int idx) { return lights_[idx]; }

    virtual int num_primitives() const { return prims_.size(); }
    virtual iprimitive* get_primitive(int idx) { return prims_[idx]; }
    
    virtual int num_cameras() const { return cameras_.size(); }
    virtual camera* get_camera(int idx) { return cameras_[idx]; }
    
    virtual int num_materials() const { return materials_.size(); }
    virtual material* get_material(int idx) { return materials_[idx]; }

    virtual void finalize();
  
  private:
    typedef std::vector<light*> lightvec;
    typedef std::vector<iprimitive*> primvec;
    typedef std::vector<camera*> cameravec;
    typedef std::vector<material*> materialvec;

    lightvec    lights_;
    primvec     prims_;
    cameravec   cameras_;
    materialvec materials_;
    int         active_camera_;
    color      amb_;
    color      bg_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

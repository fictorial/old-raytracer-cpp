//-----------------------------------------------------------------------------
// File:        iprimitive.cpp
// Repository:  $Source$
// Created:     Mon Sep 29 16:56:40 2003
// Last Change: Wed Oct 01 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/iprimitive.h"
#include "Rt/config.h"
#include "Rt/ray.h"
#include "Rt/surfacepoint.h"
#include "Rt/uvmapping.h"

namespace Rt 
{
  prim_stats::prim_stats()
    : tests(0)
    , tests_passed(0)
  {}
  
  iprimitive::statmap iprimitive::stats_;
  
  iprimitive::iprimitive()
    : mapper_(0)
  {}
  
  iprimitive::~iprimitive()
  {
    delete mapper_;
  }

  scalar iprimitive::quick_intersect(const ray& r)
  {
    surfacepoint p;
    this->intersect(r, &p);
    return p.t > 0.0;
  }
    
  bool iprimitive::intersects(const ray& r) 
  { 
    return this->quick_intersect(r) > 0.0; 
  }
  
  void iprimitive::inverse_mapping(uvmapping* m)
  {
    assert(m);
    delete mapper_;
    mapper_ = m;
  }
    
  iprimitive::statmap::const_iterator iprimitive::stats_begin()
  {
    return stats_.begin();
  }
    
  iprimitive::statmap::const_iterator iprimitive::stats_end()
  {
    return stats_.end();
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

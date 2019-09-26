#ifndef INCLUDED_RT_IPRIMITIVE_H
#define INCLUDED_RT_IPRIMITIVE_H

//-----------------------------------------------------------------------------
// File:        iprimitive.h
// Repository:  $Source$
// Created:     Thu Sep 11 03:23:12 2003
// Last Change: Wed Oct 01 04:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Interface for anything in the virtual world which can be raytraced.
//-----------------------------------------------------------------------------

#include "Rt/config.h"

#include <map>

namespace Rt 
{
  class material;
  class ray;
  class surfacepoint;
  class v3;
  class uvmapping;

  // Statistics. Each iprimitive subclass should index iprimitive::stats_
  // with their class name in order to provide statistics for each type
  // of primitive.

  class prim_stats
  {
  public:
    // Number of total intersection tests.

    unsigned long tests;

    // Number of intersection tests that passed.
    
    unsigned long tests_passed;

    prim_stats();
  };

  class iprimitive 
  {
  public:
    iprimitive();
    virtual ~iprimitive();
    
    // Find closest intersection of ray with this primitive.  
    // If isect is null then this performs a boolean query which may be 
    // computationally faster than a full query.
    
    virtual bool intersect(const ray& r, surfacepoint* isect = 0) = 0;

    // Determine if r intersects primitive.  This should hopefully be 
    // optimized by subclasses.  Only the first intersection time is required.
    // Returns - time of first intersection.
    
    virtual scalar quick_intersect(const ray& r);

    // In this version, the caller does not care about surface intersection
    // information.  The caller just wants to know whether or not the ray
    // intersects the primitve.  This should hopefully be overrided by
    // subclasses to provide a more 
    
    bool intersects(const ray& r);
    
    // Determine if point is inside the primitive. 
    
    virtual bool inside(const v3& pt) = 0;

    // Use the given mapping object for inverse mappings from cartesian space
    // to texture space; (x,y,z)->(u,v)

    void inverse_mapping(uvmapping* m);
    uvmapping& inverse_mapping() { return *mapper_; }
    
    // Get all statistics for each type of primitive.
    
    typedef std::map<const char*, prim_stats> statmap;
    static statmap::const_iterator stats_begin();
    static statmap::const_iterator stats_end();
    
    // TODO public... blech
    
    material* mat;
    
  protected:
    static statmap stats_;
    uvmapping* mapper_;
  };

}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

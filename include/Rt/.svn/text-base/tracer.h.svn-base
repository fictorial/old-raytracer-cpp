#ifndef INCLUDED_RT_TRACER_H
#define INCLUDED_RT_TRACER_H

//-----------------------------------------------------------------------------
// File:        tracer.h
// Repository:  $Source$
// Created:     Thu Sep 11 10:50:24 2003
// Last Change: Tue Sep 30 03:00 AM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Raytraces a world into a color image.
//-----------------------------------------------------------------------------

#include "Rt/config.h"
#include "Rt/colormap.h"

#include <map>

namespace Rt 
{
  class iworld;
  class ray;
  class surfacepoint;
  class v3;
  class colormap;
  class color;
  
  class tracer 
  {
  public:
    // tracer will be responsible for freeing memory held by w.
    
    tracer(int iw, int ih, iworld* w);
    virtual ~tracer();
    
    void minweight(scalar w);
    void maxdepth(int d);
    
    colormap* trace();
    
    typedef std::map<const char*, scalar> statmap;
    statmap::const_iterator stats_begin();
    statmap::const_iterator stats_end();
    
  protected:
    bool closest_hit(const ray& r, surfacepoint* out);
    scalar shadow(const ray& r, const v3& p, color* outcolor);
    color shade(const ray& r, int depth=1, scalar weight=1);
    
  private:
    int iw_, ih_;
    int maxdepth_;
    scalar minweight_;
    iworld* world_;
    
  private:
    static statmap stats_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

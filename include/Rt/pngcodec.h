#ifndef INCLUDED_RT_PNGCODEC_H
#define INCLUDED_RT_PNGCODEC_H

//-----------------------------------------------------------------------------
// File:        pngcodec.h
// Repository:  $Source$
// Created:     Thu Sep 25 18:16:46 2003
// Last Change: Fri Sep 26 06:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A codec for reading and writing PNG images.
//-----------------------------------------------------------------------------

#include "Rt/iimagecodec.h"

namespace Rt 
{
  class rasterimage;
  class colormap;

  class pngcodec : public iimagecodec 
  {
  public:
    virtual colormap* read(const char* filename, 
      scalar screen_gamma = 2.2);
    
    virtual void write(const char* filename, colormap* i);
    
    virtual const char* info() const;
    
    struct pngcreator : public iimagecodec::creator
    {
    public:
      virtual iimagecodec* create()
      {
        return new pngcodec();
      }
    };
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

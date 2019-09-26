#ifndef INCLUDED_RT_IIMAGECODEC_H
#define INCLUDED_RT_IIMAGECODEC_H

//-----------------------------------------------------------------------------
// File:        iimagecodec
// Repository:  $Source$
// Created:     Thu Sep 25 18:11:14 2003
// Last Change: Fri Sep 26 06:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// An interface for codecs (COmpressor/DECompressor) of file-based images.
// Subclasses will be able to read and write image files of various file 
// formats.
//-----------------------------------------------------------------------------

#include "Rt/config.h"

#include <map>

namespace Rt 
{
  class colormap;
  
  class iimagecodec
  {
  public:
    // Read an image from a file into 'out' using this codec.
    // screen_gamma - The gamma of the screen on which this image will be
    //   possibly displayed.
    // Throws error message (char*) if anything goes wrong.
    
    virtual colormap* read(const char* filename, 
      scalar screen_gamma = 2.2) = 0;
    
    // Write a rasterimage to the file using this codec.
    // Throws error message (char*) if anything goes wrong.
    
    virtual void write(const char* filename, colormap* i) = 0;

    // Return information about the codec implementation.
    
    virtual const char* info() const { return ""; }

    struct creator 
    {
      virtual iimagecodec* create() = 0;
    };

    // Register (through inheritance) a codec creator for the given
    // extension.

    static void register_codec(const char* fileext, creator* c);

    // Lookup a handler for the extension.
    
    static iimagecodec* handler(const char* ext);
    
  private:
    typedef std::map<const char*, creator*> registry;
    static registry reg_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

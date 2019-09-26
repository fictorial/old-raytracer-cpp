#ifndef INCLUDED_RT_COLORMAP_H
#define INCLUDED_RT_COLORMAP_H

//-----------------------------------------------------------------------------
// File:        colormap.h
// Repository:  $Source$
// Created:     Thu Sep 25 20:45:02 2003
// Last Change: Tue Sep 30 12:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A colormap is a two dimensional image or texture supporting one or more
// channels.  Each color element is a single byte.
//-----------------------------------------------------------------------------

#include "Rt/color.h"

#include <cassert>

namespace Rt 
{
  class colormap 
  {
  public:
    typedef unsigned char color_type;

    enum channel
    {
      RED,
      GREEN,
      BLUE,
      ALPHA
    };
  
    // Maximal value a color_type may have.
    
    static const scalar COLOR_MAX;
    static const scalar INV_COLOR_MAX;
    
    // width, height - Dimensions of colormap.
    // channels - Number of color channels.  3 = RGB, 4 = RGBA.
    // colors - If non-null, the colors of the colormap in packed
    //   row-major order (E.g. RGBRGBRGBRGB...)
    // colormap will delete given colors on destruction. 
    
    colormap(unsigned width, unsigned height, unsigned channels = 3, 
      color_type* colors = 0);

    // Copies actual color data from other colormap.
    
    colormap(const colormap& other);
    void operator=(const colormap& other);
    
    virtual ~colormap();
    
    // Set a single pixel.
    
    void set(unsigned x, unsigned y, const color& c);
    void set(unsigned x, unsigned y, const color_type* c);
    
    // Set a row of pixels. 
    // y - which row; in range [ 0, h() )
    // c - color data. There must be rowbytes() colormap::type elements
    //   packed based on the number of channels in the colormap.  E.g.
    //   if there are 3 channels, c would resemble RGBRGBRGBRGB...
    
    void set_row(unsigned y, const color_type* c);

    // Get an individual pixel.
    
    void get(unsigned x, unsigned y, color* c) const;
    void get(unsigned x, unsigned y, color_type* c) const;

    // Get a row of pixels.
    // y - which row; in range [ 0, h() )
    // c - preallocated color data array.  size must equal rowbytes().
    
    void get_row(unsigned y, color_type* c) const;
  
    // Creates and returns a new colormap containing a single channel.  
    // ch - Which channel.  0=R 1=G 2=B 3=A
    // You are responsible for deleting the returned colormap.
    
    colormap* get_channel(colormap::channel ch) const;
  
    // Creates and returns a new colormap containing 3 channels, but
    // with only color values for the specified channel.  The other 2
    // channels are set to 0.
    // ch - Which channel.  0=R 1=G 2=B
    // You are responsible for deleting the returned colormap.
    
    colormap* get_channel_rgb(colormap::channel ch) const;

    // Creates and returns a new colormap containing 4 channels, but
    // with only color values for the specified channel.  The other 3
    // channels are set to 0.
    // ch - Which channel.  0=R 1=G 2=B 3=A
    // You are responsible for deleting the returned colormap.
    
    colormap* get_channel_rgba(colormap::channel ch) const;

    // Deletes a color channel.
    // ch - Which channel.  0=R 1=G 2=B 3=A
    
    void remove_channel(colormap::channel ch);
    
    unsigned w() const 
    {
      return w_;
    }

    unsigned h() const
    {
      return h_;
    }
    
    unsigned channels() const
    {
      return ch_;
    }
    
    unsigned rowbytes() const 
    {
      return w_ * ch_ * sizeof(colormap::color_type);
    }
    
  protected:
    unsigned index(unsigned x, unsigned y) const
    {
      return y * w_ * ch_ + x * ch_;
    }

  private:
    unsigned w_, h_, ch_;
    color_type* c_;
  };
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

//-----------------------------------------------------------------------------
// File:        colormap.cpp
// Repository:  $Source$
// Created:     Thu Sep 25 23:33:42 2003
// Last Change: Tue Sep 30 12:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/colormap.h"

#include <cassert>
#include <cstring>

namespace Rt 
{
  const scalar colormap::COLOR_MAX = 255.0;
  const scalar colormap::INV_COLOR_MAX = 1.0 / 255.0;

  colormap::colormap(unsigned width, unsigned height, unsigned channels, 
    color_type* colors)
    : w_(width)
    , h_(height)
    , ch_(channels)
    , c_(colors)
  {
    assert(w_ > 0 && h_ > 0);

    if (c_ == 0)
    {
      c_ = new color_type[w_ * h_ * ch_];
    }
  }

  colormap::colormap(const colormap& other)
    : w_(other.w_)
    , h_(other.h_)
    , ch_(other.ch_)
  {
    unsigned bytes = w_ * h_ * ch_;
    c_ = new color_type[bytes];
    memcpy(c_, other.c_, bytes);
  }

  void colormap::operator=(const colormap& other)
  {
    w_ = other.w_;
    h_ = other.h_;
    ch_ = other.ch_;
    
    unsigned bytes = w_ * h_ * ch_;
    c_ = new color_type[bytes];
    memcpy(c_, other.c_, bytes);
  }
  
  colormap::~colormap()
  {
    delete[] c_;
    c_ = 0;
  }
  
  void colormap::set(unsigned x, unsigned y, const color& c)
  {
    assert(c_);
    assert(x < w_ && y < h_);
    
    unsigned i = index(x, y); 
    
    c_[i] = color_type(c.r * COLOR_MAX);

    if (ch_ > 1) c_[i+1] = color_type(c.g * COLOR_MAX);
    if (ch_ > 2) c_[i+2] = color_type(c.b * COLOR_MAX);
    if (ch_ > 3) c_[i+3] = color_type(c.a * COLOR_MAX);
  }

  void colormap::set(unsigned x, unsigned y, const color_type* c)
  {
    assert(c_);
    assert(c);
    assert(x < w_ && y < h_);
    
    unsigned i = index(x, y); 
    
    c_[i] = *(c+0);

    if (ch_ > 1) c_[i+1] = *(c+1);
    if (ch_ > 2) c_[i+2] = *(c+2);
    if (ch_ > 3) c_[i+3] = *(c+3);
  }
  
  void colormap::set_row(unsigned y, const color_type* c)
  {
    assert(c_);
    assert(c);
    assert(y < h_);

    memcpy(&c_[index(0,y)], c, rowbytes());
  }
  
  void colormap::get(unsigned x, unsigned y, color* c) const
  {
    assert(c_);
    assert(c);
    
    unsigned i = index(x, y); 
    
    c->r = scalar(c_[i] * INV_COLOR_MAX);

    if (ch_ > 1) c->g = scalar(c_[i+1] * INV_COLOR_MAX);
    if (ch_ > 2) c->b = scalar(c_[i+2] * INV_COLOR_MAX);
    if (ch_ > 3) c->a = scalar(c_[i+3] * INV_COLOR_MAX);
  }

  void colormap::get(unsigned x, unsigned y, color_type* c) const
  {
    assert(c_);
    assert(c);
    assert(x < w_ && y < h_);
    
    unsigned i = index(x, y); 
    
    *(c+0) = c_[i+0];

    if (ch_ > 1) *(c+1) = c_[i+1];
    if (ch_ > 2) *(c+2) = c_[i+2];
    if (ch_ > 3) *(c+3) = c_[i+3];
  }

  void colormap::get_row(unsigned y, color_type* c) const
  {
    assert(c_);
    assert(c);
    assert(y < h_);

    memcpy(c, &c_[index(0,y)], rowbytes());
  }

  colormap* colormap::get_channel(colormap::channel ch) const
  {
    assert(c_);
    assert(ch >= colormap::RED && ch <= colormap::ALPHA);

    color_type* new_colors = new color_type[w_ * h_];
    color_type* op = new_colors;
    color_type* ip = c_;
    
    for (unsigned n = 0; n < w_ * h_; ++n, ip += ch_)
    {
      *op++ = ip[ch];
    }
    
    return new colormap(w_, h_, 1, new_colors);
  }

  colormap* colormap::get_channel_rgb(colormap::channel ch) const
  {
    assert(c_);
    assert(ch >= colormap::RED && ch <= colormap::BLUE);

    color_type* new_colors = new color_type[w_ * h_ * 3];
    color_type* op = new_colors;
    color_type* ip = c_;
    
    for (unsigned n = 0; n < w_ * h_; ++n, ip += ch_)
    {
      switch (ch)
      {
      case colormap::RED:
        *op++ = ip[RED];
        *op++ = 0;
        *op++ = 0;
        break;

      case colormap::GREEN:
        *op++ = 0;
        *op++ = ip[GREEN];
        *op++ = 0;
        break;

      case colormap::BLUE:
        *op++ = 0;
        *op++ = 0;
        *op++ = ip[BLUE];
        break;

      default:
        assert(false && "unknown channel");
      }
    }
    
    return new colormap(w_, h_, 3, new_colors);
  }

  colormap* colormap::get_channel_rgba(colormap::channel ch) const
  {
    assert(c_);
    assert(ch >= colormap::RED && ch <= colormap::ALPHA);

    color_type* new_colors = new color_type[w_ * h_ * 4];
    color_type* op = new_colors;
    color_type* ip = c_;
    
    for (unsigned n = 0; n < w_ * h_; ++n, ip += ch_)
    {
      switch (ch)
      {
      case colormap::RED:
        *op++ = ip[RED];
        *op++ = 0;
        *op++ = 0;
        *op++ = 255;
        break;

      case colormap::GREEN:
        *op++ = 0;
        *op++ = ip[GREEN];
        *op++ = 0;
        *op++ = 255;
        break;

      case colormap::BLUE:
        *op++ = 0;
        *op++ = 0;
        *op++ = ip[BLUE];
        *op++ = 255;
        break;

      case colormap::ALPHA:
        *op++ = 0;
        *op++ = 0;
        *op++ = 0;
        *op++ = ip[ALPHA];
        break;

      default:
        assert(false && "unknown channel");
      }
    }
    
    return new colormap(w_, h_, 4, new_colors);
  }

  void colormap::remove_channel(colormap::channel ch)
  {
    assert(c_);
    assert(ch >= colormap::RED && ch <= colormap::ALPHA);

    color_type* new_colors = new color_type[w_ * h_ * (ch_ - 1)];
    color_type* op = new_colors;
    color_type* ip = c_;
    
    for (unsigned n = 0; n < w_ * h_; ++n, ip += ch_)
    {
      if (ch != 0) *op++ = ip[0];
      if (ch != 1) *op++ = ip[1];
      if (ch != 2) *op++ = ip[2];
      if (ch != 3) *op++ = ip[3];
    } 

    color_type* old_data = c_;
    c_ = new_colors;
    delete[] old_data;
    
    --ch_;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

#ifndef INCLUDED_RT_COLOR_H
#define INCLUDED_RT_COLOR_H

//-----------------------------------------------------------------------------
// File:        color.h
// Repository:  $Source$
// Created:     Thu Sep 11 02:43:41 2003
// Last Change: Fri Sep 26 12:00 AM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// Color type.
//-----------------------------------------------------------------------------

#include "Rt/config.h"

#include <cassert>

namespace Rt 
{
  // a color color with a scalar color type.  This type of color is useful for
  // greater accuracy in many color operations than a type that uses a single
  // byte per channel (instead of a scalar).
  
  struct color
  {
    typedef scalar type;
    
    color::type r, g, b, a;
    
    color() 
      : r(0)
      , g(0)
      , b(0)
    {}
    
    color(color::type red, color::type green, color::type blue) 
      : r(red)
      , g(green)
      , b(blue) 
    {}
    
    void set(color::type red, color::type green, color::type blue) 
    { 
      r = red; 
      g = green; 
      b = blue; 
    }

    color::type operator[](unsigned i) const
    {
      switch (i)
      {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        case 3: return a;
        default:
          assert(false && "index out of bounds");
      }
    }
  };

  inline color operator+(const color& a, const color& b) 
  { return color(a.r+b.r, a.g+b.g, a.b+b.b); }
  inline color operator-(const color& a, const color& b) 
  { return color(a.r-b.r, a.g-b.g, a.b-b.b); }
  inline color operator*(const color& a, const color& b) 
  { return color(a.r*b.r, a.g*b.g, a.b*b.b); }
  
  inline color& operator+=(color& a, const color& b) 
  { a.r+=b.r; a.g+=b.g; a.b+=b.b; return a; }
  inline color& operator-=(color& a, const color& b) 
  { a.r-=b.r; a.g-=b.g; a.b-=b.b; return a; }
  inline color& operator*=(color& a, const color& b) 
  { a.r*=b.r; a.g*=b.g; a.b*=b.b; return a; }
    
  inline color operator+(const color& c, color::type s) 
  { return color(c.r+s, c.g+s, c.b+s); }
  inline color operator+(color::type s, const color& c) 
  { return color(c.r+s, c.g+s, c.b+s); }
  inline color operator-(const color& c, color::type s) 
  { return color(c.r-s, c.g-s, c.b-s); }
  inline color operator-(color::type s, const color& c) 
  { return color(c.r-s, c.g-s, c.b-s); }
  inline color operator*(const color& c, color::type s) 
  { return color(c.r*s, c.g*s, c.b*s); }
  inline color operator*(color::type s, const color& c) 
  { return color(c.r*s, c.g*s, c.b*s); }
  
  inline color& operator+=(color& c, color::type s) 
  { c.r+=s; c.g+=s; c.b+=s; return c; }
  inline color& operator-=(color& c, color::type s) 
  { c.r-=s; c.g-=s; c.b-=s; return c; }
  inline color& operator*=(color& c, color::type s) 
  { c.r*=s; c.g*=s; c.b*=s; return c; }
  
  // Scale components such that each component is in range [0,1].  This does
  // _not_ simply clamp components as doing so would change the color possibly.
  //
  // c = 2.0 1.5 0 = orange 
  // clamped, c = 1.0 1.0 0 = yellow 
  // normalized, c = 2.0/2.0 1.5/2.0 0.0/2.0 = 1.0 0.75 0.0 = orange
  
  inline color normalized(color& c) 
  {
    color::type maxcomp = Rt::max(c.r, Rt::max(c.g, c.b));
    
    if (maxcomp > 1)   
    {
      return c * (1.0 / maxcomp);
    }
    
    return c;
  }
  
  inline void normalize(color& c) 
  {
    color::type maxcomp = Rt::max(c.r, Rt::max(c.g, c.b));
    
    if (maxcomp > 1)   
    {
      c *= (1.0 / maxcomp);
    }
  }
  
  inline bool operator< (const color& a, const color& b) 
  { 
    // arbitrary... for stl container storage.

    if      (a.r < b.r) return true;
    else if (a.r > b.r) return false;
    
    if      (a.g < b.g) return true;
    else if (a.g > b.g) return false;
    
    if      (a.b < b.b) return true;
    
    return false;
  }
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

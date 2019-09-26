#ifndef INCLUDED_RT_V3_H
#define INCLUDED_RT_V3_H

//-----------------------------------------------------------------------------
// File:        v3.h
// Repository:  $Source$
// Created:     Thu Sep 11 02:55:15 2003
// Last Change: Tue Sep 30 03:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
// Overview:
// A simple 3-vector.
//-----------------------------------------------------------------------------

#include "Rt/config.h"

#include <cassert>

namespace Rt 
{
  struct v3 
  {
    scalar x,y,z;
    
    v3() 
      : x(0)
      , y(0)
      , z(0) 
    {}
    
    v3(scalar xx, scalar yy, scalar zz) 
      : x(xx)
      , y(yy)
      , z(zz) 
    {}
    
    scalar operator[](int i) const 
    { 
      if (i==0) return x; 
      if (i==1) return y;
      if (i==2) return z;
      throw "operator[]";
    }
    
    void set(scalar x, scalar y, scalar z) 
    {
      this->x = x;
      this->y = y;
      this->z = z;
    }
  };

  inline v3 operator-(const v3& v) 
  { return v3(-v.x,-v.y,-v.z); }
  
  inline v3 operator+(const v3& a, const v3& b) 
  { return v3(a.x+b.x, a.y+b.y, a.z+b.z); }
  
  inline v3 operator-(const v3& a, const v3& b) 
  { return v3(a.x-b.x, a.y-b.y, a.z-b.z); }
  
  inline v3 operator/(const v3& a, const v3& b) 
  { return v3(a.x/b.x, a.y/b.y, a.z/b.z); }
  
  inline v3& operator+=(v3& a, const v3& b) 
  { a.x+=b.x; a.y+=b.y; a.z+=b.z; return a; }
  
  inline v3& operator-=(v3& a, const v3& b) 
  { a.x-=b.x; a.y-=b.y; a.z-=b.z; return a; }
  
  inline v3& operator*=(v3& a, const v3& b) 
  { a.x*=b.x; a.y*=b.y; a.z*=b.z; return a; }
  
  inline v3& operator/=(v3& a, const v3& b) 
  { a.x/=b.x; a.y/=b.y; a.z/=b.z; return a; }
  
  inline v3 operator+(const v3& v, scalar s) { return v3(v.x+s, v.y+s, v.z+s); }
  inline v3 operator-(const v3& v, scalar s) { return v3(v.x-s, v.y-s, v.z-s); }
  inline v3 operator*(const v3& v, scalar s) { return v3(v.x*s, v.y*s, v.z*s); }
  inline v3 operator/(const v3& v, scalar s) { return v3(v.x/s, v.y/s, v.z/s); }
  
  inline v3 operator+(scalar s, const v3& v) { return v3(s+v.x, s+v.y, s+v.z); }
  inline v3 operator-(scalar s, const v3& v) { return v3(s-v.x, s-v.y, s-v.z); }
  inline v3 operator*(scalar s, const v3& v) { return v3(s*v.x, s*v.y, s*v.z); }
  inline v3 operator/(scalar s, const v3& v) { return v3(s/v.x, s/v.y, s/v.z); }
  
  inline v3& operator+=(v3& v, scalar s) { v.x+=s; v.y+=s; v.z+=s; return v; }
  inline v3& operator-=(v3& v, scalar s) { v.x-=s; v.y-=s; v.z-=s; return v; }
  inline v3& operator*=(v3& v, scalar s) { v.x*=s; v.y*=s; v.z*=s; return v; }
  inline v3& operator/=(v3& v, scalar s) { v.x/=s; v.y/=s; v.z/=s; return v; }

  inline scalar operator*(const v3& a, const v3& b)
  { return a.x*b.x+a.y*b.y+a.z*b.z; }
  
  inline v3 operator^(const v3& a, const v3& b)
  { return v3(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); }
  
  inline v3 operator%(const v3& a, const v3& b) 
  { return v3(a.x*b.x, a.y*b.y, a.z*b.z); }
  
  inline scalar dot(const v3& a, const v3& b) { return a*b; }
  inline v3 cross(const v3& a, const v3& b) { return a^b; }
  inline v3 compmul(const v3& a, const v3& b) { return a%b; }
  inline scalar length_sqr(const v3& v) { return dot(v,v); }
  inline scalar length(const v3& v) { return ::sqrt(dot(v,v)); }
  
  inline v3 normalized(const v3& v) 
  { 
    scalar len = length(v);
    if (len < EPS)
      throw "invalid vector to normalize";
    return v * (1.0 / len);
  }
  
  inline void normalize(v3& v) 
  {
    scalar len = length(v);
    if (len < EPS)
      throw "invalid vector to normalize";
    v *= (1.0 / len);
  }
  
  v3 reflect(const v3& I, const v3& N);
  bool refract(const v3& I, const v3& N, scalar n1, scalar n2, v3* out);
        
  inline bool operator<(const v3& a, const v3& b) 
  { return length_sqr(a) <  length_sqr(b); }
  
  inline bool operator<=(const v3& a, const v3& b) 
  { return length_sqr(a) <= length_sqr(b); }
  
  inline bool operator>(const v3& a, const v3& b) 
  { return length_sqr(a) >  length_sqr(b); }
  
  inline bool operator>=(const v3& a, const v3& b) 
  { return length_sqr(a) >= length_sqr(b); }
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

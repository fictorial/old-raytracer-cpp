//-----------------------------------------------------------------------------
// File:        iimagecodec.cpp
// Repository:  $Source$
// Created:     Thu Sep 25 18:22:11 2003
// Last Change: Thu Sep 25 07:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/iimagecodec.h"

#include <map>
#include <cassert>

namespace Rt 
{
  iimagecodec::registry iimagecodec::reg_;
  
  void iimagecodec::register_codec(const char* ext, creator* c)
  {
    iimagecodec::reg_[ext] = c;
  }
  
  iimagecodec* iimagecodec::handler(const char* ext)
  {
    assert(ext);

    registry::iterator it = iimagecodec::reg_.find(ext);
    
    if (it != iimagecodec::reg_.end())
    {
      return it->second->create();
    }

    return 0;
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

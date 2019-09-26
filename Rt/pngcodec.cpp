//-----------------------------------------------------------------------------
// File:        pngcodec
// Repository:  $Source$
// Created:     Thu Sep 25 17:19:48 2003
// Last Change: Tue Sep 30 05:00 PM 2003 E
// Checked-In:  $Date$
// Author:      bhammond
// Maintainer:  $Author$
// Revision:    $Revision$
//-----------------------------------------------------------------------------

#include "Rt/pngcodec.h"
#include "Rt/iimagecodec.h"
#include "Rt/colormap.h"

#include <cassert>
#include <cstdio>

#include <png.h>

#if (PNG_LIBPNG_VER < 10201)
  #define png_voidp_NULL (png_voidp)NULL
  #define png_error_ptr_NULL (png_error_ptr)NULL
#endif

namespace Rt
{
  const char* pngcodec::info() const
  {
    static char buf[128];
    printf(buf, "PNG Codec. Compiled with libpng %s zlib %s; Using "
      "libpng %s zlib %s", PNG_LIBPNG_VER_STRING, ZLIB_VERSION,
      png_libpng_ver, zlib_version);
    return buf;
  }
  
  colormap* pngcodec::read(const char* filename, scalar screen_gamma)
  {
    assert(filename);

    FILE* fp = fopen(filename, "rb");
  
    if (!fp)
      throw "cannot open file";

    unsigned char* sigbuf = new unsigned char[8];
    
    if (fread(sigbuf, 1, 8, fp) != 8)
    {
      delete[] sigbuf;
      throw "failed to read signature";
    }

    if (!png_check_sig(sigbuf, 8))
    {
      delete[] sigbuf;
      throw "not a PNG";
    }

    delete[] sigbuf;
    
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0,0,0);
  
    if (!png_ptr)
      throw "failed to alloc PNG ptr";
      
    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    if (!info_ptr)
    {
      png_destroy_read_struct(&png_ptr, 0, 0);
      throw "failed to alloc PNG info ptr";
    } 

    png_infop end_info = png_create_info_struct(png_ptr);
  
    if (!end_info)
    {
      png_destroy_read_struct(&png_ptr, 0, 0);
      throw "failed to alloc PNG end ptr";
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    // read header image info

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type,
      compression_type, filter_method;
      
    png_get_IHDR(png_ptr, info_ptr, &width, &height,
       &bit_depth, &color_type, &interlace_type,
       &compression_type, &filter_method);

#ifndef NDEBUG
    printf("PNG image: %s bit_depth:%u w:%u h:%u\n",
      filename, unsigned(bit_depth), unsigned(width), unsigned(height));
#endif
    
    // expand palettes to RGB
    
    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
      png_set_palette_to_rgb(png_ptr);
    }
    
    // add alpha channel if transparency found
    
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) 
    {
      png_set_tRNS_to_alpha(png_ptr);
    }

    // expand grayscale to RGB for simplicity
    
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
      png_set_gray_to_rgb(png_ptr);
    }

    // strip 16 bit files to 8 bit

    if (bit_depth == 16)
    {
      png_set_strip_16(png_ptr);
    }
    
    // unpack multiple pixels per byte to one pixel / byte.
    
    if (bit_depth < 8)
    {
      png_set_packing(png_ptr);
    }

    // transform using given screen gamma relative to gamma of file.
   
    double gamma;
    
    if (png_get_gAMA(png_ptr, info_ptr, &gamma))
    {
      png_set_gamma(png_ptr, screen_gamma, gamma);
    }
    else
    {
      // no gamma in file -- choose a default. note that this is
      // inverted. the given is a recommended default for PCs.

      png_set_gamma(png_ptr, screen_gamma, 1.0 / 2.2);
    }
    
    int channels = static_cast<int>(png_get_channels(png_ptr, info_ptr));
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    colormap::color_type* rowpix = new colormap::color_type[rowbytes];
    colormap* cm = new colormap(width, height, channels);
    
    for (unsigned y = 0; y < height; ++y)
    {
      png_read_rows(png_ptr, &rowpix, 0, 1);
      cm->set_row(y, rowpix);
    }

    delete[] rowpix;
    
    png_destroy_info_struct(png_ptr, &info_ptr);
    png_destroy_info_struct(png_ptr, &end_info);
    png_destroy_read_struct(&png_ptr, 0, 0);

#ifndef NDEBUG
    puts("image loaded...");
#endif

    fclose(fp);
    return cm;
  }
  
  void pngcodec::write(const char* filename, colormap* i) 
  {
    assert(filename);
    assert(i);

    png_structp png_ptr = png_create_write_struct(
      PNG_LIBPNG_VER_STRING, png_voidp_NULL,  
      png_error_ptr_NULL, png_error_ptr_NULL);

    if (!png_ptr)
    {
      throw "failed to create png write struct";
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    
    if (!info_ptr) 
    {
      png_destroy_write_struct(&png_ptr, png_infopp(0));
      throw "failed to create png info struct";
    }
    
    if (setjmp(png_jmpbuf(png_ptr))) 
    {
      png_destroy_write_struct(&png_ptr, &info_ptr);
      throw "failed to setjmp";
    }
    
    FILE* f = fopen(filename, "wb");
    
    if (!f) 
    {
      throw "cannot open png output file";
    }
    
    int type = 0;

    switch (i->channels())
    {
    case 1: type = PNG_COLOR_TYPE_GRAY;       break;
    case 2: type = PNG_COLOR_TYPE_GRAY_ALPHA; break;
    case 3: type = PNG_COLOR_TYPE_RGB;        break;
    case 4: type = PNG_COLOR_TYPE_RGBA;       break;
    default:
      assert(false && "unsupported # of colormap channels");
      break;
    }
    
    png_init_io(png_ptr, f);
    png_set_IHDR(png_ptr, info_ptr, i->w(), i->h(), 8, 
      type, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, 
      PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    png_byte* row = new png_byte[i->w() * i->channels()];
    
    for (unsigned y = 0; y < i->h(); ++y)
    {
      i->get_row(y, row); 
      png_write_row(png_ptr, row);
    }

    delete[] row;
      
    png_write_flush(png_ptr);
    
    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    
    fclose(f);
  }
}

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

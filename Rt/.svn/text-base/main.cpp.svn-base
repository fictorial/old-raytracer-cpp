// Rt - a RayTracer.
// Brian Hammond <RtDev@brianhammond.com>
// 
// This file is to be used to create a simple test app.
// The scalar target of Rt is a Python extension module.
// 
// Define STANDALONE to create a standalone executable that
// renders a 400x300 test image to ./output.png.
// 
// Adapted from an initial version written in Python
// that was just too slow (even though it was fun to write!).
// 
// Requirements:
//  - A C++ compiler (tested with GCC 3.1)
//  - zlib
//  - libpng

#ifndef STANDALONE
  #error Do not build this file unless you want an executable.
#endif

#include "Rt/config.h"
#include "Rt/tracer.h"
#include "Rt/colormap.h"
#include "Rt/iimagecodec.h"
#include "Rt/iprimitive.h"
#include "Rt/planar_mapping.h"

// for creating test worlds

#include "Rt/v3.h"
#include "Rt/iworld.h"
#include "Rt/world.h"         // for now...
#include "Rt/colors.h"
#include "Rt/material.h"
#include "Rt/checker.h"
#include "Rt/camera.h"
#include "Rt/light.h"
#include "Rt/sphere.h"
#include "Rt/plane.h"
#include "Rt/box.h"

#include "Rt/surfacepoint.h" //for now
#include "Rt/pngcodec.h"     //for now

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdio>

#include <vector>

using namespace Rt;

namespace 
{
  // TODO should this be moved somewhere else maybe?

  void register_handlers()
  {
    static pngcodec::pngcreator png;
    iimagecodec::register_codec("png", &png);
  }
  
  // load a texture colormap

  std::vector<colormap*> maps_loaded;
  
  colormap* load_texture(const char* filename)
  {
    assert(strstr(filename, ".png") && "only support PNGs");
    
    iimagecodec* ic = iimagecodec::handler("png");
    assert(ic && "no PNG codec?");

    colormap* cm = 0;
    
    try
    {
#ifndef NDEBUG
      printf("%s", ic->info());
#endif
      cm = ic->read(filename);
    }
    catch (const char* err)
    {
      fprintf(stderr, "failed to read PNG file: %s\n", err);
      delete ic;
      throw;
    }
    catch (...)
    {
      fprintf(stderr, "caught unknown error while trying to write PNG\n");
      delete ic;
      throw;
    }
    
    delete ic;
    
    maps_loaded.push_back(cm);  //TODO total hack
    
    return cm;
  }

  void unload_maps()
  {
    puts("unloading maps...");

    for (std::vector<colormap*>::iterator it = maps_loaded.begin();
         it != maps_loaded.end(); ++it)
    {
      delete *it;
    }
  }

  const v3 ORIGIN(0,0,0);
  const v3 XAXIS(1,0,0);
  const v3 YAXIS(0,1,0); 
  const v3 ZAXIS(0,0,1);     
  const v3 UP(0,1,0);
  const v3 FORWARD(0,0,-1); 
  const v3 RIGHT(1,0,0);     

  iworld* make_test_world(int iw, int ih) 
  {
    iworld* w = new world();
    w->ambient(colors::gray2);
    w->bgcolor(colors::steelblue3);

    // A checkerboard material.
    
    material* checker1 = new checker(colors::green, colors::yellow);
    checker1->Kd(0.5);
    checker1->diffuse(colors::white);
    checker1->Ks(0.3);
    checker1->roughness(16);
    checker1->specular(colors::orange);
    checker1->Kr(0.2);
    w->add_material(checker1);
    
    // material with a diffuse texture map of the earth.
    
    material* earth_mat = new material();
    earth_mat->Kd(1.0);
    earth_mat->diffuse(colors::white);
    earth_mat->Ks(0.09);
    earth_mat->specular(colors::white);
    earth_mat->roughness(4);
    earth_mat->Kr(0.0);
    earth_mat->Kt(0.0);
    earth_mat->IOR(1.0);
    earth_mat->diffuse_map(load_texture("../res/earth/day.png"));
    w->add_material(earth_mat);
    
    // material that reflects like a mirror.
    
    material* mirrormat = new material();
    mirrormat->Kd(0.0);
    mirrormat->diffuse(colors::white);
    mirrormat->Ks(1.0);
    mirrormat->specular(colors::white);
    mirrormat->roughness(256);
    mirrormat->Kr(1.0);
    w->add_material(mirrormat);
    
    // a material that is completely transparent with a slight index of
    // refraction.
    
    material* transparent_mat = new material();
    transparent_mat->Kd(0.0);
    transparent_mat->diffuse(colors::white);
    transparent_mat->Ks(0.0);
    transparent_mat->roughness(256);
    transparent_mat->specular(colors::white);
    transparent_mat->Kr(0.0);
    transparent_mat->Kt(0.80);
    transparent_mat->IOR(1.07);
    w->add_material(transparent_mat);
    
    // a plane that simulates a simple "ground"
    
    plane* ground = new plane(YAXIS,0);
    ground->mat = checker1;
    ground->inverse_mapping(new planar_mapping(v3(50,0,50)));
    w->add_primitive(ground);
    
    // a sphere with the earth material
    
    sphere* earth_sphere = new sphere(v3(0,25,0), 25);
    earth_sphere->mat = earth_mat;
    w->add_primitive(earth_sphere);

    // a sphere with the mirror material
    
    sphere* mirror_sphere = new sphere(v3(-33,20,-28), 15);
    mirror_sphere->mat = mirrormat; 
    w->add_primitive(mirror_sphere);

    // a small box with the transparent material.

    box* b = new box(v3(10,20,-30), 10);
    b->mat = transparent_mat;
    w->add_primitive(b);
    
    /* TODO causes a SEGV ... wtf? 
    sphere* s7 = new sphere(b->center()+v3(0,25,0),5);
    s7->mat = mirrormat; 
    w->add_primitive(s7);
    */

    // a camera
    
    camera* cam = new camera();
    cam->lookat(v3(0,120,-140), earth_sphere->c(), v3(0,1,0));
    cam->hfov(60);
    w->add_camera(cam);
   
    // a spotlight
    light* l2 = new light(colors::white);  
    l2->make_spot(v3(-100,130,-50), earth_sphere->c(), 60.0, 2.0);
    l2->radius(50);
    l2->attenuation(light::NONE);
    w->add_light(l2);

    // a distant red point light that's above the ground by a bit.
    
    light* pl0 = new light(colors::red);
    pl0->make_spot(v3(80,20,100), v3(80,0,100), 45.0, 5.0);
    pl0->radius(60);
    pl0->attenuation(light::REALISTIC);
    w->add_light(pl0);
    
    return w;
  }
}

#ifdef STANDALONE

int main(int argc, char** argv) 
{
  int iw = 400, ih = 300;
  
  if (argc >= 3)
  {
    iw = atoi(argv[1]);
    ih = atoi(argv[2]);
    assert(iw > 0 && ih > 0);
  }

  srand(time(0));
  atexit(unload_maps);  //TODO hack
  
  register_handlers();  //TODO hack
  
  iworld* w = make_test_world(iw, ih);
  assert(w);

  puts("world created.. finalizing..");
  
  w->finalize();
  
  puts("ready.");
  
  tracer tr(iw, ih, w);
  colormap* output_cmap = tr.trace();
  assert(output_cmap);
  
  iimagecodec* ic = iimagecodec::handler("png");
  assert(ic && "no PNG codec?");

  //TODO option
  bool output_channel_images = false;

  colormap* output_r = 0;
  colormap* output_g = 0;
  colormap* output_b = 0;

  if (output_channel_images)
  {
    output_r = output_cmap->get_channel_rgb(colormap::RED);
    output_g = output_cmap->get_channel_rgb(colormap::GREEN);
    output_b = output_cmap->get_channel_rgb(colormap::BLUE);
  }

  puts("output images ready for writing...");
  
  try
  {
    ic->write("output.png", output_cmap);  puts("wrote output.png...");

    if (output_channel_images)
    {
      ic->write("output-r.png", output_r);   puts("wrote output-r.png...");
      ic->write("output-g.png", output_g);   puts("wrote output-g.png...");
      ic->write("output-b.png", output_b);   puts("wrote output-b.png...");
    }
  }
  catch (const char* err)
  {
    fprintf(stderr, "failed to save PNG file: %s\n", err);
  }
  catch (...)
  {
    fprintf(stderr, "caught unknown error while trying to write PNG\n");
  }
  
  delete ic;
  delete output_cmap;
  delete output_r;
  delete output_g;
  delete output_b;

  // dump stats
 
  printf("\n"
    "--------------------------------------------------------------------------\n"
    "World Statistics\n"
    "--------------------------------------------------------------------------\n");
  
  printf("%-40s: %10d\n", "Lights", w->num_lights());
  printf("%-40s: %10d\n", "Cameras", w->num_cameras());
  printf("%-40s: %10d\n", "Materials", w->num_materials());
  printf("%-40s: %10d\n", "Primitives", w->num_primitives());
  
  printf("\n"
    "--------------------------------------------------------------------------\n"
    "Raytracer Statistics\n"
    "--------------------------------------------------------------------------\n");
  
  for (tracer::statmap::const_iterator it = tr.stats_begin();
       it != tr.stats_end(); ++it)
  {
    const char* key = (*it).first;
    const scalar value = (*it).second;
  
    printf("%-40s: %10.2f\n", key, value);
  }

  printf("\n"
    "--------------------------------------------------------------------------\n"
    "Intersection Tests (Passed / Tested)\n"
    "--------------------------------------------------------------------------\n");
  
  for (iprimitive::statmap::const_iterator it = 
       iprimitive::stats_begin();
       it != iprimitive::stats_end(); ++it)
  {
    const char* key = (*it).first;
    const prim_stats& s = (*it).second;
    printf("%-40s: %6lu / %6lu (%4.2f%%)\n",
      key, s.tests_passed, s.tests, (s.tests_passed / scalar(s.tests)) * 100.0);
  }
  
  return 0;
}

#endif

// vim:ft=cpp:sw=2:sts=2:ts=8:et:norl

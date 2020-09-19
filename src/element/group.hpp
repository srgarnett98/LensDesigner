#pragma once

#include <vector>

#include "coord/vector.hpp"
#include "coord/simobj.hpp"
#include "element/surface.hpp"
#include "light/ray.hpp"


namespace element{
  //dont like the name group, will rename
  class Group: public coord::SimObj{
    public:
      std::vector<element::Surface *> surfaces;

      void set_surfaces(std::vector<element::Surface *> surfaces_);

      void append_surface(element::Surface *surface);

      void insert_surface(element::Surface *surface, int index);

      element::Surface * pop_surface(int index);

      void append_Group(element::Group group);

      void insert_Group(element::Group group, int index);

      element::Group pop_Group(std::vector<int> index_list);

      std::vector<light::ray> transfer_single_ray(light::Ray ray);

      std::vector<std::vector<light::Ray>> transfer_packet(std::vector<light::Ray> init_rays);

      //Would love a function where I can transfer light packet
      //but only for the last few surfaces
      //so if a later surface is changed, you dont need to simualte them all.
  };

  //lens not a separate class, instead a utility to make a group class?
  element::Group make_lens(coord::vector centre,
                           float angle,
                           element::Surface *side1,
                           element::Surface *side2,
                           float thickness,
                           float (*n2)(float wavelength),
                           float (*n1)(float wavelength) = material::air,
                           float (*n3)(float wavelength) = material::air,
                           float element_height = 1.0,
                           int N_sections = 1,
                           float angle_side1 = 0.0,
                           float angle_side2 = 0.0)
}

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
      std::vector<*element::Surface> elements;

      void set_elements(std::vector<*element::Surface> elements_);

      void append_element(*element::Surface surface);

      void insert_element(*element::Surface surface, int index);

      element::Surface pop_element(int index);

      void append_Group(element::Group group);

      void insert_Group(element::Group group, int index);

      element::Group pop_Group(std::vector<int> index_list);

      std::vector<light::ray> transfer_single_ray(light::Ray ray);

      std::vector<std::vector<light::Ray>> transfer_packet(std::vector<light::Ray> init_rays);
  };

  //lens not a separate class, instead a utility to make a group class?
  class Lens: public element::Group{
    public:
      void set_values(element::LensSurface surface_0,
                      element::LensSurface surface_1);

      void make_lens(curve::Geometry geometry_0,
                     curve::Geometry geometry_1,
                     float (*n1_)(float wavelength),
                     float (*n2_)(float wavelength),
                     float (*n3_)(float wavelength));
  }
}

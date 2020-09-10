#pragma once

#include <vector>

#include "coord/vector.hpp"
#include "coord/simobj.hpp"
#include "element/surface.hpp"
#include "light/ray.hpp"


namespace element{
  class Combination: public coord::SimObj{
    public:
      std::vector<*element::Surface> elements;

      std::vector<light::ray> transfer_light_packet(std::vector<light::ray>);
  }

  class Lens: public element::Combination{
    public:
      void set_values(element::LensSurface surface_0,
                      element::LensSurface surface_1)

      void make_lens(curve::Geometry geometry_0,
                     curve::Geometry geometry_1,
                     float (*n1_)(float wavelength),
                     float (*n2_)(float wavelength),
                     float (*n3_)(float wavelength))
  }
}

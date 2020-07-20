#pragma once

#include "coord/vector.hpp"
#include "element/surface.hpp"

namespace element{
  class Aperture: public element::Surface{
    public:
      float aperture_size;

      void set_values(coord::vector centre_, float angle_,
                      float element_height_ = NAN,
                      float aperture_size_ = 1.0);

      light::Ray transfer_func(light::Ray ray_);

      float solve_for_x(float y);
  };
};

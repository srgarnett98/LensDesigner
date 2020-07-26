#pragma once

#include "coord/vector.hpp"
#include "coord/simobj.hpp"
#include "light/ray.hpp"
#include "behaviour/transfer_funcs.hpp"

namespace element{
  class Surface: public coord::SimObj{
    public:
      float element_height;

      curve::Geometry *shape;

      void set_values(coord::vector centre_,
                      float angle_ = 0.0,
                      float element_height_ = NAN);

      void set_geometry(curve::Geometry *shape);

      float sag_func(float y_coord);

      float tangent_angle(float y_coord);

      virtual light::Ray transfer_func(light::Ray ray);
  };

  class LensSurface: public element::Surface {
    public:
      float (*n1)(float wavelength);
      float (*n2)(float wavelength);

      void set_values(coord::vector centre_,
                      float (*n1_)(float wavelength),
                      float (*n2_)(float wavelength),
                      float angle_ = 0.0,
                      float element_height_ = NAN)

      light::Ray transfer_func(light::Ray ray) override;
  };
};

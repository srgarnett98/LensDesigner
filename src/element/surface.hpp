#pragma once

#include "coord/vector.hpp"
#include "coord/simobj.hpp"
#include "light/ray.hpp"
#include "curve/geometry.hpp"
#include "curve/curves.hpp"
#include "behaviour/transfer_funcs.hpp"

namespace element{
  class Surface: public coord::SimObj{
    public:
      float element_height;

      unsigned N_sections;

      std::vector<coord::vector> pos_list;

      curve::Geometry *geometry;

      void set_values(coord::vector centre_,
                      float angle_ = 0.0,
                      float element_height_ = NAN);

      void set_geometry(curve::Geometry *shape);

      void generate_pos_list();

      float sag_func(float y_coord);

      float tangent_angle(float y_coord);

      light::Ray global_to_local_ray(light::Ray ray);

      light::Ray local_to_global_ray(light::Ray ray);

      virtual light::Ray transfer_func(light::Ray ray);
  };

  class LensSurface: public element::Surface {
    public:
      float (*n1)(float wavelength);
      float (*n2)(float wavelength);

      void set_values(coord::vector centre_,
                      float (*n1_)(float wavelength),
                      float (*n2_)(float wavelength),
                      curve::Geometry geometry_ = curve::flat(),
                      float angle_ = 0.0,
                      float element_height_ = NAN);

      light::Ray transfer_func(light::Ray ray) override;
  };

  class Mirror: public element::Surface {
  public:

    void set_values(coord::vector centre_,
                    curve::Geometry geometry_ = curve::flat(),
                    float angle_ = 0.0,
                    float element_height_ = NAN);

    light::Ray transfer_func(light::Ray ray) override;
  }
};

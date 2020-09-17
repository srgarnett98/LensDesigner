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

      //not used on the surface level, but need to be initialized for lenssurface
      float (*n1)(float wavelength);
      float (*n2)(float wavelength);

      //needed for aperture
      float aperture_size;

      void set_values(coord::vector centre_,
                      curve::Geometry geometry = curve::flat(),
                      float angle_ = 0.0,
                      float element_height_ = 1.0,
                      unsigned int N_sections_ = 1);

      void set_geometry(curve::Geometry *shape);

      void set_materials(float (*n1_)(float wavelength),
                         float (*n2_)(float wavelength));

      void set_aperture_size(float aperture_size_);

      void generate_pos_list();

      light::Ray global_to_local_ray(light::Ray ray);

      light::Ray local_to_global_ray(light::Ray ray);

      virtual light::Ray transfer_func(light::Ray ray);
  };

  class LensSurface: public element::Surface {
    public:
      //dont need to redefine attrs?
      float (*n1)(float wavelength);
      float (*n2)(float wavelength);

      light::Ray transfer_func(light::Ray ray) override;
  };

  class Mirror: public element::Surface {
  public:

    light::Ray transfer_func(light::Ray ray) override;
  };

  class Aperture: public element::Surface{
    public:
      //dont need to redefine attrs?
      float aperture_size;

      light::Ray transfer_func(light::Ray ray_);
  };
};

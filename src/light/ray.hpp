#pragma once

#include <cmath>

#include "coord/simobj.hpp"
#include "coord/vector.hpp"

namespace light{
  class Ray: public coord::SimObj{

    public:
      float wavelength;
      coord::vector max_coords;
      bool exists;
      float tan_angle;

      void set_values(coord::vector centre_, float angle_,
                      float wavelength = 0.76,
                      bool exists = true);

      void set_max_coords_from_y(float y_coord_);

    	void set_max_coords_from_x(float x_coord_);

    	float get_wavelength();

    	coord::vector get_max_coords();

    	float solve_for_x(float y_coord_);

    	float solve_for_y(float x_coord_);
  };
};

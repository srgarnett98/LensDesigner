#pragma once

#include <cmath>
#include <vector>

#include "coord/vector.hpp"

namespace curve{

  class Geometry{
    public:

      std::vector<coord::vector> interp_points;

      virtual float solve_for_x(float y_coord);

      virtual float normal_angle(float y_coord);

      virtual
  };
};

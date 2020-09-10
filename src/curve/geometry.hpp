#pragma once

#include <cmath>
#include <vector>

#include "coord/vector.hpp"

namespace curve{

  class Geometry{
    public:

      virtual float solve_for_x(float y_coord);

      virtual float normal_angle(float y_coord);
  };
};

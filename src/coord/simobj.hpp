#pragma once

#include "coord/vector.hpp"

namespace coord{
  class SimObj {
    public:
      coord::vector centre;
      float angle;

      void set_values(coord::vector centre_,
                      float angle_);

      coord::vector get_centre();

      float get_angle();

      coord::vector global_to_local_coords(coord::vector coord);

      coord::vector local_to_global_coords(coord::vector coord);
  };
};

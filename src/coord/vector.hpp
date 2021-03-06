#pragma once

#include <cmath>

namespace coord{
  class vector{
    public:
      float x;
      float y;

      void set_values(float x_, float y_);

      coord::vector operator + (coord::vector param);

      coord::vector operator - (coord::vector param);

      coord::vector rotate(float angle);
  };
};

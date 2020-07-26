#pragma once

#include <cmath>
#include <vector>

#include "coord/vector.hpp"
#include "curve/geometry.hpp"

namespace curve{
  class hyperbolic_curve: public curve::Geometry {
    public:
      float r;
      float k;
      std::vector<float> poly_terms;

      void set_values(float r_,
                      float k_ = 0.0,
                      std::vector<float> poly_terms = {0.0});

      float get_r();

      float get_k();

      std::vector<float> get_poly_terms();

      float solve_for_x(float y) override;

      float normal_angle(float y) override;
  };
};

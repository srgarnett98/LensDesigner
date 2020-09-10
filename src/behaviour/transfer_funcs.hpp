#pragma once

#include <cmath>

#include "coord/vector.hpp"
#include "element/surface.hpp"
#include "light/ray.hpp"

namespace behaviour{
  float calc_refract_angle(float n1, float n2, float theta1);

  float calc_reflect_angle(float theta1);

  light::Ray transfer_to_surface(light::Ray ray,
                                 element::Surface surface,
                                 float epsilon);
};

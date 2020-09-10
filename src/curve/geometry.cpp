#include "curve/geometry.hpp"

virtual float curve::Geometry::normal_angle(float y_coord_, float diff_step = 0.000001){
  //TO BE REDONE WITH ANALYTIC SOLUTIONS IN HYPERBOLIC SURFACE DEF
  float diff_x = (solve_for_x(y_coord_ + diff_step) -
                  solve_for_x(y_coord_ - diff_step)) / (2*diff_step);
  float tangent = atan(diff_x);
  return tangent;
}

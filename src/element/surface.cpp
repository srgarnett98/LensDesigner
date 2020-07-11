#include "element/surface.hpp"
/*
Base class for all Surfaces in the simulation. Lens surfaces, flat surface, aperture etc

  Parameters
  ----------

      centre = [0.0, 0.0]: [float, float]
          Coordinates of the centre of the aperture

      angle = 0.0: float in radians
          Angle of the aperture to the vertical

      element_height: default np.inf
          A height of a lens or aperture etc.
          Past this height the behaviour may be undefined

  Methods
  ----------

      tangent_angle:  float
          Calculates the tangent to the Surface at a specified height
*/

void elements::Surface::set_values(coord::vector centre_,
                                   float angle_ = 0.0,
                                   float element_height_ = NAN){
  centre = centre_;
  angle = angle_;
  element_height = element_height_;
}

light::Ray elements::Surface::transfer_func(light::Ray ray_){
  throw std::logic_error("Surface requires valid transfer function");
}

float elements::Surface::solve_for_x(float y_coord_){
  throw std::logic_error("Surface requires valid sag function");
}

float elements::Surface::tangent_angle(float y_coord_){
  //TO BE REDONE WITH ANALYTIC SOLUTIONS IN HYPERBOLIC SURFACE DEF
  float diff_x = (solve_for_x(y_coord_ + 0.000001) -
                  solve_for_x(y_coord_ - 0.000001)) / 0.000002;
  float tangent = atan(diff_x);
  tangent += angle;
  return tangent;
}
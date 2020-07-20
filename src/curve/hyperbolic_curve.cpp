#include "curve/hyperbolic_curve.hpp"
/*

  A class with the attributes of a hyperbolic curve.
  Contains a method to return the solution to that hyperbolic curve.

  Attributes
  ---------
    r- float
      radius of curvature at x=0

    k- float
      conic constant. k=-1 is a parabola, k=0 is a circle

    poly_terms = std::vector

*/
void curve::hyperbolic_curve::set_values(float r_,
                float k_,
                std::vector<float> poly_terms_){
  r = r_;
  k = k_;
  poly_terms = poly_terms_;
}

float curve::hyperbolic_curve::get_r(){
  return r;
}

float curve::hyperbolic_curve::get_k(){
  return k;
}

std::vector<float> curve::hyperbolic_curve::get_poly_terms(){
  return poly_terms;
}

float curve::hyperbolic_curve::solve_for_x(float y) {
  //calculates the x coordinate of a conic section at y

  float poly_correction = 0.0;
  for(int i=0;
      i< poly_terms.end()-poly_terms.begin();
      i++) {
    //Adds even powered terms (2, 4, 6... aka 2(i+1) i=0,1,2...)
    poly_correction += poly_terms[i] * pow(y,2*(i+1));
  }
  float x_coord;
  x_coord = pow(y, 2) / (r*(1 + std::sqrt(1-(1+k)*pow(y, 2)/pow(r, 2))));
  x_coord += poly_correction;

  return x_coord;
}

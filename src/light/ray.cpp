#include "light/ray.hpp"

/*
  Ray creates a ray object defined by a origin and angle.With this you can get an x
  coordinate for a given y, or vice versa, as well as set when the line terminates, and creating
  arrays representing the line for plotting purposes.

Params:
------
vector centre : FORMERLY ORIGIN
  Origin point that the ray spawns from

angle : float, in radians, [default = 0.76]
  Clockwise angle to the horizontal axis

wavelength : float, [Default = 0.76]
  Wavelength of the ray

Attributes :
---------- -
max_coords : [float, float]
  The maximum point that the ray reaches.Mainly used for drawing rays
  within their limits

Methods :
------
solve_for_x(float y) :
  Returns the corresponding x coord from a y coord.

solve_for_y(float x) :
  Returns the corresponding x coord from a y coord.

set_max_coords_from_x(float x) :
  Sets max_coords to the limit of the ray at that x coord

set_max_coords_from_y(float y) :
  Sets max_coords to the limit of the ray at that y coord

*/

void light::Ray::set_values(coord::vector centre_, float angle_,
                float wavelength_,
                bool exists_){
  SimObj::set_values(centre_, angle_);
	wavelength = wavelength_;
  exists = exists_;
}

void light::Ray::set_max_coords_from_y(float y_coord_) {
	max_coords.y = y_coord_;
	max_coords.x = solve_for_x(y_coord_);
}

void light::Ray::set_max_coords_from_x(float x_coord_) {
	max_coords.x = x_coord_;
	max_coords.y = solve_for_y(x_coord_);
}

float light::Ray::get_wavelength() {
	return wavelength;
}

coord::vector light::Ray::get_max_coords() {
	return max_coords;
}

float light::Ray::solve_for_x(float y_coord_) {
	//increase in x using tan(angle) = dy/dx where dy and dx are difference in y and x
	float dx = (y_coord_ - centre.y) / tan(angle);
	//add that increase to the starting x to find where the x coord is at that y.
	float x_coord_ = centre.x + dx;

	return x_coord_;
}

float light::Ray::solve_for_y(float x_coord_) {
	//increase in y using tan(angle) = dy/dx where dy and dx are difference in y and x
	float dy = (x_coord_ - centre.x) * tan(angle);
	//add that increase to the starting y to find where the y coord is at that x.
	float y_coord_ = centre.y + dy;

	return y_coord_;
}

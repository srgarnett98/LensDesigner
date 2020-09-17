#include "coord/simobj.hpp"

void coord::SimObj::set_values(coord::vector centre_, float angle_ = 0.0) {
  centre = centre_;
  double constrainAngle(double x){
    x = fmod(x + M_PI,M_PI_2);
    if (x < 0)
        x += M_PI_2;
    return x - M_PI;
  }
  angle = constrainAngle(angle_);
}

coord::vector coord::SimObj::get_centre(){
  return centre;
}

float coord::SimObj::get_angle(){
  return angle;
}

coord::vector coord::SimObj::global_to_local_coords(coord::vector coord){
  /*
  Turns (x, y) coordinate from the global frame, into the frame of the simobj
  Does this by removing the centre of the SimObj, and then rotating
  */
  coord::vector result;
  result = coord - centre;
  if (angle!= 0.0) {
    result = result.rotate(angle);
  }

  return result;
}

coord::vector coord::SimObj::local_to_global_coords(coord::vector coord){
  /*
  Turns (x, y) coordinate from the local frame, into the global frame
  Does this by removing the centre of the SimObj, and then rotating
  */
  coord::vector result, origin;
  origin.set_values(float(0.0), float(0.0));
  result = coord - global_to_local_coords(origin);
  if (angle!= 0.0) {
    result = result.rotate(-angle);
  }

  return result;
}

light::Ray coord::SimObj::global_to_local_ray(light::Ray ray){
  coords::Vector local_coords = surface.global_to_local_coords(ray.centre);
  float new_angle = ray.angle - angle;

  light::Ray new_ray;
  new_ray.centre= local_coords;
  new_ray.angle = new_angle;
  return new_ray;
};

light::Ray coord::SimObj::local_to_global_ray(light::Ray ray){
  coords::Vector global_coords = surface.local_to_global_coords(ray.centre);
  float new_angle = ray.angle + angle;
  light::Ray new_ray;
  new_ray.centre= global_coords;
  new_ray.angle = new_angle;
  return new_ray;
};

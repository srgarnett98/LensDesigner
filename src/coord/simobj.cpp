#include "coord/simobj"

void coord::SimObj::set_values(coord::vector centre_, float angle_ = 0.0) {
  centre = centre_;
  angle = angle_;
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

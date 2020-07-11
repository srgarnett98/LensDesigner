#include "coord/vector.hpp"

void coord::vector::set_values(float x_, float y_){
  x = x_;
  y = y_;
}

coord::vector coord::vector::operator + (coord::vector param){
  /*
  Addition of 2 vectors
  */
  coord::vector result;
  result.x = x + param.x;
  result.y = y + param.y;

  return result;
}

coord::vector coord::vector::operator - (coord::vector param){
  /*
  Addition of 2 vectors
  */
  vector result;
  result.x = x - param.x;
  result.y = y - param.y;
  return result;
}

coord::vector coord::vector::rotate(float angle){
  /*
  Rotates a vector by an angle, clockwise (TODO: check this is clockwise)
  Angle must be in radians
  */
  coord::vector result;
  result.x = x * cos(angle) + y * sin(angle);
  result.y = y * cos(angle) - x * sin(angle);

  return result;
}

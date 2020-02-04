/*
Core of the module which contains the definitions of lens type objects
and the physical behaviour of them thereof.
*/

#include <iostream>
#include <cmath>

/*
###############
### Structs ###
###############
*/

/*
#################
### Functions ###
#################
*/

float calc_refract_angle(float n1, float n2, float theta1){
  /*
  Calculates the refracted angle for a ray crossing a material boundary

  Inputs
  ----------
  float n1
    The refractive index of the first material

  float n2
    The refractive index of the second material

  float theta1
    The incident angle (angle to perpendicular to the boundary) of the ray
    Unit: Radians

  Returns
  ----------
  float theta2
    The refracted angle (to perpendicular to the boundary) of the exiting ray
    Unit: Radians
  */

  float theta2;
  bool add_pi;

  try{
    // Adding pi will make the direction of the beam rotate 180 degrees
    // This ensures the exiting ray angle is in the forward direction
    add_pi = (int( (theta1 + M_PI_2)/ M_PI) %2)==1;

    // Snell's law (sin(theta1)/sin(theta2) = n1/n2) rearranged
    theta2 = asin(sin(theta1) * n1 / n2);

    //Add the Pi to ensure the direction of exiting ray is forward, if necessary
    // AKA same "direction" as incident ray
    add_pi ? theta2+= M_PI: false;
  }
  catch(...){
    //If this fails (arcsin returns an error because it isnt valid)
    //the ray is therefore past the critical angle, and reflects.
    //TODO: Model this as a reflection, and not as the ray disappearing
    return NAN;
  }
  return theta2;
}

/*
###############
### Classes ###
###############
*/

class vector{
    /*
    Vector class, since all coordinates will be in 2d cartesian coordinates
    Can write function to rotate vectors, and other transforms which are useful
    */
  public:
    float x;
    float y;

    vector operator + (vector param){
      /*
      Addition of 2 vectors
      */
      vector result(x + param.x,
                    y + param.y);
      return result;
    }

    vector operator - (vector param){
      /*
      Addition of 2 vectors
      */
      vector result(x - param.x,
                    y - param.y);
      return result;
    }

    vector rotate(float angle){
      /*
      Rotates a vector by an angle, clockwise (TODO: check this is clockwise)
      Angle must be in radians
      */
      vector result;
      result.x = x * cos(angle) + y * sin(angle);
      result.y = y * cos(angle) - x * sin(angle);

      return result;
    }

}

int main()
{
  /*
  This program will be structured as a module, for the start anyway
  Intially main will be used as a debugging/ testing area, and can be ignored
  */
  std::cout << calc_refract_angle(1.5, 1.0, 0.5)<< std::endl;

  return 0;
}

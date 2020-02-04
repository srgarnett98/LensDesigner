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

    void set_values(float x_, float y_){
      x = x_;
      y = y_;
    }

    vector operator + (vector param){
      /*
      Addition of 2 vectors
      */
      vector result;
      result.x = x + param.x;
      result.y = y + param.y;

      return result;
    }

    vector operator - (vector param){
      /*
      Addition of 2 vectors
      */
      vector result;
      result.x = x - param.x;
      result.y = y - param.y;
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

};

class SimObj {
  /*
  Base class for most objects.
  Mainly deals with coordinate transformation, which is needed for all objects
  */

  public:
    vector centre;
    float angle;

    void set_values(vector centre_, float angle_){
      centre = centre_;
      angle = angle_;
    }

    vector getCentre(){
      return centre;
    }

    float getAngle(){
      return angle;
    }

    vector global_to_local_coords(vector coord){
      /*
      Turns (x, y) coordinate from the global frame, into the frame of the simobj
      Does this by removing the centre of the SimObj, and then rotating
      */
      vector result;
      result = coord - centre;
      if (angle!= 0.0) {
        result = result.rotate(angle);
      }

      return result;
    }

    vector local_to_global_coords(vector coord){
      /*
      Turns (x, y) coordinate from the local frame, into the global frame
      Does this by removing the centre of the SimObj, and then rotating
      */
      vector result, origin;
      origin.set_values(float(0.0), float(0.0));
      result = coord - global_to_local_coords(origin);
      if (angle!= 0.0) {
        result = result.rotate(-angle);
      }

      return result;
    }
};


int main()
{
  /*
  This program will be structured as a module, for the start anyway
  Intially main will be used as a debugging/ testing area, and can be ignored
  */

  vector testVec;
  testVec.set_values(2.5, 3.5);
  std::cout << testVec.rotate(M_PI).x << std::endl;
  std::cout << testVec.rotate(M_PI).y << std::endl;

  vector testObjCentre;
  testObjCentre.set_values(2.5, 2.5);
  SimObj testObj;
  testObj.set_values(testObjCentre, M_PI_2);

  std::cout << testObj.global_to_local_coords(testVec).x << std::endl;
  std::cout << testObj.global_to_local_coords(testVec).y << std::endl;

  return 0;
}

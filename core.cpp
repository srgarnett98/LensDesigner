/*
Core of the module which contains the definitions of lens type objects
and the physical behaviour of them thereof.
*/

#include <iostream>
#include <cmath>
#include <stdexcept>

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

float pmma(float wavelength){
  // TEMPORARY VALUE FOR DEUBGGING
  return 1.5;
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

	Params
	-------

	vector centre
		Centre point of the object, or origin if its a ray

	float angle, in radians
	  The angle to the horizontal of the element.
		For lenses, 0.0 is vertical, so the normal to the lens in horizontal,
		and increasing angle rotates clockwise !!!!CHECK!!!!
		For Light, 0.0 is horizontal, increasing angle rotates clockwise

	Methods
	--------

	void set_values    (centre, angle)
		sets the values inputted into the object. Work out how to call on start.

	vector get_centre
		returns the value for the centre of the object.

	float get_angle
		returns the value for the angle of the object

	vector global_to_local_coords    (coord)
		Converts a coordinate from the global reference frame, into the local reference frame
		AKA the reference fram from which the object is at centre = [0, 0] and angle = 0.0.

	vector local_to_global_coords   (coord)
		Converts a coordinate from the local reference frame into the global reference frame.

  */

  public:
    vector centre;
    float angle;

    void set_values(vector centre_, float angle_ = 0.0){
      centre = centre_;
      angle = angle_;
    }

    vector get_centre(){
      return centre;
    }

    float get_angle(){
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

class Ray: public SimObj{
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
	public:
		float wavelength;
		vector max_coords;

	void set_values(vector centre_, float angle_ = 0.0, float wavelength_ = 0.76){
		centre = centre_;
		angle = angle_;
		wavelength = wavelength_;
	}

	void set_max_coords_from_y(float y_coord_) {
		max_coords.y = y_coord_;
		max_coords.x = solve_for_x(y_coord_);
	}

	void set_max_coords_from_x(float x_coord_) {
		max_coords.x = x_coord_;
		max_coords.y = solve_for_y(x_coord_);
	}

	float get_wavelength() {
		return wavelength;
	}

	vector get_max_coords() {
		return max_coords;
	}

	float solve_for_x(float y_coord_) {
		//increase in x using tan(angle) = dy/dx where dy and dx are difference in y and x
		float dx = (y_coord_ - centre.y) / tan(angle);
		//add that increase to the starting x to find where the x coord is at that y.
		float x_coord_ = centre.x + dx;

		return x_coord_;
	}

	float solve_for_y(float x_coord_) {
		//increase in y using tan(angle) = dy/dx where dy and dx are difference in y and x
		float dy = (x_coord_ - centre.x) * tan(angle);
		//add that increase to the starting y to find where the y coord is at that x.
		float y_coord_ = centre.y + dy;

		return y_coord_;
	}
};

class Interface: public SimObj{
    /*
    Base class for all interfaces in the simulation. Lens surfaces, flat surface, aperture etc

      Parameters
      ----------

          n1:     float or string of valid material
                  Refractive index or material before the interface

          n2:     float or string of valid material
                  Refractive index or material after the interface

          centre = [0.0, 0.0]: [float, float]
              Coordinates of the centre of the aperture

          angle = 0.0: float in radians
              Angle of the aperture to the vertical

          element_height: default np.inf
    */
    public:
      //n1 and n2 are both functions.
      //They take wavelength as the argument and return refractive index of that wavelength
      float (*n1)(float);
      float (*n2)(float);
      float element_height;

    void set_values(vector centre_, float angle_ = 0.0,
                    float (*n1_)(float) = pmma, float (*n2_)(float) = pmma,
                    float element_height_ = NAN){
      centre = centre_;
      angle = angle_;
      n1 = *n1_;
      n2 = *n2_;
      element_height = element_height_;
    }

    Ray transfer_func(Ray ray_){
      throw std::logic_error("Interface requires valid transfer function");
    }

    float solve_for_x(float y_coord_){
      throw std::logic_error("Interface requires valid sag function");
    }

    float tangent_angle(float y_coord_){
      float diff_x = (solve_for_x(y_coord_ + 0.000001) -
                      solve_for_x(y_coord_ - 0.000001)) / 0.000002;
      float tangent = atan(diff_x);
      tangent += angle;
      return tangent;
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

  Ray testRay;
  testRay.set_values(testVec, 1.0);

  std::cout << testRay.solve_for_y(3.0) << std::endl;



  return 0;
}

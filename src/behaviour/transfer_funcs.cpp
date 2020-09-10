#include "behaviour/transfer_funcs.hpp"

float behaviour::calc_refract_angle(float n1, float n2, float theta1){
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


float behaviour::calc_reflect_angle(float theta1){
  return -theta1;
}

light::Ray behaviour::transfer_to_surface(light::Ray ray
                                          element::Surface surface){
  light::Ray local_ray = surface.global_to_local_ray(ray);
  if(!local_ray.exists){
    return local_ray;
  }
  //find some way to pass pointers to each functions solve for x
  //solve intersect runs an optimised solver for f1-f2=0
  //ensure solve intersect finds the best solution
  //so solution closest to ray.centre.
  coord::vector sol = solve_intersect(local_ray,
                                      surface,
                                      surface.epsilon);
  light::Ray new_ray;
  new_ray.set_values(sol, ray.angle, ray.wavelength, ray.exists);

  return new_ray;
}

coord::vector behaviour::solve_intersect(light::Ray ray,
                                         curve::Surface surface,
                                         float epsilon) {

  /*
  Uses a pregenerated list of solutions to find rough positions of solutions
  then performs a bisect in order to get the correct level of accuracy.
  */

  // class to turnn 2 functions into a singular one
  //takes the two functions as attributes
  class fg{
    public:
      float (*f)(float y);
      float (*g)(float y);

      float f_subtract_g(float y){
        return f(y) - g(y);
      }
  };

  // function that performs a bisection function solve on a range.
  float bisect(float y1, float y2,
               float (*function)(float y),
               float epsilon){
    float sol;

    //midpoint
    float inter_y = (y1+y2)/2.0;
    float inter_sol = function(inter_y);

    //if the sides are very close, return intermediate point
    if((abs(y1-y2) < epsilon) || (inter_sol == 0.0)){
      return inter_y;
    }

    //if solution between y1 and inter_y, repeat bisect on first half
    if(inter_sol<0){
      sol = bisect(y1, inter_y, function, epsilon);

    //else if solution between y2 and inter_y, repeat bisect on second half
    }else if(inter_sol>0){
      sol = bisect(inter_y, y2, function, epsilon);
    }

    //eventually one bisect will return a value, will cascade to this return
    return sol;
  }

  unsigned success_index;
  bool success = false;

  //condition by which a solution is between index and index+1
  bool bisect_condition(unsigned index, light::Ray ray, element::Surface surface){
    //if index = (size-1), then index+1 = invalid index for std vector
    if(index == (surface.pos_list.size()-1)){
      return false;
    }
    //vec_i is vector position at index i
    //vec_i1 is vector position at index i+1
    coord::vector vec_i = surface.pos_list[i];
    coord::vector vec_i1= surface.pos_list[i+1];

    //not both being same side of 0.
    //true if f(x_i) = +ve && f(x_i+1) = -ve
    //or vice versa
    bool cond = !(
      (vec_i.x-ray.solve_for_x(vec_i.y) > 0)
      ==
      (vec_i1.x-ray.solve_for_x(vec_i1.y) > 0)
    );
    return cond;
  }

  //find ray angle, if 0-pi, looking from +y->-y, is pi-2pi, -y->+y
  if(ray.angle<M_PI && ray.angle>0){
    for(unsigned i=0; i<(surface.pos_list.size()-1); i++){
      if(bisect_condition(i, ray, surface)){
        success_index = i;
        success = true;
        break;
      }
    }
  }else{
    for(unsigned i=0; i<(surface.pos_list.size()-1); i++){
      j = surface.pos_list.size()-i-2;
      if(bisect_condition(j, ray, surface)){
        success_index = j;
        success=true;
        break;
      }
    }
  }

  //if no successes, return null
  if(!success){
    coord::vector intersection;
    intersection.x = NAN;
    intersection.y = NAN;
    return intersection;
  //many successes, need to find correct
  }

  //bisect correct segment
  //is this really necessary if the resolution is defined well?
  //maybe linearly interpolate between the successful segments?

  //construct singular function which needs to be solved
  float y_sol;
  fg eq_to_solve;
  fg.set_values(ray.solve_for_x, surface.geometry.solve_for_y);

  float y1 = surface.pos_list[success_index].y;
  float y2 = surface.pos_list[success_index+1].y;

  //force first argument to be +ve, second to be -ve
  if(fg.f_subtract_g(y1) > 0){
    y_sol = bisect(y1, y2, fg.f_subtract_g, epsilon);
  }else{
    y_sol = bisect(y2, y1, fg.f_subtract_g, epsilon);
  }


  coord::vector new_coords;
  new_coords.set_values(ray.solve_for_x(y_sol), y_sol);
  return new_coords;

}

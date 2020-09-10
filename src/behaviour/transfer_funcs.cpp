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
  //find some way to pass pointers to each functions solve for x
  //solve intersect runs an optimised solver for f1-f2=0
  //ensure solve intersect finds the best solution
  //so solution closest to ray.centre.
  coord::vector sol = solve_intersect(local_ray.solve_for_x,
                                      surface.geometry.solve_for_x,
                                      locay_ray.centre);
  light::Ray new_ray;
  new_ray.centre = sol;
  new_ray.angle=local_ray.angle;

  return new_ray;
}

class fg{
  public:
    float (*f)(float y);
    float (*g)(float y);

    float f_subtract_g(float y){
      return f(y) - g(y);
    }
}

coord::vector behaviour::solve_intersect(light::Ray ray,
                                         curve::Surface surface) {
  /*
  pseudocode ideas:
  dissection into small elements
  For each lens surface, define a minimum resolution
  split the lens into small linear sections, based on the minimum resolution
  check through all small sections, whether intersection occurs
  Will always find all roots.
  relatively constant runtime, lots of work is front-loaded
  translates to 3d well, define surface as a FEM triangle thingy
  O(n segments)
  could reduce number of segments it needs to check?
  will require user to input resolution and element width.


  so I have a list of (x,y) coords
  how can I efficiently say which pair of (x1,y1)->(x2,y2) coords
  intersects with a straight line.

  couple method with bisection method?
  go through surface element list, find where dy/dx = angle of ray
  split surface up at these parallel points. Check whether the ray is in each section
  if yes, pick first intersection point (ez)
  bisect and repeat

  bisect section doesnt need to use the surface list shit?
  once we KNOW the ray intersects in that region, can use normal bisection.
  */
  //find indexes where surface is parallel with ray
  //quite a big ask?
  // if I'm finding where dy/dx-angle =0, might as well solve  the damn thing
  int success_index;
  float ray_distance;
  float ray_distance2;
  for(unsigned i=0, i<(surface.geometry.angle_list.size()-1), i++){
    if(not((surface.geometry.pos_list[i].x-ray.solve_for_x(surface.geometry.pos_list[i].y) > 0) ==
       (surface.geometry.pos_list[i].x-ray.solve_for_x(surface.geometry.pos_list[i].y)>0))){
      ray_distance2= sqrt(geometry.pos_list[i]-geometry)
    }
  }

  //if no successes, return null
  if(segment_success.size()==0){
    coord::vector intersection;
    intersection.x = NAN;
    intersection.y = NAN;
    return intersection;
  //many successes, need to find correct
  } elif(segment_success.size() != 1){
    find_closest_segment();
  } else{
    float y1 = segment_y_coords[segment_success[0]];
    float y2 = segement_y_coords[segment_success[1]];
  }
  //passes through if only 1 success



  //bisect correct segment
  //is this really necessary if the resolution is defined well?
  //maybe linearly interpolate between the successful segments?
  fg eq_to_solve;
  fg.set_values(ray.solve_for_x, surface.geometry.solve_for_y);
  bisect(fg.f_subtract_g, y1, y2, epsilon)
}

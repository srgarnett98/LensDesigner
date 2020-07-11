#include "elements/aperture.hpp"
/*
Creates an object representing an aperture, where light passes through a small
hole in the centre

Params:
---------
    aperture_size:  float
        Total width of the aperture

    centre = [0.0, 0.0]: [float, float]
        Coordinates of the centre of the aperture

    angle = 0.0: float in radians
        Angle of the aperture to the vertical

    element_height = NAN: float
        Height of the total object in the y axis

Methods:
------
    global_to_local_coordinates(coords): [float, float]
        Takes input of global x and y coordinates, and returns the coordinates
        in the frame of reference of the lens being at the origin and vertical.

    local_to_global_coordinates(coords): [float, float]
        Takes input of local x and y coordinates, and returns the coordinates
        in the global frame of reference.

    solve_for_x(y): float
        From a local value of y, returns the local x coordinate of the surface
        Always returns 0 because it is flat.

    draw_element(axes = None): matplotlib Axes object
        Plots the lens surface on a matplotlib axes. Will create new axes
        by default, but will use the current active figure if passed.

    transformation_by_element(rays): list of list of Ray objects, sorted by source
        From incident rays, finds which pass through the aperture
        Returns the set of rays that would result from the incident set being
        blocked, with blocked rays being nan rays.
*/

void elements::Aperture::set_values(vector centre_, float angle_,
                float element_height_ = NAN,
                float aperture_size_ = 1.0){
  Surface::set_values(centre_, angle_, element_height_);
  aperture_size = aperture_size_;
}

light::Ray elements::Aperture::transfer_func(light::Ray ray_){
  /*
    Pass through aperture
    Blocks any rays (turns to null) if they don't go through the aperture, else
    propogates those rays

    Params
    ------------
        ray_:       Ray
            Incident ray on the aperture

    Returns
    -------------
        new_ray:    Ray
            Either the same ray as incident, if it would pass through the aperture,
            or a nan ray, where all its properties are nans
    */
    light::Ray new_ray;
    if (!ray_.exists) {
      return ray_;
    }

    coord::vector local_coords;
    local_coords = global_to_local_coords(ray_.centre);

    if (aperture_size / 2.0 > abs(local_coords.y)) {
      new_ray = ray_;
    } else {
      ray_.exists = false;
      new_ray = ray_;
    }
    return new_ray;
}

float elements::Aperture::solve_for_x(float y) {
  return 0.0;
}

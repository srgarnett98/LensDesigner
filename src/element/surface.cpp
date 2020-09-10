#include "element/surface.hpp"
/*
Base class for all Surfaces in the simulation. Lens surfaces, flat surface, aperture etc

  Parameters
  ----------

      centre = [0.0, 0.0]: [float, float]
          Coordinates of the centre of the aperture

      angle = 0.0: float in radians
          Angle of the aperture to the vertical

      element_height: default np.inf
          A height of a lens or aperture etc.
          Past this height the behaviour may be undefined

  Methods
  ----------

      tangent_angle:  float
          Calculates the tangent to the Surface at a specified height
*/

void element::Surface::set_values(coord::vector centre_,
                                   float angle_,
                                   float element_height_){
  centre = centre_;
  angle = angle_;
  element_height = element_height_;
}

light::Ray element::Surface::transfer_func(light::Ray ray_){
  throw "Surface requires valid transfer function";
}

light::Ray element::Surface::global_to_local_ray(light::Ray ray){
  coords::Vector local_coords = surface.global_to_local_coords(ray.centre);
  float new_angle = ray.angle - angle;

  light::Ray new_ray;
  new_ray.centre= local_coords;
  new_ray.angle = new_angle;
  return new_ray;
}

light::Ray element::Surface::local_to_global_ray(light::Ray ray){
  coords::Vector global_coords = surface.local_to_global_coords(ray.centre);
  float new_angle = ray.angle + angle;
  light::Ray new_ray;
  new_ray.centre= global_coords;
  new_ray.angle = new_angle;
  return new_ray;
}

/*
A single surface of medium change, presented as a lens surface

  Parameters
  ----------

      centre = [0.0, 0.0]: [float, float]
          Coordinates of the centre of the aperture

      angle = 0.0: float in radians
          Angle of the aperture to the vertical

      element_height: default np.inf
          A height of a lens or aperture etc.
          Past this height the behaviour may be undefined

      n1: pointer to function takes wavelength


  Methods
  ----------

      tangent_angle:  float
          Calculates the tangent to the Surface at a specified height
*/

void LensSurface::set_values(coord::vector centre_,
                            float (*n1_)(float wavelength),
                            float (*n2_)(float wavelength),
                            curve::Geometry geometry_,
                            float angle_,
                            float element_height_){
  Surface::set_values(centre_, angle_, element_height_);
  n1 = n1_;
  n2 = n2_;
}

light::Ray Surface::LensSurface::transfer_func(light::Ray ray) override{
  if (!ray.exists){
    return ray;
  }

  float n1_val = n1(ray.wavelength);
  float n2_val = n2(ray.wavelength);

  //ray is not transformed out of global in "transfer to surface"
  //coord::vector local_coords = global_to_local_coords(ray.centre);
  
  float lens_normal = normal_angle(local_coords.y);
  float angle_normal = ray.angle - lens_normal;
  float angle_refract = behaviour::calc_refract_angle(n1_val, n2_val, angle_normal);
  float new_ray_angle = angle_refract + lens_normal;

  light::Ray new_ray = Ray();
  new_ray.set-values(ray.centre, new_ray_angle, ray.wavelength, true);
  return new_ray;
};

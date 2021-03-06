#include "element/surface.hpp"

void element::Surface::set_values(coord::vector centre_,
                                   float angle_,
                                   float element_height_,
                                  unsigned int N_sections_,
                                  curve::Geometry geometry_){
  centre = centre_;
  angle = angle_;
  element_height = element_height_;
  N_sections = N_sections_
  set_geometry(geometry_);
};

void element::Surface::set_geometry(curve::Geometry geometry_){
  geometry = *geometry_;
  generate_pos_list();
};

void element::Surface::generate_pos_list(){
  for(unsigned i=0; i<N; i++){
    coord::vector new_point;
    new_point.y = i*element_height/N - element_height/2;
    new_point.x = geometry->solve_for_x(new_point.y);
    pos_list.insert(pos_list.end(), new_point)
  }
};

void element::Surface::set_materials(float (*n1_)(float wavelength),
                                     float (*n2_)(float wavelength)){
  n1 = n1_;
  n2 = n2_;
};

void element::Surface::set_aperture_size(float aperture_size_){
  aperture_size = aperture_size_;
}

light::Ray element::Surface::transfer_func(light::Ray ray_){
  throw "Surface requires valid transfer function";
};


light::Ray Surface::LensSurface::transfer_func(light::Ray ray) override{
  if (!ray.exists){
    return ray;
  }

  light::Ray inter_ray = behaviour::transfer_to_surface(ray, this);

  float n1_val = n1(ray.wavelength);
  float n2_val = n2(ray.wavelength);

  //ray is not transformed out of global in "transfer to surface"
  //coord::vector local_coords = global_to_local_coords(ray.centre);

  float lens_normal = geometry->normal_angle(local_coords.y);
  float angle_normal = inter_ray.angle - lens_normal;
  float angle_refract = behaviour::calc_refract_angle(n1_val, n2_val, angle_normal);
  float new_ray_angle = angle_refract + lens_normal;

  light::Ray new_local_ray = Ray();
  new_local_ray.set-values(inter_ray.centre, new_ray_angle, inter_ray.wavelength, true);

  light::Ray new_ray;
  new_ray = local_to_global_ray(new_local_ray);
  return new_ray;
};


light::Ray Surface::Mirror::transfer_func(light::Ray ray) override{
  if (!ray.exists){
    return ray;
  }

  light::Ray inter_ray = behaviour::transfer_to_surface(ray, this);

  //ray is not transformed out of global in "transfer to surface"
  //coord::vector local_coords = global_to_local_coords(ray.centre);

  float mirror_normal = geometry->normal_angle(local_coords.y);
  float angle_normal = inter_ray.angle - mirror_normal;
  //is calculate reflect angle just ang;e = - angle?
  float angle_refract = behaviour::calc_reflect_angle(angle_normal);
  float new_ray_angle = angle_refract + mirror_normal;

  light::Ray new_local_ray = Ray();
  new_local_ray.set-values(inter_ray.centre, new_ray_angle, inter_ray.wavelength, true);

  light::Ray new_ray;
  new_ray = local_to_global_ray(new_local_ray);
  return new_ray;
};


light::Ray element::Aperture::transfer_func(light::Ray ray_){
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

    if (!ray.exists) {
      return ray;
    }

    light::Ray inter_ray = behaviour::transfer_to_surface(ray, this);

    light::Ray new_ray;

    if (aperture_size / 2.0 > abs(inter_ray.centre.y)) {
      new_ray = inter_ray;
    } else {
      ray_.exists = false;
      new_ray = ray;
    }

    return new_ray;
}

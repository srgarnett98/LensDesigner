#include "element/group.hpp"

void element::Group::set_surfaces(std::vector<element::Surface *> surfaces_){
  surfaces = surfaces_;
}

void element::Group::append_surface(element::Surface *surface){
  //rotate surface into group.
  //surface doesnt move in psace
  surface.centre = global_to_local_coords(surface.centre);
  surface.angle = surface.angle - angle;

  surfaces.insert(surfaces.end(), surface);
}

void element::Group::insert_surface(element::Surface *surface, int index){
  //rotate surface into group.
  //surface doesnt move in psace
  surface.centre = global_to_local_coords(surface.centre);
  surface.angle = surface.angle - angle;

  surfaces.insert(index, surface);
}

element::Surface * element::Group::pop_surface(int index){
  element::Surface *surface = surfaces[index];
  surfaces.erase(index);

  //rotates the surface out of groups frame of reference
  //doesnt move the surface
  surface.centre = local_to_global_coords(surface.centre);
  surface.angle = surface.angle + angle;

  return surface;
}

void element::Group::append_Group(element::Group group){
  //rotate it first? probably
  //or leave the rotating to group::insert_surface?
  for(int i=0; i<group.size(); i++){
    append_surface(group[i]);
  }
}

void element::Group::insert_Group(element::Group group, int index){
  for(int i=0; i<group.size(); i++){
    insert_surface(group[i], index+i);
  }
}

element::Group element::Group::pop_Group(std::vector<int> index_list){
  element::Group new_group;
  new_group.set_values(centre, angle);

  for(int i=0; i<index_list.size(); i++){

    surface = pop_surface(index_list[i]);
    new_group.append_surface(surface);

    //since an element is popped, any later elements get shifted forward once
    for(int j=i+1; j<index_list.size()-1; j++){
      if(index_list[j]>index_list[i]){
        index_list[j]=index_list[j]-1;
      }
    }
  }

  return new_group;
}

std::vector<std::vector<light::Ray>> element::Group::transfer_packet(std::vector<light::Ray> init_rays){
  std::vector<std::vector<light::Ray>> total_rays;

  for(int i=0; i<init_rays.size(); i++){
    total_rays[0][i] = global_to_local_ray(init_rays[i]);
  }

  //extend total rays to the right size?
  //or append at every stage?

  for(int i=0; i<surfaces.size(); i++){
    for(int j=0; j<total_rays[i].size(); j++){
      total_rays[i+1].append(surfaces[i]->transfer_func(total_rays[i][j]));
    }
  }

  for(int i=0; i<total_rays.size(); i++){
    for(int j=0; i<total_rays[i].size(); j++){
      total_rays[i][j] = local_to_global_ray(total_rays[i][j]);
    }
  }

  return total_rays;
}

void main::LightSystem::set_values(std::vector<element::Group> groups_,
                                   std::vector<std::vector<light::Ray>> rays)
{
  groups = groups_;
  rays = rays;
}

void main::LightSystem::set_groups(std::vector<element::Group> groups_)
{
  groups = groups_;
}

void main::LightSystem::append_group(element::Group group)
{
  groups.append(group);
}

void main::LightSystem::insert_group(element::Group group, int group_index)
{
  groups.insert(group, group_index);
}

element::Group main::LightSystem::pop_group(int group_index)
{
  element::Group popped_group = groups[group_index];
  groups.pop(group_index);
  return popped_group;
}

void main::LightSystem::combine_groups(std::pair<int> start_stop_indexes)
{
  element::Group combined_group = groups.pop_group(start_stop_indexes.first);
  for(int i = start_stop_indexes.first; i<start_stop_indexes.second; i++)
  {
    //will end up popping the same group index every time, index1 + 1
    combined_group.append_Group(groups.pop_group(start_stop_indexes.first +1));
  }
  groups.insert_group(combined_group, start_stop_indexes.first);
}

void main::LightSystem::split_group(int group index, int sub_index)
{
  std::vector<int> pop_indexes;
  for(int i = 0; i<groups[group_index].surfaces.size(); i++)
  {
    pop_indexes.append(i);
  }
  element::Group second_half = groups[group_index].pop_group(pop_indexes);
  insert_group(second_half, group_index+1);
}

void main::LightSystem::append_surface(element::Surface * surface)
{
  element::Group new_group;
  new_group.append_surface(surface);
  groups.append_group(new_group);
}

void main::LightSystem::insert_surface(element::Surface * surface, int group_index)
{
  element::Group new_group;
  new_group.append_surface(surface);
  groups.insert_group(new_group, group_index);
}

element::Surface * main::LightSystem::pop_surface(int group_index, int sub_index=0);

element::Surface * main::LightSystem::get_surface(int group_index, int sub_index=0);

void main::LightSystem::set_init_rays(std::vector<light::Ray> rays);

void main::LightSystem::simulate();

void main::LightSystem::simulate_from_index(int index);

float main::LightSystem::optimise(std::vector<float *> parameter_pointers,
                                  int first_changed_group = 0);

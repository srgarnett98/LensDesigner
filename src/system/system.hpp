#pragma once

namespace main{
  class LightSystem{
    public:
      std::vector<element::Group> groups;
      std::vector<std::vector<light::Ray>> rays;

      void set_values(std::vector<*element::Surface> elements_,
                      std::vector<std::vector<light::Ray>> rays);

      void set_groups(std::vector<element::Group> groups_);

      void append_group(element::Group group);

      void insert_group(element::Group group, int group_index);

      element::Group pop_group(int group_index);

      void combine_groups(std::pair start_stop_indexes);

      void split_group(int group index, int sub_index);

      void append_surface(element::Surface * surface);

      void insert_surface(element::Surface * surface, int index);

      element::Surface * pop_surface(int group_index, int sub_index);

      element::Surface * get_surface(int group_index, int sub_index);

      void set_init_rays(std::vector<light::Ray> rays);

      void simulate();
  }
}

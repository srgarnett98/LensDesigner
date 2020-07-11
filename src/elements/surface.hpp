#include "/coord/vector.hpp"
#include "/coord/simobj.hpp"
#include "/light/ray.hpp"

namespace elements{
  class Surface: public coord::SimObj {
    public:
      float element_height;

      void set_values(coord::vector centre_,
                      float angle_ = 0.0,
                      float element_height_ = NAN);

      light::Ray transfer_func(light::Ray ray);

      float solve_for_x(float y_coord);

      float tangent_angle(float y_coord);
  }
}

/*
Core of the module which contains the definitions of lens type objects
and the physical behaviour of them thereof.
*/

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "behaviour/transfer_funcs.hpp"
#include "coord/vector.hpp"
#include "coord/simobj.hpp"
#include "light/ray.hpp"
#include "curve/hyperbolic_curve.hpp"
#include "element/surface.hpp"
#include "element/aperture.hpp"
#include "material/pmma.hpp"

int main()
{
  /*
  This program will be structured as a module, for the start anyway
  Intially main will be used as a debugging/ testing area, and can be ignored
  */

  coord::vector testVec;
  testVec.set_values(2.5, 3.5);
  std::cout << testVec.rotate(M_PI).x << std::endl;
  std::cout << testVec.rotate(M_PI).y << std::endl;
  //-2.5
  //-3.5

  coord::vector testObjCentre;
  testObjCentre.set_values(2.5, 2.5);
  coord::SimObj testObj;
  testObj.set_values(testObjCentre, M_PI_2);

  std::cout << testObj.global_to_local_coords(testVec).x << std::endl;
  std::cout << testObj.global_to_local_coords(testVec).y << std::endl;
  //1
  //0 or some kind of v.small float error (current 10^-8)

  light::Ray testRay;
  testRay.set_values(testVec, 1.0);

  std::cout << testRay.solve_for_y(3.0) << std::endl;
  std::cout << testRay.wavelength << std::endl;
  //4.2787
  //0.76

  element::Aperture testAperture;
  testAperture.set_values(testVec, 0.0);

  std::cout << testAperture.transfer_func(testRay).centre.x << std::endl;
  std::cout << testAperture.transfer_func(testRay).exists << std::endl;
  //2.5
  //true

  coord::vector testVec2;
  testVec2.set_values(2.5, 5.5);
  light::Ray testRay2;
  testRay2.set_values(testVec2, 1.0);
  std::cout << testAperture.transfer_func(testRay2).exists << std::endl;
  //false

  curve::hyperbolic_curve test_curve;
  test_curve.set_values(1.0, 0.0);
  std::cout << test_curve.solve_for_x(std::sqrt(0.5)) << std::endl;
  //0.292893



  return 0;
}

cmake_minimum_required(VERSION 3.17.3 FATAL_ERROR)

project(LensDesigner)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

#behaviour depends on: cmath
add_library(behaviour STATIC src/behaviour/transfer_funcs.cpp src/behaviour/transfer_funcs.hpp)
target_link_libraries(behaviour m)

#coord depends on: cmath
add_library(coord STATIC src/coord/simobj.cpp src/coord/simobj.hpp
                         src/coord/vector.cpp src/coord/vector.hpp)
target_link_libraries(coord m)

#curve depends on: coord, cmath
add_library(curve src/curve/curves.cpp src/curve/curves.hpp)
target_link_libraries(curve PUBLIC coord m)

#light depends on: coord, cmath
add_library(light src/light/ray.cpp src/light/ray.hpp)
target_link_libraries(light PUBLIC coord m)

#element depends on: coord, light, curve
add_library(element src/element/surface.cpp src/element/surface.hpp
                    src/element/group.cpp src/element/group.hpp)
target_link_libraries(element PUBLIC coord light curve)

#material has no dependencies
add_library(material src/material/materials.cpp src/material/materials.hpp)

add_executable(LensDesigner src/main.cpp)
target_link_libraries(LensDesigner behaviour coord curve light element material)

#link <cmath>
target_link_libraries(LensDesigner m)

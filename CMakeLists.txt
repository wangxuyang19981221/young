cmake_minimum_required(VERSION 3.10)


project(C++Primer)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC)


add_compile_options(-std=c++11 -Wall -g)

set(Folder ${CMAKE_SOURCE_DIR}/src)


include_directories(${CMAKE_SOURCE_DIR}/include )

add_executable(main 5_2x.cpp ${Folder}/screen.cpp ${Folder}/sales_data.cpp)

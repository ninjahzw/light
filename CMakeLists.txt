cmake_minimum_required(VERSION 3.2.3)
project(light_server)
 
include_directories(include)
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
#link_directories("/usr/local/lib")
set(CMAKE_CXX_COMPILER "g++-4.9")

# c++ 14
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -std=c++1y -lm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# files
file(GLOB SOURCES "gen-cpp/*.cpp")
file(GLOB LIGHT_SERV  "src/*.cpp")
file(GLOB LIGHT  "src/lightlib/*.cpp")
file(GLOB L_TEST "src/test/*.cpp")
file(GLOB TEST_EXE "build/*Test")

# libs
add_library (gen ${SOURCES})
add_library (light ${LIGHT})
add_library (light_server_lib ${LIGHT_SERV})

# the executables
add_executable(light_server "src/LightServer.cpp")
add_executable(client "client/CppClient.cpp")

# add dependency libraries (NOTE pthread to add thread support).
target_link_libraries(light pthread glog)
target_link_libraries(light_server_lib light gen thrift pthread glog)
target_link_libraries(light_server light_server_lib gen thrift glog)
target_link_libraries(client gen thrift)

#############
# Add tests #
#############
foreach( testsourcefile ${L_TEST} )
  # get file name from the full path
  get_filename_component(filename ${testsourcefile} NAME)
  # get rid of the suffix
  string( REPLACE ".cpp" "" testname ${filename} )
  add_executable( ${testname} ${testsourcefile} )
  # Make sure YourLib is linked to each app
  target_link_libraries( ${testname} light glog gtest pthread)
endforeach( testsourcefile ${L_TEST} )


########################
# To Support Run Tests #
########################
add_custom_target(runtests WORKING_DIRECTORY "." COMMAND 
  find . -name '*Test' | sh )


cmake_minimum_required(VERSION 4.0)
project(raylib_testing_1 CXX)

set(CMAKE_CXX_STANDARD 20) # use C++20 for modern features

# fetch RayLib from github
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        6.0 # change to update
)
set(FETCHCONTENT_QUIET NO)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# target / project (1):

# create executable
add_executable(hello_raylib src_testing/hello_raylib.cpp)

# link RayLib, include in executable
target_link_libraries(hello_raylib PRIVATE raylib)
# uncomment line below if project not building
#target_include_directories(raylib_testing_1 PRIVATE ${raylib_SOURCE_DIR}/src)

# target / project (2):

add_executable(sandels src_sandels/sandels.cpp)
target_link_libraries(sandels PRIVATE raylib)



#cmake_minimum_required(VERSION 4.0)
#project(raylib_testing_1)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(raylib_testing_1 main.cpp)

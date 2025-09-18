cmake_minimum_required(VERSION 3.15)
project(sfmlgame1)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.1   # latest stable
)
FetchContent_MakeAvailable(SFML)

# Collect all .cpp files in src/
file(GLOB SRC_FILES src/*.cpp)

add_executable(sfmlgame1 ${SRC_FILES})
target_link_libraries(sfmlgame1 sfml-graphics sfml-window sfml-system sfml-audio)

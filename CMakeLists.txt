cmake_minimum_required(VERSION 3.26)
project(manatee)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(Lua REQUIRED)

add_executable(main src/Main.cpp)

target_link_libraries(main PRIVATE ${SDL2_LIBRARIES} ${LUA_LIBRARIES})
target_include_directories(main
  PRIVATE
  ${LUA_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/external
  ${PROJECT_SOURCE_DIR}/external/glm
  ${PROJECT_SOURCE_DIR}/external/sol2/include
)

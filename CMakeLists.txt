cmake_minimum_required(VERSION 3.26)
project(manatee)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(main src/Main.cpp)

target_link_libraries(main
  PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  ${LUA_LIBRARIES}
  sol2
  imgui::imgui
  glm::glm
)
target_include_directories(main PRIVATE ${LUA_INCLUDE_DIR})

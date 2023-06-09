cmake_minimum_required(VERSION 3.26)
project(manatee)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Lua REQUIRED)

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
  sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG v3.3.0
)
FetchContent_MakeAvailable(sol2)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.89.5
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

file(GLOB SOURCES "src/**/*.cpp")
add_executable(main src/Main.cpp ${SOURCES})

target_link_libraries(main
  PRIVATE
  ${SDL2_LIBRARIES}
  SDL2_image::SDL2_image
  ${LUA_LIBRARIES}
  sol2
  glm::glm
  spdlog::spdlog
)
target_include_directories(main
  PRIVATE
  ${LUA_INCLUDE_DIR}
  ${imgui_SOURCE_DIR}
)

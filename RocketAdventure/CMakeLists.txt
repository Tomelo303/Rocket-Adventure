
find_package(SDL2 REQUIRED)

# Add source to this project's executable.
add_executable (RocketAdventure "main.cpp" "Game/Game.cpp" "Game/Game.h")

target_link_libraries(RocketAdventure SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RocketAdventure PROPERTY CXX_STANDARD 20)
endif()

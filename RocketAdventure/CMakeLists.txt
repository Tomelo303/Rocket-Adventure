# Find packages that are required for the project to execute properly
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add source to this project's executable.
add_executable (RocketAdventure
  "main.cpp"
  "Game/Game.cpp"
  "Game/Game.h"
  "Player/Player.cpp"
  "Player/Player.h"
)

# Link libraries so they are visible for the project
target_link_libraries(RocketAdventure SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(RocketAdventure SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RocketAdventure PROPERTY CXX_STANDARD 20)
endif()

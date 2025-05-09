﻿# Find packages that are required for the project to execute properly
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Add source to this project's executable.
add_executable (RocketAdventure
  "main.cpp"
  "Game/Game.cpp"			   "Game/Game.h"
  "Entity/Entity.cpp"		   "Entity/Entity.h"
  "Player/Player.cpp"		   "Player/Player.h"
  "Obstacle/Obstacle.cpp"      "Obstacle/Obstacle.h"
  "Boost/Boost.cpp"			   "Boost/Boost.h"
  "Background/Background.cpp"  "Background/Background.h" 
  "Texture/Texture.cpp"		   "Texture/Texture.h"
  "Collision/Collision.cpp"    "Collision/Collision.h"
  "Text/Text.cpp"			   "Text/Text.h"
  "Vector2/Vector2.cpp"		   "Vector2/Vector2.h"
)

# Link libraries so they are visible for the project
target_link_libraries(RocketAdventure SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(RocketAdventure SDL2_image::SDL2_image)
target_link_libraries(RocketAdventure SDL2_ttf::SDL2_ttf)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RocketAdventure PROPERTY CXX_STANDARD 20)
endif()

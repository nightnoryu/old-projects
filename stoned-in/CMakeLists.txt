# CMake version
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Project name
project(stoned-in)

# Add our game files
set(SOURCES
    src/main.cpp
    src/Bullet.cpp
    src/BulletsContainer.cpp
    src/Game.cpp
    src/Player.cpp
    src/Utils.cpp
    src/Animation.cpp
    src/Map.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Set up SFML packages
set(SFML_STATIC_LIBRARIES TRUE)
find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)

# Set C++ version and SFML definitions
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${JPEG_LIBRARIES} ${FREETYPE_LIBRARIES})
include_directories(${SFML_INCLUDE_DIR})

# Copy assets to the binary directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

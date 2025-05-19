cmake_minimum_required(VERSION 3.14)
project(TrashFight VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source directories
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(CLIENT_DIR "${SOURCE_DIR}/client")

# Find dependencies
find_package(nlohmann_json REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SunnyEngine REQUIRED)

# Find ENet using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ENET REQUIRED libenet)
if(NOT ENET_FOUND)
    message(FATAL_ERROR "ENet not found. Ensure ENet is installed.")
endif()

#------------------CLIENT------------------
# Client sources
file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS
    ${CLIENT_DIR}/*.cpp
)

add_executable(TrashFight ${CLIENT_SOURCES})

target_include_directories(TrashFight PRIVATE 
    ${CLIENT_DIR}
)

target_link_libraries(TrashFight PRIVATE
    SunnyEngine::SunnyEngine
    nlohmann_json::nlohmann_json
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
    ${ENET_LIBRARIES}
)

# Compile options
target_compile_options(TrashFight PRIVATE -Wall -Wextra -O2)

#cmake .. -DCMAKE_PREFIX_PATH=/home/arshia/.local

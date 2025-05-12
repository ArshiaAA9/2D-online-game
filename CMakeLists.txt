cmake_minimum_required(VERSION 3.14)
project(TrashFight VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library configuration
set(SUNNY_ENGINE_DIR "/home/arshia/.local")
set(SUNNY_ENGINE_LIB "${SUNNY_ENGINE_DIR}/lib/libSunnyEngine.a")  # Full correct path

# Verify library exists
if(NOT EXISTS ${SUNNY_ENGINE_LIB})
    message(FATAL_ERROR "SunnyEngine library not found at: ${SUNNY_ENGINE_LIB}")
endif()

# Source directories
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(CLIENT_DIR "${SOURCE_DIR}/client")
set(SERVER_DIR "${SOURCE_DIR}/server")
set(COMMON_DIR "${SOURCE_DIR}/common")

# Find dependencies
find_package(nlohmann_json REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

# Find ENet using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ENET REQUIRED libenet)
if(NOT ENET_FOUND)
    message(FATAL_ERROR "ENet not found. Ensure ENet is installed (e.g., 'sudo pacman -S enet').")
endif()

#------------------CLIENT------------------
# Client sources
file(GLOB CLIENT_SOURCES
    "${CLIENT_DIR}/main.cpp"
    "${CLIENT_DIR}/events/*.cpp"
    "${CLIENT_DIR}/game/*.cpp"
    "${CLIENT_DIR}/rendering/*.cpp"
    "${CLIENT_DIR}/settings/*.cpp"
    "${CLIENT_DIR}/networking/*.cpp"
)

add_executable(TrashFight ${CLIENT_SOURCES})

target_include_directories(TrashFight PRIVATE 
    ${CLIENT_DIR}
    ${COMMON_DIR}
    ${SERVER_DIR}
    ${SUNNY_ENGINE_DIR}/include  # Headers should be in include/SunnyEngine/
)

target_link_libraries(TrashFight PRIVATE
    ${SUNNY_ENGINE_LIB}  # Use full path variable
    nlohmann_json::nlohmann_json
    SDL3::SDL3 
    SDL3_ttf::SDL3_ttf
    ${ENET_LIBRARIES}
)

#------------------SERVER------------------
file(GLOB SERVER_SOURCES
    "${SERVER_DIR}/main.cpp"
    "${SERVER_DIR}/networking/*.cpp"
)

add_executable(TrashFightServer ${SERVER_SOURCES})

target_include_directories(TrashFightServer PRIVATE
    ${SERVER_DIR}
    ${COMMON_DIR}
    ${CLIENT_DIR} # For rendering/events
    ${ENET_INCLUDE_DIRS}
)

target_link_libraries(TrashFightServer PRIVATE
    ${ENET_LIBRARIES}
    SDL3::SDL3 # Needed for rendering/events
)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Compile options
target_compile_options(TrashFight PRIVATE -Wall -Wextra -O2)
target_compile_options(TrashFightServer PRIVATE -Wall -Wextra -O2)








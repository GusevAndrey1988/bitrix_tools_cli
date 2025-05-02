cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(EXPORT_COMPILE_COMMANDS ON)

project(bitrix_tools_cli VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_Declare(
    jinja2
    GIT_REPOSITORY https://github.com/flexferrum/Jinja2Cpp.git
    GIT_TAG e97a54e51336938470eacb4ce261bde903e22e54 # 1.3.2
)

set(BOOST_INCLUDE_LIBRARIES program_options)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG 199ef13d6034c85232431130142159af3adfce22 # boost-1.88.0
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(json jinja2 Boost)

file(COPY "${PROJECT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/config" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(bitrix_tools_cli)

target_sources(bitrix_tools_cli PUBLIC ${SRC_FILES})

target_include_directories(bitrix_tools_cli
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)

target_link_libraries(bitrix_tools_cli
    PRIVATE
        nlohmann_json::nlohmann_json
        jinja2cpp
        Boost::program_options
)

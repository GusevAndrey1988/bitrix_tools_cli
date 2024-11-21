cmake_minimum_required(VERSION 3.30)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(EXPORT_COMPILE_COMMANDS)

project(bitrix_tools_cli VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

file(COPY "${PROJECT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(bitrix_tools_cli)

target_sources(bitrix_tools_cli
    PUBLIC "${PROJECT_SOURCE_DIR}/src/main.cpp"
    PUBLIC "${PROJECT_SOURCE_DIR}/src/command_manager.cpp"
    PUBLIC "${PROJECT_SOURCE_DIR}/src/template.cpp"
    PUBLIC "${PROJECT_SOURCE_DIR}/src/commands/create_default_config_cmd.cpp"
    PUBLIC "${PROJECT_SOURCE_DIR}/src/commands/generate_component_cmd.cpp"
)

target_include_directories(bitrix_tools_cli
    PUBLIC "${PROJECT_SOURCE_DIR}/headers"
)

target_link_libraries(bitrix_tools_cli
    PRIVATE
        nlohmann_json::nlohmann_json
)
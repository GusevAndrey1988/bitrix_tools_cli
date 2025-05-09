cmake_minimum_required(VERSION 3.26)

set(EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fPIC)
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

project(bitrix_tools_cli VERSION 0.0.1)

set(BUILD_TYPE_DIR "release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_DIR "debug")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${BUILD_TYPE_DIR}/bin)

set(APPLICATION_DIR "${CMAKE_PROJECT_NAME}")

set(APPLICATION_ETC_DIR "../etc/${APPLICATION_DIR}")

include(FetchContent)
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.86.0
)

FetchContent_MakeAvailable(boost)

set(BOOST_LIBRARIES program_options)

file(COPY "${PROJECT_SOURCE_DIR}/resources/templates" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_ETC_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/resources/config" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APPLICATION_ETC_DIR}")

configure_file("${PROJECT_SOURCE_DIR}/config/variables.in" "${PROJECT_SOURCE_DIR}/include/generated/variables.h")

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

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(thirdparty/json)

add_subdirectory(thirdparty/jinja2cpp)
set (JINJA2CPP_INSTALL CACHE BOOL {} FALSE)

install(TARGETS bitrix_tools_cli DESTINATION "opt/bitrix_tools_cli/bin")
install(DIRECTORY resources/ DESTINATION "opt/bitrix_tools_cli/etc")

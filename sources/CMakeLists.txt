file (GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/sources/main.cpp
    ${CMAKE_SOURCE_DIR}/sources/**/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

#PCH support
#NOTE: Unlike VS, in CMake you don't need to include pch.h in any source files
target_precompile_headers(${PROJECT_NAME} PUBLIC pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
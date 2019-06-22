cmake_minimum_required(VERSION 3.0.0)

project(DataStructure VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_BUILD_TYPE Debug)

# Set C++0X
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_DEFAULT 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Qt5Core)

# Create a list with all .cpp source files
set( project_sources
     main.cpp
     node.cpp
     binaryTree.cpp
     graph.cpp
)

# Create executable with all necessary source files
add_executable(${PROJECT_NAME}
               ${project_sources}
)

target_link_libraries(${PROJECT_NAME} Qt5::Core)

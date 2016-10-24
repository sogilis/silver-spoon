cmake_minimum_required(VERSION 2.8)
project(silver_spoon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

################################################################################
#PACKAGES
find_package(OpenCV REQUIRED)

################################################################################
#INCLUDES
include_directories(
    include
)

################################################################################
#SOURCES
file(GLOB_RECURSE SILVER_SPOON_SRC "src/SilverSpoon/*.cpp")

################################################################################
#LINK
LIST(APPEND LINK_LIBS
    ${OpenCV_LIBS}
)

################################################################################
#EXECUTABLE
add_executable(${PROJECT_NAME} ${SILVER_SPOON_SRC} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})

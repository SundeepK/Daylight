cmake_minimum_required(VERSION 2.6)
project(Daylight)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")
set(SHAD "${PROJECT_SOURCE_DIR}/shaders/")

set(SRC "${PROJECT_SOURCE_DIR}/src/")

# Define sources and executable
set(EXECUTABLE_NAME Daylight)
set(DAYLIGHT_SOURCES "${SHAD}blur_x.frag"  "${SHAD}blur_y.frag" "${SHAD}lightFs.frag" "${SRC}DirectionalLight.cpp" "${SRC}Intersect.cpp" "${SRC}IntersectFinder.cpp" "${SRC}Light.cpp" "${SRC}LightEngine.cpp" "${SRC}SpotLight.cpp" "${SRC}VectorMath.cpp" "${SRC}ClosestIntersectionFinder.cpp" "${SRC}main.cpp")
#file(GLOB DAYLIGHT_SOURCES *.cpp)
add_executable(${EXECUTABLE_NAME} ${DAYLIGHT_SOURCES})

file(COPY ${SHAD} DESTINATION "shaders")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
include(CPack)

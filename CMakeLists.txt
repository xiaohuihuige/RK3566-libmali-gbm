cmake_minimum_required(VERSION 3.10)
project(gbm_es2_demo)

option(GLES_TRIANGLE_DEMO "Build shared libraries" ON)
option(GLES_CAMERA_DEMO "Build shared libraries" OFF)

if(GLES_TRIANGLE_DEMO)
    add_definitions(-DGLES_TRIANGLE_DEMO)
endif()

if(GLES_CAMERA_DEMO)
    add_definitions(-DGLES_CAMERA_DEMO)
endif()

add_definitions(-DSTB_IMAGE_IMPLEMENTATION)

set(CMAKE_C_STANDARD 99) 
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(GLOB all_SRC
    "./src/gles_demo/*.h"
    "./src/gles_demo/*.c"
    "./src/gles_util/*.h"
    "./src/gles_util/*.c"
    "./src/*.h"
    "./src/*.c"
    "*.c"
)

include (FindPkgConfig)

pkg_check_modules (DRM libdrm)
pkg_check_modules (GBM gbm)
pkg_check_modules (EGL egl)
pkg_check_modules (GLESV2 glesv2)
#pkg_check_modules (MALI libmali)

include_directories(
    ${DRM_INCLUDE_DIRS}
    ${GBM_INCLUDE_DIRS}
    ${EGL_INCLUDE_DIRS}
    ${GLESV2_INCLUDE_DIRS}
    ${CUSTOM_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/gles_demo
    ${CMAKE_SOURCE_DIR}/src/gles_util
)

set(LIBS ${LIBS} ${DRM_LIBRARIES} ${GBM_LIBRARIES} ${EGL_LIBRARIES} ${GLESV2_LIBRARIES})

add_executable(gbm_es2_demo ${all_SRC})

target_link_libraries(gbm_es2_demo "-lmali" "-lm" ${LIBS} )

MESSAGE("gbm_es2_demo links " ${LIBS})
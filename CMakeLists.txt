cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/cmake)
include(pj-init)

project(forestanza VERSION ${REPO_VERSION})

include(pj-common)
add_subdirectory(ext)

include(pj-flags)
add_subdirectory(mod)

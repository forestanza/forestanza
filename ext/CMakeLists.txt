# BUG: ignored
# set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE CACHE INTERNAL "")

### curlcpp {{{1
find_package(CURL "7.28.0" REQUIRED)
include_directories(${CURL_INCLUDE_DIRS} curlcpp/include)
add_subdirectory(curlcpp/src)
set(CURLCPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/curlcpp/include PARENT_SCOPE)
set(CURLCPP_LIBRARIES curlcpp PARENT_SCOPE)
# ALT:(w/o find/include_dir)
# set(curlcpp CACHE INTERNAL "")
# add_subdirectory(curlcpp)

### cpr {{{1
cmake_policy(PUSH)
set(CMAKE_POLICY_DEFAULT_CMP0048 OLD CACHE INTERNAL "")
# BUG: cmake_policy() is reset on call cmake_minimum_required()
# cmake_policy(VERSION 2.8.7)

option(USE_SYSTEM_CURL "" ON)
option(BUILD_CPR_TESTS "" OFF)
# option(CMAKE_USE_OPENSSL "" ON)

if(CMAKE_CROSSCOMPILING AND WIN32 AND MINGW)
  # NOTE:BAD:(wine) yandex is broken for verifypeer if on
  # BUT:(wine) baidu won't work w/o it at all
  #   https://github.com/jimhester/gmailr/issues/44
  option(INSECURE_CURL "" ON)
endif()

add_subdirectory(cpr)  # EXCLUDE_FROM_ALL
cmake_policy(POP)
# }}}


### json {{{1
set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json PARENT_SCOPE)
# }}}

# BUG: ignored
# set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS TRUE CACHE INTERNAL "")

find_package(CURL REQUIRED)

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

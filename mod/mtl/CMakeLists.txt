include(mod-pj)

include_directories(SYSTEM ${CPR_INCLUDE_DIRS} ${CURLCPP_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

set(LIBS ${CPR_LIBRARIES} ${CURLCPP_LIBRARIES})
include(mod-all)

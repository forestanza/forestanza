include_directories(SYSTEM ${CPR_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})

include(mod-tmpl)

target_link_libraries(${NM} ${CPR_LIBRARIES})

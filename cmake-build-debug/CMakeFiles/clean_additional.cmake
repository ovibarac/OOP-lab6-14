# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/qtlab10_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/qtlab10_autogen.dir/ParseCache.txt"
  "qtlab10_autogen"
  )
endif()

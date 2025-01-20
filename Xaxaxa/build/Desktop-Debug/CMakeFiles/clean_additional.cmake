# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appXaxaxa_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appXaxaxa_autogen.dir/ParseCache.txt"
  "appXaxaxa_autogen"
  )
endif()

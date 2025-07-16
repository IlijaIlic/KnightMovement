# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\KnightMovement_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\KnightMovement_autogen.dir\\ParseCache.txt"
  "KnightMovement_autogen"
  )
endif()

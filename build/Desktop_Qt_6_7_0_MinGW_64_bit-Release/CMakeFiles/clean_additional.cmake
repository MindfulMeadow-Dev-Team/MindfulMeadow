# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\MindfulMeadow_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MindfulMeadow_autogen.dir\\ParseCache.txt"
  "MindfulMeadow_autogen"
  )
endif()

set(MY_SOURCES
  src/policy/bintPolicy.cpp
  src/policy/bstrPolicy.cpp
  src/policy/blistPolicy.cpp
  src/policy/bdictPolicy.cpp
  )

#add_executable(bencode ${MY_SOURCES})
add_library(bencode SHARED ${MY_SOURCES})
target_include_directories(bencode PRIVATE src/)
target_include_directories(bencode PUBLIC include/)

cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("index_utilites")

file (GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
add_library(index_utilites STATIC ${SOURCES})
target_include_directories(index_utilites PUBLIC "include/public")
target_include_directories(index_utilites PRIVATE "include/private")

set_property(TARGET index_utilites PROPERTY CXX_STANDARD 20)

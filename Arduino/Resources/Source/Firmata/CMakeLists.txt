cmake_minimum_required (VERSION 3.15)

project (ModelicaFirmata)

# Set platform-specific variables and flags
if (WIN32)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  add_definitions(-DWINDOWS -D_CRT_SECURE_NO_WARNINGS)
  if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(PLATFORM win64)
  else ()
    set(PLATFORM win32)
  endif ()
elseif (UNIX)
  set(PLATFORM x86_64-linux)
  add_definitions(-DLINUX)
  # Additional flags for GCC or Clang could be added here
endif ()

# Define the ModelicaFirmata library
add_library(ModelicaFirmata SHARED 
  FirmataConnection.cpp
  FirmataConnection.h
  ModelicaFirmata.cpp
  ModelicaFirmata.h
  serial.cpp
  serial.h
  ../../Include/ModelicaUtilityFunctions.c
  ../Arduino/ModelicaUtilities.cpp
)

target_compile_definitions(ModelicaFirmata PUBLIC
  WINDOWS
  _CRT_SECURE_NO_WARNINGS
)


#set_property(TARGET ModelicaFirmata PROPERTY
#  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Include directories
target_include_directories(ModelicaFirmata PUBLIC
  .
  ../../Include
  ../../Sketches
  ../Arduino
)

# Post-build command to copy the library file to the appropriate directory
add_custom_command(TARGET ModelicaFirmata POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
  "$<TARGET_FILE:ModelicaFirmata>"
  "${CMAKE_CURRENT_SOURCE_DIR}/../../Library/${PLATFORM}"
)

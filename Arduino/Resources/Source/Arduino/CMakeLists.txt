cmake_minimum_required (VERSION 3.15)

project (Arduino)

# Determine the platform
set(PLATFORM x86_64-linux)

file(GLOB SRC_FILES *.h *.cpp)

add_library(ModelicaArduino SHARED ${SRC_FILES})

target_compile_definitions(ModelicaArduino PUBLIC
  ARDUINO=100
)

target_include_directories(ModelicaArduino PUBLIC
  .
  ../../Include
  ../../Sketches
)

add_custom_command(TARGET ModelicaArduino POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:ModelicaArduino>" "${CMAKE_CURRENT_SOURCE_DIR}/../../Library/${PLATFORM}/ModelicaArduino.so"
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:ModelicaArduino>" "${CMAKE_CURRENT_SOURCE_DIR}/../../Library/${PLATFORM}/libModelicaArduino.so"
)
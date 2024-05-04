cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(fan_test)

file(GLOB_RECURSE SRC_FILES
  main/*.c
)

target_sources(app PRIVATE ${SRC_FILES})

include_directories(
  main/hw/driver
  main/mw/zigbee
)

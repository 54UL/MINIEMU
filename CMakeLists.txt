cmake_minimum_required(VERSION 3.1)
project(MINEMU C)

# MINEMU MODULES
add_subdirectory(src/Core)
add_subdirectory(src/Chip8)
add_subdirectory(src/App)

# APP EXECUTABLE TARGET
add_executable(MINEMU "src/main.c")
target_link_libraries(MINEMU PUBLIC Core App Chip8)


# Custom targets
#add_custom_target(BUILD_MINEMU_APP
#    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target src/App
#)
#add_custom_target(BUILD_MINEMU_EMULATORS
#    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target src/Chip8
#)
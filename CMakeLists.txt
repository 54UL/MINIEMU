cmake_minimum_required(VERSION 3.1)
project(MINEMU)

# BUILD CONFIGS
set(MINEMU_TESTS OFF)

# gtests
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# MINEMU MODULES
add_subdirectory(src/Core)
add_subdirectory(src/Chip8)
add_subdirectory(src/App)

if (MINEMU_TESTS) 
  # TEST EXECUTABLE TARGET
  message("MINEMU TESTS TARGET")
  add_subdirectory(src/Tests)
else()
  # APP EXECUTABLE TARGET
  message("MINEMU EXECUTABLE")
  add_executable(MINEMU "src/main.c")
  target_compile_options(MINEMU PUBLIC -Wall -Wextra)
  target_link_libraries(MINEMU PUBLIC Core Chip8)

  if(PSP)
  message("PSP TOOLCHAIN FOUND, CREATING PBP FILE")

    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
    )
else()
    message("PSP TOOLCHAIN NOT FOUND")
endif()

endif()

# TODO ADD CUSTOM TARGETS
# Custom targets
#add_custom_target(BUILD_MINEMU_APP
#    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target src/App
#)
#add_custom_target(BUILD_MINEMU_EMULATORS
#    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target src/Chip8
#)
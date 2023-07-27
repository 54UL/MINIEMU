project(App C)
set(CMAKE_C_COMPILER "gcc")

message("Configuring MINEMU APP...")

# DEPENDENCIES

# SDL
find_package(SDL2 REQUIRED)

# List all the source files of the App
set(APP_SOURCES
    include/App.h
    include/EmulatorShell.h
    include/SDL_TinyApp.h
    SDL_TinyAppImpl/SDL_TinyApp.c
    UI/EmulatorShell.c
    UI/Fonts/Default_7x8.h
)

# Create the app library (used in parent cmake to build the app)
add_library(App STATIC
    ${APP_SOURCES}
)

# Compile options
target_compile_options(App PUBLIC -std=c11 -Wall -Wextra)

# Include directories for App
target_include_directories(App PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add additional include directories for UI and UI fonts
target_include_directories(App PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/UI
    ${CMAKE_CURRENT_SOURCE_DIR}/UI/Fonts
)

# Link any necessary libraries (e.g., SDL)
target_link_libraries(App PRIVATE SDL2 Core)


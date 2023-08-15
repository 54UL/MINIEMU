project(App)
# set(CMAKE_C_COMPILER "gcc")

# PACKAGES
find_package(SDL2 REQUIRED)

# List all the source files of the App
set(APP_SOURCES
    UI/Fonts/Default_7x8.h
    SDL_TinyAppImpl/SDL_TinyApp.h
    SDL_TinyAppImpl/SDL_TinyApp.c
    UI/EmulatorShell.h
    UI/EmulatorShell.c
    include/App.h
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

# Link any necessary libraries
target_link_libraries(App PUBLIC SDL2 Core)


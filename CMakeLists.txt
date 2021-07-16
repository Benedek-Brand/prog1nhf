cmake_minimum_required(VERSION 3.17)
project(nhz C)

set(CMAKE_C_STANDARD 99)

add_executable(nhz main.c animacio.c animacio.h vezerles.c felszabadito.c Mezok_kezelese.c Minden_inicializalasi_elem.c rajzok.c SDL_letrehozas.c structurak.h utkereses.c utkereses.h)
target_link_libraries(nhz m)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
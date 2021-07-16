cmake_minimum_required(VERSION 3.17)
project(nhz C)

set(CMAKE_C_STANDARD 99)


add_executable(nhz src/main.c src/animacio.c headers/animacio.h src/vezerles.c src/felszabadito.c src/Mezok_kezelese.c src/Minden_inicializalasi_elem.c src/rajzok.c src/SDL_letrehozas.c headers/structurak.h src/utkereses.c headers/utkereses.h headers/debugmalloc.h headers/felszabadito.h headers/Mezok_kezelese.h headers/Minden_inicializalasi_elem.h headers/rajzok.h headers/SDL_letrehozas.h headers/vezerles.h)
target_link_libraries(nhz m)
INCLUDE(FindPkgConfig)

include_directories(src)
include_directories(headers)
include_directories(textures)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2GFX REQUIRED SDL2_gfx)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2GFX_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

#include "SDL_letrehozas.h"

void sdl_init(SDL_Window **pwindow, SDL_Renderer **prenderer,int Width,int Height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width,
                                          Height, SDL_WINDOW_FULLSCREEN_DESKTOP);//SDL_WINDOW_FULLSCREEN_DESKTOP
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderSetLogicalSize(renderer, Width, Height);

    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}
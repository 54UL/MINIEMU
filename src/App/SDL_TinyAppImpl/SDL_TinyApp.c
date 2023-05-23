#include "SDL_TinyApp.h"
#include <SDL2/SDL.h>

static SDL_Window *s_window;
static SDL_Renderer *s_renderer;
static unsigned int *s_pixels;
static SDL_Texture *s_screen_texture;
static int s_width, s_height;
static SDL_Event event;

#define SCREEN_FACTOR 10

void Init_SDL(uint16_t w, uint16_t h)
{
    SDL_Init(SDL_INIT_VIDEO);

    s_window = SDL_CreateWindow("CC8",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                w, h,
                                SDL_WINDOW_RESIZABLE);

    s_renderer = SDL_CreateRenderer(s_window,
                                    -1, SDL_RENDERER_PRESENTVSYNC);

    s_width = w;
    s_height = h;

    // Since we are going to display a low resolution buffer
    // it is best to limit the window size so that it cannot
    // be smaller than our internal buffer size.
    SDL_SetWindowMinimumSize(s_window, s_width * SCREEN_FACTOR, s_height * SCREEN_FACTOR);
    SDL_RenderSetLogicalSize(s_renderer, s_width * SCREEN_FACTOR, s_height * SCREEN_FACTOR);
    SDL_RenderSetIntegerScale(s_renderer, 1);

    s_screen_texture = SDL_CreateTexture(s_renderer,
                                         SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                         s_width, s_height);

    s_pixels = calloc(s_width * s_height, sizeof(int));

    //Randomize the buffer (ready state)
    int i = 0,j = 0;
    for (i = 0; i < s_height; i++) 
    {
        for (j = 0; j < s_width; j++)
        {
             s_pixels[i+j*s_height] = rand() % 0xffffff;
        }
    }

    // Register basic callbacks
}


uint8_t Step_SDL(StepCallBack renderCallback, ActionCallback actionsCallback)
{
    //Consider to put this in a thread
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                return 0;

            case SDL_KEYDOWN:
                actionsCallback(event.key.keysym.sym);
                break;
    
            default:
                break;
        }
    }

    //middle-ware like code
    renderCallback(s_pixels);

    // It's a good idea to clear the screen every frame,
    // as artifacts may occur if the window overlaps with
    // other windows or transparent overlays.
    SDL_RenderClear(s_renderer);
    SDL_UpdateTexture(s_screen_texture, NULL, s_pixels, s_width * 4);
    SDL_RenderCopy(s_renderer, s_screen_texture, NULL, NULL);
    SDL_RenderPresent(s_renderer);
    return 1;
}

void Reset_SDL(void)
{
    // TODO
    free(s_pixels);
}

void Exit_SDL_App(void)
{
    // TODO
}


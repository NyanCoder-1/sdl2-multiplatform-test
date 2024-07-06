#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL.h>
#include <SDL_ttf.h>
#else // __EMSCRIPTEN__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif // __EMSCRIPTEN__
#include <filesystem>
#include <iostream>
#include <sstream>

bool quit = false; // Main loop flag
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surfaceTextScreenSize;
TTF_Font *fontSans;
int surfaceWidth = 512, surfaceHeight = 512;

void cleanup()
{
    if (surfaceTextScreenSize) {
        SDL_FreeSurface(surfaceTextScreenSize);
        surfaceTextScreenSize = nullptr;
    }
    if (fontSans) {
        TTF_CloseFont(fontSans);
        fontSans = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void mainLoop()
{
    // Event handler
    SDL_Event e;
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                SDL_RenderSetViewport(renderer, NULL);
                surfaceWidth = e.window.data1;
                surfaceHeight = e.window.data2;
                {
                    SDL_Color colorWhite = {255, 255, 255};
                    std::stringstream strScreenSize;
                    strScreenSize << "Screen size: " << surfaceWidth << "x" << surfaceHeight;
                    SDL_FreeSurface(surfaceTextScreenSize);
                    surfaceTextScreenSize = TTF_RenderUTF8_Blended(fontSans, strScreenSize.str().c_str(), colorWhite);
                    std::cout << strScreenSize.str() << std::endl;
                }
                break;
            }
            break;
        }
    }

    SDL_Texture *textureScreenSizeText = SDL_CreateTextureFromSurface(renderer, surfaceTextScreenSize);
    int w = surfaceTextScreenSize->w ? surfaceTextScreenSize->w : 200;
    int h = surfaceTextScreenSize->h ? surfaceTextScreenSize->h : 100;
    SDL_Rect rectTextureScreenSizeText = {
        .x = 0,
        .y = 0,
        .w = w,
        .h = h
    };

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureScreenSizeText, NULL, &rectTextureScreenSizeText);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(textureScreenSizeText);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(surfaceWidth, surfaceHeight, SDL_WINDOW_RESIZABLE, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0x3f, 0x3f, 0, 255);
    if (TTF_Init())
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
    fontSans = TTF_OpenFont((std::filesystem::current_path()/".."/"assets"/"roboto-regular.ttf").c_str(), 24);
    if (!fontSans) {
        std::cerr << "Couldn't open ttf font file: " << (std::filesystem::current_path()/".."/"assets"/"roboto-regular.ttf").c_str() << " with error \"" << TTF_GetError() << "\"" << std::endl;
        exit(EXIT_FAILURE);
    }
    TTF_SetFontHinting(fontSans, TTF_HINTING_LIGHT_SUBPIXEL);
    SDL_Color colorWhite = {255, 255, 255};
    {
        std::stringstream strScreenSize;
        strScreenSize << "Screen size: " << surfaceWidth << "x" << surfaceHeight;
        surfaceTextScreenSize = TTF_RenderUTF8_Blended(fontSans, strScreenSize.str().c_str(), colorWhite);
        std::cout << strScreenSize.str() << std::endl;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainLoop, 0, 1);
#else  // __EMSCRIPTEN__

    // While application is running
    while (!quit)
    {
        mainLoop();
    }

    cleanup();
#endif // __EMSCRIPTEN__

    return 0;
}
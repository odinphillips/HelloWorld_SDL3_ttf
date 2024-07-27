#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static int Init() {
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        SDL_Log("SDL_Init() Error: %s", SDL_GetError());
        return -1;
    }
    
    ret = TTF_Init();
    if (ret < 0) {
        SDL_Log("TTF_Init() Error: %s", TTF_GetError());
        return -1;
    }

    window = SDL_CreateWindow("HelloWorld SDL3 ttf", 640, 480, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow() Error: ", SDL_GetError());
        return -1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer() Error: ", SDL_GetError());
        return -1;
    }

    return 0;
}

static void Term() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

static void Start() {
    SDL_Event event;
    SDL_bool running = SDL_TRUE;

    TTF_Font* font = TTF_OpenFont("fonts/courgette/Courgette-Regular.ttf", 32);
    if (font == NULL) {
        SDL_Log("TTF_OpenFont() Error: %s", TTF_GetError());
        return;
    }

    // main loop
    while (running) {
        // go through all pending events until there are no more
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: // triggered on window close
                    running = SDL_FALSE;
                    break;
                case SDL_EVENT_KEY_DOWN: // triggered when user presses ESC key
                    if (event.key.key == SDLK_ESCAPE) {
                        running = SDL_FALSE;
                    }
            }
        }

        // set background color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // for SDL_RenderClear()

        // clear the window to red fade color
        SDL_RenderClear(renderer);

        SDL_Color White = {200, 200, 200};
        SDL_Surface* surface = TTF_RenderText_Blended(font, "HelloWorld SDL3 TTF", White); // TODO: destroy surface?
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // ! Crashed on/before? shutdown from thisline's mem alloc??? 
        SDL_DestroySurface(surface);
        SDL_FRect dstRect{100, 100, 200, 80}; // x, y, w, h
        SDL_RenderTexture(renderer, texture, NULL, &dstRect);
        SDL_DestroyTexture(texture); // ? Is this safe to do here ?

        // draw everything to screen
        SDL_RenderPresent(renderer);
    }
    TTF_CloseFont(font);
}

int main(int argc, char* argv[]) {
    int ret = Init();
    if (ret == 0) {    
        Start();
    }
    Term();
    return ret;
}

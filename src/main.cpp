#include <SDL2/SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdio.h>

int main()
{

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) <0) printf("ERROR:%s\n",SDL_GetError());
    window = SDL_CreateWindow("sdl-test",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,500,0);
    if(window != NULL) {
        bool quit = false;
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        if(renderer == NULL) quit=true;
        else {
            SDL_SetRenderDrawColor(renderer,0,0,0,255);
        }
        SDL_Event event;
        SDL_Rect r;
        r.x=100,r.y=100,r.w=10,r.h=10;
        while(!quit) {

            while( SDL_PollEvent( &event ) != 0) {
                if( event.type == SDL_QUIT ) quit=true;
            }
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

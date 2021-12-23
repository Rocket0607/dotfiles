#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>

#include <stdbool.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} WindowInfo;

typedef struct {
    int top_pipe[2];
    int bottom_pipe[2];
} PipeCoords;

void init_SDL();
WindowInfo create_window(const char* p_window_title, int p_window_width, int p_window_height);
int* pipe_coords(int mid_coord);
SDL_Rect create_sdl_rect(int[4] dimensions /* x y w h */);


int main(int argc, char* argsp[]) 
{
    init_SDL();
    
    WindowInfo window_info = create_window("GAME", WINDOW_WIDTH, WINDOW_HEIGHT);
    
    bool game_running = true;
    SDL_Event event;

    SDL_Rect r = create_sdl_rect([50, 20, 50, 50]); // array values are [x, y, w, h]
    
    const int max_vel = 4;
    int vel = max_vel;
    
    while (game_running) {
        while (SDL_PollEvent(&event)) {
          switch (event.type) {
            case SDL_QUIT:
              game_running = false;
              break;
            case SDL_KEYDOWN:
              switch (event.key.keysym.sym)
              {
                  case SDLK_LEFT:  printf("left pressed\n"); break;
                  case SDLK_RIGHT: printf("right pressed\n"); break;
                  case SDLK_UP:    vel = -15; break;
                  case SDLK_DOWN:  printf("down pressed\n"); break;
              }
              break;
          }
        }
        
        SDL_SetRenderDrawColor(window_info.renderer, 255, 255, 255, 255);
        
        SDL_RenderClear(window_info.renderer);

        r.y += vel;
        if (vel < max_vel) {
          vel += 1;
        }

        // Set render color to blue ( rect will be rendered in this color )
        SDL_SetRenderDrawColor( window_info.renderer, 0, 0, 0, 255 );

        // Render rect
        SDL_RenderFillRect( window_info.renderer, &r );
        
        SDL_RenderPresent(window_info.renderer);

        SDL_Delay(8);
        
    }
    
    SDL_DestroyWindow(window_info.window);
    SDL_Quit();
    
    return 0;
    
}

void init_SDL() 
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        printf("SDL_init has failed. Error: %s\n", SDL_GetError());
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        printf("IMG_init has failed. Error: %s\n", SDL_GetError());
    }
}

WindowInfo create_window(const char* p_window_title, int p_window_width, int p_window_height)
{
    WindowInfo window_info;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    
    window = SDL_CreateWindow(p_window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_window_width, p_window_height, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        printf("Window failed to init. Error: %s \n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    window_info.window = window;
    window_info.renderer = renderer;
    
    return window_info;
}

int* pipe_coords(int mid_coord)
{
    PipeCoords pipe_coords;
    const int gap_size = 10;

    pipe_coords.top_pipe[0] = 0;
    pipe_coords.top_pipe[1] = mid_coord - gap_size / 2;

    pipe_coords.bottom_pipe[0] = SCREEN_HEIGHT;
    pipe_coords.bottom_pipe[1] = mid_coord + gap_size / 2;

    return pipe_coords;
}

SDL_Rect create_sdl_rect(int dimensions[4] /* x y w h */)
{
    SDL_Rect r;
    r.x = dimensions[0]
    r.y = dimensions[1]
    r.w = dimensions[2]
    r.h = dimensions[3]

    return r;
}

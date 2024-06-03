#include <stdio.h>
#include <SDL2/SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct rect {
    float x;
    float y;
    float width;
    float height;
} rect;

struct rect2 {
    float x;
    float y;
    float width;
    float height;
} rect2;


struct ball {
    float x;
    float y;
    float width;
    float height;
} ball;

float delta(){
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();
    return delta_time;
}

unsigned int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }

    int iWindowFlag = SDL_WINDOW_BORDERLESS;
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        iWindowFlag
    );
    if (!window) {
         fprintf(stderr, "Error creating SDL Window.\n");
         return FALSE;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
         fprintf(stderr, "Error creating SDL Renderer.\n");
         return FALSE;
    }
    
    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    SDL_PumpEvents();

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                game_is_running = FALSE;
            }else if (event.key.keysym.sym == SDLK_RIGHT){
                rect.y += 10;
            }else if (event.key.keysym.sym == SDLK_LEFT){
                rect.y -= 10;    
            }else if (event.key.keysym.sym == SDLK_d){
                rect2.y += 10;  
            }else if (event.key.keysym.sym == SDLK_a)
                rect2.y -= 10;  
            break;  
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_SPACE]){
        rect.y += 10;
        printf("a");
    }
}

void setup() {
    //Inicializar 
    rect.x = 170;
    rect.y = 20,
    rect.width = 6;
    rect.height = 55;

    rect2.x = 630;
    rect2.y = 20,
    rect2.width = 6;
    rect2.height = 55;
}

void update() {
    // Atualizar a tela

    //int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    //if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
    //    SDL_Delay(time_to_wait);
    //}

    
    //rect.x += 10.0f * delta();
    //rect.y += 10.0f * delta();
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Desenhar na tela
    SDL_Rect retan1 = { 
        (int)rect.x, 
        (int)rect.y, 
        (int)rect.width, 
        (int)rect.height
    };

    SDL_Rect retan2 = { 
        (int)rect2.x, 
        (int)rect2.y, 
        (int)rect2.width, 
        (int)rect2.height
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_RenderFillRect(renderer, &retan1);

    SDL_RenderFillRect(renderer, &retan2);

    SDL_RenderPresent(renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}
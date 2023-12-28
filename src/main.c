#include "include/common.h"

int main(void){
    int game_is_running = false;
    int last_frame_time = 0;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    Jogo meu_jogo;

    game_is_running = initialize_window(&window, &renderer, &font);

    setup(&meu_jogo);

    while (game_is_running) {
        process_input(&game_is_running, &meu_jogo);
        update(&last_frame_time, &game_is_running, &meu_jogo);
        render(renderer,&meu_jogo, font);
    }

    destroy_window(&window,&renderer, &font);

    return 0;
}
#include "include/common.h"

int main() {
    // Inicializa o SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar o SDL: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow("Solitaire Weverto_Jair", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erro ao criar a janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
    if (TTF_Init() != 0) {
    fprintf(stderr, "Erro ao inicializar SDL_ttf: %s\n", TTF_GetError());
    // Tratar o erro conforme necessário
    }

    Jogo meu_jogo;
    inicializar_jogo(&meu_jogo);

    char comando = '1';

    do {
        // Limpa o renderizador
        SDL_RenderClear(renderer);

        meu_jogo.start_time = SDL_GetTicks();

        game_run(&meu_jogo, &comando);
        renderizar_game(&meu_jogo, renderer);

        // Atualiza a janela
        SDL_RenderPresent(renderer);
        

    } while (comando != 0);

    // Libera recursos e finaliza o SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();

    return 0;
}

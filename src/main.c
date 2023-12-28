#include "include/common.h"             //inclue as bibliotecas gerais

//Função principal do código
int main(void) {
    // Variável que indica se o jogo está em execução
    int game_is_running = false;

    // Armazena o tempo do último frame para cálculos de delta time
    int last_frame_time = 0;

    // Ponteiros para a janela, o renderizador e a fonte do SDL
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    // Estrutura que representa o jogo
    Jogo meu_jogo;

    // Inicializa a janela, o renderizador e a fonte, e verifica se foi bem-sucedido
    game_is_running = initialize_window(&window, &renderer, &font);

    // Configura o estado inicial do jogo
    setup(&meu_jogo);

    // Loop principal do jogo
    while (game_is_running) {
        // Processa a entrada do usuário, atualiza o estado do jogo e renderiza
        process_input(&game_is_running, &meu_jogo);
        update(&last_frame_time, &game_is_running, &meu_jogo);
        render(renderer, &meu_jogo, font);
    }

    // Destrói a janela, o renderizador e a fonte ao sair do jogo
    destroy_window(&window, &renderer, &font);

    // Retorna 0 para indicar que o programa foi concluído com sucesso
    return 0;
}

// Inclui as bibliotecas necessárias
#include "include/common.h"             
#include <stdio.h>

/**
 * @brief Função principal do jogo para o nível específico.
 *
 * @param meu_jogo Ponteiro para a estrutura do jogo.
 * @return Retorna 0 ao sair do jogo.
 */
int nivel(Jogo *meu_jogo) {
    // Variável que indica se o jogo está em execução
    int game_is_running = false;


    // Armazena o tempo do último frame para cálculos de delta time
    int last_frame_time = 0;

    // Ponteiros para a janela, o renderizador e a fonte do SDL
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;

    // Inicializa a janela, o renderizador e a fonte, e verifica se foi bem-sucedido
    game_is_running = initialize_window(&window, &renderer, &font, meu_jogo->nivel);

    // Configura o estado inicial do jogo
    setup(meu_jogo);

    // Loop principal do jogo
    while (game_is_running) {
        // Processa a entrada do usuário, atualiza o estado do jogo e renderiza
        process_input(&game_is_running, meu_jogo);
        update(&last_frame_time, &game_is_running, meu_jogo);
        render(renderer, meu_jogo, font);
    }

    // Calcula o tempo decorrido após o primeiro comando '1'
    if (meu_jogo->start_time != 0) {
        time_t end_time = time(NULL);
        double tempo_decorrido = difftime(end_time, meu_jogo->first_command_time);

        printf("Tempo decorrido: %.2lf segundos\n", tempo_decorrido);
        printf("Número de jogadas: %d\n", meu_jogo->jogadas);
    }

    // Destrói a janela, o renderizador e a fonte ao sair do jogo
    destroy_window(&window, &renderer, &font);

    return 0;
}


// Função principal do programa
int main(void) {

    Jogo meu_jogo;

    char buffer[100];  // Buffer para armazenar caracteres inválidos
    int game_level =0;


    //pequeno menu para executar os niveis pedidos no trabalho
    while(game_level == 0)
    {
        printf("\nSolitario PG Trabalho 3:\n");
        printf("Qual nivel deseja jogar??\n");
        printf("Nivel 1 (DONE!)- pressione 1- \n");
        printf("Nivel 2 (em progresso..)- pressione 2- \n");
        printf("Nivel 3 (em progresso..)- pressione 3- \n");
        printf("Sair- pressione 0- \n");
        printf("Nivel:");
        if(scanf("%d", &game_level)!= 1)
        {
            // Limpa o buffer de entrada para evitar um loop infinito
            scanf("%s", buffer);
            printf("Erro, digite um parametro válido\n");
            game_level = 0;
            continue;
        }

        switch (game_level)
        {
        case 1:
            meu_jogo.nivel = 1;
            nivel(&meu_jogo);
            game_level = 0;
            break;
        case 2:
            meu_jogo.nivel = 2;
            nivel(&meu_jogo);
            game_level = 0;
            break;
        case 3:
            meu_jogo.nivel = 3;
            nivel(&meu_jogo);
            game_level = 0;
            break;
        case 0:
            game_level = -1;
            break;
        default:
            game_level = 0;
            break;
        }
    }

    
}


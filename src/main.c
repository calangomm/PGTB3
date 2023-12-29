<<<<<<< Updated upstream
#include "include/common.h"

int main() {
    printf("\n\nImprimindo Jogo:\n\n");
    Jogo meu_jogo;
    inicializar_jogo(&meu_jogo);
=======
#include "include/common.h"             //inclue as bibliotecas gerais
#include <stdio.h>

//Função principal do código nivel1
int nivel(Jogo *meu_jogo) {
    // Variável que indica se o jogo está em execução
    int game_is_running = false;
>>>>>>> Stashed changes

    char comando;

    do {
        printf("\n\nImprimindo Jogo:\n\n");
        imprimir_jogo(&meu_jogo);

<<<<<<< Updated upstream
        printf("\nEscolha uma opção:\n");
        printf("1 - Atualizar Descarte\n");
        printf("2 - Mover para Fundação\n");
        printf("0 - Sair\n");

        printf("Comando: ");
        scanf(" %c", &comando);

        switch (comando) {
            case '1':
                atualizar_descarte(&meu_jogo);

                // Inicia o temporizador no primeiro comando '1'
                if (meu_jogo.start_time == 0) {
                    meu_jogo.start_time = time(NULL);
                    meu_jogo.first_command_time = meu_jogo.start_time;
                }

                meu_jogo.jogadas++;
                break;

            case '2':
                if (!mover_para_fundacao(&meu_jogo)) {
                    printf("Não foi possível mover para a fundação.\n");
                 } else {
                    meu_jogo.jogadas++;  // Incrementa a contagem de jogadas
                }
                break;
            case '0':
                printf("Saindo do jogo.\n");
                break;
=======
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
>>>>>>> Stashed changes

            default:
                printf("Comando inválido. Tente novamente.\n");
        }

        limpar_buffer();  // Limpar o buffer de entrada
        limpar_terminal(); //limpa terminal
        if(checagem_fim_de_jogo(&meu_jogo)){
            break;
        }
        

    } while (comando != '0');

    // Calcula o tempo decorrido após o primeiro comando '1'
    if (meu_jogo.start_time != 0) {
        time_t end_time = time(NULL);
        double tempo_decorrido = difftime(end_time, meu_jogo.first_command_time);

        printf("Tempo decorrido: %.2lf segundos\n", tempo_decorrido);
        printf("Número de jogadas: %d\n", meu_jogo.jogadas);
    }
    return 0;
}


//Função principal do código
int main(void) {

    Jogo meu_jogo;

    char buffer[100];  // Buffer para armazenar caracteres inválidos
    int game_level =0;

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


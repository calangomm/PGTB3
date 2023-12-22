#include "include/common.h"

int main() {
    printf("\n\nImprimindo Jogo:\n\n");
    Jogo meu_jogo;
    inicializar_jogo(&meu_jogo);

    char comando;

    do {
        printf("\n\nImprimindo Jogo:\n\n");
        imprimir_jogo(&meu_jogo);

        printf("\nEscolha uma opção:\n");
        printf("1 - Atualizar Descarte\n");
        printf("2 - Mover para Fundação\n");
        printf("0 - Sair\n");

        printf("\n\n");

        printf("Número de jogadas: %d\n", meu_jogo.jogadas);
        printf("Pontuação: %d\n", meu_jogo.pontuacao);

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
        printf("Pontuação: %d\n", meu_jogo.pontuacao);
    }
    return 0;
}

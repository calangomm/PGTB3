#include "include/common.h"

int main() {
    // Inicializa uma instância da estrutura Jogo
    Jogo meu_jogo;
    inicializar_jogo(&meu_jogo);

    // Variável para armazenar o comando do jogador
    char comando;

    // Loop principal do jogo
    do {
        // Exibe o estado atual do jogo
        printf("\n\nImprimindo Jogo:\n\n");
        imprimir_jogo(&meu_jogo);

        // Exibe as opções de comando para o jogador
        printf("\nEscolha uma opção:\n");
        printf("1 - Atualizar Descarte\n");
        printf("2 - Mover para Fundação\n");
        printf("0 - Sair\n");

        // Solicita ao jogador que insira um comando
        printf("Comando: ");
        scanf(" %c", &comando);

        // Executa a ação correspondente ao comando
        switch (comando) {
            case '1':
                // Atualiza o descarte e inicia o temporizador no primeiro comando '1'
                atualizar_descarte(&meu_jogo);
                if (meu_jogo.start_time == 0) {
                    meu_jogo.start_time = time(NULL);
                    meu_jogo.first_command_time = meu_jogo.start_time;
                }
                meu_jogo.jogadas++;
                break;

            case '2':
                // Tenta mover uma carta para a fundação
                if (!mover_para_fundacao(&meu_jogo)) {
                    printf("Não foi possível mover para a fundação.\n");
                } else {
                    meu_jogo.jogadas++;  // Incrementa a contagem de jogadas
                }
                break;

            case '0':
                // Finaliza o jogo
                printf("Saindo do jogo.\n");
                break;

            default:
                // Mensagem para comando inválido
                printf("Comando inválido. Tente novamente.\n");
        }

        // Limpa o buffer de entrada
        limpar_buffer();

        // Limpa o terminal
        limpar_terminal();

        // Verifica se o jogo chegou ao fim
        if (checagem_fim_de_jogo(&meu_jogo)) {
            break;
        }

    } while (comando != '0');

    // Calcula o tempo decorrido após o primeiro comando '1'
    if (meu_jogo.start_time != 0) {
        time_t end_time = time(NULL);
        double tempo_decorrido = difftime(end_time, meu_jogo.first_command_time);

        // Exibe o tempo decorrido e o número de jogadas
        printf("Tempo decorrido: %.2lf segundos\n", tempo_decorrido);
        printf("Número de jogadas: %d\n", meu_jogo.jogadas);
    }

    return 0;
}

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

        printf("Comando: ");
        scanf(" %c", &comando);

        switch (comando) {
            case '1':
                atualizar_descarte(&meu_jogo);
                break;

            case '2':
                if (!mover_para_fundacao(&meu_jogo)) {
                    printf("Não foi possível mover para a fundação.\n");
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
        

    } while (comando != '0');

    return 0;
}
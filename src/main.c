#include "include/common.h"

<<<<<<< Updated upstream
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
=======
int game_is_running = false;

void update(Jogo *meu_jogo, int *game_is_running){
    //area jogavel
    if(mouse_last_cord.y >= Y_AREA_JOGAVEL_INI && mouse_last_cord.y <= Y_AREA_JOGAVEL_FINAL)
    {   
        //baralho
        if(mouse_last_cord.x >=  DIST_HEADER_LEFT && mouse_last_cord.x <= X_FINAL_BARALHO)atualizar_descarte(meu_jogo);
        //descarte
        else if(mouse_last_cord.x >=  X_INICIAL_DESCARTE && mouse_last_cord.x <= X_FINAL_DESCARTE)mover_para_fundacao(meu_jogo);
    }
    *game_is_running =checagem_fim_de_jogo(meu_jogo);    
}

int main() {
    Jogo meu_jogo;
    
    game_is_running = inicializar_window();
    printf("grafico inicializado com sucesso\n");

    setup(&meu_jogo);
    SDL_Event event;

    while(game_is_running){
        process_input(&game_is_running); // to implement
        if(mouse_last_cord.click == 1){
            update(&meu_jogo, &game_is_running);
            mouse_last_cord.click = 0;
        }
        render(&meu_jogo);       
>>>>>>> Stashed changes
    }
    return 0;
}

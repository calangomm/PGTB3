#include "include/common.h"

int game_is_running = false;
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

int inicializar_window(void){
    graph_init2("solitario", WINDOW_WIDTH, WINDOW_HEIGHT);
    graph_start();
    return true;
}


void setup(Jogo *meu_jogo){
    header.x = DIST_HEADER_LEFT;
    header.y = DIST_HEADER_TOP;
    header.width = HEADER_WIDTH;
    header.height = HEADER_HEIGHT;

    graph_baralho.x = DIST_HEADER_LEFT;
    graph_baralho.y = DIST_HEADER_TOP+HEADER_HEIGHT+DIST_CARD_HEADER;
    graph_baralho.width = CARD_WIDTH;
    graph_baralho.height = CARD_HEIGHT;

    inicializar_jogo(meu_jogo);
}


void process_input(Jogo *meu_jogo){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type){
        case SDL_QUIT:
            game_is_running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                game_is_running = false;
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                if(meu_jogo->game_Started==0)
                {
                    meu_jogo->game_Started = SDL_GetTicks();
                }
                //atualiza as coordenadas do mouse quando há clique
                mouse_last_cord.x = event.button.x;
                mouse_last_cord.y = event.button.y;
            }
    }
}


void update(Jogo *meu_jogo){
    //Logica para um time.step fixo
    //gasta tempo até ter terminado o frametime

    //logica do game
    //dentro da area de game
    if(mouse_last_cord.y >= graph_baralho.y && mouse_last_cord.y <= graph_baralho.y + CARD_HEIGHT){
        //area do baralho
        if(mouse_last_cord.x > DIST_HEADER_LEFT && mouse_last_cord.x <= X_FINAL_BARALHO){
            printf("Baralho Selecionado\n");
            atualizar_descarte(meu_jogo);
        }
        if(mouse_last_cord.x > X_INICIAL_DESCARTE && mouse_last_cord.x <= X_FINAL_DESCARTE){
            printf("Descarte Selecionado\n");
            mover_para_fundacao(meu_jogo);
        }
        if(mouse_last_cord.x > X_I_FUND1 && mouse_last_cord.x <= X_F_FUND1){
            printf("Fundação 1 Selecionado\n");
        }
        if(mouse_last_cord.x > X_I_FUND2 && mouse_last_cord.x <= X_F_FUND2){
            printf("Fundação 2 Selecionado\n");
        }
        if(mouse_last_cord.x > X_I_FUND3 && mouse_last_cord.x <= X_F_FUND3){
            printf("Fundação 3 Selecionado\n");
        }
        if(mouse_last_cord.x > X_I_FUND4 && mouse_last_cord.x <= X_F_FUND4){
            printf("Fundação 4 Selecionado\n");
        }
        mouse_last_cord.y = 0;
        mouse_last_cord.x = 0;
    }

    display_elapsed_time(meu_jogo);

    checagem_fim_de_jogo(meu_jogo);

    
}


void render(Jogo *jogo){
    graph_rect(0,
                0,
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                c_backgroung,
                true);

    graph_round_rect(header.x,
                    header.y,
                    header.width,
                    header.height,
                    c_backgroung,
                    true);


    /*// Fundo das cartas caso vazias
    for (int i = 0; i < 7; i++) {
        if(i==2)SDL_SetRenderDrawColor(renderer, 41,153,97,255);
        else SDL_SetRenderDrawColor(renderer, 20,120,50,255);
        SDL_RenderFillRect(renderer, );
    }

    SDL_RenderPresent(renderer);*/
    graph_refresh();

}

void destroy_window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main() {
    Jogo meu_jogo;


    game_is_running = inicializar_window();
    
    setup(&meu_jogo); //to do

    while(game_is_running){
        process_input(&meu_jogo);
        update(&meu_jogo);
        render(&meu_jogo);
    }

    destroy_window();


    return 0;
}
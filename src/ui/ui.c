
int inicializar_window(void){
    graph_init2("solitario", WINDOW_WIDTH, WINDOW_HEIGHT);
    return true;
}

void desenha_carta_header(Carta *carta, const char *path, int x, int y)
{
    printf("\nCarta desenhada num: %d, naipe %c, virada %d\n",carta->numero,"cdhs"[carta->naipe - 1], carta->virada);
    const char* caminho_da_carta = transform_card_to_path(carta, path);
    printf("caminho da carta - %s\n",caminho_da_carta);
    graph_image(caminho_da_carta, x, y, CARD_WIDTH, CARD_HEIGHT);
}


void render(Jogo *jogo){
    //background
    graph_rect(0, 0, graph_get_width(), graph_get_height(), C_BACKGROUND, TRUE);

    //header
    graph_rect( DIST_HEADER_LEFT,
                DIST_HEADER_TOP,
                HEADER_WIDTH,
                HEADER_HEIGHT,
                C_HEADER,
                TRUE);
    
    graph_card cartas_desenho;

    cartas_desenho.y = DIST_HEADER_TOP + HEADER_HEIGHT + DIST_CARD_HEADER;
    cartas_desenho.x = DIST_HEADER_LEFT;


    //desenha cartas
    for(int i = 0; i<7; i++)
    {
        switch (i)
        {
        case 0:
            if(jogo->baralho.indice>0){
                desenha_carta_header(&jogo->baralho.cartas[jogo->baralho.indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  graph_round_rect(cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 1:
            if(jogo->descarte.indice>0){
                desenha_carta_header(&jogo->descarte.cartas[jogo->descarte.indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  graph_round_rect(cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 3:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  graph_round_rect(cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 4:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  graph_round_rect(cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 5:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  graph_round_rect(cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 6:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  graph_round_rect(cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        }

        cartas_desenho.x = cartas_desenho.x + CARD_WIDTH + CARDS_DIST;
    }

    graph_refresh();
}

void destroy_window(void){
    void  graph_exit();	
}
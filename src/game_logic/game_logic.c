// game_logic/game_logic.c
#include "../include/common.h"
#include <stdlib.h>


void inicializar_carta(Carta *carta, int virada, int naipe, int numero) {
    carta->virada = virada;
    carta->naipe = naipe;
    carta->numero = numero;
}

void inicializar_deck(Deck *deck) {
    deck->indice = 0;

    for (int naipe = 1; naipe <= NUM_NAIPES; ++naipe) {
        for (int numero = 1; numero <= NUM_NUMEROS; ++numero) {
            inicializar_carta(&deck->cartas[deck->indice], 1, naipe, numero);
            deck->indice++;
        }
    }
}

void randomizar_deck(Deck *deck) {
    srand((unsigned int)time(NULL));
    // Embaralha as cartas usando o algoritmo de Fisher-Yates
    for (int i = NUM_CARTAS; i > 0; --i) {
        int j = rand() % (i + 1);
        // Troca as cartas i e j
        Carta temp = deck->cartas[i - 1];
        deck->cartas[i - 1] = deck->cartas[j];
        deck->cartas[j] = temp;
    }
}

void inicializar_jogo(Jogo *jogo) {
    inicializar_deck(&jogo->baralho);
    randomizar_deck(&jogo->baralho);

    jogo->descarte.indice = 0;
<<<<<<< Updated upstream
=======
    jogo->fundacao[0].indice = 0;
    jogo->fundacao[1].indice = 0;
    jogo->fundacao[2].indice = 0;
    jogo->fundacao[3].indice = 0;
    jogo->jogadas = 0;
    jogo->pontos = 0;
>>>>>>> Stashed changes

    for (int i = 0; i < 4; ++i) {
        jogo->fundacao[i].indice = 0;
    }

    jogo->start_time = 0;  // Inicializa o temporizador
    jogo->first_command_time = 0;  // Inicializa o tempo do primeiro comando '1'
    jogo->jogadas = 0;  // Inicializa a contagem de jogadas

}

void retirar_carta(Deck *origem, Deck *destino, int v) {
    if (origem->indice > 0) {
        destino->cartas[destino->indice] = origem->cartas[origem->indice - 1];
        destino->cartas[destino->indice].virada = v;
        origem->indice--;
        destino->indice++;
    } else {
        printf("O deck de origem está vazio.\n");
    }
}

// Função para verificar se duas cartas têm cores diferentes
bool cores_diferentes(Carta origem, Carta destino) {
    // Cores: 1 (vermelho) e 2 (preto)
    int cor_origem, cor_destino;

    // Determinar a cor da carta de origem
    if (origem.naipe == 1 || origem.naipe == 4) {
        cor_origem = 2; // Preto
    } else {
        cor_origem = 1; // Vermelho
    }

    // Determinar a cor da carta de destino
    if (destino.naipe == 1 || destino.naipe == 4) {
        cor_destino = 2; // Preto
    } else {
        cor_destino = 1; // Vermelho
    }

    // Comparar as cores
    return cor_origem != cor_destino;
}

// Função para verificar se a carta de origem é do mesmo naipe e a carta seguinte da carta de destino
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino) {
    // Verificar se são do mesmo naipe
    bool mesmo_naipe = origem.naipe == destino.naipe;

    // Verificar se a carta de origem é a carta seguinte da carta de destino
    bool carta_seguinte = origem.numero == destino.numero + 1;

    return mesmo_naipe && carta_seguinte;
}

void atualizar_descarte(Jogo *jogo) {
    // Verificar se há cartas no baralho
    if (jogo->baralho.indice > 0) {
        // Retirar a carta do baralho e enviá-la para o descarte
        retirar_carta(&jogo->baralho, &jogo->descarte, 0);

        // Imprimir mensagem indicando a ação
        printf("Uma carta foi movida do baralho para o descarte.\n");
    } else if (jogo->descarte.indice > 0) {
        // Se o baralho estiver vazio, mover todas as cartas do descarte para o baralho
        while (jogo->descarte.indice > 0) {
            if (jogo->baralho.indice < NUM_CARTAS) {
                retirar_carta(&jogo->descarte, &jogo->baralho, 1);
            } else {
                printf("Erro: Tentativa de mover carta para o baralho cheio.\n");
                break;
            }
        }

        // Imprimir mensagem indicando a ação
        printf("Todas as cartas do descarte foram movidas para o baralho.\n");
    } else {
        printf("O baralho e o descarte estão vazios. Não é possível mover carta para o descarte.\n");
    }
}


int mover_para_fundacao(Jogo *jogo) {
    // Verificar se há cartas no descarte
    if (jogo->descarte.indice > 0) {
        // Obter a carta do topo do descarte
        Carta origem = jogo->descarte.cartas[jogo->descarte.indice - 1];

        // Procurar por uma fundação com o mesmo naipe e número seguinte
        for (int i = 0; i < 4; ++i) {
            if (jogo->fundacao[i].indice > 0) {
                Carta topo_fundacao = jogo->fundacao[i].cartas[jogo->fundacao[i].indice - 1];
                if (topo_fundacao.naipe == origem.naipe && topo_fundacao.numero +1 == origem.numero) {
                    // Mover a carta para a fundação
                    retirar_carta(&jogo->descarte, &jogo->fundacao[i], 0);
                    printf("Uma carta foi movida do descarte para a fundação %d.\n", i + 1);
                    return 1; // Retornar 1 indicando sucesso
                }
            }
        }

        // Verificar se a carta do descarte é um "1" e se há uma fundação vazia
        if (origem.numero == 1) {
            for (int i = 0; i < 4; ++i) {
                if (jogo->fundacao[i].indice == 0) {
                    // Mover a carta para a fundação
                    retirar_carta(&jogo->descarte, &jogo->fundacao[i], 0);
                    printf("Uma carta foi movida do descarte para a fundação %d.\n", i + 1);
                    return 1; // Retornar 1 indicando sucesso
                }
            }
        }

        printf("Não há fundações disponíveis para a carta do descarte.\n");
        return 0; // Retornar 0 indicando falha
    } else {
        printf("O descarte está vazio. Não é possível mover carta para a fundação.\n");
        return 0; // Retornar 0 indicando falha
    }
}


int checagem_fim_de_jogo(Jogo *jogo)
{
    Carta fund0 = jogo->fundacao[0].cartas[jogo->fundacao[0].indice - 1];
    Carta fund1 = jogo->fundacao[1].cartas[jogo->fundacao[1].indice - 1];
    Carta fund2 = jogo->fundacao[2].cartas[jogo->fundacao[2].indice - 1];
    Carta fund3 = jogo->fundacao[3].cartas[jogo->fundacao[3].indice - 1];

    if(fund0.numero == 13 && fund1.numero == 13 && fund2.numero == 13 && fund3.numero == 13){
        //jogo acabou
        return 0;
    }
    //jogo não acabou
<<<<<<< Updated upstream
    return 0;
=======
    return 1;
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

    mouse_last_cord.click = 0;

    inicializar_jogo(meu_jogo);
    render(meu_jogo);
}

char map_numero_para_letra(int numero) {
    if (numero == 1) return 'a';
    else if (numero == 10) return 't';
    else if (numero == 11) return 'j';
    else if (numero == 12) return 'q';
    else if (numero == 13) return 'k';
    else return '0' + numero;  // Converte outros números para caracteres ('2' a '9')
}

const char* transform_card_to_path(const Carta* carta, const char* path_folder_images) {
    // Construa o sufixo com base na virada da carta
    const char* sufixo = carta->virada == 0 ? "" : "b";

    // Alocar memória para a string de caminho
    char* caminho_da_carta = (char*)malloc(100);

    if(carta->virada == 1 ){
        sprintf(caminho_da_carta, "%s/%s.png", path_folder_images, sufixo);
        return caminho_da_carta;
    }

    // Mapeie o número para uma letra
    char letra_numero = map_numero_para_letra(carta->numero);

    

    // Formate o caminho da carta usando sprintf
    sprintf(caminho_da_carta, "%s/%c%c%s.png", path_folder_images, "cdhs"[carta->naipe - 1], letra_numero, sufixo);

    // Retorne o ponteiro para a string de caminho alocada dinamicamente
    return caminho_da_carta;
}

// Função para liberar a memória alocada para o caminho da carta
void liberar_caminho_da_carta(const char* caminho_da_carta) {
    free((void*)caminho_da_carta);
}


void process_input(int *game_is_running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *game_is_running = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Botão esquerdo do mouse pressionado
                    mouse_last_cord.x = event.button.x;
                    mouse_last_cord.y = event.button.y;
                    mouse_last_cord.click = 1;
                    printf("Botão esquerdo do mouse pressionado em (%d, %d)\n", mouse_last_cord.x, mouse_last_cord.y);
                }
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    // Tecla ESC pressionada
                    *game_is_running = false;
                }
                break;

            // Adicione outros casos de eventos conforme necessário

            default:
                break;
        }
    }
>>>>>>> Stashed changes
}
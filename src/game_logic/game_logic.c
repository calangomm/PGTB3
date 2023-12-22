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

    for (int i = 0; i < 4; ++i) {
        jogo->fundacao[i].indice = 0;
    }

    jogo->start_time = 0;  // Inicializa o temporizador
    jogo->first_command_time = 0;  // Inicializa o tempo do primeiro comando '1'
    jogo->jogadas = 0;  // Inicializa a contagem de jogadas
    jogo->pontos = 0;
    jogo->contador_time = 0;

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
        return 1;
    }
    //jogo não acabou
    return 0;
}

int check_keyboard(SDL_Event *event, char *comando, Jogo *jogo) {
    if (event->type == SDL_QUIT) {
        *comando = 0;
        return 1;  // Indica que uma tecla foi processada
    } else if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                *comando = 0;
                return 1;  // Indica que uma tecla foi processada
            case SDLK_1:
                printf("Tecla 1 pressionada\n");
                // Adicione sua lógica aqui
                return 1;  // Indica que uma tecla foi processada
            case SDLK_2:
                printf("Tecla 2 pressionada\n");
                // Adicione sua lógica aqui
                return 1;  // Indica que uma tecla foi processada
        }
    } else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
        // Verifica se é o botão esquerdo do mouse
        if (jogo->first_command_time == 0) {
            // Inicia o timer GameStartTime quando o botão esquerdo é pressionado pela primeira vez
            jogo->first_command_time = SDL_GetTicks();
            printf("Botão esquerdo do mouse pressionado. Iniciando o timer.\n");
        }
        return 1;  // Indica que uma tecla foi processada
    }


    return 0;  // Nenhuma tecla foi processada
}

void game_run(Jogo *jogo, char *comando) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (check_keyboard(&event, comando, jogo)) {
            printf("Tecla pressionada dentro de game_run\n");
        }
    }
}
        

#include "../include/common.h"
#include "game_logic.h"


/**
 * @brief Inicializa uma carta com os valores fornecidos.
 *
 * @param carta Ponteiro para a estrutura de carta a ser inicializada.
 * @param virada Valor de virada da carta (0 ou 1).
 * @param naipe Número do naipe (1 a 4).
 * @param numero Número da carta (1 a 13).
 */
void inicializar_carta(Carta *carta, int virada, int naipe, int numero) {
    carta->virada = virada;
    carta->naipe = naipe;
    carta->numero = numero;
}


/**
 * @brief Inicializa um deck de cartas.
 *
 * @param deck Ponteiro para a estrutura de deck a ser inicializada.
 */
void inicializar_deck(Deck *deck) {
    deck->indice = 0;

    for (int naipe = 1; naipe <= NUM_NAIPES; ++naipe) {
        for (int numero = 1; numero <= NUM_NUMEROS; ++numero) {
            inicializar_carta(&deck->cartas[deck->indice], 1, naipe, numero);
            deck->indice++;
        }
    }
}


/**
 * @brief Embaralha as cartas em um deck usando o algoritmo de Fisher-Yates.
 *
 * @param deck Ponteiro para o deck a ser embaralhado.
 */
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


/**
 * @brief Inicializa a estrutura de jogo.
 *
 * @param jogo Ponteiro para a estrutura de jogo a ser inicializada.
 */
void inicializar_jogo(Jogo *jogo) {
    inicializar_deck(&jogo->baralho);
    randomizar_deck(&jogo->baralho);

    jogo->descarte.indice = 0;
    jogo->fundacao[0].indice = 0;
    jogo->fundacao[1].indice = 0;
    jogo->fundacao[2].indice = 0;
    jogo->fundacao[3].indice = 0;
    jogo->pontos = 0;

    for (int i = 0; i < 4; ++i) {
        jogo->fundacao[i].indice = 0;
    }

    jogo->start_time = 0;  // Inicializa o temporizador
    jogo->first_command_time = 0;  // Inicializa o tempo do primeiro comando '1'
    jogo->jogadas = 0;  // Inicializa a contagem de jogadas

}


/**
 * @brief Retira uma carta de um deck de origem e a coloca em um deck de destino.
 *
 * @param origem Ponteiro para o deck de origem.
 * @param destino Ponteiro para o deck de destino.
 * @param v Valor de virada da carta no deck de destino (0 ou 1).
 */
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


/**
 * @brief Verifica se duas cartas têm cores diferentes.
 *
 * @param origem Carta de origem.
 * @param destino Carta de destino.
 * @return true Se as cartas têm cores diferentes.
 * @return false Se as cartas têm a mesma cor.
 */
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


/**
 * @brief Verifica se o movimento de uma carta para a fundação é válido.
 *
 * @param origem Carta de origem.
 * @param destino Carta no topo da fundação.
 * @return true Se o movimento é válido.
 * @return false Se o movimento não é válido.
 */
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino) {
    // Verificar se são do mesmo naipe
    bool mesmo_naipe = origem.naipe == destino.naipe;

    // Verificar se a carta de origem é a carta seguinte da carta de destino
    bool carta_seguinte = origem.numero == destino.numero + 1;

    return mesmo_naipe && carta_seguinte;
}



/**
 * @brief Atualiza o deck de descarte, movendo cartas do baralho, se necessário.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void atualizar_descarte(Jogo *jogo) {
    // Verificar se há cartas no baralho
    if (jogo->baralho.indice > 0) {
        // Retirar a carta do baralho e enviá-la para o descarte
        retirar_carta(&jogo->baralho, &jogo->descarte, 0);

        // Imprimir mensagem indicando a ação
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


/**
 * @brief Move uma carta do descarte para a fundação, se possível.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 * @return int 1 se o movimento foi bem-sucedido, 0 se não foi.
 */
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
                    jogo->pontos++;
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
                    jogo->pontos++;
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


/**
 * @brief Verifica se as condições de fim de jogo foram atendidas.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 * @param game_is_running Ponteiro para a variável de controle do jogo.
 */
void checagem_fim_de_jogo(Jogo *jogo, int *game_is_running)
{
    Carta fund0 = jogo->fundacao[0].cartas[jogo->fundacao[0].indice - 1];
    Carta fund1 = jogo->fundacao[1].cartas[jogo->fundacao[1].indice - 1];
    Carta fund2 = jogo->fundacao[2].cartas[jogo->fundacao[2].indice - 1];
    Carta fund3 = jogo->fundacao[3].cartas[jogo->fundacao[3].indice - 1];

    if(fund0.numero == 13 && fund1.numero == 13 && fund2.numero == 13 && fund3.numero == 13){
        //jogo acabou
        *game_is_running = 0;
    };
}


/**
 * @brief Mapeia um número de carta para uma letra.
 *
 * @param numero Número da carta.
 * @return char Letra correspondente ao número da carta.
 */
char map_numero_para_letra(int numero) {
    if (numero == 1) return 'a';
    else if (numero == 10) return 't';
    else if (numero == 11) return 'j';
    else if (numero == 12) return 'q';
    else if (numero == 13) return 'k';
    else return '0' + numero;  // Converte outros números para caracteres ('2' a '9')
}


/**
 * @brief Transforma uma carta em um caminho de imagem.
 *
 * @param carta Ponteiro para a carta a ser transformada.
 * @param path_folder_images Caminho da pasta de imagens.
 * @return const char* Ponteiro para a string do caminho da carta alocada dinamicamente.
 */
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



/**
 * @brief Libera a memória alocada para o caminho da carta.
 *
 * @param caminho_da_carta Ponteiro para a string do caminho da carta.
 */
void liberar_caminho_da_carta(const char* caminho_da_carta) {
    free((void*)caminho_da_carta);
}


/**
 * @brief Configura o jogo inicialmente.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void setup(Jogo *jogo) {
    inicializar_jogo(jogo);

    time_show.s = 0;
    time_show.m = 0;
}


/**
 * @brief Calcula a diferença de tempo desde o início do jogo.
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void calcular_diferenca_tempo(Jogo *jogo) {
    if (jogo->first_command_time == 1) {
        // Obter o tempo atual
        int tempo_atual = SDL_GetTicks();

        // Calcular a diferença de tempo em milissegundos
        int diferenca_tempo_ms = tempo_atual - jogo->start_time;

        // Converter milissegundos para segundos e minutos
        int segundos = diferenca_tempo_ms / 1000;
        int minutos = segundos / 60;

        // Atualizar a estrutura TimeShow
        time_show.s = segundos % 60;
        time_show.m = minutos;
    }
}


/**
 * @brief Atualiza o estado do jogo.
 *
 * @param last_frame_time Ponteiro para o tempo do último quadro.
 * @param game_is_running Ponteiro para a variável de controle do jogo.
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void update(int *last_frame_time, int *game_is_running, Jogo *jogo) {
    //gasta tempo para ficar no frametime desejado
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), *last_frame_time + FRAME_TARGET_TIME));

    // Store the milliseconds of the current frame to be used in the next one
    *last_frame_time = SDL_GetTicks();

    calcular_diferenca_tempo(jogo);
    
    //area jogavel
    if(mouse_last_cord.y >= Y_AREA_JOGAVEL_INI && mouse_last_cord.y <= Y_AREA_JOGAVEL_FINAL)
    {   
        //baralho
        if(mouse_last_cord.x >=  DIST_HEADER_LEFT && mouse_last_cord.x <= X_FINAL_BARALHO)
        {
            atualizar_descarte(jogo);
            mouse_last_cord.x = 0;
            mouse_last_cord.y = 0;
            jogo->jogadas++;
        }
        //descarte
        else if(mouse_last_cord.x >=  X_INICIAL_DESCARTE && mouse_last_cord.x <= X_FINAL_DESCARTE){
            mover_para_fundacao(jogo);
            mouse_last_cord.x = 0;
            mouse_last_cord.y = 0;
            jogo->jogadas++;
        }
    }
    checagem_fim_de_jogo(jogo,game_is_running);
}
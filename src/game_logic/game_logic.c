// game_logic/game_logic.c
#include "../include/common.h"
#include <stdlib.h>


/**
 * Inicializa uma estrutura de carta com os valores fornecidos.
 * 
 * @param carta Um ponteiro para a estrutura Carta a ser inicializada.
 * @param virada Valor booleano indicando se a carta está virada para cima (1) ou para baixo (0).
 * @param naipe Naipe da carta (1 a 4, representando ♣, ♦, ♥, ♠, respectivamente).
 * @param numero Número da carta (1 a 13, representando A, 2 a 10, J, Q, K, respectivamente).
 * @return Nenhum retorno.
 */
void inicializar_carta(Carta *carta, int virada, int naipe, int numero) {
    // Atribui os valores fornecidos à estrutura de carta
    carta->virada = virada;
    carta->naipe = naipe;
    carta->numero = numero;
}


/**
 * Inicializa um deck de cartas preenchendo-o com cartas viradas para cima.
 * 
 * @param deck Um ponteiro para a estrutura Deck a ser inicializada.
 * @return Nenhum retorno.
 */
void inicializar_deck(Deck *deck) {
    // Zera o índice do deck, indicando que ele está vazio
    deck->indice = 0;

    // Loop para inicializar cada carta no deck
    for (int naipe = 1; naipe <= NUM_NAIPES; ++naipe) {
        for (int numero = 1; numero <= NUM_NUMEROS; ++numero) {
            // Chama a função inicializar_carta para criar uma carta com os valores fornecidos
            inicializar_carta(&deck->cartas[deck->indice], 1, naipe, numero);
            
            // Incrementa o índice do deck para a próxima carta
            deck->indice++;
        }
    }
}


/**
 * Embaralha as cartas em um deck utilizando o algoritmo de Fisher-Yates.
 * 
 * @param deck Um ponteiro para a estrutura Deck contendo as cartas a serem randomizadas.
 * @return Nenhum retorno.
 */
void randomizar_deck(Deck *deck) {
    // Inicializa a semente do gerador de números aleatórios com o tempo atual
    srand((unsigned int)time(NULL));

    // Embaralha as cartas usando o algoritmo de Fisher-Yates
    for (int i = NUM_CARTAS; i > 0; --i) {
        // Gera um índice aleatório j no intervalo [0, i]
        int j = rand() % (i + 1);

        // Troca as cartas nas posições i e j
        Carta temp = deck->cartas[i - 1];
        deck->cartas[i - 1] = deck->cartas[j];
        deck->cartas[j] = temp;
    }
}


/**
 * Inicializa a estrutura de jogo, incluindo o baralho, descarte, fundações e temporizadores.
 * 
 * @param jogo Um ponteiro para a estrutura Jogo a ser inicializada.
 * @return Nenhum retorno.
 */
void inicializar_jogo(Jogo *jogo) {
    // Inicializa o baralho e o embaralha
    inicializar_deck(&jogo->baralho);
    randomizar_deck(&jogo->baralho);

    // Zera o índice do descarte
    jogo->descarte.indice = 0;

    // Zera os índices das fundações
    for (int i = 0; i < 4; ++i) {
        jogo->fundacao[i].indice = 0;
    }

    // Inicializa os temporizadores
    jogo->start_time = 0;               // Inicializa o temporizador
    jogo->first_command_time = 0;       // Inicializa o tempo do primeiro comando '1'
    jogo->jogadas = 0;                  // Inicializa a contagem de jogadas
}


/**
 * Retira uma carta de um deck de origem e adiciona-a a um deck de destino.
 * 
 * @param origem Ponteiro para o deck de origem.
 * @param destino Ponteiro para o deck de destino.
 * @param v Valor booleano indicando se a carta deve ser virada para cima (1) ou para baixo (0) no deck de destino.
 * @return Nenhum retorno.
 */
void retirar_carta(Deck *origem, Deck *destino, int v) {
    // Verifica se o deck de origem não está vazio
    if (origem->indice > 0) {
        // Adiciona a carta do topo do deck de origem ao topo do deck de destino
        destino->cartas[destino->indice] = origem->cartas[origem->indice - 1];

        // Define a virada da carta no deck de destino conforme o parâmetro v
        destino->cartas[destino->indice].virada = v;

        // Atualiza os índices dos decks
        origem->indice--;
        destino->indice++;
    } else {
        // Mensagem de aviso se o deck de origem estiver vazio
        printf("O deck de origem está vazio.\n");
    }
}


/**
 * Verifica se duas cartas têm cores diferentes.
 * 
 * @param origem Carta de origem para comparação.
 * @param destino Carta de destino para comparação.
 * @return Valor booleano indicando se as cartas têm cores diferentes (true) ou não (false).
 */
bool cores_diferentes(Carta origem, Carta destino) {
    // Cores: 1 (vermelho) e 2 (preto)
    int cor_origem, cor_destino;

    // Determina a cor da carta de origem
    if (origem.naipe == 1 || origem.naipe == 4) {
        cor_origem = 2; // Preto
    } else {
        cor_origem = 1; // Vermelho
    }

    // Determina a cor da carta de destino
    if (destino.naipe == 1 || destino.naipe == 4) {
        cor_destino = 2; // Preto
    } else {
        cor_destino = 1; // Vermelho
    }

    // Compara as cores e retorna verdadeiro se forem diferentes
    return cor_origem != cor_destino;
}


/**
 * Verifica se a carta de origem é do mesmo naipe e se é a carta seguinte à carta de destino na fundação.
 * 
 * @param origem Carta de origem para comparação.
 * @param destino Carta de destino para comparação.
 * @return Valor booleano indicando se o movimento é válido (true) ou não (false).
 */
bool verificar_movimento_valido_fundacao(Carta origem, Carta destino) {
    // Verifica se as cartas são do mesmo naipe
    bool mesmo_naipe = origem.naipe == destino.naipe;

    // Verifica se a carta de origem é a carta seguinte à carta de destino
    bool carta_seguinte = origem.numero == destino.numero + 1;

    // Retorna verdadeiro se ambas as condições forem atendidas
    return mesmo_naipe && carta_seguinte;
}


/**
 * Atualiza o descarte, movendo cartas do baralho para o descarte ou vice-versa conforme necessário.
 * 
 * @param jogo Um ponteiro para a estrutura Jogo contendo o estado do jogo.
 * @return Nenhum retorno.
 */
void atualizar_descarte(Jogo *jogo) {
    // Verifica se há cartas no baralho
    if (jogo->baralho.indice > 0) {
        // Retira a carta do baralho e a envia para o descarte
        retirar_carta(&jogo->baralho, &jogo->descarte, 0);

        // Imprime mensagem indicando a ação
        printf("Uma carta foi movida do baralho para o descarte.\n");
    } else if (jogo->descarte.indice > 0) {
        // Se o baralho estiver vazio, move todas as cartas do descarte para o baralho
        while (jogo->descarte.indice > 0) {
            if (jogo->baralho.indice < NUM_CARTAS) {
                retirar_carta(&jogo->descarte, &jogo->baralho, 1);
            } else {
                // Mensagem de erro se o baralho estiver cheio
                printf("Erro: Tentativa de mover carta para o baralho cheio.\n");
                break;
            }
        }

        // Imprime mensagem indicando a ação
        printf("Todas as cartas do descarte foram movidas para o baralho.\n");
    } else {
        // Mensagem se tanto o baralho quanto o descarte estiverem vazios
        printf("O baralho e o descarte estão vazios. Não é possível mover carta para o descarte.\n");
    }
}



/**
 * Tenta mover uma carta do descarte para uma fundação.
 * 
 * @param jogo Um ponteiro para a estrutura Jogo contendo o estado do jogo.
 * @return 1 se a movimentação foi bem-sucedida, 0 caso contrário.
 */
int mover_para_fundacao(Jogo *jogo) {
    // Verifica se há cartas no descarte
    if (jogo->descarte.indice > 0) {
        // Obtém a carta do topo do descarte
        Carta origem = jogo->descarte.cartas[jogo->descarte.indice - 1];

        // Procura por uma fundação com o mesmo naipe e número seguinte
        for (int i = 0; i < 4; ++i) {
            if (jogo->fundacao[i].indice > 0) {
                Carta topo_fundacao = jogo->fundacao[i].cartas[jogo->fundacao[i].indice - 1];
                if (topo_fundacao.naipe == origem.naipe && topo_fundacao.numero + 1 == origem.numero) {
                    // Move a carta para a fundação
                    retirar_carta(&jogo->descarte, &jogo->fundacao[i], 0);
                    printf("Uma carta foi movida do descarte para a fundação %d.\n", i + 1);
                    return 1; // Retorna 1 indicando sucesso
                }
            }
        }

        // Verifica se a carta do descarte é um "1" e se há uma fundação vazia
        if (origem.numero == 1) {
            for (int i = 0; i < 4; ++i) {
                if (jogo->fundacao[i].indice == 0) {
                    // Move a carta para a fundação
                    retirar_carta(&jogo->descarte, &jogo->fundacao[i], 0);
                    printf("Uma carta foi movida do descarte para a fundação %d.\n", i + 1);
                    return 1; // Retorna 1 indicando sucesso
                }
            }
        }

        printf("Não há fundações disponíveis para a carta do descarte.\n");
        return 0; // Retorna 0 indicando falha
    } else {
        printf("O descarte está vazio. Não é possível mover carta para a fundação.\n");
        return 0; // Retorna 0 indicando falha
    }
}



/**
 * Checa se o jogo chegou ao fim, verificando se todas as fundações possuem a carta "K" (número 13).
 * 
 * @param jogo Um ponteiro para a estrutura do jogo.
 * @return 1 se o jogo chegou ao fim, 0 caso contrário.
 */
int checagem_fim_de_jogo(Jogo *jogo) {
    // Obtém as cartas do topo de cada fundação
    Carta fund0 = jogo->fundacao[0].cartas[jogo->fundacao[0].indice - 1];
    Carta fund1 = jogo->fundacao[1].cartas[jogo->fundacao[1].indice - 1];
    Carta fund2 = jogo->fundacao[2].cartas[jogo->fundacao[2].indice - 1];
    Carta fund3 = jogo->fundacao[3].cartas[jogo->fundacao[3].indice - 1];
    
    // Verifica se todas as fundações têm a carta "K" (número 13)
    if (fund0.numero == 13 && fund1.numero == 13 && fund2.numero == 13 && fund3.numero == 13) {
        // O jogo acabou
        return 1;
    }

    // O jogo ainda não acabou
    return 0;
}

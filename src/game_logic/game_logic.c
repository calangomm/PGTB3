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


/**
 * @brief Envia as cartas de baralho para as pilhas 
 * na ordem de inicialização do jogo, de 1 a 7
 *
 * @param jogo Ponteiro para a estrutura de jogo a ser processada
 */
void enviar_para_pilhas(Jogo *jogo){
    for(int i = 0; i< NUM_PILHAS; i++)
    {
        for(int j = i; j < NUM_PILHAS; j++)
        {   
            printf("int i = %d, int j =%d\n", i, j);
            if(j == i) retirar_carta(&jogo->baralho, &jogo->pilhas[j], 0);
            else retirar_carta(&jogo->baralho, &jogo->pilhas[j], 1);
            
        }
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

    for(int i = 0; i < NUM_PILHAS; i++)
    {   
        if(i<NUM_NAIPES)jogo->fundacao[i].indice = 0;
        jogo->pilhas[i].indice = 0;
    }

    if(jogo->nivel >1)
    {   
        enviar_para_pilhas(jogo);
    }

    jogo->pontos = 0;

    jogo->start_time = 0;  // Inicializa o temporizador
    jogo->first_command_time = 0;  // Inicializa o tempo do primeiro comando '1'
    jogo->jogadas = 0;  // Inicializa a contagem de jogadas
    jogo->selecao = -1;

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
                    jogo->pontos++;
                    jogo->jogadas++;
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
                    jogo->jogadas++;
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


int move_pilha_pilha(Deck *origem, Deck *destino, int nivel)
{
    bool carta_seguinte = false;

    if(destino->indice==0 && nivel != 3)
    {
        if(origem->cartas[origem->indice - 1].numero==13)
        {
            retirar_carta(origem, destino, 0);
            return 1;
        }
        else return 0;
    }
    else if(destino->indice!=0 && nivel != 3)
    {
        carta_seguinte = origem->cartas[origem->indice-1].numero == destino->cartas[destino->indice-1].numero - 1;
        if(cores_diferentes(origem->cartas[origem->indice - 1],
                            destino->cartas[destino->indice - 1])
                            && carta_seguinte)
        {
            printf("cores diferentes, movendo\n");
            retirar_carta(origem, destino, 0);
            return 1;
        }
    }
    else if(nivel == 3){
        int indice = origem->indice;
        int numero_desejado = 0;

        if(destino->indice==0)
        {
            printf("Pilha de destino não possiu cartas!\n");
            numero_desejado = 14;
            carta_seguinte = origem->cartas[indice-1].numero == numero_desejado - 1;
        }
        else{
            numero_desejado = destino->cartas[destino->indice-1].numero;
            carta_seguinte = origem->cartas[indice-1].numero == numero_desejado - 1;
        }

        for(;!(carta_seguinte) && (origem->cartas[indice-1].virada ==0) && indice > 0  ;indice --)
        {
            carta_seguinte = origem->cartas[indice-1].numero == numero_desejado - 1;
            if(carta_seguinte)break;
        }

        int counter = 0;

        if(destino->indice == 0 && carta_seguinte)
        {
            printf("destino->indice == 0 && carta_seguinte!\n");
            for(int i = indice; i<=origem->indice;i++){
                destino->cartas[destino->indice] = origem->cartas[i-1];
                counter++;
                destino->indice++;
            }
            origem->indice = origem->indice - counter;
            return 1;
        }

        if(!cores_diferentes(origem->cartas[indice - 1],
                            destino->cartas[destino->indice - 1]))
        {
            return 0;
        }
        
        for(int i = indice; i<=origem->indice;i++){
                destino->cartas[destino->indice] = origem->cartas[i-1];
                counter++;
                destino->indice++;
        }
        printf("Carta encontrada para movimentação");
        origem->indice = origem->indice - counter;
        return 1;

    }

}


void move_carta_pilha_fund(Deck *origem, Jogo *jogo) {
    // Verifica se há cartas na pilha de origem
    printf("Move carta_pilha_fund!!\n");
    if (origem->indice > 0) {
        // Obtém a carta do topo da pilha de origem
        Carta origem_carta = origem->cartas[origem->indice-1];

        // Procura por uma fundação com o mesmo naipe e número seguinte
        for (int i = 0; i < NUM_NAIPES; ++i) {
            if (jogo->fundacao[i].indice > 0) {
                Carta topo_fundacao = jogo->fundacao[i].cartas[jogo->fundacao[i].indice - 1];
                if (topo_fundacao.naipe == origem_carta.naipe && topo_fundacao.numero + 1 == origem_carta.numero) {
                    // Mover a carta para a fundação
                    retirar_carta(origem, &jogo->fundacao[i], origem_carta.virada);
                    jogo->pontos++;
                    jogo->jogadas++;
                    return; // Sai da função após o movimento bem-sucedido
                }
            }
        }

        // Verifica se a carta da pilha é um "1" e se há uma fundação vazia
        if (origem_carta.numero == 1) {
            for (int i = 0; i < NUM_NAIPES; ++i) {
                if (jogo->fundacao[i].indice == 0) {
                    // Mover a carta para a fundação
                    retirar_carta(origem, &jogo->fundacao[i], origem_carta.virada);
                    jogo->pontos++;
                    jogo->jogadas++;
                    return; // Sai da função após o movimento bem-sucedido
                }
            }
        }

        printf("Não há fundações disponíveis para a carta da pilha.\n");
    } else {
        printf("A pilha está vazia. Não é possível mover carta para a fundação.\n");
    }
}

void move_carta_fund_pilha(Deck *destino, Jogo *jogo)
{
    printf("Move carta_fund_pilha!!\n");
    for (int i = 1; i <= NUM_NAIPES; i++) {
        if (mouse_last_cord.x >= X_I_PILHA4 + (i - 1) * (CARD_WIDTH + CARDS_DIST) &&
            mouse_last_cord.x <= X_I_PILHA4 + i * CARD_WIDTH + (i - 1) * CARDS_DIST) {
            retirar_carta(&jogo->fundacao[i], destino, 0); 
            break;
        }
    }
}

/**
 * @brief Verifica o que foi selecionado, e retorna um valor para a proxima selecao
 *
 * @param jogo Ponteiro para a estrutura de jogo.
 */
int process_selecao(int primeira, int segunda, Jogo *jogo) {
    // Verifica se a seleção é inválida
    if(primeira == -1)
    {   
        if(segunda >= 1 && segunda <=7)
        {
            if(jogo->pilhas[segunda-1].cartas[jogo->pilhas[segunda-1].indice-1].virada==1)
            {
                jogo->pilhas[segunda-1].cartas[jogo->pilhas[segunda-1].indice-1].virada = 0;
                return -1;
            }
        }
        return segunda;
    }

    if (primeira > 8 || segunda < 0 || segunda > 8) {
        return -1;
    }
    if (primeira == segunda) {
            return -1;  // Seleção inválida, des-seleciona
    }

    if(primeira == 0) //descarte
    {   if (segunda >= 1 && segunda <= 7){
            printf("Move descarte a pilha%d!!\n", segunda);
            move_pilha_pilha(&jogo->descarte, &jogo->pilhas[segunda - 1], jogo->nivel); //move descarte para pilhas
        }
        if(segunda == 8)
        {
            move_carta_pilha_fund(&jogo->descarte, jogo);
        }
    }
    // Movimentação pilha a pilha
    else if (segunda >= 1 && segunda <= 7 && primeira >= 1 && primeira <= 7 ) {
        printf("Move pilha a pilha!!\n");
        move_pilha_pilha(&jogo->pilhas[primeira - 1], &jogo->pilhas[segunda - 1], jogo->nivel); //pilha para pilha
    }
    // Movimentação de carta para a fundação
    else if (segunda == 8) {
        if (primeira < 0 || primeira > 7) {
            return -1;  // Seleção inválida, des-seleciona
        }
        move_carta_pilha_fund(&jogo->pilhas[primeira - 1], jogo);
    }
    // Movimentação de carta da fundação para a pilha
    else if (primeira == 8 && segunda >= 1 && segunda <= 7) {
        move_carta_fund_pilha(&jogo->pilhas[segunda - 1], jogo);
    }

    return -1;
}

void zera_mouse_cords(void)
{
    mouse_last_cord.x = 0;
    mouse_last_cord.y = 0;
}

/**
 * @brief Atualiza o estado do jogo.
 *
 * @param last_frame_time Ponteiro para o tempo do último quadro.
 * @param game_is_running Ponteiro para a variável de controle do jogo.
 * @param jogo Ponteiro para a estrutura de jogo.
 */
void update(int *last_frame_time, int *game_is_running, Jogo *jogo) {
    //Aguarda o tempo desejado
    //while(!SDL_TICKS_PASSED(SDL_GetTicks(), *last_frame_time + FRAME_TARGET_TIME));
    
    // Store the milliseconds of the current frame to be used in the next one
    *last_frame_time = SDL_GetTicks();

    calcular_diferenca_tempo(jogo);
    
    //area superior
    if(mouse_last_cord.y >= Y_AREA_JOGAVEL_INI && mouse_last_cord.y <= Y_AREA_JOGAVEL_FINAL){   
        //baralho
        if(mouse_last_cord.x >=  X_I_PILHA1 && mouse_last_cord.x <= X_F_PILHA1){
            zera_mouse_cords();
            atualizar_descarte(jogo);
            jogo->jogadas++;
            
            if(jogo->nivel>1){
                if(jogo->selecao != -1){
                    jogo->selecao = -1; //tira a seleção
                    printf("jogada inválida, Atualizando descarte!!\n");
                }
            }
        }
        //descarte
        else if(mouse_last_cord.x >=  X_I_PILHA2 && mouse_last_cord.x <= X_F_PILHA2){
            if(jogo->nivel==1){
                mover_para_fundacao(jogo);
            }
            if(jogo->nivel>1){
                printf("Selecionado Descarte!!\n");
                jogo->selecao = process_selecao(jogo->selecao, 0, jogo);
            }
            zera_mouse_cords();
        }
        //fundação
        else if(mouse_last_cord.x >=  X_I_PILHA4 && mouse_last_cord.x <= X_F_PILHA7){    
            if(jogo->nivel>1){
                printf("Selecionado Fundacao!!\n");
                jogo->selecao = process_selecao(jogo->selecao, 8, jogo);
            }
            zera_mouse_cords();
        }

    }
    if(jogo->nivel>1){
        //area inferior tabuleiro
        if(mouse_last_cord.y >= DIST_TABULEIRO_TOP && mouse_last_cord.y <= DIST_TABULEIRO_BACK){
            for (int i = 1; i <= 7; i++) {
            if (mouse_last_cord.x >= X_I_PILHA1 + (i - 1) * (CARD_WIDTH + CARDS_DIST) &&
                mouse_last_cord.x <= X_I_PILHA1 + i * CARD_WIDTH + (i - 1) * CARDS_DIST) {
                printf("Selecionado Tabuleiro%d!!\n", i);
                jogo->selecao = process_selecao(jogo->selecao, i, jogo);
                zera_mouse_cords();
                break;
            }
            }
        }
    }
    
    checagem_fim_de_jogo(jogo,game_is_running);
}
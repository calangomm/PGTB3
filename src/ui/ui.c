#include "../include/common.h"

#ifndef SDL_TTF_H
#define SDL_TTF_H
#include <SDL_ttf.h>
#endif

void window_background(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 41, 153, 97, 255);
    SDL_RenderClear(renderer);
}


void desenhar_bloco(SDL_Renderer *renderer, const Bloco *bloco, int x, int y) {
    SDL_SetRenderDrawColor(renderer, bloco->cor_r, bloco->cor_g, bloco->cor_b, 255);
    SDL_Rect bloco_rect = {x, y, bloco->largura, bloco->altura};
    SDL_RenderFillRect(renderer, &bloco_rect);
}

void renderizar_row(SDL_Renderer *renderer, Bloco *blocos, int num_blocos, int distancia_entre_blocos, int x_inicial, int y_inicial) {
    for (int i = 0; i < num_blocos; ++i) {
        int x = x_inicial + i * (blocos[i].largura + distancia_entre_blocos);
        int y = y_inicial;
        desenhar_bloco(renderer, &blocos[i], x, y);
    }
}

void renderizar_base(SDL_Renderer *renderer, int distancia_entre_blocos, int x_inicial, int y_inicial) {
    Bloco blocos_da_primeira_linha[] = {
        {HEADER_WIDTH, HEADER_HEIGHT, 64, 64, 64}  // Bloco vermelho
    };

    // Número de blocos na primeira linha
    int num_blocos_na_primeira_linha = sizeof(blocos_da_primeira_linha) / sizeof(Bloco);

    // Renderiza a primeira linha na janela
    renderizar_row(renderer, blocos_da_primeira_linha, num_blocos_na_primeira_linha, distancia_entre_blocos, x_inicial, y_inicial);

    // Posição inicial da segunda linha
    int y_segunda_linha = y_inicial + blocos_da_primeira_linha[0].altura + distancia_entre_blocos;

    Bloco blocos_da_segunda_linha[] = {
        {CARD_WIDTH, CARD_HEIGHT, 20, 120, 50}, 
        {CARD_WIDTH, CARD_HEIGHT, 20, 120, 50},  
        {CARD_WIDTH, CARD_HEIGHT, 41, 153, 97},  
        {CARD_WIDTH, CARD_HEIGHT, 20, 120, 50},  
        {CARD_WIDTH, CARD_HEIGHT, 20, 120, 50},  
        {CARD_WIDTH, CARD_HEIGHT, 20, 120, 50},  
        {CARD_WIDTH, CARD_HEIGHT, 20, 120, 50}    
    };

    // Número de blocos na segunda linha
    int num_blocos_na_segunda_linha = sizeof(blocos_da_segunda_linha) / sizeof(Bloco);

    // Renderiza a segunda linha na janela
    renderizar_row(renderer, blocos_da_segunda_linha, num_blocos_na_segunda_linha, distancia_entre_blocos, x_inicial, y_segunda_linha);
}

Uint32 calculateElapsedTime(int GameStartTime ) {
    // Obtém o tempo atual
    Uint32 currentTime = SDL_GetTicks();

    // Calcula o tempo decorrido em milissegundos
    Uint32 elapsedTime = currentTime - GameStartTime;

    // Converte para segundos
    Uint32 elapsedSeconds = elapsedTime / 1000;  // 1 segundo = 1000 milissegundos

    return elapsedSeconds;
}

// Função para renderizar texto na tela
void renderizar_texto(SDL_Renderer *renderer, const char *texto, int x, int y, int tamanho) {
    // Configurar a fonte e cor do texto
    TTF_Font *fonte = TTF_OpenFont("caminho/para/sua/fonte.ttf", tamanho);
    SDL_Color cor = {255, 255, 255};

    // Criar uma superfície de texto
    SDL_Surface *surface = TTF_RenderText_Blended(fonte, texto, cor);

    // Criar uma textura a partir da superfície
    SDL_Texture *textura = SDL_CreateTextureFromSurface(renderer, surface);

    // Obter as dimensões da textura para posicionamento
    int largura, altura;
    SDL_QueryTexture(textura, NULL, NULL, &largura, &altura);

    // Definir a posição da textura na tela
    SDL_Rect destino = {x, y, largura, altura};

    // Renderizar a textura na tela
    SDL_RenderCopy(renderer, textura, NULL, &destino);

    // Limpar recursos
    SDL_DestroyTexture(textura);
    SDL_FreeSurface(surface);
    TTF_CloseFont(fonte);
}

void renderizar_texto(SDL_Renderer *renderer, const char *texto, int x, int y, int tamanho) {
    // Configurar a fonte e cor do texto
    TTF_Font *fonte = TTF_OpenFont("caminho/para/sua/fonte.ttf", tamanho);
    SDL_Color cor = {255, 255, 255}; // Cor branca, você pode ajustar conforme necessário

    // Criar uma superfície de texto
    SDL_Surface *surface = TTF_RenderText_Blended(fonte, texto, cor);

    // Criar uma textura a partir da superfície
    SDL_Texture *textura = SDL_CreateTextureFromSurface(renderer, surface);

    // Obter as dimensões da textura para posicionamento
    int largura, altura;
    SDL_QueryTexture(textura, NULL, NULL, &largura, &altura);

    // Definir a posição da textura na tela
    SDL_Rect destino = {x, y, largura, altura};

    // Renderizar a textura na tela
    SDL_RenderCopy(renderer, textura, NULL, &destino);

    // Limpar recursos
    SDL_DestroyTexture(textura);
    SDL_FreeSurface(surface);
    TTF_CloseFont(fonte);
}

void renderizar_header_status(Jogo *meu_jogo, SDL_Renderer *renderer) {
    // Converter o contador de tempo para uma string
    char texto[20];
    sprintf(texto, "Tempo: %u segundos", meu_jogo->contador_time);

    // Renderizar o texto na posição desejada
    renderizar_texto(renderer, texto, 0, 0, 10);
}

void renderizar_cartas_fRow(Jogo *meu_jogo)
{
    //to implement
}

void renderizar_game(Jogo *meu_jogo, SDL_Renderer *renderer)
{
    if(meu_jogo->first_command_time != 0)
    {
        meu_jogo->contador_time = calculateElapsedTime(meu_jogo->first_command_time);
        printf("Tempo decorrido em segundos: %u\n", meu_jogo->contador_time);
    }   
    window_background(renderer);
    renderizar_base(renderer, CARDS_DIST, DIST_HEADER_LEFT, DIST_HEADER_TOP);
    renderizar_header_status(meu_jogo, renderer);
    renderizar_cartas_fRow(meu_jogo);
}
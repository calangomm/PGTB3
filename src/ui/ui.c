#include "../include/common.h"
#include "ui.h"
#include <stdbool.h>


#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"


/**
 * @brief Inicializa a janela SDL, o renderizador e a fonte TTF.
 *
 * @param window Ponteiro para a variável que receberá a janela SDL.
 * @param renderer Ponteiro para a variável que receberá o renderizador SDL.
 * @param font Ponteiro para a variável que receberá a fonte TTF.
 *
 * @return Retorna verdadeiro (true) se a inicialização for bem-sucedida, falso (false) caso contrário.
 */
int initialize_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // Criar janela SDL
    *window = SDL_CreateWindow(
        "Solitario",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL
    );
    if (!(*window)) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }

    // Criar renderizador SDL
    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if (!(*renderer)) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }
    
    // Inicializar SDL_ttf
    if (TTF_Init() != 0) {
        fprintf(stderr, "Error initializing SDL_ttf: %s\n", TTF_GetError());
        return false;
    }

    // Carregar a fonte TTF
    *font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!(*font)) {
        fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
        return false;
    }

    return true;
}


/**
 * @brief Processa os eventos de entrada do usuário.
 *
 * @param game_is_running Ponteiro para a variável que indica se o jogo está em execução.
 * @param jogo Ponteiro para a estrutura que representa o estado do jogo.
 */
void process_input(int *game_is_running, Jogo *jogo) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                // Evento de fechamento da janela
                *game_is_running = false;
                break;
            case SDL_KEYDOWN:
                // Tecla do teclado pressionada
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    *game_is_running = false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Botão do mouse pressionado
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Botão esquerdo do mouse pressionado
                    mouse_last_cord.x = event.button.x;
                    mouse_last_cord.y = event.button.y;

                    // Iniciar o contador de inicio de game
                    if(jogo->start_time == 0)
                    {
                        jogo->start_time = SDL_GetTicks();
                        jogo->first_command_time = 1;
                    }
                }
                break;
            default:
                break;
        }
    }
}


/**
 * @brief Desenha um retângulo no renderer SDL.
 *
 * @param renderer Ponteiro para o renderer onde o retângulo será desenhado.
 * @param x Coordenada x do canto superior esquerdo do retângulo.
 * @param y Coordenada y do canto superior esquerdo do retângulo.
 * @param width Largura do retângulo.
 * @param height Altura do retângulo.
 * @param color Cor do retângulo (R, G, B, A).
 * @param filled Indica se o retângulo deve ser preenchido (true) ou apenas contornado (false).
 */
void draw_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color color, bool filled) {
    // Definindo a cor para o retângulo (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Definindo as coordenadas e dimensões do retângulo
    SDL_Rect rect = {x, y, width, height};

    // Desenhando o retângulo
    if (filled) {
        // Preencher o retângulo
        SDL_RenderFillRect(renderer, &rect);
    } else {
        // Contornar o retângulo
        SDL_RenderDrawRect(renderer, &rect);
    }
}


/**
 * @brief Carrega uma textura a partir de um arquivo de imagem.
 *
 * @param renderer Ponteiro para o renderer SDL onde a textura será utilizada.
 * @param path Caminho para o arquivo de imagem.
 *
 * @return Retorna um ponteiro para a textura carregada ou NULL em caso de erro.
 */
SDL_Texture* load_texture(SDL_Renderer *renderer, const char *path) {
    // Carregar a imagem como uma superfície SDL
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
        return NULL;
    }

    // Criar uma textura a partir da superfície carregada
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    // Liberar a superfície, já que a textura foi criada
    SDL_FreeSurface(surface);
    return texture;
}


/**
 * @brief Desenha uma imagem em um renderer SDL.
 *
 * @param renderer Ponteiro para o renderer onde a imagem será desenhada.
 * @param path Caminho para o arquivo de imagem.
 * @param x Coordenada x do canto superior esquerdo da imagem.
 * @param y Coordenada y do canto superior esquerdo da imagem.
 * @param width Largura da imagem.
 * @param height Altura da imagem.
 */
void draw_image(SDL_Renderer *renderer, const char *path, int x, int y, int width, int height) {
    // Carrega a textura da imagem
    SDL_Texture *image_texture = load_texture(renderer, path);
    if (!image_texture) {
        return; // Não foi possível carregar a textura da imagem
    }

    // Define o retângulo de destino para o desenho da imagem
    SDL_Rect dest_rect = {x, y, width, height};

    // Desenha a textura na tela
    SDL_RenderCopy(renderer, image_texture, NULL, &dest_rect);

    // Libera a textura, já que não será mais necessária
    SDL_DestroyTexture(image_texture);
}


/**
 * @brief Desenha uma carta no cabeçalho do jogo.
 *
 * @param renderer Ponteiro para o renderer onde a carta será desenhada.
 * @param carta Ponteiro para a estrutura que representa a carta.
 * @param path Caminho base para os arquivos de imagem das cartas.
 * @param x Coordenada x do canto superior esquerdo da carta.
 * @param y Coordenada y do canto superior esquerdo da carta.
 */
void desenha_carta_header(SDL_Renderer *renderer,Carta *carta, const char *path, int x, int y)
{
    const char* caminho_da_carta = transform_card_to_path(carta, path);
    draw_image(renderer, caminho_da_carta, x, y, CARD_WIDTH, CARD_HEIGHT);
}


/**
 * Renderiza um texto em um renderer SDL com opções de posicionamento, tamanho e cores.
 *
 * @param renderer  O renderer SDL onde o texto será renderizado.
 * @param font      A fonte TTF usada para renderizar o texto.
 * @param text      O texto a ser renderizado.
 * @param x         A coordenada x inicial do bloco onde o texto será renderizado.
 * @param y         A coordenada y inicial do bloco onde o texto será renderizado.
 * @param blockWidth Largura do bloco onde o texto será renderizado. Se for 0, a largura do texto será usada.
 * @param blockHeight Altura do bloco onde o texto será renderizado. Se for 0, a altura do texto será usada.
 * @param textColor Cor do texto.
 * @param bgColor   Cor de fundo do bloco onde o texto será renderizado.
 */
void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y, int blockWidth, int blockHeight, SDL_Color textColor, SDL_Color bgColor) {
    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, text, textColor, bgColor);
    if (textSurface == NULL) {
        fprintf(stderr, "Error rendering text: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        fprintf(stderr, "Error creating text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Se o blocoWidth e blockHeight não forem fornecidos, use o tamanho do texto como dimensões do bloco
    if (blockWidth <= 0) {
        blockWidth = textSurface->w;
    }
    if (blockHeight <= 0) {
        blockHeight = textSurface->h;
    }

    // Crie um retângulo para o bloco onde o texto será renderizado
    SDL_Rect blockRect = {x, y, blockWidth, blockHeight};

    // Renderize o fundo do bloco com a cor bgColor
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &blockRect);

    // Calcule as coordenadas para centralizar o texto no bloco
    int textX = x + (blockWidth - textSurface->w) / 2;
    int textY = y + (blockHeight - textSurface->h) / 2;

    SDL_Rect destRect = {textX, textY, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &destRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}


/**
 * @brief Formata o tempo em minutos e segundos para uma string no formato "MM:SS".
 *
 * @param stringFormatada Ponteiro para a string onde o tempo formatado será armazenado.
 * @param minutos Valor dos minutos.
 * @param segundos Valor dos segundos.
 */
void formatarTempo(char *stringFormatada, int minutos, int segundos) {
    sprintf(stringFormatada, "%02d:%02d", minutos, segundos);
}


/**
 * @brief Renderiza o estado atual do jogo na tela.
 *
 * @param renderer Ponteiro para o renderer SDL onde o jogo será renderizado.
 * @param jogo Ponteiro para a estrutura que representa o estado do jogo.
 * @param font Ponteiro para a fonte TTF utilizada na renderização.
 */
void render(SDL_Renderer *renderer, Jogo *jogo, TTF_Font *font) {
    // cria o background e limpa a dela do que tinha antes
    SDL_SetRenderDrawColor(renderer, C_BACKGROUND.r, C_BACKGROUND.g, C_BACKGROUND.b, C_BACKGROUND.a);
    SDL_RenderClear(renderer);

    // Chamar a função draw_rectangle para desenhar um retângulo específico
    draw_rectangle(renderer, DIST_HEADER_LEFT, DIST_HEADER_TOP, 
                    HEADER_WIDTH, HEADER_HEIGHT, 
                    C_HEADER, true);


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
                desenha_carta_header(renderer, &jogo->baralho.cartas[jogo->baralho.indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,true);
            break;
        case 1:
            if(jogo->descarte.indice>0){
                desenha_carta_header(renderer,&jogo->descarte.cartas[jogo->descarte.indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,true);
            break;
        case 3:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,true);
            break;
        case 4:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,true);
            break;
        case 5:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,true);
            break;
        case 6:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,true);
            break;
        }

        cartas_desenho.x = cartas_desenho.x + CARD_WIDTH + CARDS_DIST;
    }

    //renderiza texto jogadas
    render_text(renderer, font, "Plays", DIST_L_H_PLAYS
                ,DIST_TOP_H_PLAYS,PLAY_BOX_WIDHT,PLAY_BOX_HEIGHT,C_TEXT,C_HEADER);


    char buffer[50];
    sprintf(buffer, "%d", jogo->jogadas);

    //renderiza contador de jogadas com o numero de jogadas
    render_text(renderer, font, buffer, DIST_L_H_PLAYS_BOX,
                DIST_TOP_H_PLAYS,PLAY_BOX_WIDHT,PLAY_BOX_HEIGHT,C_P_BACK_TXT,C_P_BACK_BOX);

    //renderiza texto Pontos
    render_text(renderer, font, "Points", DIST_L_H_POINTS
                ,DIST_TOP_H_PLAYS,POINTS_BOX_WIDHT,PLAY_BOX_HEIGHT,C_TEXT,C_HEADER);

    sprintf(buffer, "%d", jogo->pontos);

    //renderiza contador de jogadas com o numero de jogadas
    render_text(renderer, font, buffer, DIST_L_H_POINTS_BOX,
                DIST_TOP_H_PLAYS,PLAY_BOX_WIDHT,PLAY_BOX_HEIGHT,C_P_BACK_TXT,C_P_BACK_BOX);


    formatarTempo(buffer, time_show.m, time_show.s);

    //renderiza temporizador do jogo
    render_text(renderer, font, buffer, DIST_L_H_TIMER_BOX,
                DIST_TOP_H_PLAYS,TIMER_BOX_WIDHT,PLAY_BOX_HEIGHT,C_P_BACK_BOX,C_HEADER);

    // Atualize a tela (renderiza)
    SDL_RenderPresent(renderer);

}


/**
 * @brief Destrói os recursos associados à janela, ao renderer e à fonte TTF.
 *
 * @param window Ponteiro para a janela SDL a ser destruída.
 * @param renderer Ponteiro para o renderer SDL a ser destruído.
 * @param font Ponteiro para a fonte TTF a ser destruída.
 */
void destroy_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    TTF_CloseFont(*font);
    TTF_Quit();

    SDL_Quit();
}


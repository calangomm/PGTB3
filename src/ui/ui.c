#include "../include/common.h"
#include "ui.h"

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"

int initialize_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
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

void process_input(int *game_is_running, Jogo *jogo) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                *game_is_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    *game_is_running = false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Botão esquerdo do mouse pressionado
                    mouse_last_cord.x = event.button.x;
                    mouse_last_cord.y = event.button.y;

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


void draw_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color color, bool filled) {
    // Definindo a cor para o retângulo (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Definindo as coordenadas e dimensões do retângulo
    SDL_Rect rect = {x, y, width, height};

    // Desenhando o retângulo
    if (filled) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

SDL_Texture* load_texture(SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    SDL_FreeSurface(surface);
    return texture;
}

void draw_image(SDL_Renderer *renderer, const char *path, int x, int y, int width, int height) {
    SDL_Texture *image_texture = load_texture(renderer, path);
    if (!image_texture) {
        return; // Não foi possível carregar a textura da imagem
    }

    SDL_Rect dest_rect = {x, y, width, height};

    // Desenha a textura na tela
    SDL_RenderCopy(renderer, image_texture, NULL, &dest_rect);

    // Libera a textura
    SDL_DestroyTexture(image_texture);
}

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

void formatarTempo(char *stringFormatada, int minutos, int segundos) {
    sprintf(stringFormatada, "%02d:%02d", minutos, segundos);
}



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
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 1:
            if(jogo->descarte.indice>0){
                desenha_carta_header(renderer,&jogo->descarte.cartas[jogo->descarte.indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 3:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 4:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 5:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
            break;
        case 6:
            if(jogo->fundacao[i-3].indice>0){
                desenha_carta_header(renderer,&jogo->fundacao[i-3].cartas[jogo->fundacao[i-3].indice-1],
                                    "../assets/images/cards", cartas_desenho.x, cartas_desenho.y);
            }
            else  draw_rectangle(renderer,cartas_desenho.x,cartas_desenho.y,CARD_WIDTH,CARD_HEIGHT,C_CARDS_BACK,TRUE);
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

    // Atualize a tela (renderize)
    SDL_RenderPresent(renderer);

}

void destroy_window(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    TTF_CloseFont(*font);
    TTF_Quit();

    SDL_Quit();
}


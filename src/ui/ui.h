<<<<<<< Updated upstream
=======
#ifndef UI_WM_H
#define UI_WM_H

#include "../include/common.h"
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH (DIST_HEADER_LEFT*2+CARD_WIDTH*7+CARDS_DIST*6)
#define WINDOW_HEIGHT 212
#define WINDOW_POS 100


#define HEADER_WIDTH 691
#define HEADER_HEIGHT 50

#define CARD_WIDTH 73
#define CARD_HEIGHT 97

#define CARDS_DIST 30

#define DIST_HEADER_TOP 15
#define DIST_HEADER_LEFT 50

int inicializar_grafico();
void renderizar_game(void);
void tecla_pressionada(GLFWwindow* window, int key, int scancode, int action, int mods);
void desenhar_retangulo(float x, float y, float largura, float altura, float cor_r, float cor_g, float cor_b);
void renderizar_header(void);

<<<<<<< Updated upstream
#endif
>>>>>>> Stashed changes
=======
#endif
>>>>>>> Stashed changes

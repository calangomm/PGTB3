<<<<<<< Updated upstream
<<<<<<< Updated upstream

=======
#include "../include/common.h"
#include <GLFW/glfw3.h>


=======
#include "../include/common.h"
#include <GLFW/glfw3.h>


>>>>>>> Stashed changes
GLFWwindow* janela;

int inicializar_grafico() {
    // Inicializar o GLFW
    if (!glfwInit()) {
        // Tratamento de erro
        fprintf(stderr, "Erro ao inicializar o GLFW\n");
        return -1;
    }

    // Configurar o GLFW para usar OpenGL versão 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    janela = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Meu Jogo OpenGL", NULL, NULL);

    if (!janela) {
        // Tratamento de erro
        glfwTerminate();
        return -1;
    }

    // Tornar a janela atual
    glfwMakeContextCurrent(janela);

    // Configurar a função de retorno de chamada para teclas
    glfwSetKeyCallback(janela, tecla_pressionada);

    printf("OpenGL %s\n", glGetString(GL_VERSION));

    return 0; // Indica que a inicialização foi bem-sucedida
}

void desenhar_retangulo(float x, float y, float largura, float altura, float cor_r, float cor_g, float cor_b) {
    // Adiciona mensagens de depuração
    printf("Desenhando retângulo nas coordenadas: x=%.2f, y=%.2f, largura=%.2f, altura=%.2f\n", x, y, largura, altura);

    // Definir a cor do retângulo
    glColor3f(cor_r, cor_g, cor_b);

    // Desenhar o retângulo usando triângulos
    glBegin(GL_QUADS);
    glVertex2f(x, y);                // Canto superior esquerdo
    glVertex2f(x + largura, y);      // Canto superior direito
    glVertex2f(x + largura, y - altura); // Canto inferior direito
    glVertex2f(x, y - altura);        // Canto inferior esquerdo
    glEnd();
}



void renderizar_header(void){
    //desenha o fundo do header
    printf("Renderizando o cabeçalho...\n");
    desenhar_retangulo(DIST_HEADER_LEFT, DIST_HEADER_TOP, HEADER_WIDTH, HEADER_HEIGHT, 0.5f, 0.5f, 0.5f);  // Cor cinza
}

void renderizar_game(void) {
    // Definir a cor de fundo (41/255, 153/255, 97/255)
    glClearColor(41.0f / 255.0f, 153.0f / 255.0f, 97.0f / 255.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    renderizar_header();

    glfwSwapInterval(1);

    glfwWaitEventsTimeout(0.01);
    // Processar eventos
    glfwPollEvents();

    glfwSwapBuffers(janela);
}

void tecla_pressionada(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);  // Sinaliza para fechar a janela
    }
}

<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

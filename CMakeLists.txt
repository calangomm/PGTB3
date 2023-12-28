# Define a versão mínima do CMake necessária para compilar o projeto.
cmake_minimum_required(VERSION 3.16)

# Define o nome do projeto e sua versão.
project(SolitarioGame VERSION 1.0)

# Encontra o caminho para os cabeçalhos da biblioteca SDL (Simple DirectMedia Layer).
find_path(SDL_INCLUDE_DIRS SDL.h PATHS "/usr/include/SDL2")

# Encontra a biblioteca SDL.
find_library(SDL_LIBRARIES NAMES SDL2)

# Encontra o caminho para os cabeçalhos da biblioteca SDL_ttf (TrueType Font library for SDL).
find_path(SDL_TTF_INCLUDE_DIRS SDL_ttf.h PATHS "/usr/include/SDL")

# Encontra a biblioteca SDL_ttf.
find_library(SDL_TTF_LIBRARIES NAMES SDL2_ttf)

# Encontra o caminho para os cabeçalhos da biblioteca SDL_image (Image loading library for SDL).
find_path(SDL_IMAGE_INCLUDE_DIRS SDL_image.h PATHS "/usr/include/SDL2")

# Encontra a biblioteca SDL_image.
find_library(SDL_IMAGE_LIBRARIES NAMES SDL2_image)

# Inclui os diretórios dos cabeçalhos necessários.
include_directories(${SDL_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS})

# Obtém a lista de arquivos-fonte no diretório src e suas subpastas.
file(GLOB SOURCES "src/*.c" "src/game_logic/*.c" "src/utils/*.c" "src/ui/*.c")

# Cria um executável chamado 'game' usando os arquivos-fonte encontrados.
add_executable(game ${SOURCES})

# Liga as bibliotecas necessárias ao executável 'game'.
target_link_libraries(game ${SDL_LIBRARIES} ${SDL_TTF_LIBRARIES} ${SDL_IMAGE_LIBRARIES})

# Copia o diretório 'assets' para o diretório de compilação durante a construção.
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

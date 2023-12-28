# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(MeuProjetoC VERSION 1.0)

# Encontre o cabeçalho do SDL
find_path(SDL_INCLUDE_DIRS SDL.h PATHS "/usr/include/SDL2")

# Encontre a biblioteca do SDL
find_library(SDL_LIBRARIES NAMES SDL2)

# Encontre o cabeçalho do SDL_ttf
find_path(SDL_TTF_INCLUDE_DIRS SDL_ttf.h PATHS "/usr/include/SDL")

# Encontre a biblioteca do SDL_ttf
find_library(SDL_TTF_LIBRARIES NAMES SDL2_ttf)

# Encontre a biblioteca SDL2_image
find_path(SDL_IMAGE_INCLUDE_DIRS SDL_image.h PATHS "/usr/include/SDL2")

# Encontre a biblioteca do SDL2_image
find_library(SDL_IMAGE_LIBRARIES NAMES SDL2_image)

# Inclua os diretórios de cabeçalho da SDL, SDL_ttf, SDL2_image
include_directories(${SDL_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} ${SDL_IMAGE_INCLUDE_DIRS})

# Lista de todos os arquivos .c em src
file(GLOB SOURCES "src/*.c" "src/game_logic/*.c" "src/utils/*.c")

# Cria o executável game a partir dos arquivos .c
add_executable(game ${SOURCES})

# Link com as bibliotecas SDL, SDL_ttf, SDL2_image
target_link_libraries(game ${SDL_LIBRARIES} ${SDL_TTF_LIBRARIES} ${SDL_IMAGE_LIBRARIES})

# Copie o diretório de assets para o diretório de build
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

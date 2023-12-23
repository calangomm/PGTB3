# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(MeuProjetoC VERSION 1.0)

# Encontre a biblioteca SDL2
find_package(SDL2 REQUIRED)

# Encontre a biblioteca SDL_ttf
find_package(SDL_ttf REQUIRED)

# Inclua os diretórios de cabeçalho da SDL2, SDL_ttf e pg
include_directories(${SDL2_INCLUDE_DIRS} ${SDL_TTF_INCLUDE_DIRS} "/usr/local/include")


# Lista de todos os arquivos .c em src
file(GLOB SOURCES "src/*.c" "src/game_logic/*.c" "src/utils/*.c")

# Cria o executável main a partir dos arquivos .c
add_executable(game ${SOURCES})

# Link com as bibliotecas SDL2, SDL_ttf e pg
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL_TTF_LIBRARIES} -L/caminho/para/bibliotecas -lpg)

# Copie o diretório de assets para o diretório de build
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
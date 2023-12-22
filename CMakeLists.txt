# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(MeuProjetoC VERSION 1.0)

# Lista de todos os arquivos .c em src
file(GLOB SOURCES "src/*.c" "src/game_logic/*.c" "src/utils/*.c" "src/ui/*.c" "/usr/local/include/pg/*.c")

# Adiciona o diretório src à lista de diretórios incluídos
include_directories(src /usr/local/include/pg)

# Encontrar a biblioteca SDL2
find_package(SDL2 REQUIRED)

# Adicionar os diretórios de inclusão do SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Encontrar a biblioteca SDL_ttf
find_package(SDL_ttf REQUIRED)

# Adicionar os diretórios de inclusão do SDL_ttf
include_directories(${SDL_TTF_INCLUDE_DIRS})

# Cria o executável main a partir dos arquivos .c
add_executable(main ${SOURCES})

# Adicionar os arquivos do SDL2 e SDL_ttf às bibliotecas que devem ser linkadas
target_link_libraries(main ${SDL2_LIBRARIES} ${SDL_TTF_LIBRARIES})

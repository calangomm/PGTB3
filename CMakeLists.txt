# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)  # Pode ajustar a versão conforme necessário

project(MeuProjetoC VERSION 1.0)

# Lista de todos os arquivos .c em src
file(GLOB SOURCES "src/*.c" "src/game_logic/*.c" "src/utils/*.c" "src/ui/*.c")

# Adiciona o diretório src à lista de diretórios incluídos
include_directories(src)

# Cria o executável main a partir dos arquivos .c
add_executable(main ${SOURCES})

# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)  # Pode ajustar a versão conforme necessário

project(MeuProjetoC VERSION 1.0)

# Lista de todos os arquivos .c em src
file(GLOB SOURCES "src/*.c" "src/game_logic/*.c" "src/utils/*.c")

# Adiciona o diretório src à lista de diretórios incluídos
<<<<<<< Updated upstream
include_directories(src)

# Cria o executável main a partir dos arquivos .c
add_executable(main ${SOURCES})
=======
include_directories(src /usr/local/include/pg)

# Encontrar a biblioteca GLFW
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})

# Cria o executável main a partir dos arquivos .c
add_executable(main ${SOURCES})

# Link com as bibliotecas do GLFW e OpenGL
target_link_libraries(main glfw)
target_link_libraries(main GL)

# Adicionar os arquivos do GLFW às bibliotecas que devem ser linkadas
target_link_libraries(main ${GLFW_LIBRARIES})
>>>>>>> Stashed changes

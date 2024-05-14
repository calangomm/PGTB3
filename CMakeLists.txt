cmake_minimum_required(VERSION 3.10)
project(game C)

# Configurar a versão do C
set(CMAKE_C_STANDARD 11)

# Configurar as pastas de código-fonte
set(SOURCE_FILES
    src/game_logic/game_logic.c
    src/game_logic/game_logic.h
    src/include/common.h
    src/main.c
    src/ui/ui.c
    src/ui/ui.h
    src/utils/utils.c
    src/utils/utils.h
)

# Adicionar o diretório de headers
include_directories(
    src/game_logic
    src/include
    src/ui
    src/utils
    dependencies/SDL2/include  # Incluindo diretório de headers do SDL2
    dependencies/SDL2
    dependencies/SDL2_image  # Incluindo diretório de headers do SDL2_image
    dependencies/SDL2_ttf # Incluindo diretório de headers do SDL2_ttf
    dependencies/FreeType/include  # Incluindo diretório de headers do FreeType
)

# Adicionar o executável
add_executable(game ${SOURCE_FILES})

# Configurar manualmente o FreeType
set(FREETYPE_LIBRARIES 
    "${CMAKE_SOURCE_DIR}/dependencies/freetype-2.11.0/objs/.libs/libfreetype.a"
    "-lpthread"
    "-lpng"  # Adicionar a biblioteca PNG
    "-lz"  # Adicionar a biblioteca zlib
    "-lm"  # Adicionar a biblioteca libm
    "-ldl"
)
set(SDL2_LIBRARIES
    "${CMAKE_SOURCE_DIR}/dependencies/SDL2/libSDL2.a"
    "${CMAKE_SOURCE_DIR}/dependencies/SDL2/build/.libs/libSDL2.a"
)
set(SDL2_IMAGE_LIBRARIES
    "${CMAKE_SOURCE_DIR}/dependencies/SDL2_image/libSDL2_image.a"
    "${CMAKE_SOURCE_DIR}/dependencies/SDL2_image/.libs/libSDL2_image.a"
)
set(SDL2_TTF_LIBRARIES
    "${CMAKE_SOURCE_DIR}/dependencies/SDL2_ttf/.libs/libSDL2_ttf.a"
)

# Adicionar as bibliotecas
target_link_libraries(game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${FREETYPE_LIBRARIES})

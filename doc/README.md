A documentação do proffs é uma merda, não use ela, uso de ram vai pro krlho sempre

#Estrutura básica:
src/: Para códigos-fonte.
lib/: Para bibliotecas externas, como 'libpg'.
assets/: Para recursos gráficos, como imagens de cartas.
doc/: Para documentação do projeto.
bin/: Para arquivos executáveis compilados.

#Recomendação de estrutura:
src/: Contém o código fonte do seu projeto.
	main.c: Ponto de entrada do programa.
	game_logic/: Funções relacionadas à lógica do jogo.
	ui/: Código para a interface de usuário e renderização.
	utils/: Funções utilitárias, como manipulação de strings, etc.
	include/: Para arquivos de cabeçalho (.h) que declaram funções e estruturas a serem compartilhadas entre diferentes partes do código.

lib/: Bibliotecas externas, como a 'libpg'.

assets/: Recursos gráficos e de mídia.
	images/: Imagens das cartas e fundos.
	fonts/: Tipos de letras, se necessário.

doc/: Documentação do projeto.
	README.md: Instruções gerais e descrição do projeto.
	Outros documentos que explicam o design e a implementação (PDF da atividade...).

tests/: Testes unitários e de integração. (Se você fizer, eu normalmente n faço teste unitario em trabalho)

bin/: Arquivos executáveis compilados.

scripts/: Scripts úteis, como scripts de build.

Bibliografia:

www.youtube.com/watch?v=XfZ6WrV5Z7Y -- Creating a Game Loop with C & SDL (Tutorial)

wiki.libsdl.org

https://stackoverflow.com/questions/75622498/cmake-cannot-find-sdl2-no-matter-what-i-try

https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html

https://www.doxygen.nl/

https://microtek.ac.in/adminassets/pdf/C_programming_notes_.pdf

Sites para verificação dos pixels:

https://pixspy.com/

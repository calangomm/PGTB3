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

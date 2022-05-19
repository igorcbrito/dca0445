
### Exercício 2.2 - 1:

O objetivo deste exercício consiste em pegar dois pontos inseridos pelo usuário, desde que sejam dentro das dimensões da imagem selecionada, e com base nesses dois pontos formar uma área retangular com tons invertidos (negativo). Para construir o programa, foi utilizado como base o código pixels.cpp cedido pelo professor.

Inicialmente, foi utilizado uma estrutura de dado de par para representar os pontos P1 e P2 e também suas coordenadas. Após lidas as posições x e y de cada um dos pontos, foi criada uma validação para que se garanta que o programa não funcione com pontos inválidos, como valores negativos e também coordenadas que estejam fora da figura escolhida.

Para criar a área negativa, bastou-se alterar o preenchecimento dos pixels dentro da área demarcada pelos pontos P1 e P2 por seus valores multiplicados por -1.


### Exercício 2.2 - 2:

O objetivo deste exercício consistem em realizar a troca dos quadrantes nas diagonais de uma figura. O código usado como base para criação do programa foi o pixels.cpp, onde foi realizada a criação de novas variáveis matriciais no tamanho exato de cada quadrante quadrante da figura.
Após a criação das matrizes que representam os quadrantes, foram utilizadas estruturas de loop for para copiar cada pixel de cada quadrante para as matrizes correspondentes. 
Em seguida foram utilizados outros loops para criar a nova imagem completa, substituindo com a ajuda de deslocamentos na variável de iteração do loop, os quadrantes.
Resumindo, a imagem escolhida foi separada em quatro imagens menores, uma com cada quadrante da imagem original. Em seguida, uma nova imagem foi preenchida realizando a troca dos quadrantes nas diagonais.

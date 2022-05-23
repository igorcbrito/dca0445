Exercício 5.2:

Neste exercício, foi pedido que se adicione um novo tipo de filtragem espacial, o filtro laplaciano do gaussiano. 
Como o nome sugere, o filtro antes de aplicar a detecção de bordas laplaciana, realiza uma suaviação de por meio do filtro gaussiano a fim de atenuar ruídos que podem
atrapalhar na detecção de bordas.

O kernel, ou máscara, utilizada na filtragem é representada por uma matriz 5x5 originada a partir da expressão abaixo.

As adaptações necessárias no código addwheited.cpp cedido pelo professor, consistem na adição da matriz do filtro laplaciano do gaussiano e também em uma nova opção do
switch case para selecionar a aplicação do filtro. Ao apertar 'x' o usuário pode verificar o resultado como o obtido abaixo.


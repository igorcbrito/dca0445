### Exercício 4.2.1

Neste exercício, foi proposto a realização de uma equalização em um vídeo capturado pela webcam do computador em tempo real, considerando o processamento das imagens em tons de cinza.

Sendo assim, após a captura das imagens pela webcam, foi feito uma conversão de cores da fonte de imagem para uma escala de tons de cinza utilizando a função cvtColor(image, imageGrayscale, cv::COLOR_RGB2GRAY, 0); do opencv que transforma o padrão de cores da imagem para uma escala de tons de cinza e copia para uma outra matriz.

Logo em seguida, foi utilizada a função equalizeHist(imageGrayscale, imageGrayscale); que realiza a equalização do histograma da imagem.   
Vale salientar que todo o processamento feito nas imagens ocorreu quadro a quadro do vídeo.

Como resultado, nota-se um aumento no contraste da imagem, mas que em algumas situações causa o efeito de falso contorno, como na imagem abaixo.

Repare, que durante a transição de uma cena escura para uma clara, é produzido um contorno no fundo da imagem que não existe, de fato.

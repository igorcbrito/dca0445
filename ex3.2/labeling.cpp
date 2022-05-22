#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

// falta terminar

int main(int argc, char** argv){
  cv::Mat image, realce;
  int width, height;
  int nobjects;
  //int fundo_ = 0;
  
  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }

  width=image.cols;
  height=image.rows;
  std::cout << width << "x" << height << std::endl;

  p.x=0;
  p.y=0;

  // excluir objetos das bordas
  // percorrer as bordas e execultar o floodfill, quando achar uma bolha que esta na bordar colorir com o fundo
  nobjects=0;
  for(int i=0; i<height; i++){ // percorrendo as linhas ( o y) 
    if(image.at<uchar>(i,0) == 255){
        // achou um objeto
        p.x=0;
        p.y=i;
  		// preenche o objeto com a cor de fundo
		  cv::floodFill(image,p,0);
    } 
    if(image.at<uchar>(i,height-1) == 255){
        // achou um objeto
        p.x=height-1;
        p.y=i;
  		// preenche o objeto com a cor de fundo
		  cv::floodFill(image,p,0);
    }  
  } 
  for(int j=0; j<width; j++){
    if(image.at<uchar>(0,j) == 255){
        // achou um objeto
        p.x=j;
        p.y=0;
  		// preenche o objeto com a cor de fundo
		  cv::floodFill(image,p,0);
    }
    if(image.at<uchar>(width-1,j) == 255){
        // achou um objeto
        p.x=j;
        p.y=width-1;
  		// preenche o objeto com a cor de fundo
		  cv::floodFill(image,p,0);
    }  
  }

  // pinta as bolhas de cinza(contando)
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
        // achou um objeto
        nobjects++;
        p.x=j;
        p.y=i;
  		// preenche o objeto com o contador
		  cv::floodFill(image,p,nobjects);
      }
    }
  }
  cv::imwrite("labeling_gray.png", image);

  // Agora pintamos o fundo da imagem, de outra cor
  // Pintando de branco, o fundo vai se diferenciar dos buracos(preto), e das bolhas(cinza)
  // O ponto 0,0 faz parte do fundo
  p.x=0;
  p.y=0;
  cv::floodFill(image,p,255);

  // Com o fundo branco podemos percorrer a imagem procurando buracos(pretos), e realizar a contagem.
  int bolhas = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if((int)image.at<uchar>(i,j) == 0 && (int)image.at<uchar>(i,j-1) != 255){
        std::cout << "PASSOU"; 
        bolhas++;
        p.x=j;
        p.y=i;
        cv::floodFill(image,p,255);
        p.x=j-1;
        p.y=i;
        cv::floodFill(image,p,255);
      }
      else if((int)image.at<uchar>(i,j) == 0){
        std::cout << "1pizza2";
        p.x=j;
        p.y=i;
        floodFill(image,p,255);
      }
    }  
  }

  std::cout << "a figura tem " << nobjects << " bolhas\n";
  std::cout << "Sendo " << bolhas << " bolhas com buracos\n";
  std::cout << "E " << nobjects-bolhas << " bolhas sem buracos\n";
  cv::equalizeHist(image, realce);
  cv::imshow("image", image);
  cv::imshow("realce", realce);
  cv::imwrite("labeling.png", image);
  cv::imwrite("labeling-edges.png", realce);
  cv::waitKey();
  return 0;
}

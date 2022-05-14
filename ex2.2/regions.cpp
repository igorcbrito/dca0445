#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>

using namespace cv;
using namespace std;

int main(int, char**){
  cv::Mat image;
  cv::Vec3b val;

  pair<int, int> p1;
  pair<int, int> p2;

  image= cv::imread("pikachu.jpg",cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "A imagem não foi aberta!" << std::endl;

  cout << "Informe a coordenada horizontal do primeiro ponto: ";
  cin >> p1.first;

  cout << endl << "Informe a posição vertical do primeiro ponto: ";
  cin >> p1.second;

  cout << endl << "Informe a coordenada horizontal do segundo ponto: ";
  cin >> p2.first;

  cout << endl << "Informe a coordenada vertical do segundo ponto: ";
  cin >> p2.second;

  if(p1.first < 0 || p1.second < 0 || p2.first < 0 || p2.second < 0){
    cout << endl << "Nao eh possivel utilizar coordenadas negativas!" << endl;
    return -1;
  }

  else if(p1.first > image.size().width || p2.first > image.size().width){
    cout << endl << "As coordenadas utilizadas excedem as dimensoes da imagem!" << endl;
    return -1;
  } 

  else if(p1.second > image.size().height || p2.second > image.size().height){
    cout << endl << "As coordenadas utilizadas excedem as dimensoes da imagem!" << endl;
    return -1;
  } 
  cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);

  cv::imshow("Original", image);  

  for(int i=p1.first;i<p2.first;i++){
    for(int j=p1.second;j<p2.second;j++){
      image.at<uchar>(i,j)*=-1;
    }
  }
  
  cv::namedWindow("Negativo", cv::WINDOW_AUTOSIZE);
  
  cv::imshow("Negativo", image);  
  cv::waitKey();
  
  return 0;
}

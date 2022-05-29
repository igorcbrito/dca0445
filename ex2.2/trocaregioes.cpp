#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//biel é uma imagem quadrada 256*256
int main(int, char**){
  cv::Mat image;// quarter1, quarter2, quarter3, quarter4, aux;
  cv::Mat quarter1(128,128, CV_8U);
  cv::Mat quarter2(128,128, CV_8U);
  cv::Mat quarter3(128,128, CV_8U);
  cv::Mat quarter4(128,128, CV_8U);
  cv::Mat aux(256,256, CV_8U);
  cv::Vec3b val;

  image= cv::imread("biel.png",cv::IMREAD_GRAYSCALE);

  if(!image.data)
    std::cout << "A imagem nao foi aberta!" << std::endl;

  cv::namedWindow("Trocado", cv::WINDOW_AUTOSIZE);

  cout << "Tamanho pela metade: " << image.size().width/2;
  cout << "Tamanho pela metade: " << image.size().height/2 << endl;
  

  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      quarter1.at<uchar>(i,j)=image.at<uchar>(i,j);
    }
  }

  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      quarter2.at<uchar>(i,j)=image.at<uchar>(i,j+image.size().width/2);
    }
  }

  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      quarter3.at<uchar>(i,j)=image.at<uchar>(i+image.size().height/2,j);
    }
  }
   
  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      quarter4.at<uchar>(i,j)=image.at<uchar>(i+image.size().height/2,j+image.size().width/2);
    }
  }

  // Preencher nova imagem

  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      aux.at<uchar>(i,j)=quarter4.at<uchar>(i,j);
    }
  }

  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      aux.at<uchar>(i,j+image.size().width/2)=quarter3.at<uchar>(i,j);
    }
  }

  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      aux.at<uchar>(i+image.size().height/2,j)=quarter2.at<uchar>(i,j);
    }
  }
   cout << "Até aqui ok!"<< endl;
  for(int i=0;i<image.size().width/2;i++){
    for(int j=0;j<image.size().height/2;j++){
      aux.at<uchar>(i+image.size().height/2,j+image.size().width/2)=quarter4.at<uchar>(i,j);
    }
  }

  cv::imshow("Trocado", aux);  
  cv::imwrite("Trocado.png", aux);
  cv::waitKey();
  return 0;
}

#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, char** argv){
  cv::Mat image, imageGrayscale, realce;
  int width, height;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes, output;
  cv::Mat histR, histG, histB;
  int nbins = 64;
  int key;

	cap.open(0);
  
  if(!cap.isOpened()){
    std::cout << "cameras indisponiveis";
    return -1;
  }
  
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);  
  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "largura = " << width << std::endl;
  std::cout << "altura  = " << height << std::endl;

  int histw = nbins, histh = nbins/2;
  cv::Mat histImgR(histh, histw, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat histImgG(histh, histw, CV_8UC3, cv::Scalar(0,0,0));
  cv::Mat histImgB(histh, histw, CV_8UC3, cv::Scalar(0,0,0));

  while(1){
    cap >> image;

    cvtColor(image, imageGrayscale, cv::COLOR_RGB2GRAY, 0);
    cv::equalizeHist(imageGrayscale, imageGrayscale);
    std::cout << "RAPARIGA" << std::endl;
 
    cv::imshow("Ao vivo", imageGrayscale);
    key = cv::waitKey(30);
    if(key == 27) break;
  }
  return 0;
}

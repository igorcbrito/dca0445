#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image;
  int width, height;
  cv::VideoCapture cap;
  std::vector<cv::Mat> planes;
  cv::Mat histR, histG, histB, oldHist;
  int nbins = 64;
  float range[] = {0, 255};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  int key;
  double hist_comp;
  double calibration_threshold = 1; // inicia como se os histogramas fossem iguais
  int cont = 0;
  bool firstImage= true;


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
    cv::split (image, planes);
    cv::calcHist(&planes[0], 1, 0, cv::Mat(), histR, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    cv::calcHist(&planes[1], 1, 0, cv::Mat(), histG, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    cv::calcHist(&planes[2], 1, 0, cv::Mat(), histB, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    
    cv::normalize(histR, histR, 0, histImgR.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(histG, histG, 0, histImgG.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(histB, histB, 0, histImgB.rows, cv::NORM_MINMAX, -1, cv::Mat());
    
    histImgR.setTo(cv::Scalar(0));
    histImgG.setTo(cv::Scalar(0));
    histImgB.setTo(cv::Scalar(0));
    
    for(int i=0; i<nbins; i++){
      cv::line(histImgR,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histR.at<float>(i))),
               cv::Scalar(0, 0, 255), 1, 8, 0);
      cv::line(histImgG,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histG.at<float>(i))),
               cv::Scalar(0, 255, 0), 1, 8, 0);
      cv::line(histImgB,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histB.at<float>(i))),
               cv::Scalar(255, 0, 0), 1, 8, 0);
    }
    histImgR.copyTo(image(cv::Rect(0, 0       ,nbins, histh)));
    histImgG.copyTo(image(cv::Rect(0, histh   ,nbins, histh)));
    histImgB.copyTo(image(cv::Rect(0, 2*histh ,nbins, histh)));
    cv::imshow("image", image);
    key = cv::waitKey(30);
    
    // Vamos usar o canal azul para identificar o movimento
    // Apenas uma componente de cor é suficiente
    // primeiro capturamos a imagem estática para calibrar o programa, pois devido ao ruído da câmera podemos ter 'falsa detecção'

    // calibração --> as primeiras 100 imagens serão usadas para calibrar
    
    if(firstImage==true){
      std::cout << std::endl << std::endl;
      std::cout << "Deixe a camera estática para calibração  " << std::endl;
      std::cout << "As primeiras 100 imagens serão usadas  " << std::endl;
    }

    if(firstImage == false){
      hist_comp = compareHist(histB, oldHist, cv::HISTCMP_CORREL);
        if(cont<100){
          if(calibration_threshold > hist_comp)  calibration_threshold = hist_comp;
          cont++;
          if(cont == 100){
            calibration_threshold = calibration_threshold * 0.95; // 95% --> safety margin
            std::cout << "Calibrado com limiar de: "<< calibration_threshold << std::endl;
          }
        }else{
          if( hist_comp < calibration_threshold){
              std::cout << "MOVIMENTO DETECTADO!!!  \a" << std::endl;
          }
        }
        
    }

    histB.copyTo(oldHist);
    firstImage = false;
    
    if(key == 27) break;
    
  }

  return 0;
}

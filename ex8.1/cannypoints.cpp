#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 4
//#define JITTER 4
#define RAIO 3

int top_slider = 10;
int top_slider_max = 200;

int top_slider2 = 3;
int top_slider_max2 = 5;

int top_jitter = 4;
int top_jitter_max = 6;

char TrackbarName[50];
char TrackbarName2[50];
char TrackbarName3[50];

vector<int> yrange;
vector<int> xrange;
Mat image, border, image2, points; // image2 is gray - canny
int width, height, x, y;
Vec3b colors;

void on_trackbar_canny(int, void*){
  //if(top_jitter<1) top_jitter = 1;
  Canny(image2, border, top_slider, 3*top_slider);
  imshow("Canny Points", border);

//tava aqui
 
  random_shuffle(xrange.begin(), xrange.end());
  
  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){

      x = i+rand()%(2*(top_jitter+1))-(top_jitter+1)+1;
      y = j+rand()%(2*(top_jitter+1))-(top_jitter+1)+1;
    
      if(border.at<uchar>(i, j) != 0){ // encontrado uma região de borda por canny 
        colors = image.at<Vec3b>(x,y);
        circle(points, cv::Point(y,x),top_slider2, CV_RGB(colors[2],colors[1],colors[0]), -1, CV_8UC3);
      }else{
        colors = image.at<Vec3b>(x,y);
        circle(points, cv::Point(y,x),RAIO, CV_RGB(colors[2],colors[1],colors[0]), -1, CV_8UC3);
      }
    }
  }
  
   imshow("Canny_points output",points);
}

int main(int argc, char** argv){
  int width, height;

  image= imread(argv[1],cv::IMREAD_COLOR);
  if(!image.data) cout << "Erro na abertura da imagem." << endl;
  cvtColor(image,image2, cv::COLOR_BGR2GRAY);
  imwrite("imggray.jpg", image2);
  
  width=image.size().width;
  height=image.size().height;

  points = Mat(height, width, CV_8UC3, Scalar(255,255,255));

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0); 
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  sprintf( TrackbarName, "Threshold", top_slider_max );
  sprintf( TrackbarName2, "Raio", top_slider_max2 );
  sprintf( TrackbarName3, "Jitter>=1", top_jitter_max );

  namedWindow("Canny Points",1);
  createTrackbar( TrackbarName, "Canny Points",
                &top_slider,
                top_slider_max,
                on_trackbar_canny );

  createTrackbar( TrackbarName2, "Canny Points",
                  &top_slider2,
                  top_slider_max2,
                  on_trackbar_canny );
  
    createTrackbar( TrackbarName3, "Canny Points",
                  &top_jitter,
                  top_jitter_max,
                  on_trackbar_canny );
  on_trackbar_canny(top_slider, 0 );

  waitKey();
  imwrite("cannyborders.png", border);
  imwrite("pontos.jpg", points);
  return 0;
}



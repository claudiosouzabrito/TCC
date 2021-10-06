// C++ program for the above approach
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
using namespace cv;
using namespace std;
  
// Driver code
int main(){
    
  Mat image = imread("map.png",1); //447 x 220 = 98.340    

  map<int, int> diffPixels;

  for(int i=0; i < image.rows; i++){
    
    for(int j=0; j < image.cols; j++){

      int pixel = image.at<Vec3b>(i, j)[2];
      if(diffPixels.find(pixel) == diffPixels.end()){
        diffPixels[pixel] = 1;
      }

      
    }
  }

  // circle(image, Point(1,110),0, Scalar(0,255,0));
  for(auto it = diffPixels.cbegin(); it != diffPixels.cend(); ++it){
    cout << it->first << "\n";
  }
  // imshow("mapa", image);
  // waitKey(0);
  // imwrite("mappos.png", image);

  return 0;
}
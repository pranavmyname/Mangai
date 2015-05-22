#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "fun.h"
#include<iostream>

using namespace cv;
using namespace std;

int th=200;

void findcircles(Mat img,int M, int N,bool a[]){
    Mat dst,roi;
    int ctr=0;
    vector<Vec3f> circles;
    //roi.copyTo(img1);
    for (int i=0;i<img.rows;i+=img.rows/M){
            for(int j=0;j<img.cols;j+=img.cols/N){
                    roi=img(Rect(j,i,img.cols/M,img.rows/N));
                    cvtColor(roi,dst,CV_RGB2GRAY);
                    GaussianBlur(dst,dst,Size(9,9),2,2);
                    HoughCircles(dst,circles,CV_HOUGH_GRADIENT,1,dst.rows/8,th,100,0,0);
                    a[ctr]=(circles.size());

                    cout<<a[ctr]<<endl;
                    ctr++;
            }
    }
}
int main(int argc, char *argv[])
{
    Mat img;
    bool a[4];
    img = imread("cir.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;
//    namedWindow( "lena", CV_WINDOW_KEEPRATIO );
//    namedWindow( "roi1", CV_WINDOW_KEEPRATIO );
//    imshow("lena", img);
    //dst=Mat::zeros(img.size(),CV_8UC1);
    //img.copyTo(img1);
    //namedWindow("output",CV_WINDOW_KEEPRATIO);
    //createTrackbar("Threshold","output",&th,500,findcircles);
    findcircles(img,2,2,a);
    for(int i=0;i<4;i++) cout<<a[i]<<endl;

    waitKey(0);
}




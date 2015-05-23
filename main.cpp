#include <opencv2/core/core.hpp>
#include<opencv/cv.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "fun.h"
#include<iostream>

using namespace cv;
using namespace std;

int th=70;

void imagegrab(Mat img,int &x,int &y,int &width,int &height)
{
    Mat dst;
    int lx=10000,mx=0,ly=10000,my=0;
    vector<Vec3f> circles;
    cvtColor(img,dst,CV_RGB2GRAY);
    HoughCircles(dst,circles,CV_HOUGH_GRADIENT,1,dst.rows/8,70,20,0,20);
    for(int i=0;i<circles.size();i++)
    {
        if(circles[i][0]<lx) lx=circles[i][0];
        if(circles[i][0]>mx) mx=circles[i][0];
        if(circles[i][1]<ly) ly=circles[i][1];
        if(circles[i][1]>my) my=circles[i][1];
    }
    x=lx-20,y=ly-20;
    width=mx-lx+60,height=my-ly+60;
}
void findcircles(Mat img,int M, int N,int x,int y,int width,int height,bool a[]){
    Mat dst,roi;
    int ctr=0,lx=10000,mx=0,ly=10000,my=0;
    string name="a";
    vector<Vec3f> circles;
    //cout<<circles.size()<<"\t"<<lx<<"\t"<<mx<<"\t"<<ly<<"\t"<<my<<endl;
    Mat dekho=img(Rect(x,y,width,height));
    imshow("dekho",dekho);
    for (int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                    //cout<<"j= "<<j<<" i= "<<i<<endl;
                    roi=dekho(Rect(j*dekho.cols/M,i*dekho.rows/N,dekho.cols/M,dekho.rows/N));
                    cvtColor(roi,dst,CV_RGB2GRAY);
                    GaussianBlur(dst,dst,Size(9,9),2,2);
                    HoughCircles(dst,circles,CV_HOUGH_GRADIENT,1,dst.rows/8,th,20,0,20);
                    a[ctr]=(circles.size());
                    for( size_t i = 0; i < circles.size(); i++ )
                      {
                          Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                          int radius = cvRound(circles[i][2]);
                          //cout<<"radius = "<<radius<<endl;
                          // circle center
                          circle( roi, center, 3, Scalar(0,255,0), -1, 8, 0 );
                          // circle outline
                          circle( roi, center, radius, Scalar(0,0,255), 3, 8, 0 );
                       }
                    namedWindow(name,CV_WINDOW_AUTOSIZE);
                    imshow(name,roi);
                    name+=1;
                    cout<<circles.size()<<"\t";
                    ctr++;
            }
    }
}
int main(int argc, char *argv[])
{
    Mat img;
    bool a[4];
    VideoCapture vid(1);
    vid>>img;
    //img = imread("cir.jpg", CV_LOAD_IMAGE_COLOR);
    if(img.empty())
       return -1;
//    namedWindow( "lena", CV_WINDOW_KEEPRATIO );
//    namedWindow( "roi1", CV_WINDOW_KEEPRATIO );
//    imshow("lena", img);
    //dst=Mat::zeros(img.size(),CV_8UC1);
    //img.copyTo(img1);
    //namedWindow("output",CV_WINDOW_KEEPRATIO);
    //createTrackbar("Threshold","output",&th,500,findcircles);
    int x,y,width,height;
    imagegrab(img,x,y,width,height);
    cout<<"inside main "<<x<<"\t y=0"<<y<<"\t"<<width<<"  "<<height;
    while(waitKey(1000)<0){
            vid>>img;
            findcircles(img,2,2,x,y,width,height,a);
            cout<<endl;
    }
    for(int i=0;i<4;i++) cout<<a[i]<<endl;

    waitKey(0);
}




//M is not of rows
//N is no of cols
bool findcircles(Mat img,int M, int N){
    Mat dst,roi;
    bool a[M*N];
    //roi.copyTo(img1);
    for (int i=0;i<img.rows;i+=img.rows/M){
            for(int j=0;j<img.cols;j+=img.cols/N){
                    roi=img(Rect(j,i,img.cols/M,img.rows/N));
                    cvtColor(roi,dst,CV_RGB2GRAY);
                    GaussianBlur(dst,dst,Size(9,9),2,2);

                    vector<Vec3f> circles;
                    HoughCircles(dst,circles,CV_HOUGH_GRADIENT,1,dst.rows/8,th,100,0,0);
                    cout<<circles.size()<<endl;
            }
    }
    return circles.size();
}

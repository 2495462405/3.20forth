//
//  main.cpp
//  test
//
//  Created by 徐亦燊 on 2020/2/28.
//  Copyright © 2020 徐亦燊. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{

    cv::Mat binaryMat;
    cv::Mat labelMat;
    cv::Mat statsMat;
    cv::Mat centrMat;
    cv::Mat erodeMat;
    cv::Mat dilateMat;
    cv::Mat resultMat;
    cv::Mat srcMat = imread("/Users/xuyishen/Desktop/sa jiganyouhaximeiyouga/2020.3.20/3.20forth/clip.png", 0);
  bitwise_not(srcMat, srcMat);
    cv::threshold(srcMat, binaryMat, 0, 255, THRESH_OTSU);
  
    cv::Mat kernel;
    kernel=getStructuringElement(MORPH_ELLIPSE, Size(31,31));
    //cv::morphologyEx(binaryMat,binaryMat,cv::MORPH_OPEN,kernel);
    erode(binaryMat, erodeMat, kernel);
    erode(erodeMat, erodeMat, kernel);
    erode(erodeMat, erodeMat, kernel);
    dilate(erodeMat, dilateMat, kernel);
    dilate(dilateMat, dilateMat, kernel);
    int nComp = cv::connectedComponentsWithStats(binaryMat,labelMat,statsMat,centrMat, 8, CV_32S);
    
    int b=0;
    for (int i = 1; i < nComp; i++)
    {
        
        Rect bndbox;
        bndbox.x=statsMat.at<int>(i,0);
        bndbox.y=statsMat.at<int>(i,1);
        bndbox.width=statsMat.at<int>(i,2);
        bndbox.height=statsMat.at<int>(i,3);
        if(bndbox.width<40 or bndbox.height<40)
        {continue;}
        else
        {b=b+1;}
        rectangle(binaryMat,bndbox,CV_RGB(255,255,255),1,8,0);
    }
    cout <<"number is  "<< b << endl;
    imshow("binaryMat", binaryMat);
    imshow("frame", srcMat);
    waitKey(0);
    return 0;
}

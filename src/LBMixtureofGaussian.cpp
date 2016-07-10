#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include<typeinfo>
#include "LrTextureShadRem.h"
#include "ChromacityShadRem.h"
#include "GeometryShadRem.h"
#include "PhysicalShadRem.h"
#include "SrTextureShadRem.h"
//enableLBMixtureOfGaussians閫夌敤
#include "LBMixtureOfGaussians.h"
using namespace std;
using namespace cv;
bool isOverlap(const Rect & a, const Rect & b) {
	const Rect * l_rect = &a, *r_rect = &b;
	if (a.x > b.x) {
		const Rect * tmp = l_rect;
		l_rect = r_rect;
		r_rect = tmp;
	}
	if (l_rect->width < r_rect->x - l_rect->x)
		return false;
	else if (l_rect->y <= r_rect->y && l_rect->height >= r_rect->y - l_rect->y)
		return true;
	else if (l_rect->y > r_rect->y && r_rect->height >= l_rect->y - r_rect->y)
		return true;
	else
		return false;
}

void mergeRects(list<Rect> & rects) {
	int x = 0, y = 0, width = 0, height = 0;    //临时变量
	for (list<Rect>::iterator i = rects.begin(); i != rects.end();) {
		bool merged = false;    //多引入一个变量判断i是否被merge非常有用！
		list<Rect>::iterator j = i;
		for (j++; j != rects.end(); j++) {
			if (isOverlap(*i, *j)) {
				if (i->x < j->x) {
					x = i->x;
					width = max(j->x - i->x + j->width, i->width);
				} else {
					x = j->x;
					width = max(i->x - j->x + i->width, j->width);
				}
				if (i->y < j->y) {
					y = i->y;
					height = max(j->y - i->y + j->height, i->height);
				} else {
					y = j->y;
					height = max(i->y - j->y + i->height, j->height);
				}
				//合并
				j->x = x;
				j->y = y;
				j->width = width;
				j->height = height;
				i = rects.erase(i);    //删除被合并项。注意：删除前者（i）更新后者（j）！
				merged = true;
			}
		}
		if (!merged)
			i++;
	}
}
void save(Mat frame,Mat img_mask,Mat img_back,Mat img_deal,int i){
	  char n1[40];
	  char n2[40];
	  char n3[40];
	  char n4[40];
	  char path[40];
	  char path2[40];
  sprintf(path, "%s%s%d", "mkdir ","/home/zjl/test/03/", i);
  system(path);//创建一个文件夹
  sprintf(path2, "%s%d","/home/zjl/test/03/",i);
  sprintf(n1, "%s%s%s", path2,"/frame", ".jpg");
  sprintf(n2, "%s%s%s", path2, "/fg", ".jpg");
  sprintf(n3, "%s%s%s", path2, "/bg", ".jpg");
  sprintf(n4, "%s%s%s", path2, "/deal", ".jpg");
  imwrite(n1,frame);
  imwrite(n2,img_mask);
  imwrite(n3,img_back);
  imwrite(n4,img_deal);
}
int main(int argc, char **argv)
{
  CvCapture *capture = 0;

 // capture = cvCaptureFromCAM(0);
  capture = cvCaptureFromFile("/home/zjl/test/7.mp4");//Shadow Detection Source Code and Ground Truth Data
//MAH00231_clip.mp4
  if(!capture){
    std::cerr << "Cannot open initialize webcam!" << std::endl;
    return 1;
  }
  IplImage *frame = cvQueryFrame(capture);
  LBMixtureOfGaussians* bgs = new LBMixtureOfGaussians;

  int key = 0;
//  std::cout<<"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<std::endl;
  printf("hello\n");
  int i=0;
  while(key != 'q')
  {
	i++;
	for(int j=0;j<10;j++)
    frame = cvQueryFrame(capture);

    if(!frame) break;
    cv::Mat img_back(frame,true);
    cv::Mat img_input(frame,true);
    cv::Mat B=img_input;
   // cv::resize(img_input,img_input,cv::Size(320,240));
    //cv::imshow("input", img_input);
    cv::Mat img_mask;

    bgs->process(img_input, img_mask,img_back); // automatically shows the foreground mask image
   // std::cout<<"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<std::endl;
    //Mat erode_img_mask;
    erode(img_mask,img_mask,cv::Mat());
    dilate(img_mask,img_mask,cv::Mat());

    imshow("img_mask_0",img_mask);
    imshow("img_back",img_back);

    //shadow remove
    LrTextureShadRem lrTex;
    ChromacityShadRem chr;
    PhysicalShadRem phy;
    GeometryShadRem geo;
    SrTextureShadRem srTex;

    cv::Mat lrTexMask;
    //cout<<img_;
    //waitKey();
    //cout<<typeid(B).name()<<' '<<typeid(img_mask).name()<<' '<<typeid(img_back).name();
    //cvtColor(preimg,aftimg, CV_BGR2GRAY);
    //lrTex.removeShadows(B, img_mask, img_back, lrTexMask);
    cvtColor(img_mask,img_mask, CV_BGR2GRAY);
    //lrTex.removeShadows(B, img_mask, img_back, lrTexMask);
    //chr.removeShadows(B, img_mask, img_back, lrTexMask);
    phy.removeShadows(B, img_mask, img_back, lrTexMask);    //nengyong
    //geo.removeShadows(B, img_mask, img_back, lrTexMask);
    //srTex.removeShadows(B, img_mask, img_back, lrTexMask);  //keyong

    //if(i%10==0)
    	//save(frame,img_mask,img_back,lrTexMask,i);

    //findContours(lrTexMask,lrTexMask,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    imshow("lrTexMask",lrTexMask);
    IplImage img_erod =IplImage(lrTexMask);
    IplImage *img_erode=&img_erod;
    cvErode( img_erode,img_erode, NULL,1); //腐蚀
    cvDilate( img_erode,img_erode, NULL,1); //膨胀
    cvDilate( img_erode,img_erode, NULL,1); //膨胀
    cvDilate( img_erode,img_erode, NULL,1); //膨胀
    // yuan tu huan kuang
    vector<vector<Point> > contours;
    findContours(lrTexMask,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    list<Rect> rects;
    vector<vector<Point> >::iterator itc=contours.begin();
/*
    while(itc!=contours.end()){
        	Rect r0=boundingRect(*itc);
        	rectangle(lrTexMask,r0,cv::Scalar(255),2);
        	rectangle(B,r0,cv::Scalar(255),2);
        	//rects.push_back(r0);
        	cout << r0 <<"\n";
        	++itc;
    }
*/

    while(itc!=contours.end()){
    	Rect r0=boundingRect(*itc);
    	//cvRect r=cvRect();
    	cout<< r0<< "\n";
    	rects.push_back(r0);
    	++itc;
    }
    mergeRects(rects);
    itc=contours.begin();
    list<Rect>::iterator iter=rects.begin();
    while(iter!=rects.end()){
       //	Rect r0=boundingRect(*iter);
          	//rectangle(lrTexMask,ir,cv::Scalar(255),2);
          	//
    	//cout << *iter <<"\n";
       	rectangle(B,*iter,cv::Scalar(255),2);
        ++iter;
    }



    //if(!img_mask.empty())
    //  do something

    key = cvWaitKey(15);
  }
  std::cout<<"hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<std::endl;
  delete bgs;

  cvDestroyAllWindows();
  cvReleaseCapture(&capture);

  return 0;
}

//============================================================================
// Name        : test.cpp
// Author      : Venkatesh Lokare
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int beta=70;
double alpha=1.5;
double theta=30;

int main()
{
int hl;
cin>>hl;
Mat img = imread("pic.jpg", CV_LOAD_IMAGE_COLOR);
Mat new_image = Mat::zeros( img.size(), img.type() );
Mat new_image_con = Mat::zeros( img.size(), img.type() );
Mat new_image_rot = Mat::zeros( img.size(), img.type() );
Mat new_image_blur = Mat::zeros( img.size(), img.type() );
Mat new_image_sharp = Mat::zeros( img.size(), img.type() );
Mat histo = Mat::zeros( img.size()*2, img.type() );

//Bright
for(int y=0;y<img.rows;y++)
{
    for(int x=0;x<img.cols;x++)
    {
        // get pixel
        Vec3b color = img.at<Vec3b>(Point(x,y));

        // ... do something to the color ....
        float blue = color.val[0];
        float green = color.val[1];
        float red = color.val[2];

        //cout<<red<<" "<<green<<" "<<blue<<endl;
        for( int c = 0; c < 3; c++ )
                      {
              new_image.at<Vec3b>(x,y)[c] =
                 saturate_cast<uchar>(( img.at<Vec3b>(x,y)[c] ) + beta );
                     }
    }
}

//Contrast
for(int y=0;y<img.rows;y++)
{
    for(int x=0;x<img.cols;x++)
    {
        // get pixel
        Vec3b color = img.at<Vec3b>(Point(x,y));

        // ... do something to the color ....
        float blue = color.val[0];
        float green = color.val[1];
        float red = color.val[2];

        //cout<<red<<" "<<green<<" "<<blue<<endl;
        for( int c = 0; c < 3; c++ )
                      {
              new_image_con.at<Vec3b>(y,x)[c] =
                 saturate_cast<uchar>(alpha*( img.at<Vec3b>(y,x)[c] ) );
                     }
    }
}

//Rotate
int px,py,ox,oy;
 theta=(3.14/180)*theta;
 ox=img.cols/2;
 oy=img.rows/2;
 for(int y=0;y<img.rows;y++)
 {
     for(int x=0;x<img.cols;x++)
     {
         // get pixel
         Vec3b color = img.at<Vec3b>(Point(x,y));
         px = cos(theta) * (x-ox) - sin(theta) * (y-oy) + ox;
         py = sin(theta) * (x-ox) + cos(theta) * (y-oy) + oy;
         // set pixel
         if(px<img.cols && py<img.rows && py>0 && px>0)
        new_image_rot.at<Vec3b>(Point(px,py)) = color;
     }
 }


//BLur
 int kernel [5][5]= {{0,0,1,0,0},
                         {0,1,3,1,0},
                         {1,3,7,3,1},
                         {0,1,3,1,0},
                         {0,0,1,0,0}};
     int kernelSize = 5;
     int sumKernel = 27;
     int r,g,b;
     Vec3b color;

     for(int y=kernelSize/2; y<img.rows-(kernelSize/2); y++){
         for(int x=kernelSize/2; x<img.cols-(kernelSize/2); x++){

             r = 0;
             g = 0;
             b = 0;

             for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                 for(int j = -kernelSize/2; j<= kernelSize/2; j++){

                     color = img.at<Vec3b>(Point(x+i,y+j));
                     r += color.val[2]*kernel[kernelSize/2+i][kernelSize/2+j];
                     g += color.val[1]*kernel[kernelSize/2+i][kernelSize/2+j];
                     b += color.val[0]*kernel[kernelSize/2+i][kernelSize/2+j];
                 }
             }

             r = r/sumKernel;
             g = g/sumKernel;
             b = b/sumKernel;
             color.val[0]=b;
             color.val[1]=g;
			 color.val[2]=r;

             new_image_blur.at<Vec3b>(Point(x,y)) = color;

         }
     }

//Sharpen
     int kernel1 [3][3]= {{0,-1,0},
                            {-1,5,-1},
                            {0,-1,0}};
        int kernelSize1 = 3;
        int sumKernel1 = 1;
        int r1,g1,b1;
        Vec3b color1;

        for(int y=kernelSize1/2; y<img.rows-(kernelSize1/2); y++){
            for(int x=kernelSize1/2; x<img.cols-(kernelSize1/2); x++){

                r1 = 0;
                g1 = 0;
                b1 = 0;

                for(int i = -kernelSize1/2; i<= kernelSize1/2; i++){
                    for(int j = -kernelSize1/2; j<= kernelSize1/2; j++){
                    	  color1 = new_image_blur.at<Vec3b>(Point(x+i,y+j));
                        r1 += color1.val[2]*kernel1[kernelSize1/2+i][kernelSize1/2+j];
                        g1 += color1.val[1]*kernel1[kernelSize1/2+i][kernelSize1/2+j];
                        b1 += color1.val[0]*kernel1[kernelSize1/2+i][kernelSize1/2+j];
                    }
                }

                r1 = r1/sumKernel1;
                g1 = g1/sumKernel1;
                b1 = b1/sumKernel1;
                color1.val[0]=b1;
                color1.val[1]=g1;
                color1.val[2]=r1;

                new_image_sharp.at<Vec3b>(Point(x,y)) = color1;

            }
        }
//HIstogram
int reda[256],bluea[256],greena[256];
Vec3b Colo,white,redc,bluec,greenc,black;
white.val[0]=white.val[1]=white.val[2]=255;
redc.val[0]=redc.val[1]=redc.val[2]=0;
bluec.val[0]=bluec.val[1]=bluec.val[2]=0;
greenc.val[0]=greenc.val[1]=greenc.val[2]=0;
black.val[0]=black.val[1]=black.val[2]=0;

redc[2]=255;
bluec[0]=255;
greenc[1]=255;

for(int v=0;v<256;v++)
    greena[v]=bluea[v]=reda[v]=0;
double N=0;
for(int y=0;y<img.rows;y++)
{
for(int x=0;x<img.cols;x++)
    {
        // get pixel
        Vec3b color = img.at<Vec3b>(Point(x,y));

        // ... do something to the color ....
        int blue = color.val[0];
        int green = color.val[1];
        int red = color.val[2];
        reda[red]++;
        bluea[blue]++;
        greena[green]++;
        N++;
    }
}


for(int y=0;y<histo.rows;y++)
{
for(int x=0;x<histo.cols;x++)
    {
	histo.at<Vec3b>(Point(x,y)) = white;
    }
}

double sum_r=0,sum_b=0,sum_g=0;
for(int q=0;q<256;q++)
{
    sum_r+=reda[q]*q;
    sum_g+=greena[q]*q;
    sum_b+=bluea[q]*q;
}
double mean_r=sum_r/N,mean_g=sum_g/N,mean_b=sum_b/N;


double tot_r=0,tot_g=0,tot_b=0;
for(int q=0;q<256;q++)
{
    tot_r+=reda[q]*(q-mean_r)*(q-mean_r);
    tot_g+=greena[q]*(q-mean_g)*(q-mean_g);
    tot_b+=bluea[q]*(q-mean_b)*(q-mean_b);
}
double SD_R=sqrt(tot_r/N),SD_G=sqrt(tot_g/N),SD_B=sqrt(tot_b/N);

cout<<"Red Mean::"<<mean_r<<" Red Sd::"<<SD_R<<endl;
cout<<"Green Mean::"<<mean_g<<" Green Sd::"<<SD_G<<endl;
cout<<"BLue Mean::"<<mean_b<<" BLue Sd::"<<SD_B<<endl;

//to draw horizontal line
for(int x=0;x<1000;x++)
{
histo.at<Vec3b>(Point(x,700)) = black;
}

//to draw vertical line
for(int y=0;y<720;y++){
histo.at<Vec3b>(Point(30,y)) = black;
histo.at<Vec3b>(Point(30+2+256+25,y)) = black;
histo.at<Vec3b>(Point(30+2+256+25+256+25,y)) = black;
}
int x=32;
int y=700;

for(int v=0;v<256;v++)
{
    y=700;
                for(int c=0;c<=reda[v]/10;c++)
                {if(y>0)
                 {
                  //newImage->setPixel(x, y--, b);
                  histo.at<Vec3b>(Point(x,y--)) = redc;
                    }
                }
                x++;

}

x+=25+2;
for(int v=0;v<256;v++)
{
    y=700;
                for(int c=0;c<=greena[v]/10;c++)
                {if(y>0)
                 {
                  //newImage->setPixel(x, y--, b);
                  histo.at<Vec3b>(Point(x,y--)) = greenc;
                    }
                }
                x++;

}

x+=25+2;

for(int v=0;v<256;v++)
{
    y=700;
                for(int c=0;c<=bluea[v]/10;c++)
                {if(y>0)
                 {
                  //newImage->setPixel(x, y--, b);
                  histo.at<Vec3b>(Point(x,y--)) = bluec;
                    }
                }
                x++;

}





namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
imshow("MyWindow", img);
namedWindow("Bright", CV_WINDOW_AUTOSIZE);
imshow("Bright", new_image);
namedWindow("Contrast", CV_WINDOW_AUTOSIZE);
imshow("Contrast", new_image_con);
namedWindow("Rotate", CV_WINDOW_AUTOSIZE);
imshow("Rotate", new_image_rot);
namedWindow("Blur", CV_WINDOW_AUTOSIZE);
imshow("Blur", new_image_blur);
namedWindow("Sharpen", CV_WINDOW_AUTOSIZE);
imshow("Sharpen", new_image_sharp);
namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
imshow("Histogram", histo);
waitKey(0);

return 0;
}

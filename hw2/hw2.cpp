//#include "opencv2/core/core_c.h"
//#include "opencv2/core/core.hpp"
//#include "opencv2/flann/miniflann.hpp"
//#include "opencv2/imgproc/imgproc_c.h"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/video/video.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/ml/ml.hpp"
//#include "opencv2/highgui/highgui_c.h"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/contrib/contrib.hpp"
//#include  <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>
#include <cv.h>
#include <highgui.h>
#include <vector>
#include <math.h>

#define histo_size 300
using namespace cv;
using namespace std;

void color_to_gray(Mat& img, Mat& img_gray)
{
   for(int r=0;r<img.rows;r++)
  {
          for(int c=0;c<img.cols;c++)
          {
                  Vec3b intensity = img.at<Vec3b>(r,c);

                img_gray.at<uchar>(r,c) = 0.114*intensity.val[0]+0.587*intensity.val[1]+0.229*intensity.val[2];
          }
  }

}

void histo_equalization(vector<int> hist, vector<int> f_histo)
{

}
// param: img(gray)
void  get_histogram(const Mat& img, vector<int>& histo, int& h_max)
{
 //       cout << "rows:" << img_gray.rows << endl;
 //       cout << "cols:" << img_gray.cols << endl;
        for(int r=0;r< img.rows;r++)
        {
                for(int c=0; c< img.cols;c++)
                {
                        Scalar intensity = img.at<uchar>(r,c);
                        histo[intensity.val[0]]++;
                }
        }

        // get h_max: find max of histogram
        for(int r=0; r < histo.size();r++)
        {
                if(histo[r] > h_max)
                {
                        h_max = histo[r];
                }
           //    cout << "histo[" << r << "]:" << histo[r] << endl;

        }

}

void print_histogram(vector<int>& histo, int size)
{
        for(int i =0; i < size;i++)
        {
                cout << "hist[" << i << "]:" << histo[i] << endl;
        }
}

void show_histogram(vector<int>& histo)
{

        Mat canvas = Mat::ones(histo_size,256,CV_8UC1);
        //cout << "canvas:" << canvas << endl;

        for(int j=0;j < histo.size();j++)
        {

                line(
                                canvas,
                                Point(j,256),
                              //  Point(j,256-(histo[j]*histo_size/h_max)),
                                Point(j,256-histo[j]),
                                Scalar(256,256,256),
                                1,8,0
                    );
        }

        imshow("histo",canvas);

}
int main()
{
   // read grayscale image
   Mat img_gray = imread("./mystery.pgm",CV_LOAD_IMAGE_GRAYSCALE);
 //       cout << img_gray << endl;
 //  imshow("input image",img_gray);

        cout << "rows:" << img_gray.rows << endl;
        cout << "cols:" << img_gray.cols << endl;
        cout << "total:" << img_gray.rows * img_gray.cols << endl;

        vector<int> hist= vector<int>(256,0.0d);

        int hist_size = img_gray.rows * img_gray.cols;
        int h_max = -1;
        get_histogram(img_gray, hist,h_max); // fill histo, h_max
        show_histogram(hist);
       print_histogram(hist,50);

        vector<int> cu_hist(hist.size(),0);
        // compute cumulative histogram
        int sum = 0;
        for(int i=0;i < hist.size();i++)
        {
                if(hist[i]!=0)
                {
                         sum += hist[i];
                         cu_hist[i] = sum;

                }
               // cu_hist[i]=cu_hist[i-1]+hist[i];

        }
        int N= sum;
        cout << "after cumulation" << endl;
        print_histogram(cu_hist,50);
        cout << "N:" << N << endl;

        //normalize
        for(int i=0;i < cu_hist.size();i++)
        {
                if(hist[i] != 0)
                {
                        float a = cu_hist[i]/(float)N;
                        // cout << "a:" << a << endl;
                        cu_hist[i]=a*255;
                }
        }
        // after normalization
        cout << "after normalization" << endl;
        print_histogram(cu_hist,35);
      //  show_histogram(cu_hist);

        Mat new_M;
        img_gray.copyTo(new_M);
        for(int r=0;r < img_gray.rows;r++)
        {
                for(int c= 0; c < img_gray.cols;c++)
                {
                        Scalar intensity = img_gray.at<uchar>(r,c);
                        int new_value = cu_hist[intensity.val[0]];
                         new_M.at<uchar>(r,c) = new_value;
                      //  new_inten.val[0] = new_value;
                }
        }

        imshow("original", img_gray);
        imshow("after histo equal:", new_M);

//        show_histogram(cu_hist);

        waitKey(0);

        return 0;
}

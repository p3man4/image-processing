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

#define histo_size 256
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
         //       cout << "histo[" << r << "]:" << histo[r] << endl;

        }

}

void show_histogram(vector<int> histo, int h_max)
{
        Mat canvas = Mat::ones(histo_size,256,CV_8UC1);
        //cout << "canvas:" << canvas << endl;

        for(int j=0;j < histo.size();j++)
        {

                line(
                                canvas,
                                Point(j,256),
                                Point(j,256-(histo[j]*histo_size/h_max)),
                                Scalar(256,256,256),
                                1,8,0
                    );
        }

        imshow("histo",canvas);

}
int main()
{

   Mat img = imread("parrots.ppm",CV_LOAD_IMAGE_COLOR);
 //  imshow("input image",img);

   Mat img_gray; // by my code
   Mat  img_gray2; // by opencv code

   img_gray.create(img.size(),CV_8UC1);
//   img_gray2.create(img.size(),CV_8UC1);

   color_to_gray(img,img_gray);
   imshow("Output image1",img_gray);

    //    cvtColor(img,img_gray2,CV_BGR2GRAY);
    //    imshow("Output image2",img_gray2);
   //     imwrite("./gray_image.pgm",img_gray2);

        vector<int> histo= vector<int>(256,0);

        int h_max = -1;
        get_histogram(img_gray, histo,h_max); // fill histo, h_max

        Mat canvas = Mat::ones(histo_size,256,CV_8UC1);
        //cout << "canvas:" << canvas << endl;
        show_histogram(histo,h_max);

        waitKey(0);

        return 0;
}

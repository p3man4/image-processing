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

void print_content(Mat& img_gray)
{
        for(int r =0; r < img_gray.rows;++r)
        {
                for(int c=0;c < img_gray.cols;++c)
                {
                        Scalar intensity = img_gray.at<uchar>(r,c);
                        if(intensity.val[0] > 100)
                        {
                                cout << "r,c:" << r << "," << c << ":" << intensity.val[0] << endl;
                        }
                }
        }
}
int main()
{
   // read grayscale image
        Mat img_stuff = imread("./stuff.pgm",CV_LOAD_IMAGE_GRAYSCALE);
        Mat img_stuff2 = imread("./stufmin1.pgm",CV_LOAD_IMAGE_GRAYSCALE);

//        imshow("image1", img_stuff);
        //cout << "<r1,c1>:" << img_stuff.rows << "," << img_stuff.cols;
        //cout << "<r2,c2>:" << img_stuff2.rows << "," << img_stuff2.cols;

//        imshow("image2", img_stuff2);

        Mat new_image;
        new_image.create(img_stuff.size(),CV_8UC1);

        for(int r=0;r < img_stuff.rows;r++)
        {
                for(int c=0; c <img_stuff.cols;c++)
                {
                        Scalar intensity = img_stuff.at<uchar>(r,c);
                        Scalar intensity2 = img_stuff2.at<uchar>(r,c);
                        new_image.at<uchar>(r,c)=abs(intensity.val[0]-intensity2.val[0]);

                }
        }
 //       imshow("new image",new_image);
        print_content(new_image);

  //      namedWindow("newimage", CV_WINDOW_AUTOSIZE);
        imwrite("./newimage.jpg",new_image);
        waitKey(0);

        return 0;
}

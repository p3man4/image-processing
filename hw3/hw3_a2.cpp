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
#include <cstdlib> // atoi

#define histo_size 300

#define CLIP(x) (x<0)? 0 : x > 255? 255 : x

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

void do_avg(Mat& img_base,Mat& img, Mat&img_new)
{

        img_new.create(img_base.size(),CV_8UC1);

        for(int r=0;r < img_base.rows;r++)
        {
                for(int c=0; c <img_base.cols;c++)
                {
                        Scalar intensity = img_base.at<uchar>(r,c);
                        Scalar intensity2 = img.at<uchar>(r,c);
                        img_new.at<uchar>(r,c)=CLIP(intensity.val[0]+intensity2.val[0]);

                }
        }

}
int main(int argc, char* argv[])
{

   // read grayscale image
        Mat base = imread("./Frames/Cat0.pgm",CV_LOAD_IMAGE_GRAYSCALE);

        //int num_loop = 40;//5,10,20,40
        int num_loop = atoi(argv[1]);
        cout << "num loop:" << num_loop << endl;
        Mat img_new;
        int id=1;
        for(; id <= num_loop-1;++id)
        {
                // create file
                stringstream sstm;
                sstm << "./Frames/Cat"  << id << ".pgm";
                string fid = sstm.str();
                Mat img_added = imread(fid,CV_LOAD_IMAGE_GRAYSCALE);

                // avg image
                do_avg(base,img_added,img_new);
                base = img_new;
        }

        if(id==1)
                img_new =base;
 //       print_content(new_image);

  //      namedWindow("newimage", CV_WINDOW_AUTOSIZE);
  //      imwrite("./newimage.jpg",new_image);

        imshow("new image", img_new);
        waitKey(0);

        return 0;
}

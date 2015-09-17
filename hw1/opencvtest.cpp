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
#include  <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace cv;

int main()
{

   Mat img = imread("parrots.ppm",CV_LOAD_IMAGE_COLOR);
 //  imshow("opencvtest",img);
  Mat img2;
  img2.create(img.size(),CV_8UC3);
  for(int r=0;r<img.rows;r++)
  {
          for(int c=0;c<img.cols;c++)
          {
                img2.at<Vec3b>(r,c)[0] = 255-img.at<Vec3b>(r,c)[0];
                img2.at<Vec3b>(r,c)[1] = 255-img.at<Vec3b>(r,c)[1];
                img2.at<Vec3b>(r,c)[2] = 255-img.at<Vec3b>(r,c)[2];
          }
  }
  imshow("Output image",img2);

   waitKey(0);
   return 0;
}

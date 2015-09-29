// input parameter: number of images to add

#include <cv.h>
#include <highgui.h>
#include <vector>
#include <math.h>
#include <cstdlib> // atoi

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


int main(int argc, char* argv[])
{

   // read grayscale image
        Mat img_base = imread("./Frames/Cat0.pgm",CV_LOAD_IMAGE_GRAYSCALE);

        //int num_loop = 40;//5,10,20,40
        int num_loop = atoi(argv[1]);
        cout << "num loop:" << num_loop << endl;
        Mat img_new;
		img_new.create(img_base.size(),CV_8UC1);
      //  int id=0;
		vector< vector <double> > sum_table(img_base.rows, vector < double>(img_base.cols,0.0));
        
		for(int id=0; id <  num_loop;++id)
        {
                // create file
                stringstream sstm;
                sstm << "./Frames/Cat"  << id << ".pgm";
                string fid = sstm.str();
                Mat img_added = imread(fid,CV_LOAD_IMAGE_GRAYSCALE);
       

		        for(int r=0;r < img_added.rows;r++)
       			 {
                		for(int c=0; c <img_added.cols;c++)
                		{
                        	//	Scalar intensity = img_base.at<uchar>(r,c);
                        		Scalar intensity = img_added.at<uchar>(r,c);
                        //		img_new.at<uchar>(r,c)=CLIP(intensity.val[0]+intensity2.val[0]);
								sum_table[r][c] +=  intensity.val[0]; 
                		}
        		}



        }

		// normalize
		for(int r=0;r <img_base.rows;++r)
		{
			for(int c=0;c <img_base.cols;++c)
			{
				sum_table[r][c] /= num_loop;
				img_new.at<uchar>(r,c) = sum_table[r][c];
			}
		}

 
 //       print_content(new_image);

  //      namedWindow("newimage", CV_WINDOW_AUTOSIZE);
		stringstream sstm;
		sstm << "./addimage_upto_" << num_loop << ".jpg";
		string img_name = sstm.str();
      	imwrite(img_name,img_new);

        imshow("new image", img_new);
        waitKey(0);

        return 0;
}

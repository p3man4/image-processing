// input parameter: [u/m] [size of kernel]
// example: >> ./hw3_b1 u 3  // uniform averaging kernel with size of 3
// >> ./hw3_b1 m 7 // median filtering with size of 7

#include <cv.h>
#include <highgui.h>
#include <vector>
#include <math.h>
#include <cstdlib> // atoi
#include <algorithm> // sort
#include <gflags/gflags.h>
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
                        cout << "r,c:" << r << "," << c << ":" << intensity.val[0] << endl;
                }
        }
}

/*
// pad img_gray based on the size of mask(odd size)
void padding(Mat& img_gray, Mat& img_padded, int mask_size)
{
	int pad_size = mask_size/2;
	int img_padded_rows = img_gray.rows + pad_size;
	int img_padded_cols = img_gray.cols + pad_size;

	img_padded=Mat::zeros(img_padded_rows,img_padded_cols, CV_8UC1);
	
    for(int r =0; r < img_gray.rows;++r)
    {
            for(int c=0;c < img_gray.cols;++c)
            {
				img_padded<uchar>(r+pad_size,c+pad_size)=img_gray<uchar>(r,c);

            }
    }

}
*/

void do_median(Mat& img_gray, Mat& img_gray_median, int median_size)
{
//		int norm_count = 0;
//		int sum_value = 0;

	   
       for(int y =0; y < img_gray.rows;++y)
        {
                for(int x=0;x < img_gray.cols;++x)
                {
			//		norm_count = 0;
			//		sum_value = 0;
				 	vector <int> img_sub;
       
					for(int t=0; t < median_size; ++t)
					{
						for(int s=0; s < median_size;++s)
						{
							int y2 = y+t;
							int x2 = x+s;
							if(y2 >=0 && x2 >=0 && y2 < img_gray.rows && x2 < img_gray.rows)
							{
							//	norm_count++;
								Scalar intensity = img_gray.at<uchar>(y2,x2);
			//				 	cout << "img_gray(" << y2 <<"," << x2 << "):" << intensity.val[0] << endl;	
																
								img_sub.push_back(intensity.val[0]);

							}

						}
					}

					//sorting
					sort(img_sub.begin(),img_sub.end());

			//		int temp = sum_value/norm_count;
			//		cout <<"temp:" << temp << endl;
					img_gray_median.at<uchar>(y,x)  = img_sub[(median_size-1)/2];

         		// 	cout << "img_gray(" << y <<"," << x << "):" << img_gray_cv.at<uchar>(y,x)<< endl;	
				}
        }


}

// for 3 by 3 kernel
// g(y,x) = sum_{-1 to 1}sum_{-1 to 1} w(t,s)f(y+t,x+s) / sum_{-1 to 1}sum_{-1 to 1}w(t,s)
// for k by k kernel
// g(y,x) = sum_{-(k-1)/2 to (k-1)/2}sum_{-(k-1)/2 to (k-1)/2} w(t,s)f(y+t,x+s) / sum_{-(k-1)/2 to (k-1)/2}sum_{-(k-1)/2 to (k-1)/2}w(t,s)

void do_convolution (Mat& img_gray, Mat& img_gray_cv, Mat& mask)
{
//	Mat img_padded;
//	padding(img_gray, img_padded, mask_size);
		int norm_count = 0;
		int sum_value = 0;

       for(int y =0; y < img_gray.rows;++y)
        {
                for(int x=0;x < img_gray.cols;++x)
                {
					norm_count = 0;
					sum_value = 0;

					for(int t=0; t < mask.rows; ++t)
					{
						for(int s=0; s < mask.cols;++s)
						{
							int y2 = y+t;
							int x2 = x+s;
							if(y2 >=0 && x2 >=0 && y2 < img_gray.rows && x2 < img_gray.rows)
							{
								norm_count++;
								Scalar intensity = img_gray.at<uchar>(y2,x2);
			//				 	cout << "img_gray(" << y2 <<"," << x2 << "):" << intensity.val[0] << endl;	
								
								Scalar intensity_mask = mask.at<uchar>(t,s);
								
								sum_value += intensity_mask.val[0]*intensity.val[0];

							}

						}
					}

					int temp = sum_value/norm_count;
			//		cout <<"temp:" << temp << endl;
					img_gray_cv.at<uchar>(y,x)  = sum_value / norm_count;

         		// 	cout << "img_gray(" << y <<"," << x << "):" << img_gray_cv.at<uchar>(y,x)<< endl;	
				}
        }


}
int main(int argc, char* argv[])
{

   // read grayscale image
        Mat img_noisygull = imread("./noisygull.png",CV_LOAD_IMAGE_GRAYSCALE);

        char* flag_type  = argv[1];
		
		bool is_uniform = true;
		if(*flag_type == 'u') {
			cout << "type:Uniform averaging kernels" << endl;
			
		}else if(*flag_type == 'm') {
			cout << "type:Meidan filtering" << endl;
			is_uniform = false;
		}else {
			cout <<"illegal Type " << endl;
			return 0;
		}


		int k_size = atoi(argv[2]); // kernel size
   
		
		Mat mask1 = Mat::ones(k_size,k_size,CV_8UC1);

		Mat img_noisygull_cv;
		img_noisygull_cv.create(img_noisygull.size(),CV_8UC1);

		if(is_uniform)
		{
			 do_convolution (img_noisygull, img_noisygull_cv, mask1);
	
		}else
		{
			do_median(img_noisygull, img_noisygull_cv, k_size);
		}

		imshow("original image", img_noisygull);


		imshow("after smoothing",img_noisygull_cv);



			/*
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
      
*/
		waitKey(0);
        return 0;
}

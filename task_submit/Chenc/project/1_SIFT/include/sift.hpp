#ifndef SIFT_HPP
#define SIFT_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector> 
using namespace cv;
using namespace std;
 
typedef double pixel_t;                	 	     //pixel 
#define INIT_SIGMA 0.5                               //initial sigam
#define SIGMA 1.6
#define INTERVALS 3                                  //three picture per octaves
#define RATIO 10                                     //radius
#define MAX_INTERPOLATION_STEPS 5                    //max_step
#define DXTHRESHOLD 0.03                             //|thredhold| < 0.03
#define ORI_HIST_BINS 36                             //hist bin
#define ORI_SIGMA_TIMES 1.5
#define ORI_WINDOW_RADIUS 3.0 * ORI_SIGMA_TIMES 
#define ORI_SMOOTH_TIMES 2
#define ORI_PEAK_RATIO 0.8
#define FEATURE_ELEMENT_LENGTH 128
#define DESCR_HIST_BINS 8
#define IMG_BORDER 5 
#define DESCR_WINDOW_WIDTH 4
#define DESCR_SCALE_ADJUST 3
#define DESCR_MAG_THR 0.2
#define INT_DESCR_FCTR 512.0

struct Keypoint//initial the keypoint
{
	int    octave;                                    
	int    interval;                                   
	double offset_interval;                             
	int    x;                                             
	int    y;
	double scale;                                         //scale = sigma0*pow(2.0, o+s/S)
	double dx;                                            //
	double dy; 
	double offset_x;
	double offset_y;
 
	double octave_scale;                                  //offset_i;
	double ori;                                           //angle of keypoints
	int    descr_length;
	double descriptor[FEATURE_ELEMENT_LENGTH];            //descriptor           
	double val;                                           //extrenum
};
void read_features(std::vector<Keypoint>&features, const char*file);//
void write_features(const std::vector<Keypoint>&features, const char*file);//write the keypoints in a file
void testInverse3D(); 
void DrawKeyPoints(Mat &src, std::vector<Keypoint>& keypoints);
void DownSample(const Mat& src, Mat& dst);
void UpSample(const Mat& src, Mat& dst);
void GaussianTemplateSmooth(const Mat &src, Mat &dst, double);
void GaussianSmooth2D(const Mat &src, Mat &dst, double sigma);
void Sift(const Mat &src, std::vector<Keypoint>& features, double sigma=SIGMA, int intervals=INTERVALS);
void CreateInitSmoothGray(const Mat &src, Mat &dst, double);
void GaussianPyramid(const Mat &src, std::vector<Mat>&gauss_pyr, int octaves, int intervals, double sigma);
void Sub(const Mat& a, const Mat& b, Mat & c);
void DogPyramid(const std::vector<Mat>& gauss_pyr, std::vector<Mat>& dog_pyr, int octaves, int intervals);
void DetectionLocalExtrema(const std::vector<Mat>& dog_pyr, std::vector<Keypoint>& extrema, int octaves, int intervals);
void DrawSiftFeatures(Mat& src, std::vector<Keypoint>& features);
double CaculateDistance(Keypoint& kp1,Keypoint& kp2);
void FindMatching(Mat& src,Mat& src1,Mat& src2,std::vector<Keypoint>& kp1,std::vector<Keypoint>& kp2,double threshold);
void Drawlines(Mat& src,Mat& src1,Mat& src2,Keypoint& kp1,double x,double y);

 
#endif



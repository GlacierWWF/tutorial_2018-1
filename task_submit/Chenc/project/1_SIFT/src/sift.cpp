#include"sift.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

using namespace std;
using namespace cv;

//using convertToGray function to create grayimage
void ConvertToGray(const Mat& src,Mat& dst)
{
	cv::Size size = src.size();
	if(dst.empty())
		dst.create(size,CV_64F);                              
		//create image of mat
	
	uchar*    srcData = src.data;                            
	//point to the data region that stored all pixels
	pixel_t*  dstData = (pixel_t*)dst.data;                   
	//a matix data region point to dst
	
	int  dstStep = dst.step/sizeof(dstData[0]);         
	//step of one line
 	for(int j=0;j<src.cols;j++)
	{
		for(int i=0;i<src.rows;i++)
		{
			double b = (srcData+src.step*i+src.channels()*j)[0]/255.0;
			double g = (srcData+src.step*i+src.channels()*j)[1]/255.0;
			double r = (srcData+src.step*i+src.channels()*j)[2]/255.0;
			*(dstData+dstStep*i+dst.channels()*j) = (r+g+b)/3.0;
		}
	}
}

//down sample to shrink the image
void DownSample(const Mat& src, Mat& dst)
{
	if(src.channels() != 1)
		return;
 
	if(src.cols <=1 || src.rows <=1)
	{
		src.copyTo(dst);
		return;
	}
 
	dst.create((int)(src.rows/2), (int)(src.cols/2), src.type());
 
	pixel_t* srcData = (pixel_t*)src.data;
	pixel_t* dstData = (pixel_t*)dst.data;
 
	int srcStep = src.step/sizeof(srcData[0]);
	int dstStep = dst.step/sizeof(dstData[0]);
 
	int m = 0, n = 0;
	for(int j = 0; j < src.cols; j+=2, n++)
	{
		m = 0;
		for(int i = 0; i < src.rows; i+=2, m++)
		{
			pixel_t sample = *(srcData + srcStep * i + src.channels() * j);
			if(m < dst.rows && n < dst.cols)
			{
				*(dstData + dstStep * m + dst.channels() * n) = sample;
			}
		}
	}
 
}

//upsample to enlarge the image
void UpSample(const Mat &src, Mat &dst)
{
	if(src.channels() != 1)
		return;
	dst.create(src.rows*2, src.cols*2, src.type());
 
	pixel_t* srcData = (pixel_t*)src.data;
	pixel_t* dstData = (pixel_t*)dst.data;
 
	int srcStep = src.step/sizeof(srcData[0]);
	int dstStep = dst.step/sizeof(dstData[0]);
 
	int m = 0, n = 0;
	for(int j = 0; j < src.cols-1; j++, n+=2)
	{
		m = 0;
		for(int i = 0; i < src.rows-1; i++, m+=2)
		{
			double sample = *(srcData + srcStep * i + src.channels() * j);
			*(dstData + dstStep * m + dst.channels() * n) = sample;
			
			double rs = *(srcData + srcStep * (i) + src.channels()*j)+(*(srcData + srcStep * (i+1) + src.channels()*j));
			*(dstData + dstStep * (m+1) + dst.channels() * n) = rs/2;
			double cs = *(srcData + srcStep * i + src.channels()*(j))+(*(srcData + srcStep * i + src.channels()*(j+1)));
			*(dstData + dstStep * m + dst.channels() * (n+1)) = cs/2;
 
			double center = (*(srcData + srcStep * (i+1) + src.channels() * j))
						+ (*(srcData + srcStep * i + src.channels() * j))
						+ (*(srcData + srcStep * (i+1) + src.channels() * (j+1)))
						+ (*(srcData + srcStep * i + src.channels() * (j+1)));
 
			*(dstData + dstStep * (m+1) + dst.channels() * (n+1)) = center/4;
 
		}
 
	}
 
	if(dst.rows < 3 || dst.cols < 3)
		return;
 
	//last two rows and two cols
	for(int k = dst.rows-1; k >=0; k--)
	{
		*(dstData + dstStep *(k) + dst.channels()*(dst.cols-2))=*(dstData + dstStep *(k) + dst.channels()*(dst.cols-3));
		*(dstData + dstStep *(k) + dst.channels()*(dst.cols-1))=*(dstData + dstStep *(k) + dst.channels()*(dst.cols-3));
	}
	for(int k = dst.cols-1; k >=0; k--)
	{
		*(dstData + dstStep *(dst.rows-2) + dst.channels()*(k))=*(dstData + dstStep *(dst.rows-3) + dst.channels()*(k));
		*(dstData + dstStep *(dst.rows-1) + dst.channels()*(k))=*(dstData + dstStep *(dst.rows-3) + dst.channels()*(k));
	}
 
}
//using opencv system function
void GaussianSmooth(const Mat &src, Mat &dst, double sigma)
{ 
	GaussianBlur(src, dst, Size(0,0), sigma, sigma); 
}
//create gaussianblur
void CreateInitSmoothGray(const Mat &src, Mat &dst, double sigma = SIGMA)
{
	cv::Mat gray;                                  //gray image       
	cv::Mat up;                                    //up-sample image
	
	ConvertToGray(src, gray);
	UpSample(gray, up);                            //the Interpolation
	double  sigma_init = sqrt(sigma * sigma - (INIT_SIGMA * 2) * (INIT_SIGMA * 2));//sigma of -1 interval
	GaussianBlur(up, dst, Size(0,0),sigma_init,sigma_init);           //Gaussian smooth
}

//system function


//create gaussianpyramid
//initial sigmas
//every octaves include interval number + 3,so the interval number of dogpyramid + 2
void GaussianPyramid(const Mat &src, vector<Mat>&gauss_pyr, int octaves, int intervals = INTERVALS, double sigma = SIGMA)
{
	double *sigmas = new double[intervals+3];
	double k = pow(2.0, 1.0/intervals);
 
	sigmas[0] = sigma;
 
	double sig_prev;
	double sig_total;
 
	for(int i = 1; i < intervals + 3; i++ )
	{
		sig_prev = pow( k, i - 1 ) * sigma;
		sig_total = sig_prev * k;
		sigmas[i] = sqrt( sig_total * sig_total - sig_prev * sig_prev );
	}
 
	for(int o = 0; o < octaves; o++)
	{
		for(int i = 0; i < intervals+3; i++)
		{
			Mat mat;
			if(o == 0 && i == 0)
			{
				src.copyTo(mat);
			}
			else if(i == 0)
			{
				DownSample(gauss_pyr[(o-1)*(intervals+3)+intervals], mat);
			}
			
			else
			{
				GaussianSmooth(gauss_pyr[o * (intervals+3)+i-1], mat, sigmas[i]);
			}
			gauss_pyr.push_back(mat);
		}
	}
	
	delete[] sigmas;
}

//substract two pictures
void Sub(const Mat& a, const Mat& b, Mat & c)
{
	if(a.rows != b.rows || a.cols != b.cols || a.type() != b.type())
		return;
	if(!c.empty())
		return;
	c.create(a.size(), a.type());
 
	pixel_t* ap = (pixel_t*)a.data;
	pixel_t* ap_end = (pixel_t*)a.dataend;
	pixel_t* bp = (pixel_t*)b.data;
	pixel_t* cp = (pixel_t*)c.data;
	int step = a.step/sizeof(pixel_t);
 
	while(ap != ap_end)
	{
		*cp++ = *ap++ - *bp++;
	}
}

//create the dogpyramid
//aim to use difference to replace differencial
void DogPyramid(const vector<Mat>& gauss_pyr, vector<Mat>& dog_pyr, int octaves, int intervals=INTERVALS)
{
	for(int o = 0; o < octaves; o ++)
	{
		for(int i = 1; i < intervals+3; i++)
		{
			Mat mat;
			Sub(gauss_pyr[o*(intervals+3)+i], gauss_pyr[o*(intervals+3)+i-1], mat);
			dog_pyr.push_back(mat);
		}
	}
}

//detect the extremun
bool isExtremum(int x, int y, const vector<Mat>& dog_pyr, int index)
{
	pixel_t * data = (pixel_t *)dog_pyr[index].data;
	int      step = dog_pyr[index].step/sizeof(data[0]);
	pixel_t   val  = *(data+y*step+x);
 
	if(val > 0)
	{
		for(int i = -1; i <= 1; i++)
		{
			int stp = dog_pyr[index+i].step/sizeof(data[0]);
			for(int j = -1; j <= 1; j++)
			{
				for(int k = -1; k <= 1; k++)
				{
					if( val < *((pixel_t*)dog_pyr[index+i].data+stp*(y+j)+(x+k)))
					{
						return false;
					}
				}
			}
		}
	}
	else
	{
		for(int i = -1; i <= 1; i++)
		{
			int stp = dog_pyr[index+i].step/sizeof(pixel_t);
			for(int j = -1; j <= 1; j++)
			{
				for(int k = -1; k <= 1; k++)
				{
					//检查最小极值
					if( val > *((pixel_t*)dog_pyr[index+i].data+stp*(y+j)+(x+k)))
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

//delete edge response 
#define DAt(x, y) (*(data+(y)*step+(x))) 
bool passEdgeResponse(int x, int y, const vector<Mat>& dog_pyr, int index, double r = RATIO)
{
	pixel_t *data = (pixel_t *)dog_pyr[index].data;
	int step = dog_pyr[index].step/sizeof(data[0]);
	pixel_t val = *(data+y*step+x);
 
	double Dxx;
	double Dyy;
	double Dxy;
	double Tr_h;                                                         //tr
	double Det_h;                                                        //det
	 
	Dxx = DAt(x+1,y) + DAt(x-1,y) - 2*val;
	Dyy = DAt(x,y+1) + DAt(x,y-1) - 2*val;
	Dxy = (DAt(x+1,y+1) + DAt(x-1,y-1) - DAt(x-1,y+1) - DAt(x+1,y-1))/4.0;
 
	Tr_h  = Dxx + Dyy;
	Det_h = Dxx * Dyy - Dxy * Dxy;
 
	if(Det_h <=0)return false;
	
	if(Tr_h * Tr_h / Det_h < (r + 1) * (r + 1) / r) return true;
 
	return false;
}

#define Hat(i, j) (*(H+(i)*3 + (j)))

//return the value of pixel
double PyrAt(const vector<Mat>& pyr, int index, int x, int y)
{
	pixel_t *data = (pixel_t*)pyr[index].data;
	int      step = pyr[index].step/sizeof(data[0]);
	pixel_t   val = *(data+y*step+x);
	
	return val;
}


#define At(index, x, y) (PyrAt(dog_pyr, (index), (x), (y)))
 
//
void DerivativeOf3D(int x, int y, const vector<Mat>& dog_pyr, int index, double *dx)
{
	double Dx = (At(index, x+1, y)-At(index, x-1, y))/2.0;
	double Dy = (At(index, x, y+1)-At(index, x, y-1))/2.0;
	double Ds = (At(index+1, x, y)-At(index-1, x, y))/2.0;
 
	dx[0] = Dx;
	dx[1] = Dy;
	dx[2] = Ds;
}
 

void Hessian3D(int x, int y, const vector<Mat>& dog_pyr, int index, double *H)
{
	double val, Dxx, Dyy, Dss, Dxy, Dxs, Dys;
	
	val = At(index, x, y);
 
	Dxx = At(index, x+1, y) + At(index, x-1, y) - 2*val;
	Dyy = At(index, x, y+1) + At(index, x, y-1) - 2*val;
	Dss = At(index+1, x, y) + At(index-1, x, y) - 2*val;
 
	Dxy = (At(index, x+1, y+1) + At(index, x-1, y-1)
		 - At(index, x+1, y-1) - At(index, x-1, y+1))/4.0;
 
	Dxs = (At(index+1, x+1, y) + At(index-1, x-1, y)
		 - At(index-1, x+1, y) - At(index+1, x-1, y))/4.0;
 
	Dys = (At(index+1, x, y+1) + At(index-1, x, y-1)
		 - At(index+1, x, y-1) - At(index-1, x, y+1))/4.0;
 
	Hat(0, 0) = Dxx;
	Hat(1, 1) = Dyy;
	Hat(2, 2) = Dss;
 
	Hat(1, 0) = Hat(0, 1) = Dxy;
	Hat(2, 0) = Hat(0 ,2) = Dxs;
	Hat(2, 1) = Hat(1, 2) = Dys;
}

//inverse the matrix
#define HIat(i, j) (*(H_inve+(i)*3 + (j)))
bool Inverse3D(const double *H, double *H_inve)
{
 
	double A = Hat(0, 0)*Hat(1, 1)*Hat(2, 2) 
			 + Hat(0, 1)*Hat(1, 2)*Hat(2, 0)
			 + Hat(0, 2)*Hat(1, 0)*Hat(2, 1)
			 - Hat(0, 0)*Hat(1, 2)*Hat(2, 1)
			 - Hat(0, 1)*Hat(1, 0)*Hat(2, 2)
			 - Hat(0, 2)*Hat(1, 1)*Hat(2, 0);
 
	if(fabs(A) < 1e-10) return false;
 
	HIat(0, 0) = Hat(1, 1) * Hat(2, 2) - Hat(2, 1)*Hat(1, 2);
	HIat(0, 1) = -(Hat(0, 1) * Hat(2, 2) - Hat(2, 1) * Hat(0, 2));
	HIat(0, 2) = Hat(0, 1) * Hat(1, 2) - Hat(0, 2)*Hat(1, 1);
	
	HIat(1, 0) = Hat(1, 2) * Hat(2, 0) - Hat(2, 2)*Hat(1, 0);
	HIat(1, 1) = -(Hat(0, 2) * Hat(2, 0) - Hat(0, 0) * Hat(2, 2));
	HIat(1, 2) = Hat(0, 2) * Hat(1, 0) - Hat(0, 0)*Hat(1, 2);
	
	HIat(2, 0) = Hat(1, 0) * Hat(2, 1) - Hat(1, 1)*Hat(2, 0);
	HIat(2, 1) = -(Hat(0, 0) * Hat(2, 1) - Hat(0, 1) * Hat(2, 0));
	HIat(2, 2) = Hat(0, 0) * Hat(1, 1) - Hat(0, 1)*Hat(1, 0);
 
	for(int i = 0; i < 9; i++)
	{
		*(H_inve+i) /= A;
	}
	return true;
}


//caculate offset x = x^
void GetOffsetX(int x, int y, const vector<Mat>& dog_pyr, int index, double *offset_x)
{
	//x^ = -H^(-1) * dx; dx = (Dx, Dy, Ds)^T
	double H[9], H_inve[9]= {0};
	Hessian3D(x, y, dog_pyr, index, H);
	Inverse3D(H, H_inve);
	double dx[3];
	DerivativeOf3D(x, y, dog_pyr, index, dx);
	
	for(int i = 0; i < 3; i ++)
	{
		offset_x[i] = 0.0;
		for(int j = 0; j < 3; j++)
		{
			offset_x[i] += H_inve[i*3 + j] * dx[j];
		}
		offset_x[i] = -offset_x[i];
	}
}
 
//caculate |D(x^)|
double GetFabsDx(int x, int y, const vector<Mat>& dog_pyr, int index, const double* offset_x)
{
	//|D(x^)|=D + 0.5 * dx * offset_x; dx=(Dx, Dy, Ds)^T
	double dx[3];
	DerivativeOf3D(x, y, dog_pyr, index, dx);
 
	double term = 0.0;
	for(int i = 0; i < 3; i++)
		term += dx[i] * offset_x[i];
 
	pixel_t *data = (pixel_t *)dog_pyr[index].data;
	int step = dog_pyr[index].step/sizeof(data[0]);
	pixel_t val = *(data+y*step+x);
 
	return fabs(val + 0.5 * term);
}

//return some good keypoints
Keypoint* InterploationExtremum(int x, int y, const vector<Mat>& dog_pyr, int index, int octave, int interval, double dxthreshold = DXTHRESHOLD)
{
	//计算x=(x,y,sigma)^T
	//x^ = -H^(-1) * dx; dx = (Dx, Dy, Ds)^T
	double offset_x[3]={0};
 
	const Mat &mat = dog_pyr[index];
 
	int idx   = index;
	int intvl = interval;
	int i     = 0; 
 
	while(i < MAX_INTERPOLATION_STEPS)
	{
		GetOffsetX(x, y, dog_pyr, idx, offset_x);
		//4. Accurate keypoint localization.  Lowe
		//if the dx,dy,dsigma > 0.5，it means that the extremum lies closer to a different sample point.
		if(fabs(offset_x[0]) < 0.5 && fabs(offset_x[1]) < 0.5 && fabs(offset_x[2]) < 0.5)
			break;
 
		//replace with points around
		x += cvRound(offset_x[0]);
		y += cvRound(offset_x[1]);
		interval += cvRound(offset_x[2]);
 
		idx = index - intvl + interval;
		//only x + 1,y + 1,x -1,y -1
		if( interval < 1 || interval > INTERVALS ||x >= mat.cols-1 || x < 2 ||y >= mat.rows-1 || y < 2)  
		{
			return NULL;
		}
 
		i++;
	}
 
	//failed
	if(i >= MAX_INTERPOLATION_STEPS)
		return NULL;
 
	//rejecting unstable extrema
	//|D(x^)| < 0.03
	if(GetFabsDx(x, y, dog_pyr, idx, offset_x) < dxthreshold/INTERVALS)
	{
		return NULL;
	}
 
	Keypoint *keypoint = new Keypoint;
 
 
	keypoint->x = x;
	keypoint->y = y;
 
	keypoint->offset_x        = offset_x[0];
	keypoint->offset_y        = offset_x[1];
 
	keypoint->interval        = interval;
	keypoint->offset_interval = offset_x[2];
 
	keypoint->octave          = octave;
 
	keypoint->dx              = (x + offset_x[0])*pow(2.0, octave);
	keypoint->dy              = (y + offset_x[1])*pow(2.0, octave);
 
	return keypoint;
}

//the full function of detect extrenum
void DetectionLocalExtrema(const vector<Mat>& dog_pyr, vector<Keypoint>& extrema, int octaves, int intervals=INTERVALS)
{
 
	double  thresh = 0.5 * DXTHRESHOLD / intervals;
 
	for(int o = 0; o < octaves; o++)
	{
		//ignore the first and last
		for(int i = 1; i < (intervals + 2) - 1; i++)
		{
			int index    = o*(intervals+2)+i;                             
			pixel_t *data = (pixel_t *)dog_pyr[index].data;               
			int step     = dog_pyr[index].step/sizeof(data[0]);           
	
			for(int y = IMG_BORDER; y < dog_pyr[index].rows-IMG_BORDER; y++)
			{
				for(int x = IMG_BORDER; x < dog_pyr[index].cols-IMG_BORDER; x++)
				{
					pixel_t val = *(data+y*step+x);
					if(std::fabs(val) > thresh )                           
					{ 		
						if(isExtremum(x,y, dog_pyr, index))                
						{
							Keypoint *extrmum = InterploationExtremum(x, y, dog_pyr, index, o, i);
							if(extrmum)
							{
								if(passEdgeResponse(extrmum->x,extrmum->y, dog_pyr, index))
								{	
									extrmum->val = *(data+extrmum->y*step+extrmum->x);
									extrema.push_back(*extrmum);
								}
 
								delete extrmum;
	
							}//extrmum
						}//isExtremum
					}//std::fabs
				}//for x
			}//for y
		
		}
	}
}

//calculate the scale
void CalculateScale(vector<Keypoint>& features, double sigma = SIGMA, int intervals = INTERVALS)
{
	double intvl = 0;
	for(int i = 0; i < features.size(); i++)
	{
		intvl                    = features[i].interval + features[i].offset_interval;
		features[i].scale        = sigma * pow(2.0, features[i].octave + intvl/intervals);
		features[i].octave_scale = sigma * pow(2.0, intvl/intervals);
	}
 
}
 
//resize
void HalfFeatures(vector<Keypoint>& features)
{
	for(int i = 0; i < features.size(); i++)
	{
		features[i].dx /= 2;
		features[i].dy /= 2;
 
		features[i].scale /= 2;
	}
}

//the grad the angle of keypoints
bool CalcGradMagOri(const Mat& gauss, int x, int y, double& mag, double& ori)
{
	if(x > 0 && x < gauss.cols-1 && y > 0 && y < gauss.rows -1)
	{
		pixel_t *data = (pixel_t*)gauss.data;
		int step     = gauss.step/sizeof(*data);
 
		double dx = *(data+step*y+(x+1))-(*(data+step*y+(x-1)));//dx = (x + 1) - (x - 1)
		double dy = *(data+step*(y+1)+x)-(*(data+step*(y-1)+x));//dy = (y + 1) - (y - 1)
 
		mag = sqrt(dx*dx + dy*dy);//grad 
		ori = atan2(dy, dx);//angle
		return true;
	}
	else
		return false;
}

double* CalculateOrientationHistogram(const Mat& gauss, int x, int y, int bins, int radius, double sigma)
{
	double* hist = new double[bins];//create array of hist and initialize
	for(int i = 0; i < bins; i++) 
		*(hist + i) = 0.0;
 
	double  mag;
	double  ori;
	double  weight;
 
	int           bin;
	const double PI2   = 2.0*CV_PI;
	double        econs = -1.0/(2.0*sigma*sigma);
 
	for(int i = -radius; i <= radius; i++)
	{
		for(int j = -radius; j <= radius; j++)
		{
			if(CalcGradMagOri(gauss, x+i, y+j, mag, ori))
			{
				weight = exp((i*i+j*j)*econs);
				bin    = cvRound(bins * (CV_PI - ori)/PI2);//return <int>
				bin    = bin < bins ? bin : 0;
 
				hist[bin] += mag * weight;//caculate the hist 
			}
		}
	}
 
	return hist;
}

//*gausssmooth twice!
void GaussSmoothOriHist(double *hist, int n)
{
	double prev = hist[n-1];
	double temp;
	double h0   = hist[0];
 
	for(int i = 0; i < n; i++)
	{
		temp    = hist[i];
		hist[i] = 0.25 * prev + 0.5 * hist[i] + 0.25 * (i+1 >= n ? h0 : hist[i+1]);//gausssmooth the hist of direction
		prev    = temp;
	}
}

//the main direction of a hist
double DominantDirection(double *hist, int n)
{
	double maxd = hist[0];
	for(int i = 1; i < n; i++)
	{
		if(hist[i] > maxd)//max of 36 bins
			maxd = hist[i];
	}
	return maxd;
}


void CopyKeypoint(const Keypoint& src, Keypoint& dst)
{
	dst.dx = src.dx;
	dst.dy = src.dy;
 
	dst.interval        = src.interval;
	dst.octave          = src.octave;
	dst.octave_scale    = src.octave_scale;
	dst.offset_interval = src.offset_interval;
 
	dst.offset_x = src.offset_x;
	dst.offset_y = src.offset_y;
	
	dst.ori      = src.ori;
	dst.scale    = src.scale;
	dst.val      = src.val;
	dst.x        = src.x;
	dst.y        = src.y;
}


//caculate the angle of a keypoint more precise
//the max of a hist represent the main direcition of this keypoint
//and the 80% of the max 's direction are stored as subdirection of the keypoint
#define Parabola_Interpolate(l, c, r) (0.5*((l)-(r))/((l)-2.0*(c)+(r))) 
void CalcOriFeatures(const Keypoint& keypoint, vector<Keypoint>& features, const double *hist, int n, double mag_thr)
{
	double  bin;
	double  PI2 = CV_PI * 2.0;
	int l;
	int r;
 
	for(int i = 0; i < n; i++)
	{
		l = (i == 0) ? n-1 : i -1;
		r = (i+1)%n;
 
		//hist[i] is the max value
		if(hist[i] > hist[l] && hist[i] > hist[r] && hist[i] >= mag_thr)
		{
			bin = i + Parabola_Interpolate(hist[l], hist[i], hist[r]);
			bin = (bin < 0) ? (bin + n) : (bin >=n ? (bin -n) : bin);
 
			Keypoint new_key;
 
			CopyKeypoint(keypoint, new_key);
 
			new_key.ori = ((PI2 * bin)/n) - CV_PI;
			features.push_back(new_key);
		}
	}
}

//devide the direction to keypoints
void OrientationAssignment(vector<Keypoint>& extrema, vector<Keypoint>& features, const vector<Mat>& gauss_pyr)
{
	int n = extrema.size();
	double *hist;
 
	for(int i = 0; i < n; i++)
	{
 
		hist = CalculateOrientationHistogram(gauss_pyr[extrema[i].octave*(INTERVALS+3)+extrema[i].interval],
			extrema[i].x, extrema[i].y, ORI_HIST_BINS, cvRound(ORI_WINDOW_RADIUS*extrema[i].octave_scale), 
			ORI_SIGMA_TIMES*extrema[i].octave_scale);//calculate the main direction
		for(int j = 0; j < ORI_SMOOTH_TIMES; j++)
			GaussSmoothOriHist(hist, ORI_HIST_BINS); //gaussian smooth
		double highest_peak = DominantDirection(hist, ORI_HIST_BINS);//max level of a hist 
		                                                                          //
		CalcOriFeatures(extrema[i], features, hist, ORI_HIST_BINS, highest_peak*ORI_PEAK_RATIO);//calculate the precise direction
 
		delete[] hist;
	
	}
}
 
void InterpHistEntry(double ***hist, double xbin, double ybin, double obin, double mag, int bins, int d)
{
	double d_r, d_c, d_o, v_r, v_c, v_o;
	double** row, * h;
	int r0, c0, o0, rb, cb, ob, r, c, o;
 
	r0 = cvFloor( ybin );
	c0 = cvFloor( xbin );
	o0 = cvFloor( obin );
	d_r = ybin - r0;
	d_c = xbin - c0;
	d_o = obin - o0;
	//interpolation : xbin,ybin,obin:(the location and direction of windows of points) 
	//all points are within 4x4 windows
	//r0 < = xbin,c0 <= ybin
	//r0,rc = 0,1,2
	//xbin,ybin (-1,2),r0<xbin -> r0<=xbin<=r0+1
	//mag in[r0,r1]
	for( r = 0; r <= 1; r++ )
	{
		rb = r0 + r;
		if( rb >= 0  &&  rb < d )
		{
			v_r = mag * ( ( r == 0 )? 1.0 - d_r : d_r );
			row = hist[rb];
			for( c = 0; c <= 1; c++ )
			{
				cb = c0 + c;
				if( cb >= 0  &&  cb < d )
				{
					v_c = v_r * ( ( c == 0 )? 1.0 - d_c : d_c );
					h = row[cb];
					for( o = 0; o <= 1; o++ )
					{
						ob = ( o0 + o ) % bins;
						v_o = v_c * ( ( o == 0 )? 1.0 - d_o : d_o );
						h[ob] += v_o;
					}
				}
			}
		}
	}
 
	
}

//caculate the descriptor -> hist graph
double*** CalculateDescrHist(const Mat& gauss, int x, int y, double octave_scale, double ori, int bins, int width)
{
	double ***hist = new double**[width];
 
	for(int i = 0; i < width; i++)
	{
		hist[i] = new double*[width];
		for(int j = 0; j < width; j++)
		{
			hist[i][j] = new double[bins];
		}
	}
	
	for(int r = 0; r < width; r++ )
		for(int c = 0; c < width; c++ )
			for(int o = 0; o < bins; o++ )
				hist[r][c][o]=0.0;
 
 
	double cos_ori = cos(ori);
	double sin_ori = sin(ori);
 
	double sigma = 0.5 * width;
	double conste = -1.0/(2*sigma*sigma);
 
	double PI2 = CV_PI * 2;
 
	double sub_hist_width = DESCR_SCALE_ADJUST * octave_scale;
 
	//caculate the radius of descriptor
	int    radius   = (sub_hist_width*sqrt(2.0)*(width+1))/2.0 + 0.5; 
	double grad_ori;
	double grad_mag;
 
	for(int i = -radius; i <= radius; i++)
	{
		for(int j =-radius; j <= radius; j++)
		{
			double rot_x = (cos_ori * j - sin_ori * i) / sub_hist_width;
			double rot_y = (sin_ori * j + cos_ori * i) / sub_hist_width;
 
			double xbin = rot_x + width/2 - 0.5;//xbin,ybin in 4x4
			double ybin = rot_y + width/2 - 0.5;
 
			if(xbin > -1.0 && xbin < width && ybin > -1.0 && ybin < width)
			{
				if(CalcGradMagOri(gauss, x+j, y + i, grad_mag, grad_ori)) 
				{
					grad_ori = (CV_PI-grad_ori) - ori;
					while(grad_ori < 0.0)
						grad_ori += PI2;
					while(grad_ori >= PI2)
						grad_ori -= PI2;
 
					double obin = grad_ori * (bins/PI2);
 
					double weight = exp(conste*(rot_x*rot_x + rot_y * rot_y));
 
					InterpHistEntry(hist, xbin, ybin, obin, grad_mag*weight, bins, width);
 
				}
			}
		}
	}
 
	return hist;
}
 
void NormalizeDescr(Keypoint& feat)
{
	double cur, len_inv, len_sq = 0.0;
	int i, d = feat.descr_length;
 
	for( i = 0; i < d; i++ )
	{
		cur = feat.descriptor[i];
		len_sq += cur*cur;
	}
	len_inv = 1.0 / sqrt( len_sq );
	for( i = 0; i < d; i++ )
		feat.descriptor[i] *= len_inv;
}


//making the hist convert to descriptor
void HistToDescriptor(double ***hist, int width, int bins, Keypoint& feature)
{
	int int_val, i, r, c, o, k = 0;
 
	for( r = 0; r < width; r++ )
		for( c = 0; c < width; c++ )
			for( o = 0; o < bins; o++ )
			{
				feature.descriptor[k++] = hist[r][c][o];
			}
 
	feature.descr_length = k;
	NormalizeDescr(feature);
 
	for( i = 0; i < k; i++ )
		if( feature.descriptor[i] > DESCR_MAG_THR )    
			feature.descriptor[i] = DESCR_MAG_THR;
 
	NormalizeDescr(feature);
 
	for( i = 0; i < k; i++ )
	{
		int_val = INT_DESCR_FCTR * feature.descriptor[i];
		feature.descriptor[i] = min( 255, int_val );
	}
}


//describe the keypoints
//3 important values: location,scale,direction
//build the descriptor and let it stable
//make the SIFT descriptor vector
void DescriptorRepresentation(vector<Keypoint>& features, const vector<Mat>& gauss_pyr, int bins, int width)
{
	double ***hist;
 
	for(int i = 0; i < features.size(); i++)
	{                                                                       //
		hist = CalculateDescrHist(gauss_pyr[features[i].octave*(INTERVALS+3)+features[i].interval],
			features[i].x, features[i].y, features[i].octave_scale, features[i].ori, bins, width);
 
		HistToDescriptor(hist, width, bins, features[i]);   
 
		for(int j = 0; j < width; j++)
		{
			for(int k = 0; k < width; k++)
			{
				delete[] hist[j][k];
			}
			delete[] hist[j];
		}
		delete[] hist;
	}
}
 

//compare the keypoint base on scale
bool FeatureCmp(Keypoint& f1, Keypoint& f2)
{
	return f1.scale < f2.scale;
}


void Sift(const Mat &src, vector<Keypoint>& features, double sigma, int intervals)
{
	std::cout<<"***********************************************"<<endl;
	std::cout<<"1.Create -1 octave gaussian pyramid image"<<std::endl;
	cv::Mat	 init_gray;
	CreateInitSmoothGray(src, init_gray, sigma);                                   
	int octaves = log((double)min(init_gray.rows, init_gray.cols))/log(2.0) - 2;
	std::cout<<"(1) The height and width of init_gray_img = "<<init_gray.rows<<"*"<<init_gray.cols<<std::endl;
	std::cout<<"(2) The octaves of the gauss pyramid      = "<<octaves<<std::endl;
 
 
	std::cout <<"2.Building gaussian pyramid ..."<<std::endl;                                                         
	std::vector<Mat> gauss_pyr;                                                  
	GaussianPyramid(init_gray, gauss_pyr, octaves, intervals, sigma);            
	//write_pyr(gauss_pyr, "gausspyramid");
	
 
	std::cout <<"3.Building difference of gaussian pyramid..."<<std::endl;                   
	vector<Mat> dog_pyr;                                                          
	DogPyramid(gauss_pyr, dog_pyr, octaves, intervals);                           
	//write_pyr(dog_pyr, "dogpyramid");
 
 
 
	std::cout <<"4.Deatecting local extrema..."<<std::endl;                                                     
	vector<Keypoint> extrema;                                                     
	DetectionLocalExtrema(dog_pyr, extrema, octaves, intervals);                  
	std::cout <<"(3) keypoints cout: "<< extrema.size()<<" --"<<std::endl;	
	std::cout <<"(4) extrema detection finished."<<std::endl;
	std::cout <<"(5) please look dir gausspyramid, dogpyramid and extrema.txt.--"<<endl;
 
 
 
	std::cout <<"5.CalculateScale..."<<std::endl;   
	CalculateScale(extrema, sigma, intervals);                                    
	HalfFeatures(extrema);
 
 
 
	std::cout << "6.Orientation assignment..."<<std::endl;                                    
	OrientationAssignment(extrema, features, gauss_pyr);                         
	std::cout << "(6) features count: "<<features.size()<<std::endl;
	  
 
 
	std::cout << "7.DescriptorRepresentation..."<<std::endl;
	DescriptorRepresentation(features, gauss_pyr, DESCR_HIST_BINS, DESCR_WINDOW_WIDTH);
	sort(features.begin(), features.end(), FeatureCmp);                           
	cout << "finished."<<endl;
	std::cout<<"***********************************************"<<endl;
	
}

void DrawSiftFeature(Mat& src, Keypoint& feat, CvScalar color)
{
	int len, hlen, blen, start_x, start_y, end_x, end_y, h1_x, h1_y, h2_x, h2_y;
	double scl, ori;
	double scale = 5.0;
	double hscale = 0.75;
	CvPoint start, end, h1, h2;
	/* compute points for an arrow scaled and rotated by feat's scl and ori */
	start_x = cvRound( feat.dx );
	start_y = cvRound( feat.dy );
	scl = feat.scale;
	ori = feat.ori;
	len = cvRound( scl * scale );
	hlen = cvRound( scl * hscale );
	blen = len - hlen;
	end_x = cvRound( len *  cos( ori ) ) + start_x;
	end_y = cvRound( len * -sin( ori ) ) + start_y;
	h1_x = cvRound( blen *  cos( ori + CV_PI / 18.0 ) ) + start_x;
	h1_y = cvRound( blen * -sin( ori + CV_PI / 18.0 ) ) + start_y;
	h2_x = cvRound( blen *  cos( ori - CV_PI / 18.0 ) ) + start_x;
	h2_y = cvRound( blen * -sin( ori - CV_PI / 18.0 ) ) + start_y;
	start = cvPoint( start_x, start_y );
	end = cvPoint( end_x, end_y );
	h1 = cvPoint( h1_x, h1_y );
	h2 = cvPoint( h2_x, h2_y );
 
	line( src, start, end, color, 1, 8, 0 );
	line( src, end, h1, color, 1, 8, 0 );
	line( src, end, h2, color, 1, 8, 0 );
}

void DrawSiftFeatures(Mat& src, vector<Keypoint>& features)
{
	CvScalar color = CV_RGB( 0, 0, 255 );
	for(int i = 0; i < features.size(); i++)
	{
		DrawSiftFeature(src, features[i], color);
	}
}

void DrawKeyPoints(Mat &src, vector<Keypoint>& keypoints)
{
	int j = 0;
	for(int i = 0; i < keypoints.size(); i++)
	{
	
		CvScalar color = {0, 0 ,255};
		circle(src, Point(keypoints[i].dx, keypoints[i].dy), 3, color);
		j++;
	}
}
 
void read_features(vector<Keypoint>&features, const char*file)
{
	ifstream in(file);
	int n = 0, dims = 0;
	in >> n >> dims; 
	cout <<n <<" " <<dims<<endl;
	for(int i = 0; i < n; i++)
	{
		Keypoint key;
		in >> key.dy >> key.dx  >> key.scale >> key.ori;
		for(int j = 0; j < dims; j++)
		{
			in >> key.descriptor[j];
		}
		features.push_back(key);
	}
	in.close();
}

void write_features(const vector<Keypoint>&features, const char*file)
{
	ofstream dout(file);
	dout << features.size()<<" "<< FEATURE_ELEMENT_LENGTH<<endl;
	for(int i = 0; i < features.size(); i++)
	{
		dout <<features[i].dy<< " " << features[i].dx<<" "<<features[i].scale<< " "<<features[i].ori<<endl;
		for(int j = 0; j < FEATURE_ELEMENT_LENGTH; j++)
		{
			if(j % 20 == 0)
				dout<<endl;
			dout << features[i].descriptor[j]<<" "; 
		}
		dout<<endl;
	}
	dout.close();
}


double CaculateDistance(Keypoint& kp1,Keypoint& kp2) //caculate the distance between two keypoints
{
	double distance = 0;
	for(int j = 0;j < FEATURE_ELEMENT_LENGTH; j++)
	{
		double temp;
		temp =pow((double)kp1.descriptor[j]-(double)kp2.descriptor[j],2);
		//cout<<"temp is :"<<temp<<endl;
		distance = distance + temp;	  
	}
	
	return sqrt(distance);
}

void FindMatching(Mat& src,Mat& src1,Mat& src2,std::vector<Keypoint>& kp1,std::vector<Keypoint>& kp2,double threshold)
{
	double distance;
	int a = 0;
	for(int i = 0; i < kp1.size() ; i++)
	{
		double best_match_x = 0;
		double best_match_y = 0;

		double array[kp2.size()];
		double mindistance = 10000;
		int count = 0;
		for(int j = 0 ; j < kp2.size() ; j++)
		{
				distance = CaculateDistance(kp1[i],kp2[j]);
				array[count] = distance;
				//cout<<"keypoint1 "<<i<<" to "<<" keypoint2 "<<j<<" distance is "<<distance<<endl;
				if(array[count] < mindistance)
				{
					mindistance = array[count];
					best_match_x = kp2[j].dx;
					best_match_y = kp2[j].dy;
						
				}
				count++;
				//need to find smallest distance		
		}
		
		if(distance > 480)
		{
			continue;
		}
		if(abs(kp1[i].dy - best_match_y) >100.0)
		{
			continue;
		}

		//cout<<"best_match_point is "<<"kp1 "<<kp1[i].dx<<" , "<<kp1[i].dy<<" - >kp2 "<<best_match_x<<" , "<<best_match_y<<endl;
		Drawlines(src,src1,src2,kp1[i],best_match_x,best_match_y);
		a = a+1;
		//cout<<j<<endl;
		//cout<<"******************************************"<<endl;
		//cout<<"coordinate of x is "<<"( "<<kp1[i].x<<","<<kp1[i].y<<" )"<<endl;
		//cout<<"coordinate of x is "<<"( "<<best_match_x<<","best_match_y<<" )"<<endl;
		//cout<<"******************************************"<<endl;
	}
	cout<<"------------------------------------------------------"<<endl;
	cout<<"The number of Match points(The number of lines) are :"<<a<<endl;
	cout<<"------------------------------------------------------"<<endl;
}

void Drawlines(Mat& src,Mat& src1,Mat& src2,Keypoint& kp1,double x,double y)
{
	Point a = Point(kp1.dx,kp1.dy);
	Point b = Point(x+src1.cols,y);
	line(src,a,b,Scalar(255,0,0),1,8);
}

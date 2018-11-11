//
//  SIFT.cpp
//  SIFT
//
//  Created by 张涵健 on 2018/11/7.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#include "../include/SIFT.hpp"
#include <iostream>
#include <stdarg.h>
/*************** 定义会用到的参数和宏 ****************/

// 每一组中默认的采样数，即小s的值。
static const int SIFT_INTVLS = 3;

//最初的高斯模糊的尺度默认值，即假设的第0组（某些地方叫做-1组）的尺度
static const float SIFT_SIGMA = 1.6f;

// 关键点对比 |D(x)|的默认值，公式14的阈值
static const float SIFT_CONTR_THR = 0.04f;

// 关键点的主曲率比的默认阈值
static const float SIFT_CURV_THR = 10.f;

//是否在构建高斯金字塔之前扩展图像的宽和高位原来的两倍（即是否建立-1组）
static const bool SIFT_IMG_DBL = true;

// 描述子直方图数组的默认宽度，即描述子建立中的4*4的周边区域
static const int SIFT_DESCR_WIDTH = 4;

// 每个描述子数组中的默认柱的个数（ 4*4*8=128）
static const int SIFT_DESCR_HIST_BINS = 8;

// 假设输入图像的高斯模糊的尺度
static const float SIFT_INIT_SIGMA = 0.5f;

// width of border in which to ignore keypoints
static const int SIFT_IMG_BORDER = 5;

//公式12的为了寻找关键点插值中心的最大迭代次数
static const int SIFT_MAX_INTERP_STEPS = 5;

// 方向梯度直方图中的柱的个数
static const int SIFT_ORI_HIST_BINS = 36;

// determines gaussian sigma for orientation assignment
static const float SIFT_ORI_SIG_FCTR = 1.5f;

// determines the radius of the region used in orientation assignment
static const float SIFT_ORI_RADIUS = 3 * SIFT_ORI_SIG_FCTR;

// orientation magnitude relative to max that results in new feature
static const float SIFT_ORI_PEAK_RATIO = 0.8f;

// determines the size of a single descriptor orientation histogram
static const float SIFT_DESCR_SCL_FCTR = 3.f;

// threshold on magnitude of elements of descriptor vector
static const float SIFT_DESCR_MAG_THR = 0.2f;

// factor used to convert floating-point descriptor to unsigned char
static const float SIFT_INT_DESCR_FCTR = 512.f;

static const float atan2_p1 = 0.9997878412794807f*(float)(180/CV_PI);
static const float atan2_p3 = -0.3258083974640975f*(float)(180/CV_PI);
static const float atan2_p5 = 0.1555786518463281f*(float)(180/CV_PI);
static const float atan2_p7 = -0.04432655554792128f*(float)(180/CV_PI);
enum { BLOCK_SIZE = 1024 };
int nbins = 9;

#if 0
// intermediate type used for DoG pyramids
typedef short sift_wt;
static const int SIFT_FIXPT_SCALE = 48;
#else
// intermediate type used for DoG pyramids
typedef float sift_wt;
static const int SIFT_FIXPT_SCALE = 1;
#endif
static void exp(float* W, const float* w, int len){
    for (int i = 0; i < len; i++){
        *(W+i) = exp(*(w+i));
    }
}

static void fastAtan2(const float *Y, const float *X, float *angle, int len, bool angleInDegrees=true )
{
    int i = 0;
    float scale = angleInDegrees ? 1 : (float)(CV_PI/180);

    for( ; i < len; i++ )
    {
        float x = X[i], y = Y[i];
        //cout << "x: " << x << " "<< " y: " << y << endl;
        float ax = std::abs(x), ay = std::abs(y);
        float a, c, c2;
        if( ax >= ay )
        {
            c = ay/(ax + (float)DBL_EPSILON);
            c2 = c*c;
            a = (((atan2_p7*c2 + atan2_p5)*c2 + atan2_p3)*c2 + atan2_p1)*c;
        }
        else
        {
            c = ax/(ay + (float)DBL_EPSILON);
            c2 = c*c;
            a = 90.f - (((atan2_p7*c2 + atan2_p5)*c2 + atan2_p3)*c2 + atan2_p1)*c;
        }
        if( x < 0 )
            a = 180.f - a;
        if( y < 0 )
            a = 360.f - a;
        angle[i] = (float)(a*scale);
        //cout << " angle: " << angle[i] << endl;
    }
}

static void magnitude(const float* x, const float* y, float* mag, int len)
{
    int i = 0;

    for( ; i < len; i++ )
    {
        float x0 = x[i], y0 = y[i];
        mag[i] = std::sqrt(x0*x0 + y0*y0);
        //cout << "mag: " << mag[i] << endl;
    }
}

SIFT::SIFT( int _nfeatures, int _nOctaveLayers,
           double _contrastThreshold, double _edgeThreshold, double _sigma )
: nfeatures(_nfeatures), nOctaveLayers(_nOctaveLayers),
contrastThreshold(_contrastThreshold), edgeThreshold(_edgeThreshold), sigma(_sigma)
{
}

static inline void
unpackOctave(const KeyPoint& kpt, int& octave, int& layer, float& scale)
{
    octave = kpt.octave & 255;
    layer = (kpt.octave >> 8) & 255;
    octave = octave < 128 ? octave : (-128 | octave);
    scale = octave >= 0 ? 1.f/(1 << octave) : (float)(1 << -octave);
}
//1、创建基图像矩阵createInitialImage 函数：
static Mat createInitialImage( const Mat& img, bool doubleImageSize, float sigma )
{
    Mat gray, gray_fpt;
    if( img.channels() == 3 || img.channels() == 4 )
        cvtColor(img, gray, COLOR_BGR2GRAY);
    else
        img.copyTo(gray);
    //typedef float sift_wt;
    //static const int SIFT_FIXPT_SCALE = 1
    gray.convertTo(gray_fpt, DataType<sift_wt>::type, SIFT_FIXPT_SCALE, 0);

    float sig_diff;

    if( doubleImageSize )
    {
        sig_diff = sqrtf( std::max(sigma * sigma - SIFT_INIT_SIGMA * SIFT_INIT_SIGMA * 4, 0.01f) );
        Mat dbl;
        resize(gray_fpt, dbl, Size(gray.cols*2, gray.rows*2), 0, 0, INTER_LINEAR);
        GaussianBlur(dbl, dbl, Size(), sig_diff, sig_diff);
        return dbl;
    }
    else
    {
        sig_diff = sqrtf( std::max(sigma * sigma - SIFT_INIT_SIGMA * SIFT_INIT_SIGMA, 0.01f) );
        GaussianBlur(gray_fpt, gray_fpt, Size(), sig_diff, sig_diff);
        return gray_fpt;
    }
}

//2、建立高斯金字塔
void SIFT::buildGaussianPyramid( const Mat& base, vector<Mat>& pyr, int nOctaves ) const
{
    vector<double> sig(nOctaveLayers + 3);
    pyr.resize(nOctaves*(nOctaveLayers + 3));

    // precompute Gaussian sigmas using the following formula:
    //  \sigma_{total}^2 = \sigma_{i}^2 + \sigma_{i-1}^2
    sig[0] = sigma;
    double k = pow( 2., 1. / nOctaveLayers );
    for( int i = 1; i < nOctaveLayers + 3; i++ )
    {
        double sig_prev = pow(k, (double)(i-1))*sigma;
        double sig_total = sig_prev*k;
        sig[i] = std::sqrt(sig_total*sig_total - sig_prev*sig_prev);
    }

    for( int o = 0; o < nOctaves; o++ )
    {
        for( int i = 0; i < nOctaveLayers + 3; i++ )
        {
            Mat& dst = pyr[o*(nOctaveLayers + 3) + i];
            if( o == 0  &&  i == 0 )
                dst = base;
            // base of new octave is halved image from end of previous octave
            else if( i == 0 )
            {
                const Mat& src = pyr[(o-1)*(nOctaveLayers + 3) + nOctaveLayers];
                resize(src, dst, Size(src.cols/2, src.rows/2),
                       0, 0, INTER_NEAREST);
            }
            else
            {
                const Mat& src = pyr[o*(nOctaveLayers + 3) + i-1];
                GaussianBlur(src, dst, Size(), sig[i], sig[i]);
            }
        }
    }
}

//3、建立DoG金字塔
void SIFT::buildDoGPyramid( const vector<Mat>& gpyr, vector<Mat>& dogpyr ) const
{
    int nOctaves = (int)gpyr.size()/(nOctaveLayers + 3);
    dogpyr.resize( nOctaves*(nOctaveLayers + 2) );

    for( int o = 0; o < nOctaves; o++ )
    {
        for( int i = 0; i < nOctaveLayers + 2; i++ )
        {
            const Mat& src1 = gpyr[o*(nOctaveLayers + 3) + i];
            const Mat& src2 = gpyr[o*(nOctaveLayers + 3) + i + 1];
            Mat& dst = dogpyr[o*(nOctaveLayers + 2) + i];
            subtract(src2, src1, dst, noArray(), DataType<sift_wt>::type);
        }
    }
}

//4、2 建立方向直方图
// Computes a gradient orientation histogram at a specified pixel
static float calcOrientationHist( const Mat& img, Point pt, int radius,
                                 float sigma, float* hist, int n )
{
    int i, j, k, len = (radius*2+1)*(radius*2+1);

    float expf_scale = -1.f/(2.f * sigma * sigma);
    AutoBuffer<float> buf(len*4 + n+4);
    float *X = buf, *Y = X + len, *Mag = X, *Ori = Y + len, *W = Ori + len;
    float* temphist = W + len + 2;

    for( i = 0; i < n; i++ )
        temphist[i] = 0.f;

    for( i = -radius, k = 0; i <= radius; i++ )
    {
        int y = pt.y + i;
        if( y <= 0 || y >= img.rows - 1 )
            continue;
        for( j = -radius; j <= radius; j++ )
        {
            int x = pt.x + j;
            if( x <= 0 || x >= img.cols - 1 )
                continue;

            float dx = (float)(img.at<sift_wt>(y, x+1) - img.at<sift_wt>(y, x-1));
            float dy = (float)(img.at<sift_wt>(y-1, x) - img.at<sift_wt>(y+1, x));

            X[k] = dx; Y[k] = dy; W[k] = (i*i + j*j)*expf_scale;
            k++;
        }
    }

    len = k;

    // compute gradient values, orientations and the weights over the pixel neighborhood
    exp(W, W, len);
    fastAtan2(Y, X, Ori, len, true);
    magnitude(X, Y, Mag, len);

    for( k = 0; k < len; k++ )
    {
        int bin = cvRound((n/360.f)*Ori[k]);
        if( bin >= n )
            bin -= n;
        if( bin < 0 )
            bin += n;
        temphist[bin] += W[k]*Mag[k];
    }

    // smooth the histogram
    temphist[-1] = temphist[n-1];
    temphist[-2] = temphist[n-2];
    temphist[n] = temphist[0];
    temphist[n+1] = temphist[1];
    for( i = 0; i < n; i++ )
    {
        hist[i] = (temphist[i-2] + temphist[i+2])*(1.f/16.f) +
        (temphist[i-1] + temphist[i+1])*(4.f/16.f) +
        temphist[i]*(6.f/16.f);
    }

    float maxval = hist[0];
    for( i = 1; i < n; i++ )
        maxval = std::max(maxval, hist[i]);

    return maxval;
}

//4.1、尺度空间中关键点插值过滤
//
// Interpolates a scale-space extremum's location and scale to subpixel
// accuracy to form an image feature. Rejects features with low contrast.
// Based on Section 4 of Lowe's paper.
static bool adjustLocalExtrema( const vector<Mat>& dog_pyr, KeyPoint& kpt, int octv,
                               int& layer, int& r, int& c, int nOctaveLayers,
                               float contrastThreshold, float edgeThreshold, float sigma )
{
    const float img_scale = 1.f/(255*SIFT_FIXPT_SCALE);
    const float deriv_scale = img_scale*0.5f;
    const float second_deriv_scale = img_scale;
    const float cross_deriv_scale = img_scale*0.25f;

    float xi=0, xr=0, xc=0, contr=0;
    int i = 0;

    for( ; i < SIFT_MAX_INTERP_STEPS; i++ )
    {
        int idx = octv*(nOctaveLayers+2) + layer;
        const Mat& img = dog_pyr[idx];
        const Mat& prev = dog_pyr[idx-1];
        const Mat& next = dog_pyr[idx+1];

        Vec3f dD((img.at<sift_wt>(r, c+1) - img.at<sift_wt>(r, c-1))*deriv_scale,
                 (img.at<sift_wt>(r+1, c) - img.at<sift_wt>(r-1, c))*deriv_scale,
                 (next.at<sift_wt>(r, c) - prev.at<sift_wt>(r, c))*deriv_scale);

        float v2 = (float)img.at<sift_wt>(r, c)*2;
        float dxx = (img.at<sift_wt>(r, c+1) + img.at<sift_wt>(r, c-1) - v2)*second_deriv_scale;
        float dyy = (img.at<sift_wt>(r+1, c) + img.at<sift_wt>(r-1, c) - v2)*second_deriv_scale;
        float dss = (next.at<sift_wt>(r, c) + prev.at<sift_wt>(r, c) - v2)*second_deriv_scale;
        float dxy = (img.at<sift_wt>(r+1, c+1) - img.at<sift_wt>(r+1, c-1) -
                     img.at<sift_wt>(r-1, c+1) + img.at<sift_wt>(r-1, c-1))*cross_deriv_scale;
        float dxs = (next.at<sift_wt>(r, c+1) - next.at<sift_wt>(r, c-1) -
                     prev.at<sift_wt>(r, c+1) + prev.at<sift_wt>(r, c-1))*cross_deriv_scale;
        float dys = (next.at<sift_wt>(r+1, c) - next.at<sift_wt>(r-1, c) -
                     prev.at<sift_wt>(r+1, c) + prev.at<sift_wt>(r-1, c))*cross_deriv_scale;

        Matx33f H(dxx, dxy, dxs,
                  dxy, dyy, dys,
                  dxs, dys, dss);

        Vec3f X = H.solve(dD, DECOMP_LU);

        xi = -X[2];
        xr = -X[1];
        xc = -X[0];

        if( std::abs(xi) < 0.5f && std::abs(xr) < 0.5f && std::abs(xc) < 0.5f )
            break;

        if( std::abs(xi) > (float)(INT_MAX/3) ||
           std::abs(xr) > (float)(INT_MAX/3) ||
           std::abs(xc) > (float)(INT_MAX/3) )
            return false;

        c += cvRound(xc);
        r += cvRound(xr);
        layer += cvRound(xi);

        if( layer < 1 || layer > nOctaveLayers ||
           c < SIFT_IMG_BORDER || c >= img.cols - SIFT_IMG_BORDER  ||
           r < SIFT_IMG_BORDER || r >= img.rows - SIFT_IMG_BORDER )
            return false;
    }

    // ensure convergence of interpolation
    if( i >= SIFT_MAX_INTERP_STEPS )
        return false;

    {
        int idx = octv*(nOctaveLayers+2) + layer;
        const Mat& img = dog_pyr[idx];
        const Mat& prev = dog_pyr[idx-1];
        const Mat& next = dog_pyr[idx+1];
        Matx31f dD((img.at<sift_wt>(r, c+1) - img.at<sift_wt>(r, c-1))*deriv_scale,
                   (img.at<sift_wt>(r+1, c) - img.at<sift_wt>(r-1, c))*deriv_scale,
                   (next.at<sift_wt>(r, c) - prev.at<sift_wt>(r, c))*deriv_scale);
        float t = dD.dot(Matx31f(xc, xr, xi));

        contr = img.at<sift_wt>(r, c)*img_scale + t * 0.5f;
        if( std::abs( contr ) * nOctaveLayers < contrastThreshold )
            return false;

        // principal curvatures are computed using the trace and det of Hessian
        float v2 = img.at<sift_wt>(r, c)*2.f;
        float dxx = (img.at<sift_wt>(r, c+1) + img.at<sift_wt>(r, c-1) - v2)*second_deriv_scale;
        float dyy = (img.at<sift_wt>(r+1, c) + img.at<sift_wt>(r-1, c) - v2)*second_deriv_scale;
        float dxy = (img.at<sift_wt>(r+1, c+1) - img.at<sift_wt>(r+1, c-1) -
                     img.at<sift_wt>(r-1, c+1) + img.at<sift_wt>(r-1, c-1)) * cross_deriv_scale;
        float tr = dxx + dyy;
        float det = dxx * dyy - dxy * dxy;

        if( det <= 0 || tr*tr*edgeThreshold >= (edgeThreshold + 1)*(edgeThreshold + 1)*det )
            return false;
    }

    kpt.pt.x = (c + xc) * (1 << octv);
    kpt.pt.y = (r + xr) * (1 << octv);
    kpt.octave = octv + (layer << 8) + (cvRound((xi + 0.5)*255) << 16);
    kpt.size = sigma*powf(2.f, (layer + xi) / nOctaveLayers)*(1 << octv)*2;
    kpt.response = std::abs(contr);

    return true;
}

//4、寻找尺度空间中的极值
//
// Detects features at extrema in DoG scale space.  Bad features are discarded
// based on contrast and ratio of principal curvatures.
void SIFT::findScaleSpaceExtrema( const vector<Mat>& gauss_pyr, const vector<Mat>& dog_pyr,
                                 vector<KeyPoint>& keypoints ) const
{
    int nOctaves = (int)gauss_pyr.size()/(nOctaveLayers + 3);
    int threshold = cvFloor(0.5 * contrastThreshold / nOctaveLayers * 255 * SIFT_FIXPT_SCALE);
    const int n = SIFT_ORI_HIST_BINS;
    float hist[n];
    KeyPoint kpt;

    keypoints.clear();

    for( int o = 0; o < nOctaves; o++ )
        for( int i = 1; i <= nOctaveLayers; i++ )
        {
            int idx = o*(nOctaveLayers+2)+i;
            const Mat& img = dog_pyr[idx];
            const Mat& prev = dog_pyr[idx-1];
            const Mat& next = dog_pyr[idx+1];
            int step = (int)img.step1();
            int rows = img.rows, cols = img.cols;

            for( int r = SIFT_IMG_BORDER; r < rows-SIFT_IMG_BORDER; r++)
            {
                const sift_wt* currptr = img.ptr<sift_wt>(r);
                const sift_wt* prevptr = prev.ptr<sift_wt>(r);
                const sift_wt* nextptr = next.ptr<sift_wt>(r);

                for( int c = SIFT_IMG_BORDER; c < cols-SIFT_IMG_BORDER; c++)
                {
                    sift_wt val = currptr[c];

                    // find local extrema with pixel accuracy
                    if( std::abs(val) > threshold &&
                       ((val > 0 && val >= currptr[c-1] && val >= currptr[c+1] &&
                         val >= currptr[c-step-1] && val >= currptr[c-step] && val >= currptr[c-step+1] &&
                         val >= currptr[c+step-1] && val >= currptr[c+step] && val >= currptr[c+step+1] &&
                         val >= nextptr[c] && val >= nextptr[c-1] && val >= nextptr[c+1] &&
                         val >= nextptr[c-step-1] && val >= nextptr[c-step] && val >= nextptr[c-step+1] &&
                         val >= nextptr[c+step-1] && val >= nextptr[c+step] && val >= nextptr[c+step+1] &&
                         val >= prevptr[c] && val >= prevptr[c-1] && val >= prevptr[c+1] &&
                         val >= prevptr[c-step-1] && val >= prevptr[c-step] && val >= prevptr[c-step+1] &&
                         val >= prevptr[c+step-1] && val >= prevptr[c+step] && val >= prevptr[c+step+1]) ||
                        (val < 0 && val <= currptr[c-1] && val <= currptr[c+1] &&
                         val <= currptr[c-step-1] && val <= currptr[c-step] && val <= currptr[c-step+1] &&
                         val <= currptr[c+step-1] && val <= currptr[c+step] && val <= currptr[c+step+1] &&
                         val <= nextptr[c] && val <= nextptr[c-1] && val <= nextptr[c+1] &&
                         val <= nextptr[c-step-1] && val <= nextptr[c-step] && val <= nextptr[c-step+1] &&
                         val <= nextptr[c+step-1] && val <= nextptr[c+step] && val <= nextptr[c+step+1] &&
                         val <= prevptr[c] && val <= prevptr[c-1] && val <= prevptr[c+1] &&
                         val <= prevptr[c-step-1] && val <= prevptr[c-step] && val <= prevptr[c-step+1] &&
                         val <= prevptr[c+step-1] && val <= prevptr[c+step] && val <= prevptr[c+step+1])))
                    {
                        int r1 = r, c1 = c, layer = i;
                        if( !adjustLocalExtrema(dog_pyr, kpt, o, layer, r1, c1,
                                                nOctaveLayers, (float)contrastThreshold,
                                                (float)edgeThreshold, (float)sigma) )
                            continue;
                        float scl_octv = kpt.size*0.5f/(1 << o);
                        float omax = calcOrientationHist(gauss_pyr[o*(nOctaveLayers+3) + layer],
                                                         Point(c1, r1),
                                                         cvRound(SIFT_ORI_RADIUS * scl_octv),
                                                         SIFT_ORI_SIG_FCTR * scl_octv,
                                                         hist, n);
                        float mag_thr = (float)(omax * SIFT_ORI_PEAK_RATIO);
                        for( int j = 0; j < n; j++ )
                        {
                            int l = j > 0 ? j - 1 : n - 1;
                            int r2 = j < n-1 ? j + 1 : 0;

                            if( hist[j] > hist[l]  &&  hist[j] > hist[r2]  &&  hist[j] >= mag_thr )
                            {
                                float bin = j + 0.5f * (hist[l]-hist[r2]) / (hist[l] - 2*hist[j] + hist[r2]);
                                bin = bin < 0 ? n + bin : bin >= n ? bin - n : bin;
                                kpt.angle = 360.f - (float)((360.f/n) * bin);
                                if(std::abs(kpt.angle - 360.f) < FLT_EPSILON)
                                    kpt.angle = 0.f;
                                keypoints.push_back(kpt);
                            }
                        }
                    }
                }
            }
        }
}

//5.1、计算sift的描述子
static void calcSIFTDescriptor( const Mat& img, Point2f ptf, float ori, float scl,
                               int d, int n, float* dst )
{
    Point pt(cvRound(ptf.x), cvRound(ptf.y));
    float cos_t = cosf(ori*(float)(CV_PI/180));
    float sin_t = sinf(ori*(float)(CV_PI/180));
    float bins_per_rad = n / 360.f;
    float exp_scale = -1.f/(d * d * 0.5f);
    float hist_width = SIFT_DESCR_SCL_FCTR * scl;
    int radius = cvRound(hist_width * 1.4142135623730951f * (d + 1) * 0.5f);
    cos_t /= hist_width;
    sin_t /= hist_width;

    int i, j, k, len = (radius*2+1)*(radius*2+1), histlen = (d+2)*(d+2)*(n+2);
    int rows = img.rows, cols = img.cols;

    AutoBuffer<float> buf(len*6 + histlen);
    float *X = buf, *Y = X + len, *Mag = Y, *Ori = Mag + len, *W = Ori + len;
    float *RBin = W + len, *CBin = RBin + len, *hist = CBin + len;

    for( i = 0; i < d+2; i++ )
    {
        for( j = 0; j < d+2; j++ )
            for( k = 0; k < n+2; k++ )
                hist[(i*(d+2) + j)*(n+2) + k] = 0.;
    }

    for( i = -radius, k = 0; i <= radius; i++ )
        for( j = -radius; j <= radius; j++ )
        {
            // Calculate sample's histogram array coords rotated relative to ori.
            // Subtract 0.5 so samples that fall e.g. in the center of row 1 (i.e.
            // r_rot = 1.5) have full weight placed in row 1 after interpolation.
            float c_rot = j * cos_t - i * sin_t;
            float r_rot = j * sin_t + i * cos_t;
            float rbin = r_rot + d/2 - 0.5f;
            float cbin = c_rot + d/2 - 0.5f;
            int r = pt.y + i, c = pt.x + j;

            if( rbin > -1 && rbin < d && cbin > -1 && cbin < d &&
               r > 0 && r < rows - 1 && c > 0 && c < cols - 1 )
            {
                float dx = (float)(img.at<sift_wt>(r, c+1) - img.at<sift_wt>(r, c-1));
                float dy = (float)(img.at<sift_wt>(r-1, c) - img.at<sift_wt>(r+1, c));
                X[k] = dx; Y[k] = dy; RBin[k] = rbin; CBin[k] = cbin;
                W[k] = (c_rot * c_rot + r_rot * r_rot)*exp_scale;
                k++;
            }
        }

    len = k;
    fastAtan2(Y, X, Ori, len, true);
    magnitude(X, Y, Mag, len);
    exp(W, W, len);

    for( k = 0; k < len; k++ )
    {
        float rbin = RBin[k], cbin = CBin[k];
        float obin = (Ori[k] - ori)*bins_per_rad;
        float mag = Mag[k]*W[k];

        int r0 = cvFloor( rbin );
        int c0 = cvFloor( cbin );
        int o0 = cvFloor( obin );
        rbin -= r0;
        cbin -= c0;
        obin -= o0;

        if( o0 < 0 )
            o0 += n;
        if( o0 >= n )
            o0 -= n;

        // histogram update using tri-linear interpolation
        float v_r1 = mag*rbin, v_r0 = mag - v_r1;
        float v_rc11 = v_r1*cbin, v_rc10 = v_r1 - v_rc11;
        float v_rc01 = v_r0*cbin, v_rc00 = v_r0 - v_rc01;
        float v_rco111 = v_rc11*obin, v_rco110 = v_rc11 - v_rco111;
        float v_rco101 = v_rc10*obin, v_rco100 = v_rc10 - v_rco101;
        float v_rco011 = v_rc01*obin, v_rco010 = v_rc01 - v_rco011;
        float v_rco001 = v_rc00*obin, v_rco000 = v_rc00 - v_rco001;

        int idx = ((r0+1)*(d+2) + c0+1)*(n+2) + o0;
        hist[idx] += v_rco000;
        hist[idx+1] += v_rco001;
        hist[idx+(n+2)] += v_rco010;
        hist[idx+(n+3)] += v_rco011;
        hist[idx+(d+2)*(n+2)] += v_rco100;
        hist[idx+(d+2)*(n+2)+1] += v_rco101;
        hist[idx+(d+3)*(n+2)] += v_rco110;
        hist[idx+(d+3)*(n+2)+1] += v_rco111;
    }

    // finalize histogram, since the orientation histograms are circular
    for( i = 0; i < d; i++ )
        for( j = 0; j < d; j++ )
        {
            int idx = ((i+1)*(d+2) + (j+1))*(n+2);
            hist[idx] += hist[idx+n];
            hist[idx+1] += hist[idx+n+1];
            for( k = 0; k < n; k++ )
                dst[(i*d + j)*n + k] = hist[idx+k];
        }
    // copy histogram to the descriptor,
    // apply hysteresis thresholding
    // and scale the result, so that it can be easily converted
    // to byte array
    float nrm2 = 0;
    len = d*d*n;
    for( k = 0; k < len; k++ )
        nrm2 += dst[k]*dst[k];
    float thr = std::sqrt(nrm2)*SIFT_DESCR_MAG_THR;
    for( i = 0, nrm2 = 0; i < k; i++ )
    {
        float val = std::min(dst[i], thr);
        dst[i] = val;
        nrm2 += val*val;
    }
    nrm2 = SIFT_INT_DESCR_FCTR/std::max(std::sqrt(nrm2), FLT_EPSILON);

#if 1
    for( k = 0; k < len; k++ )
    {
        dst[k] = saturate_cast<uchar>(dst[k]*nrm2);
    }
#else
    float nrm1 = 0;
    for( k = 0; k < len; k++ )
    {
        dst[k] *= nrm2;
        nrm1 += dst[k];
    }
    nrm1 = 1.f/std::max(nrm1, FLT_EPSILON);
    for( k = 0; k < len; k++ )
    {
        dst[k] = std::sqrt(dst[k] * nrm1);//saturate_cast<uchar>(std::sqrt(dst[k] * nrm1)*SIFT_INT_DESCR_FCTR);
    }
#endif
}
//5、计算描述子
static void calcDescriptors(const vector<Mat>& gpyr, const vector<KeyPoint>& keypoints,
                            Mat& descriptors, int nOctaveLayers, int firstOctave )
{
    int d = SIFT_DESCR_WIDTH, n = SIFT_DESCR_HIST_BINS;

    for( size_t i = 0; i < keypoints.size(); i++ )
    {
        KeyPoint kpt = keypoints[i];
        int octave, layer;
        float scale;
        unpackOctave(kpt, octave, layer, scale);
        CV_Assert(octave >= firstOctave && layer <= nOctaveLayers+2);
        float size=kpt.size*scale;
        Point2f ptf(kpt.pt.x*scale, kpt.pt.y*scale);
        const Mat& img = gpyr[(octave - firstOctave)*(nOctaveLayers + 3) + layer];

        float angle = 360.f - kpt.angle;
        if(std::abs(angle - 360.f) < FLT_EPSILON)
            angle = 0.f;
        calcSIFTDescriptor(img, ptf, angle, size*0.5f, d, n, descriptors.ptr<float>((int)i));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//nfeatures 表示需要输出的特征点的数量，程序能够通过排序输出最好的前nfeatures 个特征点，如果nfeatures=0，
//则表示输出所有的特征点；
//nOctaveLayers S=s+3中的参数小s；
//contrastThreshold 为公式14 中的参数T；
//edgeThreshold 为公式19 中的γ；
//sigma 表示基准层尺度σ0。


int SIFT::descriptorSize() const
{
    return SIFT_DESCR_WIDTH*SIFT_DESCR_WIDTH*SIFT_DESCR_HIST_BINS;
}

int SIFT::descriptorType() const
{
    return CV_32F;
}

//SIFT 类中的重载运算符( )：
void SIFT::operator()(InputArray _image, InputArray _mask,
                      vector<KeyPoint>& keypoints) const
{
    (*this)(_image, _mask, keypoints, noArray());
}

//_imgage 为输入的8 位灰度图像；
//_mask 表示可选的输入掩码矩阵，用来标注需要检测的特征点的区域；
//keypoints 为特征点矢量；
//descriptors 为输出的特征点描述符矩阵，如果不想得到该值，则需要赋予该值为cv::noArray()；
//useProvidedKeypoints 为二值标识符，默认为false 时，表示需要计算输入图像的特征点；
//为true 时，表示无需特征点检测，而是利用输入的特征点keypoints 计算它们的描述符。
void SIFT::operator()(InputArray _image, InputArray _mask,
                      vector<KeyPoint>& keypoints,
                      OutputArray _descriptors,
                      bool useProvidedKeypoints) const
{
    //定义并初始化一些变量
    //firstOctave 表示金字塔的组索引是从0 开始还是从‐1 开始，‐1 表示需要对输入图像的长宽扩大一倍，
    //actualNOctaves 和actualNLayers 分别表示实际的金字塔的组数和层数
    int firstOctave = -1, actualNOctaves = 0, actualNLayers = 0;
    //得到输入图像和掩码的矩阵
    Mat image = _image.getMat(), mask = _mask.getMat();
    //对输入图像和掩码进行必要的参数确认
    if( image.empty() || image.depth() != CV_8U )
        CV_Error( CV_StsBadArg, "image is empty or has incorrect depth (!=CV_8U)" );

    if( !mask.empty() && mask.type() != CV_8UC1 )
        CV_Error( CV_StsBadArg, "mask has incorrect type (!=CV_8UC1)" );
    //下面if 语句表示不需要计算图像的特征点，只需要根据输入的特征点keypoints 参数计算它们的描述符
    if( useProvidedKeypoints )
    {
        //因为不需要扩大输入图像的长宽，所以重新赋值firstOctave 为0
        firstOctave = 0;
        //给maxOctave 赋予一个极小的值
        int maxOctave = INT_MIN;
        //遍历全部的输入特征点，得到最小和最大组索引，以及实际的层数
        for( size_t i = 0; i < keypoints.size(); i++ )
        {
            int octave, layer;//组索引，层索引
            float scale;//尺度
            //从输入的特征点变量中提取出该特征点所在的组、层、以及它的尺度
            unpackOctave(keypoints[i], octave, layer, scale);
            //最小组索引号
            firstOctave = std::min(firstOctave, octave);
            //最大组索引号
            maxOctave = std::max(maxOctave, octave);
            //实际层数
            actualNLayers = std::max(actualNLayers, layer-2);
        }

        //确保最小组索引号不大于0
        firstOctave = std::min(firstOctave, 0);
        //确保最小组索引号大于等于‐1，实际层数小于等于输入参数nOctaveLayers
        CV_Assert( firstOctave >= -1 && actualNLayers <= nOctaveLayers );
        //计算实际的组数
        actualNOctaves = maxOctave - firstOctave + 1;
    }
    //创建基层图像矩阵base.
    //createInitialImage 函数的第二个参数表示是否进行扩大输入图像长宽尺寸操作，true
    //表示进行该操作，第三个参数为基准层尺度σ0
    Mat base = createInitialImage(image, firstOctave < 0, (float)sigma);
    //gpyr 为高斯金字塔矩阵向量，dogpyr 为DoG 金字塔矩阵向量
    vector<Mat> gpyr, dogpyr;
    // 计算金字塔的组的数量， 当actualNOctaves > 0 时， 表示进入了上面的if( useProvidedKeypoints )语句，
    //所以组数直接等于if( useProvidedKeypoints )内计算得到的值
    //如果actualNOctaves 不大于0，则计算组数
    //这里面还考虑了组的初始索引等于‐1 的情况，所以最后加上了 – firstOctave 这项
    int nOctaves = actualNOctaves > 0 ? actualNOctaves :
    cvRound(log( (double)std::min( base.cols, base.rows ) ) / log(2.) - 2) - firstOctave;

    //double t, tf = getTickFrequency();
    //t = (double)getTickCount();
    //buildGaussianPyramid 和buildDoGPyramid 分别为构建高斯金字塔和DoG 金字塔函数
    buildGaussianPyramid(base, gpyr, nOctaves);
    buildDoGPyramid(gpyr, dogpyr);

    //t = (double)getTickCount() - t;
    //printf("pyramid construction time: %g\n", t*1000./tf);
    // useProvidedKeypoints 为false，表示需要计算图像的特征点
    if( !useProvidedKeypoints )
    {
        //t = (double)getTickCount();
        //在尺度空间内找到极值点
        findScaleSpaceExtrema(gpyr, dogpyr, keypoints);
        //在特征点检测的过程中（尤其是在泰勒级数拟合的过程中）会出现特征点被重复检测到的现象，
        //因此要剔除掉那些重复的特征点
        //KeyPointsFilter 类是在modules/features2d/src/keypoint.cpp 定义的
        KeyPointsFilter::removeDuplicated( keypoints );
        //根据掩码矩阵，只保留掩码矩阵所涵盖的特征点
        if( !mask.empty() )
            KeyPointsFilter::runByPixelsMask( keypoints, mask );//??
        //保留那些最好的前nfeatures 个特征点
        if( nfeatures > 0 )
            KeyPointsFilter::retainBest(keypoints, nfeatures);
        //t = (double)getTickCount() - t;
        //printf("keypoint detection time: %g\n", t*1000./tf);
        //如果firstOctave < 0，则表示对输入图像进行了扩大处理，所以要对特征点的一些变量进行适当调整。
        //这是因为firstOctave < 0，金字塔增加了一个第‐1 组，而在检测特征点的时候，所有变量都是基于
        //这个第‐1 组的基准层尺度图像的
        if( firstOctave < 0 )
            //遍历所有特征点
            //cout << keypoints.size();
            for( size_t i = 0; i < keypoints.size(); i++ )
            {
                KeyPoint& kpt = keypoints[i];//提取出特征点
                //其实这里的firstOctave = ‐1，所以scale = 0.5
                float scale = 1.f/(float)(1 << -firstOctave);
                //重新调整特征点所在的组
                kpt.octave = (kpt.octave & ~255) | ((kpt.octave + firstOctave) & 255);
                //特征点的位置坐标调整到真正的输入图像内，即得到的坐标除以2
                kpt.pt *= scale;
                //特征点的尺度调整到相对于输入图像的尺度，即得到的尺度除以2
                kpt.size *= scale;
            }
    }
    else
    {
        // filter keypoints by mask
        //KeyPointsFilter::runByPixelsMask( keypoints, mask );

    }
    //如果需要得到特征点描述符，则进入下面的if 内，生成特征点描述符
    if( _descriptors.needed() )
    {
        //t = (double)getTickCount();
        //dsize 为特征点描述符的大小
        //即SIFT_DESCR_WIDTH*SIFT_DESCR_WIDTH*SIFT_DESCR_HIST_BINS=4×4×8=128
        int dsize = descriptorSize();

        //创建特征点描述符，为其开辟一段内存空间
        _descriptors.create((int)keypoints.size(), dsize, CV_32F);
        //描述符的矩阵形式
        Mat descriptors = _descriptors.getMat();
        //计算特征点描述符，calcDescriptors 函数在后面将给出详细的分析
        ::calcDescriptors(gpyr, keypoints, descriptors, nOctaveLayers, firstOctave);
        //t = (double)getTickCount() - t;
        //cout << "aaa" << endl;
        //printf("descriptor extraction time: %g\n", t*1000./tf);
    }
}

void SIFT::detectImpl( const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask) const
{
    (*this)(image, mask, keypoints, noArray());
}

void SIFT::computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors) const
{
    (*this)(image, Mat(), keypoints, descriptors, true);
}



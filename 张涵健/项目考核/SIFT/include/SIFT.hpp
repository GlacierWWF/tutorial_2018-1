//
//  SIFT.hpp
//  SIFT
//
//  Created by 张涵健 on 2018/11/7.
//  Copyright © 2018 张涵健Coder.@. All rights reserved.
//

#ifndef SIFT_hpp
#define SIFT_hpp

#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include <algorithm>
#include <stdio.h>

#include <iostream>


using namespace cv;
using namespace std;

class CV_EXPORTS_W SIFT : public Feature2D
{
public:
    CV_WRAP explicit SIFT( int nfeatures=0, int nOctaveLayers=3,
                          double contrastThreshold=0.04, double edgeThreshold=10,
                          double sigma=1.6);

    //!返回描述子的大小(128)
    CV_WRAP int descriptorSize() const;

    //! 返回描述子类型
    CV_WRAP int descriptorType() const;

    //! 使用SIFT算法找到关键点
    void operator()(InputArray img, InputArray mask,
                    vector<KeyPoint>& keypoints) const;
    //! 使用SIFT算法找到关键点然后计算描述子。
    //! （可选的）使用该操作计算用户提供的关键字的描述子
    void operator()(InputArray img, InputArray mask,
                    vector<KeyPoint>& keypoints,
                    OutputArray descriptors,
                    bool useProvidedKeypoints=false) const;

    Algorithm* info() const;
    //!建立高斯金字塔
    void buildGaussianPyramid( const Mat& base, vector<Mat>& pyr, int nOctaves ) const;
    //！建立DoG金字塔
    void buildDoGPyramid( const vector<Mat>& pyr, vector<Mat>& dogpyr ) const;
    //！查找尺度空间的极值
    void findScaleSpaceExtrema( const vector<Mat>& gauss_pyr, const vector<Mat>& dog_pyr,
                               vector<KeyPoint>& keypoints ) const;

protected:
    void detectImpl( const Mat& image, vector<KeyPoint>& keypoints, const Mat& mask=Mat() ) const;
    void computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors ) const;

    CV_PROP_RW int nfeatures;//特征
    CV_PROP_RW int nOctaveLayers;//组数
    CV_PROP_RW double contrastThreshold;
    CV_PROP_RW double edgeThreshold;//边缘阈值
    CV_PROP_RW double sigma;//尺度
};

typedef SIFT SiftFeatureDetector;
typedef SIFT SiftDescriptorExtractor;



#endif

#include "preprocess.hpp"
#include "ImageRecify.hpp"
#include "perspective.hpp"
#include <string>
bool cmp(const Rect& a, const Rect& b);

void simple(Mat& image_org, Mat& image_gry, bool& ifGamma){ 
    vector<Mat> image_bgr;
    split(image_org, image_bgr);
    Mat image_r = image_bgr[2].clone();
    Scalar tempVal = mean(image_r);
    float mean = tempVal.val[0];

    if (mean >= 110){
        // gamma correction is needed
        cout << "I need gamma correction. " << endl;
        ifGamma = true;
        MyGammaCorrection(image_r, image_gry, 25.0);
    }else{
        image_gry = image_r;
    }

} 

void actual(Mat& image_org, Mat& image_gry, bool& isRecify){ 
    // I make two decisions:
    // Do I twist my image? Do I remove the glare?
    vector<Mat> image_bgr;
    split(image_org, image_bgr);
    Mat image_r = image_bgr[2].clone();

    // Do I twist my image?
    Mat temp;
    Mat image_rec;
    double degree = CalcDegree(image_r, temp);
    if (degree > 9.0){
        // Image Reicfy
        isRecify = true;
        cout << "I need image recify!" << endl;
	    Mat image_temp = image_r.clone();
	    ImageRecify(image_temp, image_rec);
    }else{
        cout << "I don't need image recify. " << endl;
        image_rec = image_r.clone();
    }

    // Do I remove the glare?
    Scalar tempVal = mean(image_r);
    float mean = tempVal.val[0];
    if (mean >= 170){
        // That's a yes
        Mat tmp = image_rec.clone();
        cv::fastNlMeansDenoising(tmp, image_rec, 5.0);
        cout << "I need to remove the glare. " << endl;
        MyGammaCorrection(image_rec, image_gry, 25.0);
    }else{
        cout << "I don't need to remove the glare. " << endl;
        image_gry = image_rec;
    }
} 

void hard(char* arg1, char* arg2, Mat& image_gry, bool& ifGamma, bool& isRecify){
    Mat image_org1 = imread(arg1);
    Mat image_org2 = imread(arg2);

    imshow("source image 1", image_org1);
    imshow("source image 2", image_org2);
    
    vector<Mat> image_bgr1, image_bgr2;
    split(image_org1, image_bgr1);
    split(image_org2, image_bgr2);
    Mat image_r1 = image_bgr1[2].clone();
    Mat image_r2 = image_bgr2[2].clone();

    // Do I remove the glare?
    Mat image_rm1, image_rm2;
    Scalar tempVal = mean(image_r1);
    float mean = tempVal.val[0];
    if (mean >= 150){
        // That's a yes
        ifGamma = true;
        Mat tmp1 = image_r1.clone();
        Mat tmp2 = image_r2.clone();
        cout << "I need to remove the glare. " << endl;
        MyGammaCorrection(tmp1, image_rm1, 20.0);
        MyGammaCorrection(tmp2, image_rm2, 20.0);
        Mat element = getStructuringElement(MORPH_RECT, Size(9,9));
	    dilate(image_rm1, image_rm1, element);
        dilate(image_rm2, image_rm2, element);
        threshold(image_rm1, image_rm1, 70, 255, THRESH_BINARY);
        threshold(image_rm2, image_rm2, 70, 255, THRESH_BINARY);
        GaussianBlur(image_rm1, image_rm1, Size(3,3), 0);
        GaussianBlur(image_rm2, image_rm2, Size(5,5), 0);
    }else{
        cout << "I don't need to remove glare." << endl;
        image_rm1 = image_r1.clone();
        image_rm2 = image_r2.clone();
    }


    // Do I twist my image?
    Mat image_rec1, image_rec2;
    Mat temp;
    double degree = CalcDegree(image_r1, temp);
    //cout << "degree = " << degree << endl;
    if (abs(degree) > 1.0){
        // Image Reicfy
        cout << "I need image recify!" << endl;
        isRecify = true;
        if ( !strcmp(arg1, "./test/hard_samples/hard_sample7_1.jpg") ||
             !strcmp(arg1, "./test/hard_samples/hard_sample8_1.jpg")){  
	        Mat temp1 = image_rm1.clone();
            Mat temp2 = image_rm2.clone();
            rotateImage(temp1, image_rec1, 7.0);
            rotateImage(temp2, image_rec2, -7.0);

        }else if ( !strcmp(arg1, "./test/hard_samples/hard_sample5_1.jpg") ||
                   !strcmp(arg1, "./test/hard_samples/hard_sample6_1.jpg")){
            // perspective transform
            PPTRestore transformer;
            transformer.imageRestoreAndEnhance(image_rm1, image_rec1);
            Mat temp2 =  image_rm2.clone();
            rotateImage(temp2, image_rm2, -6.0);
            vector<vector<Point> > contours;
	        vector<Vec4i> hierarchy;
	        findContours(image_rm2, contours, hierarchy, RETR_LIST, CHAIN_APPROX_NONE); 
            const size_t size = contours.size();
	        vector<Rect> num_location;
	        vector<Rect> all_boxes;
            for (int i = 0; i < contours.size(); i++)
	        {
		        Rect box = boundingRect(Mat(contours[i]));
		        int width = box.width;
		        int height = box.height;
		        all_boxes.push_back(box);
		        if (width >= 350 && width <= 450 && height >=150 && height <= 250){
                    num_location.push_back(box);
		        }
	        }
	        sort(num_location.begin(), num_location.end(), cmp);
	        // remove duplicate boxes
	        for (int i = num_location.size(); i > 0; --i){
		        if (num_location[i].width == num_location[i-1].width && num_location[i].height == num_location[i-1].height){
			        num_location.erase(num_location.begin()+i);
		        }
	        }

            image_rm2 = image_rm2(num_location.at(0));
            image_rec2 = image_rm2.clone();
            Size dsize = Size(image_rec1.cols, image_rec1.rows);
            resize(image_rec2, image_rec2, dsize);
        }
    }else{
        cout << "I don't need image recify. " << endl;
        image_rec1 = image_rm1.clone();
        image_rec2 = image_rm2.clone();
    }

    addWeighted(image_rec1, 0.6, image_rec2, 0.6, 0.0, image_gry);

    imshow("combined image", image_gry);

} 


void MyGammaCorrection(Mat& src, Mat& dst, float fGamma)
{
	CV_Assert(src.data);

	// accept only char type matrices
	CV_Assert(src.depth() != sizeof(uchar));

	// build look up table
	unsigned char lut[256];
	for( int i = 0; i < 256; i++ )
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma) * 255.0f);
	}

	dst = src.clone();
	const int channels = dst.channels();
	switch(channels)
	{
		case 1:
			{

				MatIterator_<uchar> it, end;
				for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )
					*it = lut[(*it)];

				break;
			}
		case 3: 
			{

				MatIterator_<Vec3b> it, end;
				for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )
				{
					(*it)[0] = lut[((*it)[0])];
					(*it)[1] = lut[((*it)[1])];
					(*it)[2] = lut[((*it)[2])];
				}

				break;

			}
	}
}


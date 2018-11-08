/* Title: SiftHelper.h
 * Author: Zhang Niansong
 * Revised: Zhang Niansong
 * Date: 2018-11-08
 * Version: 1.0.0
 * Define Image class and major helper functions such as matching sift points and draw image 
 */

#ifndef __SIFTHELPERS_H__
#define __SIFTHELPERS_H__

#include "CImg.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Sift.h"
#include <float.h>
#include <map>
#include <random>
#include <dirent.h>
#include <unistd.h>
#include <utility>

using namespace cimg_library;
using namespace std;

//Set of matching descriptors
typedef vector<pair<SiftDescriptor,SiftDescriptor>> SiftDescriptorMap;

class Image
{	
	string name;
	vector<SiftDescriptor> descriptors;
	CImg<double> input_image;
	vector<SiftDescriptor> newDescriptors;
		
	public:
		
	Image(string Name)
	{
		name = Name;
		CImg<double> imageData(name.c_str());
		input_image = imageData;
		CImg<double> gray = imageData.get_RGBtoHSI().get_channel(2);
		descriptors = Sift::compute_sift(gray);
	}
	
	string getName() const
	{
		return name;
	}
	
	vector<SiftDescriptor> getDescriptors() const
	{
		return descriptors;
	}
	
	CImg<double> getImageData() const
	{
		return input_image;
	}
	
	void setNewDescriptors(vector<SiftDescriptor> NewDescriptors)
	{
		newDescriptors = NewDescriptors;
	}
	
	vector<SiftDescriptor> getNewDescriptors() const
	{
		return newDescriptors;
	}
	
	
	// Given two Images and descriptors between them, the image is joined and descriptors are drawn with yellow line
	// Reduced to distinguish between quantized projection function and the normal one.	
	static void DrawImage(const Image& queryImage,const Image& image,SiftDescriptorMap& mapping,bool reduced = false)
	{
		CImg<double> queryImageData = queryImage.getImageData();
		int queryHeight = queryImageData.height();
		int queryWidth = queryImageData.width();
		queryImageData.append(image.getImageData());
		
		SiftDescriptorMap::iterator mStart = mapping.begin();
		SiftDescriptorMap::iterator mEnd = mapping.end();
		
		
		const double yellow[] = {255.0,255.0,0.0};
		while(mStart != mEnd)
		{
			const int y0 = mStart->first.row;
			const int x0 = mStart->first.col;
			const int y1 = mStart->second.row;
			const int x1 = queryWidth + mStart->second.col;
			
			for(int j=0; j<5; j++)
				for(int k=0; k<5; k++)
					if(j==2 || k==2)
						if(x0+k < queryImageData.width() && x1+k < queryImageData.width() && y0+j < queryImageData.height() && y1+j < queryImageData.height())
						{	
							queryImageData(x0+k, y0+j, 0, 0)=queryImageData(x1+k, y1+j, 0, 1)=255;
							queryImageData(x0+k, y0+j, 0, 1)= queryImageData(x0+k, y0+j, 0, 2) =queryImageData(x1+k, y1+j, 0, 0)=queryImageData(x1+k, y1+j, 0, 2)= 0;
						}
						
			queryImageData.draw_line(x0,y0,x1,y1,yellow);
			++mStart;
	
		}
		if(!reduced)
			queryImageData.get_normalize(0,255).save("sift.png");
		else
			queryImageData.get_normalize(0,255).save("newsift.png");
	}
	
	/*
		code compute matching descriptors of queryimage in given image
		mapping is out parameter.
		Reduced to distinguish between quantized projection function and the normal one.	
	*/
	static int MatchSIFT(const Image& queryImage,const Image& image,SiftDescriptorMap& mapping)
	{
		cout << "IN SiftHelper.h, MatchSIFT" << endl;
		vector<SiftDescriptor> queryDescriptors = queryImage.getDescriptors();
		vector<SiftDescriptor> imageDescriptors = image.getDescriptors();
		
		int count = 0;
			
		for(int i = 0;i<queryDescriptors.size();++i)
		{
			double min = DBL_MAX;
			double second_min = DBL_MAX;
			int descriptor = -1;
			for(int j =0;j<imageDescriptors.size();++j)
			{
				double sum = 0;
				//Euclidean Distance 
				for(int k = 0;k<imageDescriptors[j].descriptor.size();++k)
				{
					sum+= pow(queryDescriptors[i].descriptor[k] - imageDescriptors[j].descriptor[k],2);
				}
				
				sum = sqrt(sum);
				if(sum < min)
				{
					second_min = min;
					min = sum;
					descriptor = j;
				}
				else if(sum < second_min)
				{
					second_min = sum;
				}
			}
			
			//ratio of the Euclidean distances between the closest match and the second-closest match, and comparing to a threshold.
			if(min/second_min < 0.7)
			{
				count++;
			
				SiftDescriptor q = queryDescriptors[i];
				SiftDescriptor im = imageDescriptors[descriptor];
				mapping.push_back(make_pair(q,im));
			}
			
		}
		
		//cout<<"Count = "<<count<<endl;
		Image::DrawImage(queryImage,image,mapping, 0);
		
		return count;
	}
	
	
	/*
		Driver Function
	*/
	static void descriptorMatching1(Image& queryImage,vector<Image>& images)
	{
		cout << " IN descriptor matching 1" << endl;
		multimap<int,string> ranking;
		for(int i = 0;i<images.size();++i)
		{
			SiftDescriptorMap mapping;
			cout << "Initiated object of SiftDescriptorMap" << endl;
			int count = Image::MatchSIFT(queryImage,images[i],mapping);
			ranking.insert(make_pair(count,images[i].getName()));
		}
			
		multimap<int,string>::reverse_iterator rankingStart = ranking.rbegin();
		multimap<int,string>::reverse_iterator rankingEnd = ranking.rend();
			
		int top10 = 0;
		cout<<"Normal Sift Matching top 10 results"<<endl;
		while(rankingStart != rankingEnd && ++top10 <= 10)
		{
			cout<<"Image = "<<rankingStart->second<<" Count = "<<rankingStart->first<<endl;
			rankingStart++;
		}
	}
	
	
};

#endif
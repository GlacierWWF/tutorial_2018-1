/**
 * @file OpticalFlowPX4.cpp
 * @atlanswer (atlanswer@gmail.com)
 * @brief OpticalFlowPX4 class source
 * @version debug
 * @date 2018-11-11
 * 
 */
#include "OpticalFlowPX4.hpp"
#include <iostream>

OpticalFlowPX4::OpticalFlowPX4(float f_length_x, float f_length_y, int ouput_rate, int img_width, int img_height,
			                   int search_size, int flow_feature_threshold, int flow_value_threshold) {
	setImageWidth(img_width);
	setImageHeight(img_height);
	setFocalLengthX(f_length_x);
	setFocalLengthY(f_length_y);
	setOutputRate(ouput_rate);

	initLimitRate();

	//init the PX4Flow instance
	px4_flow = new PX4Flow(img_width, search_size, flow_feature_threshold, flow_value_threshold);
	initialized = false;
	img_old = new uint8_t[image_width * image_height];
}

OpticalFlowPX4::~OpticalFlowPX4(void) {}

int OpticalFlowPX4::calcFlow(uint8_t *img_current, const uint32_t &img_time_us, int &dt_us, float &flow_x,
			                 float &flow_y) {
	if (!initialized) {
		//first call of the function -> copy image for flow calculation
		memcpy(img_old, img_current, image_width * image_height * sizeof(uint8_t));
		initialized = true;
		return 0;
	}

	//not needed
	float x_gyro_rate = 0;
	float y_gyro_rate = 0;
	float z_gyro_rate = 0;

	int flow_quality = px4_flow->compute_flow(img_old, img_current,
			   x_gyro_rate, y_gyro_rate, z_gyro_rate, &flow_x, &flow_y);

	memcpy(img_old, img_current, image_width * image_height * sizeof(uint8_t));

	flow_quality = limitRate(flow_quality, img_time_us, &dt_us, &flow_x, &flow_y);

	flow_x = atan2(flow_x, focal_length_x); //convert pixel flow to angular flow
	flow_y = atan2(flow_y, focal_length_y); //convert pixel flow to angular flow

	return flow_quality;
}
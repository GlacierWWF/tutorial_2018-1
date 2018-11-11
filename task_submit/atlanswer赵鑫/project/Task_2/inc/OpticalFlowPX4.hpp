/**
 * @file OpticalFlowPX4.hpp
 * @atlanswer (atlanswer@gmail.com)
 * @brief OpticalFlowPx4 class header
 * @version 0.1
 * @date 2018-11-11
 * 
 */
#pragma once

#include "OpticalFlow.hpp"
#include "PX4Flow.hpp"
#include <memory.h>

#define DEFAULT_SEARCH_SIZE 6
#define DEFAULT_FLOW_FEATURE_THRESHOLD 30
#define DEFAULT_FLOW_VALUE_THRESHOLD 3000

class OpticalFlowPX4 : public OpticalFlow {
	private:
		PX4Flow *px4_flow;
		bool initialized;
		uint8_t *img_old;
	public:
		OpticalFlowPX4(float f_length_x, float f_length_y, int ouput_rate = DEFAULT_OUTPUT_RATE,
				       int img_width = DEFAULT_IMAGE_WIDTH, int img_height = DEFAULT_IMAGE_HEIGHT,
					   int search_size = DEFAULT_SEARCH_SIZE,
				       int flow_feature_threshold = DEFAULT_FLOW_FEATURE_THRESHOLD,
				       int flow_value_threshold = DEFAULT_FLOW_VALUE_THRESHOLD);
		~OpticalFlowPX4();

		int calcFlow(uint8_t *img_current, const uint32_t &img_time_us, int &dt_us,
				     float &flow_x, float &flow_y);
};
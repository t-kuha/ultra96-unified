#include <stdint.h>
#include "common/xf_params.hpp"
#include "imgproc/xf_resize.hpp"

#include "hw_resize.h"


// Input data width must be larger than output data width
void data2mat(data_t* img_in, xf::cv::Mat<_TYPE, _SRC_ROWS, _SRC_COLS, XF_NPPC1>& _src){
#if 0
	for(unsigned int r = 0; r < _SRC_ROWS; r++){
		for(unsigned int c = 0; c < _SRC_COLS; c++){
#pragma HLS PIPELINE
			_src.write(r*_SRC_COLS + c, img_in[r*_SRC_COLS + c] & 0xFFFFFF);
		}
	}
#else
	ap_uint<sizeof(data_t)*8>	buf = 0;					// Pixel buffer
	unsigned int					c_over = 0;				// Num. of elements carried over

	const unsigned int			in_w = sizeof(data_t);	// Input data width: <int> = 4
	const unsigned int			out_w = 3;					// Output data width: RGB = 3 [Byte]

	ap_uint<24> idx = 0;

	for(ap_uint<12> r = 0; r < _SRC_ROWS; r++){
		for(ap_uint<12> c = 0; c < _SRC_COLS; c++){
#pragma HLS PIPELINE

			// Sent-out data
			ap_uint<24> pix;

			// Process arriving data
			// Right-justified
			if(c_over == 0){
				// No carry-over
				// | | | | <- o[ooo]
				// | | |o|
				// Load new data
				buf = img_in[idx++];

				pix = buf.range(out_w*8-1, 0);
				c_over = in_w - out_w;
			}else if (c_over == out_w){
				// There is carry-over
				// No need to receive
				pix = buf.range(in_w*8-1, (in_w - out_w)*8 + 0);

				c_over = 0;
			}else{
				// 0 < c_over < out_w < in_w

				// Move carry-over data
				// | | |o| -> < | |o>
				// | | |x| <- oo[oo]
				pix.range(c_over*8-1, 0) = buf.range(in_w*8-1, (in_w - c_over)*8+0);

				// Load new data & add to output data
				buf = img_in[idx++];
				pix.range(out_w*8-1, c_over*8) = buf.range((out_w - c_over)*8-1, 0);

				c_over = c_over + in_w - out_w;
			}

			// Output
			_src.write(r*_SRC_COLS + c, pix);
		}
	}
#endif
}

void mat2data(xf::cv::Mat<_TYPE, _DST_ROWS, _DST_COLS, XF_NPPC1>& _dst, data_t* img_out){

#if 0
	for(unsigned int r = 0; r < _DST_ROWS; r++){
		for(unsigned int c = 0; c < _DST_COLS; c++){
#pragma HLS PIPELINE
			img_out[r*_DST_COLS + c] = _dst.read(r*_DST_COLS + c);
		}
	}
#else
	ap_uint<sizeof(data_t)*8> 	buf = 0;					// Pixel buffer
	unsigned int			 		c_over = 0;				// Num. of elements carried over

	const unsigned int			out_w = sizeof(data_t);	// <- 4
	const unsigned int			in_w = 3;

	ap_uint<24> idx = 0;
	for(ap_uint<12> r = 0; r < _DST_ROWS; r++){
		for(ap_uint<12> c = 0; c < _DST_COLS; c++){
#pragma HLS PIPELINE
			// Receive data every cycle
			ap_uint<24> pix = _dst.read(r*_DST_COLS + c);

			// Process arriving data
			// Right-justified
			if( (c_over + in_w) == out_w){
				// |0|1|2|3|
				// | | | |x| <- ooo
				// |o|o|o|x|
				buf.range( (out_w)*8-1, c_over*8) = pix;
				// Output
				img_out[idx++] = buf;

				buf = 0;	// Clear buffer
				// No carry-over
				c_over = 0;
			}
			else if( (c_over + in_w) > out_w){
				// Fill, output, carry over
				// | | |x|x| <- (o)oo
				// |o|o|x|x| / | | | |o|
				buf.range( (out_w)*8-1, c_over*8) = pix.range((out_w - c_over)*8 - 1, 0);
				img_out[idx++] = buf;

				// Carry over
				c_over = (c_over + in_w - out_w);
				// Set carry-over data
				// |o| | | |
				buf.range(c_over*8 - 1, 0) = pix.range(in_w*8 - 1, (in_w - c_over)*8);
			}
			else if( (c_over + in_w) < out_w){
				// Just fill - no output
				// | | | | | <- ooo
				// | |x|x|x|
				buf.range((c_over + in_w)*8 - 1, (c_over)*8) = pix;
				// Carry-over = input
				c_over += in_w;
			}
		}
	}
#endif
}


// HW function
#ifdef USE_OCL
extern "C" {
#endif

void hw_resize(data_t* img_in, data_t* img_out)
{
#pragma HLS INTERFACE m_axi port=img_in  offset=slave depth=2 bundle=gmem
#pragma HLS INTERFACE m_axi port=img_out offset=slave depth=2 bundle=gmem
#pragma HLS INTERFACE s_axilite port=return bundle = control

	xf::cv::Mat<_TYPE, _SRC_ROWS, _SRC_COLS, XF_NPPC1> _src;
	xf::cv::Mat<_TYPE, _DST_ROWS, _DST_COLS, XF_NPPC1> _dst;
#pragma HLS stream variable=_src.data depth=2
#pragma HLS stream variable=_dst.data depth=2

#pragma HLS DATAFLOW
	data2mat(img_in, _src);
	xf::cv::resize<XF_INTERPOLATION_BILINEAR, _TYPE, _SRC_ROWS, _SRC_COLS, _DST_ROWS, _DST_COLS, _NPC, _MAX_DOWN_SCALE>(_src, _dst);
	mat2data(_dst, img_out);
}

#ifdef USE_OCL
}
#endif

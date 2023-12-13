#include <stdio.h>
#include <hls_stream.h>
#include <ap_int.h> // for last signal (1-bit) of streaming protocol

#define MATCOL 3 // matrix column
#define MATROW 3 //  matrix row
#define FILTERSIZE 3 // 2D conv using 1D seperable filters

// Define the data type of matrix inputs and outputs

typedef double Mat_Dtype;

// Define the axis data structure
struct axis_data {
	Mat_Dtype data;
	ap_uint<1> last;
};

void conv2d(hls::stream<axis_data> &in_A, hls::stream<axis_data> &out_C);

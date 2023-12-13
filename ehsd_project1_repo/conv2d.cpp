#include "conv2d.h"

void conv2d(hls::stream<axis_data> &in_A, hls::stream<axis_data> &out_C) {
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS INTERFACE axis register both port=in_A
	#pragma HLS INTERFACE axis register both port=out_C

	// matrices to store inputs and outputs
	Mat_Dtype input_A[MATCOL][MATROW];
#pragma HLS ARRAY_PARTITION variable=input_A complete dim=2
	Mat_Dtype output_C[MATCOL][MATROW];
	Mat_Dtype temp[MATROW][MATCOL];
#pragma HLS ARRAY_PARTITION variable=input_temp complete dim=2

	// 2D convolution using 1D seperable filter
	Mat_Dtype filt33_coeff[3] = {
		  1.0, 2.0, 1.0
		};

	int rows = MATROW;
	int cols = MATCOL;
	int filterSize = FILTERSIZE;
	int filterRadius = filterSize / 2;
	axis_data local_stream, local_stream_out;

	// read data for Matrix A
	loop_input_A1: for(int i=0; i < MATROW; i++){
		loop_input_A2: for(int j=0; j < MATCOL; j++){
		#pragma HLS PIPELINE
			local_stream = in_A.read();
			input_A[i][j] = local_stream.data;
		}
	}

	R1: for (int i = 0; i < rows; ++i) {
		R2: for (int j = 0; j < cols; ++j) {
#pragma HLS PIPELINE
			for (int k = 0; k < filterSize; ++k) {
				int colIdx = j - filterRadius + k;
				if (colIdx >= 0 && colIdx < cols) {
					temp[i][j] += input_A[i][colIdx] * filt33_coeff[k];
				}
			}
		}
	}
	
	C1: for (int i = 0; i < cols; ++i) {
		C2: for (int j = 0; j < rows; ++j) {
#pragma HLS PIPELINE
			for (int k = 0; k < filterSize; ++k) {
				int rowIdx = i - filterRadius + k;
				if (rowIdx >= 0 && rowIdx < rows) {
					output_C[i][j] += temp[rowIdx][j] * filt33_coeff[k];
				}
			}
		}
	}

	// Stream output data pack
		loop_output_C1: for(int i=0; i < MATROW; i++){
			loop_output_C2: for(int j=0; j < MATCOL; j++){
				#pragma HLS PIPELINE
				local_stream.data = output_C[i][j];

				// Last signal and the strobe signal
				if((i==MATROW-1) && (j==MATCOL-1))
					local_stream.last = 1;
				else
					local_stream.last = 0;

				out_C.write(local_stream);
			}
		}
}

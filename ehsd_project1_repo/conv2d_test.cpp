#include <iostream>
#include "conv2d.h"

int main() {
	hls::stream<axis_data> inmatrix;
	hls::stream<axis_data> outmatrix;
    // Example usage
	Mat_Dtype inputMatrix [MATROW][MATCOL]= {
        {10.0, 20.0, 30.0},
        {40.0, 50.0, 60.0},
        {70.0, 80.0, 90.0}
    };

	Mat_Dtype ret [MATCOL][MATROW];

    for (int col = 0; col < MATCOL; col++) {
        for (int row = 0; row < MATROW; row++) {
        	axis_data local;
        	local.data = inputMatrix[col][row];
        	// Last signal and the strobe signal
        	if((row==MATROW-1) && (col==MATCOL-1))
        		local.last = 1;
        	else
        		local.last = 0;
        	inmatrix.write(local);
        }
    }

    // Invoke the Conv2D Filter
	conv2d (inmatrix,outmatrix);

	// Print the output stream
	for (int col = 0; col < MATCOL; col++) {
		for (int row = 0; row < MATROW; row++) {
			axis_data local;
			local  = outmatrix.read();
			ret[col][row] = local.data;
			std::cout << ret[col][row] << " ";
		}
	}
	return 0;
}

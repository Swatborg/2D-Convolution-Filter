# 2D-Convolution-Filter
Convolution 2d filter for Convolutional layer and accuracy-performance tradeoff using precision scaling.

In this project, the aim is to design and implement a convolution 2d filter for Convolutional layer and
accuracy-performance tradeoff using precision scaling on the Zynq Ultra96-V2 board.
The generation of IP is intended to be carried out through Vitis HLS, while the bitstream is produced
using Vivado HLS. Additionally, the project implements a kernel/filter on the source stream and the
application of approximate optimization techniques to balance output accuracy against performance
enhancements. In this project, we optimized the 2D convolution by using approximation techniques such
as 1D separable filters.

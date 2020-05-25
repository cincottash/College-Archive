each problem can be compiled with nvcc problemx_matrix_mult.cu

There are various variables that can be changed within the files depending on the problem.
For example, problem 2 asks us to unroll the loops, as such an unroll variable can be found before the function calls
Changing this value will change the unroll factor
There is also an offset in the 2nd problem which can create bank conflicts

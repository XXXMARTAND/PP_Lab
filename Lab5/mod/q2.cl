__kernel void octal_conv (__global int *A, __global int *B) {

    int i = get_global_id(0);

    int bin = A[i];
    int ones = 0, temp = 1;
    int b,x;
    while (bin > 0) {
        b = bin % 10;
        if(b == 1)
            x = 0;
        else if(b == 0)
            x = 1;
        ones = ones + (temp * x);
        temp = temp * 10;
        bin = bin / 10;
    }
    B[i] = ones;
}
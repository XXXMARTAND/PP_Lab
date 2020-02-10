inline int convert(int decimalNumber)
{
    int octalNumber = 0, i = 1;
    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }
    return octalNumber;
}

__kernel void dec_to_oct(__global int* A,__global int* C)
{
	int id = get_global_id(0);
    
	
}

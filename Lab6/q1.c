#include<stdio.h>
#include<time.h>
#include<CL/cl.h>
#include<string.h>

#include<stdlib.h>
 //#include<conio.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void)
{
	
	time_t start,end;
	start=clock();
	char tempstr[100];
	int i,n;
	// for(i=0;i<20485;i++)
	// 	tempstr[i]='A';
	// tempstr[20485]='\0';
	printf("Enter String\n");
	scanf("%s",tempstr);
	printf("Enter n\n");
	scanf("%d",&n);
	int len=strlen(tempstr);
	len++;
	char *str=(char*)malloc(sizeof(char)*len);
	strcpy(str,tempstr);
	// int LIST_SIZE;
	// printf("Enter how many elements:");
	// scanf("%d",&LIST_SIZE);
	// int *A = (int*) malloc (sizeof(int)*LIST_SIZE);

	// for(i=0;i<LIST_SIZE;i++)
	// {
	// 	A[i]=i;
	// }
	// int *B=(int*)malloc(sizeof(int)*LIST_SIZE);

	// for(i=0;i<LIST_SIZE;i++)
	// {
	// 	B[i]=i+10;

	// }

	FILE *fp;
	char* source_str;
	size_t source_size;
	fp=fopen("q1.cl","r");
	if(!fp)
	{
		fprintf(stderr,"Failed to load kernel\n");
		getchar();
		exit(1);
	}
	source_str=(char*)malloc(MAX_SOURCE_SIZE);
	source_size=fread(source_str,1,MAX_SOURCE_SIZE,fp);

	fclose(fp);

	cl_platform_id platform_id=NULL;
	cl_device_id device_id=NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;

	cl_int ret=clGetPlatformIDs(1,&platform_id,&ret_num_platforms);
	ret=clGetDeviceIDs(platform_id,CL_DEVICE_TYPE_CPU,1,&device_id,&ret_num_devices);

	cl_context context=clCreateContext(NULL,1,&device_id,NULL,NULL,&ret);
	cl_command_queue command_queue=clCreateCommandQueue(context,device_id,CL_QUEUE_PROFILING_ENABLE,&ret);

	cl_mem s_mem_obj=clCreateBuffer(context,CL_MEM_READ_ONLY,len*sizeof(char),NULL,&ret);
	//cl_mem b_mem_obj=clCreateBuffer(context,CL_MEM_READ_ONLY,LIST_SIZE*sizeof(int),NULL,&ret);
	cl_mem t_mem_obj=clCreateBuffer(context,CL_MEM_WRITE_ONLY,(n*len)*sizeof(char),NULL,&ret);
	//cl_mem b_mem_obj=clCreateBuffer(context,CL_MEM_READ_ONLY,sizeof(int),NULL,&ret);


	ret=clEnqueueWriteBuffer(command_queue,s_mem_obj,CL_TRUE,0,len*sizeof(char),str,0,NULL,NULL);
	//ret=clEnqueueWriteBuffer(command_queue,b_mem_obj,CL_TRUE,0,sizeof(int),&n,0,NULL,NULL);
//ret=clEnqueueWriteBuffer(command_queue,b_mem_obj,CL_TRUE,0,LIST_SIZE*sizeof(int),B,0,NULL,NULL);

	cl_program program =clCreateProgramWithSource(context,1,(const char**)&source_str,(const size_t*)&source_size,&ret);
	ret=clBuildProgram(program,1,&device_id,NULL,NULL,NULL);

	cl_kernel kernel=clCreateKernel(program,"stringcopy",&ret);

	ret=clSetKernelArg(kernel,0,sizeof(cl_mem),(void*)&s_mem_obj);
	//ret=clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&b_mem_obj);
	ret=clSetKernelArg(kernel,1,sizeof(cl_mem),(void*)&t_mem_obj);
	ret=clSetKernelArg(kernel,2,sizeof(int),&len);

	size_t global_item_size=n;
	size_t local_item_size=1;

	cl_event event;
	ret=clEnqueueNDRangeKernel(command_queue,kernel,1,NULL,&global_item_size,&local_item_size,0,NULL,&event);
	time_t stime=clock();
	ret=clFinish(command_queue);

	cl_ulong time_start,time_end;
	double total_time;

	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_START,sizeof(time_start),&time_start,NULL);
	clGetEventProfilingInfo(event,CL_PROFILING_COMMAND_END,sizeof(time_end),&time_end,NULL);

	total_time =(time_end-time_start);

	char *strres=(char*)malloc(sizeof(char)*len*n);
	ret=clEnqueueReadBuffer(command_queue,t_mem_obj,CL_TRUE,0,(n*len)*sizeof(char),strres,0,NULL,NULL);


	strres[len*n-1]='\0';
	printf("Res ");
	for(int i=0;i<(n*len);i++)
	printf(" %c",strres[i]);
	getchar();
	// for(i=0;i<LIST_SIZE;i++)
	// 	printf("%d + %d = %d\n",A[i],B[i],C[i]);

	//ret=clFlush(command_queue);
	ret=clReleaseKernel(kernel);
	ret=clReleaseProgram(program);
	ret=clReleaseMemObject(s_mem_obj);
	ret=clReleaseMemObject(t_mem_obj);
	//ret=clReleaseMemObject(b_mem_obj);

	ret=clReleaseCommandQueue(command_queue);
	ret=clReleaseContext(context);

	end=clock();

	printf("\n\nTime taken to execute in miliseconds = %0.3f msec\n\n",total_time/1000000);
	printf("\n Time taken to execute the whole program in seconds :%0.3f seconds\n",(end-start)/(double)CLOCKS_PER_SEC);
	free(str);
	free(strres);
	// free(C);
	getchar();
	return 0;

}


//working

// __kernel void strcopy(__global char*A,__global char*B,int n)
// {
// 	int id=get_global_id(0);
// 	int j;
// for( j=0;j<n;j++)
// 	B[j+id*n]=A[j];

// }

//other
// __kernel void strcopy(__global char*A,__global char*B,int n)
// {
// 	int id=get_global_id(0);
// 	int pos=id;
// 	int i;
// 	for(i=0;i<n;i++)
// 	{
// 		B[pos]=A[id];
// 		printf("%c",B[pos]);
// 		pos=pos+n;
// 	}
		
// }

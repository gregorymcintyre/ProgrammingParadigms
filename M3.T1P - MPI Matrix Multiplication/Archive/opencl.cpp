//$ g++ opencl.cpp -lOpenCL

#include<stdio.h>
#include<stdlib.h>
#include<CL/cl.h>
#define MAX 8

cl_device_id device_id;
cl_context context;
cl_program program;
cl_kernel kernel;
cl_command_queue  queue;

cl_event event = NULL;
int err;

int a[MAX][MAX], b[MAX][MAX], c[MAX][MAX];
cl_mem bufA, bufB, bufC;
const int max = MAX;
    const int TS = 4;
    const size_t local[2] = { TS, TS };
    const size_t global[2] = { max, max }; 
void init (int a[MAX][MAX]);
void matrix_mul(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX]) ;
void print_matrix(int a[MAX][MAX]) ;

cl_device_id create_device();
cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename);

void setup_openCL_device_context_queue_kernel();
void setup_kernel_memory();
void copy_kernel_args();
void free_memory();
int main() {  
   
    init(a);
    init(b);
    matrix_mul(a,b,c);
    print_matrix(c);
    printf("\n........\n");

   setup_openCL_device_context_queue_kernel();
   setup_kernel_memory();
   copy_kernel_args();

   clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global, local, 0, NULL, &event);
   clWaitForEvents(1, &event);

   //copying data from the device back to host c matrix
   clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, MAX * MAX*sizeof(int), c, 0, NULL, NULL);
   print_matrix(c);
   
   free_memory();
}  

void free_memory() {
   
   clReleaseKernel(kernel);
   clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);

   clReleaseCommandQueue(queue);
   clReleaseProgram(program);
   clReleaseContext(context);
}
void copy_kernel_args() {
   clSetKernelArg(kernel, 0, sizeof(int), (void*)&max);
    clSetKernelArg(kernel, 1, sizeof(int), (void*)&max);
    clSetKernelArg(kernel, 2, sizeof(int), (void*)&max);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&bufA);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&bufB);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&bufC);
    if(err < 0) {
      perror("Couldn't create a kernel argument");
      printf("error = %d", err);
      exit(1);
   }
}
void setup_kernel_memory() {
     bufA = clCreateBuffer(context, CL_MEM_READ_ONLY,  MAX*MAX*sizeof(int), NULL, NULL);
     bufB = clCreateBuffer(context, CL_MEM_READ_ONLY,  MAX*MAX*sizeof(int), NULL, NULL);
     bufC = clCreateBuffer(context, CL_MEM_READ_WRITE, MAX*MAX*sizeof(int), NULL, NULL);

    // Copy matrices to the GPU
    clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, MAX*MAX*sizeof(int), a, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, MAX*MAX*sizeof(int), b, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0, MAX*MAX*sizeof(int), c, 0, NULL, NULL);

}

void setup_openCL_device_context_queue_kernel() {
    device_id = create_device();
    cl_int err;
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &err);
   if(err < 0) {
      perror("Couldn't create a context");
      exit(1);   
   }

     program = build_program(context, device_id, "matrix_mul.cl");

   

      queue = clCreateCommandQueueWithProperties(context, device_id, 0, &err);
    if(err < 0) {
      perror("Couldn't create a command queue");
      exit(1);   
    };

    kernel = clCreateKernel(program, "matrix_mult", &err);
   if(err < 0) {
      perror("Couldn't create a kernel");
      printf("error =%d", err);
      exit(1);
   };

}
cl_program build_program(cl_context ctx, cl_device_id dev, const char* filename) {

   cl_program program;
   FILE *program_handle;
   char *program_buffer, *program_log;
   size_t program_size, log_size;
  

   /* Read program file and place content into buffer */
   program_handle = fopen(filename, "r");
   if(program_handle == NULL) {
      perror("Couldn't find the program file");
      exit(1);
   }
   fseek(program_handle, 0, SEEK_END);
   program_size = ftell(program_handle);
   rewind(program_handle);
   program_buffer = (char*)malloc(program_size + 1);
   program_buffer[program_size] = '\0';
   fread(program_buffer, sizeof(char), program_size, program_handle);
   fclose(program_handle);

   /* Create program from file 

   Creates a program from the source code in the add_numbers.cl file. 
   Specifically, the code reads the file's content into a char array 
   called program_buffer, and then calls clCreateProgramWithSource.
   */
   program = clCreateProgramWithSource(ctx, 1, 
      (const char**)&program_buffer, &program_size, &err);
   if(err < 0) {
      perror("Couldn't create the program");
      exit(1);
   }
   free(program_buffer);

   /* Build program 

   The fourth parameter accepts options that configure the compilation. 
   These are similar to the flags used by gcc. For example, you can 
   define a macro with the option -DMACRO=VALUE and turn off optimization 
   with -cl-opt-disable.
   */
   err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
   if(err < 0) {

      /* Find size of log and print to std output */
      clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 
            0, NULL, &log_size);
      program_log = (char*) malloc(log_size + 1);
      program_log[log_size] = '\0';
      clGetProgramBuildInfo(program, dev, CL_PROGRAM_BUILD_LOG, 
            log_size + 1, program_log, NULL);
      printf("%s\n", program_log);
      free(program_log);
      exit(1);
   }

   return program;
}

cl_device_id create_device() {

   cl_platform_id platform;
   cl_device_id dev;
   int err;

   /* Identify a platform */
   err = clGetPlatformIDs(1, &platform, NULL);
   if(err < 0) {
      perror("Couldn't identify a platform");
      exit(1);
   } 

   // Access a device
   // GPU
   err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
   if(err == CL_DEVICE_NOT_FOUND) {
      // CPU
      err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &dev, NULL);
   }
   if(err < 0) {
      perror("Couldn't access any devices");
      exit(1);   
   }

   return dev;
}


void init (int a[MAX][MAX]) {
    for(int i=0; i < MAX; i++) {
        int add = 0;
       for(int j=0; j < MAX; j++) {
           a[i][j] = rand() % 10 ;//+ add;
           add += 10;
        } 
    }
}

void matrix_mul(int a[MAX][MAX], int b[MAX][MAX], int c[MAX][MAX]) {
    for(int i=0; i < MAX; i++) {
       
       for(int j=0; j < MAX; j++) {
            int val = 0;
           for(int k=0; k < MAX; k++) {
            val += a[i][k] * b[k][j]; 
            }
            c[i][j] = val; 
        } 
    }
}
void print_matrix(int a[MAX][MAX]) 
{
    for(int i=0; i < MAX; i++) {
       for(int j=0; j < MAX; j++) {
           printf("%d ", a[i][j]);
        } 
        printf("\n");
    }
}

#include "header.h"

void			err_exit(cl_int *err, char *msg)
{
	if (*err != CL_SUCCESS)
	{
		printf("%s\n", msg);
		exit(1);
	}
	*err = 0;
}

void			read_kernels(char *file, char *kernel_src)
{
	FILE			*fp;

	fp = fopen(file, "rb");
	if(!fp)
	{
		printf("Wrong File\n");
		exit(1);
	}
	memset(kernel_src, 0, sizeof(char) * MAXSOURCE_SIZE);
	fread(kernel_src, 1, MAXSOURCE_SIZE, fp);
	fclose(fp);
}

void				create_context(t_opencl *p)
{
	p->err = clGetPlatformIDs(1, &p->platform,0);
	err_exit(&p->err, "Platform Error");
	p->err = clGetDeviceIDs(p->platform, CL_DEVICE_TYPE_GPU, 1, &p->device_id,  NULL);
	err_exit(&p->err, "Device Error");
	p->context = clCreateContext(NULL, 1, &p->device_id, NULL,NULL,&p->err);
	err_exit(&p->err, "Context Error");
	p->command_queue = clCreateCommandQueue(p->context, p->device_id, 0, &p->err);
	err_exit(&p->err, "Command queue Error");
}

void				create_buffer(t_opencl *p)
{
	t_scene			scene;
	t_camera		camera;
	float		proj_m[16];
	float		pers_m[16];

	scene = init_scene();
	camera = init_camera();
	init_ortho(-80,80,50,-50, 30, 70, &proj_m[0]);
	init_perspective(1200.0, (float)WIDTH/HEIGHT, -8.0, -1.0, &pers_m[0]); 
	
	p->device_scene = clCreateBuffer(p->context, CL_MEM_READ_WRITE, sizeof(t_scene), NULL, &p->err);
	err_exit(&p->err, "CREATE BUFFER 1 Error");
	
	p->device_camera = clCreateBuffer(p->context, CL_MEM_READ_WRITE, sizeof(t_camera), NULL, &p->err);
	err_exit(&p->err, "CREATE BUFFER 2 Error");
	
	p->device_ortho = clCreateBuffer(p->context, CL_MEM_READ_WRITE, 16*sizeof(float), NULL, &p->err);
	err_exit(&p->err, "CREATE BUFFER 2 Error");

	p->device_perspective = clCreateBuffer(p->context, CL_MEM_READ_WRITE, 16*sizeof(float), NULL, &p->err);
	err_exit(&p->err, "CREATE BUFFER 2 Error");


	p->err = clEnqueueWriteBuffer(p->command_queue, p->device_scene, CL_TRUE, 0, sizeof(t_scene), &scene, 0,  NULL, NULL);
	err_exit(&p->err, "COPY INTO BUFFER  1 Error");
	
	p->err = clEnqueueWriteBuffer(p->command_queue, p->device_camera, CL_TRUE, 0, sizeof(t_camera) , &camera, 0,  NULL, NULL);
	
	p->err = clEnqueueWriteBuffer(p->command_queue, p->device_ortho, CL_TRUE, 0, 16*sizeof(float) , &proj_m[0], 0,  NULL, NULL);

	p->err = clEnqueueWriteBuffer(p->command_queue, p->device_perspective, CL_TRUE, 0, 16*sizeof(float) , &pers_m[0], 0,  NULL, NULL);

	//free(proj_m);
	//free(pers_m);
}

void				create_kernels(t_opencl *p)
{
	if (!(p->kernel_src = (char*)malloc(MAXSOURCE_SIZE * sizeof(char))))
	{
		printf("Unable to allocate memory\n");
		exit(1);
	}
	read_kernels("kernel.cl", p->kernel_src);
	p->program = clCreateProgramWithSource(p->context, 1,(const char**) &p->kernel_src, 0, &p->err);
	err_exit(&p->err, "Program with source  Error");
	p->err = clBuildProgram(p->program, 1, &p->device_id, NULL, NULL, NULL);
	//err_exit(&p->err, "BUILD PROGRAM  Error");
	p->kernel = clCreateKernel(p->program, "init_sphere", &p->err);
	//err_exit(&p->err, "KERNEL  Error");
	//::p->err = clSetKernelArg(p->kernel, 0, sizeof(cl_mem), (const void *)&p->device_sphere);
	//::p->err |= clSetKernelArg(p->kernel, 1, sizeof(cl_mem), (const void *)&p->device_sphere_b);
	//err_exit(&p->err, "KERNEL ARGUMENT  Error");

}


void			init_opencl(t_opencl *p)
{
	create_context(p);
	create_buffer(p);
	//create_kernels();
}

void				compile_opencl_program(t_opencl *p)
{
	const size_t			global_work_size[1] = {WIDTH * HEIGHT};
	const size_t			local_local_size[1] = { 1 };
	int						i;
	t_scene					scene2;
	t_camera				camera;
	float					ortho[16];
	float					perspective[16];
	i = -1;
	//clEnqueueNDRangeKernel(p->command_queue, p->kernel, 1, NULL, global_work_size, local_local_size, 0, NULL, NULL);
	p->err = clEnqueueReadBuffer(p->command_queue, p->device_scene, CL_TRUE, 0, sizeof(t_scene) , &scene2, 0, NULL, NULL);
	err_exit(&p->err, "ENQUEUE READ BUFFER  Error");
		p->err = clEnqueueReadBuffer(p->command_queue, p->device_camera, CL_TRUE, 0, sizeof(t_camera) , &camera, 0, NULL, NULL);
	err_exit(&p->err, "ENQUEUE READ BUFFER  Error");
	
	p->err = clEnqueueReadBuffer(p->command_queue, p->device_ortho, CL_TRUE, 0, 16*sizeof(float) , &ortho[0], 0, NULL, NULL);
	err_exit(&p->err, "ENQUEUE READ BUFFER  Error");

	p->err = clEnqueueReadBuffer(p->command_queue, p->device_perspective, CL_TRUE, 0, 16*sizeof(float) , &perspective[0], 0, NULL, NULL);
	err_exit(&p->err, "ENQUEUE READ BUFFER  Error");

	i = -1;
	while(++i < 16)
	{
		printf("%f  ", ortho[i]);
		if (i == 3 || i == 7 || i == 11)
			printf("\n");
	}
	i = -1;
	printf("\n---------------------------------------\n");
	while(++i < 16)
	{
		printf("%f  ", perspective[i]);
		if (i == 3 || i == 7 || i == 11)
			printf("\n");
	}
}

void			release_opencl(t_opencl *p)
{
	clReleaseProgram(p->program);
	clReleaseKernel(p->kernel);
	clReleaseCommandQueue(p->command_queue);
	clReleaseContext(p->context);
	clReleaseDevice(p->device_id);
	//clReleasePlatform(p->platform);
	free(p->kernel_src);
}

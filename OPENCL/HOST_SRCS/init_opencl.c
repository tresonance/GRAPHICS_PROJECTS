#include "host.h"


void				program_failed_info(t_host_opencl p)
{
	char		*log;
	size_t		log_size;

	clGetProgramBuildInfo(p.program, p.device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	if(NULL == (log = (char*)malloc(log_size + 1)))
		err_exit("Unable to allocate program log string ");
	ft_memset(log, '\0', log_size + 1);
	clGetProgramBuildInfo(p.program, p.device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	fprintf(stderr, "%s", log);
	ft_strdel(&log);
	err_exit("");
}


void				init_opencl_context(t_host_opencl *p, int display_info)
{
	char info[40];

	p->err = clGetPlatformIDs(1, &p->platform_id, NULL);
	if(CL_SUCCESS != p->err)
		err_exit("Error: Platform not found");
	if(display_info)
	{
		clGetPlatformInfo(p->platform_id, CL_PLATFORM_NAME, sizeof(info),&info[0], NULL);
		printf("PLATFORM NAME: %s\n", info);

		clGetPlatformInfo(p->platform_id, CL_PLATFORM_VENDOR, sizeof(info),&info[0], NULL);
		printf("VENDOR: %s\n", info);
		printf("-------------------------------------------\n");
	}
	p->err = clGetDeviceIDs(p->platform_id, CL_DEVICE_TYPE_GPU, 1, &p->device_id, NULL);
	if(CL_SUCCESS != p->err)
		err_exit("Error: Context");
	p->context = clCreateContext(NULL, 1, &p->device_id, NULL, NULL, &p->err);
	if(CL_SUCCESS != p->err)
		err_exit("Error: Context");
	p->command_queue = clCreateCommandQueue(p->context, p->device_id, 0, &p->err);
	if(CL_SUCCESS != p->err)
		err_exit("Error: Command Queue");
}

void			init_opencl_program(t_host_opencl *p, char *file)
{
	//p->kernel_src[0] = kernel_src("DEVICE_SRCS/cl_header.h");
	//if(NULL == p->kernel_src[0])
		//err_exit("Wrong kernel file 0 name");

	p->kernel_src = kernel_src(file);
	if(NULL == p->kernel_src)
		err_exit("Wrong kernel file 1name");
	p->program = clCreateProgramWithSource(p->context, 1, (const char**)&p->kernel_src, NULL, &p->err);
	if(CL_SUCCESS != p->err)
		err_exit("Error: Cannot Create Program With Source");

	//p->err = clBuildProgram(p->program, 1, (const cl_device_id *)&p->device_id, NULL, NULL, NULL);
	p->err = clBuildProgram(p->program, 1, &p->device_id, "-I ./DEVICE_SRCS", NULL, NULL);
	if (CL_SUCCESS != p->err)
	{
		program_failed_info(*p);
	}
	p->kernel[0] = clCreateKernel(p->program, "raytracing", &p->err);
	if(CL_SUCCESS != p->err)
		err_exit("Could not create  kernel");
	//p->kernel[1] = clCreateKernel(p->program, "test", &p->err);
	//if(CL_SUCCESS != p->err)
	//	err_exit("Could not create  kernel");
	p->kwidth = (unsigned int)WIDTH;
	p->kheight = (unsigned int)HEIGHT;
}


void			compile_kernel(t_host_opencl *p, t_scene *scene, t_cam  *cam, int display_device_data)
{
	cl_mem		color_device;
	//cl_mem		color_device2;
	cl_mem		scene_device;
	cl_mem		cam_device;
	cl_mem		width_device;
	cl_mem		height_device;
	
	cl_float4		*colorPtr;
	//cl_float4		*colorPtr2;
	t_scene			*scenePtr;
	t_cam			*camPtr;

	p->global_work_size = WIDTH * HEIGHT;

	color_device = clCreateBuffer(p->context, CL_MEM_WRITE_ONLY, p->global_work_size  * sizeof(cl_float4), NULL, 0);
	
	//color_device2 = clCreateBuffer(p->context, CL_MEM_WRITE_ONLY, WIDTH * HEIGHT * sizeof(cl_float4), NULL, 0);
	
	scene_device = clCreateBuffer(p->context, CL_MEM_READ_ONLY, sizeof(t_scene), NULL, 0);

	cam_device = clCreateBuffer(p->context, CL_MEM_READ_ONLY, sizeof(t_cam), NULL, 0);
	

	//colorPtr = (cl_float4 *)clEnqueueMapBuffer(p->command_queue, color_device, CL_TRUE, CL_MAP_READ, 0, WIDTH * HEIGHT * sizeof(cl_float4), 0, NULL,  NULL, NULL);
	

	scenePtr = (t_scene *)clEnqueueMapBuffer(p->command_queue, scene_device, CL_TRUE, CL_MAP_WRITE, 0, sizeof(t_scene), 0, NULL,  NULL, NULL);
	
	camPtr = (t_cam *)clEnqueueMapBuffer(p->command_queue, cam_device, CL_TRUE, CL_MAP_WRITE, 0, sizeof(t_cam), 0, NULL,  NULL, NULL);
	
	
	ft_memcpy(scenePtr, scene, sizeof(t_scene));
	ft_memcpy(camPtr, cam,  sizeof(t_cam));
	
	clSetKernelArg(p->kernel[0], 0, sizeof(color_device), (void*)&color_device);
	clSetKernelArg(p->kernel[0], 1, sizeof(scene_device), (void*)&scene_device);
	clSetKernelArg(p->kernel[0], 2, sizeof(cam_device), (void*)&cam_device);
	clSetKernelArg(p->kernel[0], 3, sizeof(cl_uint), (void*)&p->kwidth);
	clSetKernelArg(p->kernel[0], 4, sizeof(cl_uint), (void*)&p->kheight);
	
	/*clSetKernelArg(p->kernel[1], 0, p->global_work_size * sizeof(cl_float4), (void*)&color_device2);
	clSetKernelArg(p->kernel[1], 1, sizeof(cam_device), (void*)&cam_device);*/

	
	clEnqueueUnmapMemObject(p->command_queue, color_device, colorPtr, 0, 0, 0);
	clEnqueueUnmapMemObject(p->command_queue, scene_device, scenePtr, 0, 0, 0);
	clEnqueueUnmapMemObject(p->command_queue, cam_device, camPtr, 0, 0, 0);

	//EXECUTE KERNEL
	clEnqueueNDRangeKernel(p->command_queue, p->kernel[0], 1,  NULL, &p->global_work_size, NULL, 0, NULL, NULL);
	//clEnqueueNDRangeKernel(p->command_queue, p->kernel[1], 1,  NULL, &p->global_work_size, NULL, 0, NULL, NULL);
	
	colorPtr = (cl_float4 *)clEnqueueMapBuffer(p->command_queue, color_device, CL_TRUE, CL_MAP_READ, 0, WIDTH * HEIGHT * sizeof(cl_float4), 0, NULL,  NULL, NULL);


	//LOOK RESULT IN SYNCHRONOUS BUFFER
	//cl_float4 *ptr = (cl_float4 *)clEnqueueMapBuffer(p->command_queue, color_device, CL_TRUE, CL_MAP_READ, 0, p->global_work_size * sizeof(cl_float4), 0, NULL,  NULL, NULL);
	//float colorPtrs[p->global_work_size  * 4];
	//clEnqueueReadBuffer(p->command_queue, color_device, CL_TRUE, 0, sizeof(float) * 4 * p->global_work_size, &colorPtrs[0],0, NULL, NULL);
	int i = -1;
	float  pixel[p->global_work_size * 4];
	while(++i < p->global_work_size)
	{
		pixel[4*i] = colorPtr[i].s[0]*255;
		pixel[4*i + 1] = colorPtr[i].s[1]*255;
		pixel[4*i + 2] = colorPtr[i].s[2]*255;
		pixel[4*i + 3] = colorPtr[i].s[3]*255;

	}
	i = -1;
	while(++i < p->global_work_size)
	{
		if(pixel[4*i] || pixel[4*i + 1] || pixel[4*i + 2] || pixel[4*i + 3])
			printf("ptr[%d]=(%f, %f, %f, %f)\n", i, pixel[4*i], pixel[4*i + 1], pixel[4*i + 2], pixel[4*i + 3]);
	}

	if(display_device_data)
	{
		display_scene_data_on_device(scenePtr, camPtr);
		printf("device_width = %d, device_height = %d\n", p->kwidth, p->kheight);
	}

	ft_strdel(&p->kernel_src);
	clReleaseMemObject(color_device);
	clReleaseMemObject(scene_device);
	clReleaseMemObject(cam_device);
	//clReleaseMemObject(width_device);
	//clReleaseMemObject(height_device);
	//clReleaseMemObject(device_matrix_word_to_cam);
	//clReleaseMemObject(device_matrix_wordl_transform);
}

#include <iostream>
#include <memory>	// std::unique_ptr
#include <string.h>

#include "fimg.h"
#include "hw_resize.h"

#ifdef USE_OCL
#include "xcl2.hpp"
#endif


int main(int argc, const char * argv[])
{
	std::cout << ".... Vitis Vision Library ...." << std::endl;

	if(argc < 2){
		std::cerr << "Usage: " << argv[0] << " <input image>" << std::endl;
		return -1;
	}

	int ret = 0;

	std::string img_in = argv[1];
	std::string img_out = "out.jpg";
	std::string xclbin_path = "bc_1.xclbin";

	fimg fii, fio;

	// Load image
	ret = fii.load(img_in.c_str());
	if(ret != 0){
		std::cerr << "[ERROR] load_image()" << std::endl;
		return -1;
	}

	unsigned int width = fii.cols();
	unsigned int height = fii.rows();
	unsigned int bpp = fii.bpp();

	// Check input image size
	if( (width != _SRC_COLS) || (height != _SRC_ROWS) ){
		std::cerr << "[ERROR] load_image()" << std::endl;
		return -1;
	}

	// Allocate output image
	ret = fio.allocate(_DST_COLS,  _DST_ROWS,  bpp /* = 3*8*/);
	if(ret != 0){
		std::cerr << "[ERROR] Failed to allocate output image" << std::endl;
		return -1;
	}

	// Size of OpenCL queue buffer
	const unsigned int align = sizeof(data_t);
	unsigned int num_in, num_out;
	if ( (width*height*3) % align == 0 ){
		num_in = (width*height*3)/align;
	}else{
		num_in = (width*height*3)/align + 1;
	}

	if ( (_DST_ROWS*_DST_COLS*3) % align == 0 ){
		num_out = (_DST_ROWS*_DST_COLS*3)/align;
	}else{
		num_out = (_DST_ROWS*_DST_COLS*3)/align + 1;
	}

#ifdef USE_OCL
    cl_int err;

    // Get the device:
    std::vector<cl::Device> devices = xcl::get_xil_devices();
    cl::Device device = devices[0];

    // Context, command queue and device name:
    OCL_CHECK(err, cl::Context context(device, NULL, NULL, NULL, &err));
    OCL_CHECK(err, cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE, &err));
    OCL_CHECK(err, std::string device_name = device.getInfo<CL_DEVICE_NAME>(&err));
    std::cout << "INFO: Device found - " << device_name << std::endl;

    // Load xclbin
    std::cout << "Loading: '" << xclbin_path << std::endl;
    std::ifstream bin_file(xclbin_path, std::ifstream::binary);
    bin_file.seekg (0, bin_file.end);
    unsigned int nb = bin_file.tellg();
    bin_file.seekg (0, bin_file.beg);
    std::unique_ptr<char[]> buf { new char[nb] };
    bin_file.read(buf.get(), nb);

    // Creating Program from Binary File
    cl::Program::Binaries bins;
    bins.push_back({buf.get(), nb});
    devices.resize(1);
    cl::Program program(context, devices, bins);

    // Create a kernel:
    OCL_CHECK(err, cl::Kernel krnl(program, "hw_resize", &err));

    // Allocate the buffers:
    std::vector<cl::Memory> inBufVec, outBufVec;
    OCL_CHECK(err, cl::Buffer cl_in(context, CL_MEM_READ_ONLY, num_in*sizeof(data_t), NULL, &err));
    OCL_CHECK(err, cl::Buffer cl_out(context, CL_MEM_WRITE_ONLY, num_out*sizeof(data_t), NULL, &err));

    // Set the kernel arguments
    OCL_CHECK(err, err = krnl.setArg(0, cl_in));
    OCL_CHECK(err, err = krnl.setArg(1, cl_out));

    // Copy input vectors to memory
    OCL_CHECK(err,
    		q.enqueueWriteBuffer(cl_in, CL_TRUE, 0, width*height*bpp/8, fii.get()));

    cl::Event event_sp;

    // Execute the kernel:
    OCL_CHECK(err, err = q.enqueueTask(krnl, NULL, &event_sp));

    clWaitForEvents(1, (const cl_event*)&event_sp);

//    event_sp.getProfilingInfo(CL_PROFILING_COMMAND_START, &start);
//    event_sp.getProfilingInfo(CL_PROFILING_COMMAND_END, &end);
//    diff_prof = end - start;
//    std::cout << (diff_prof / 1000000) << "ms" << std::endl;

    // Copying Device result data to Host memory
    OCL_CHECK(err,
    		q.enqueueReadBuffer(cl_out, CL_TRUE, 0, _DST_ROWS*_DST_COLS*bpp/8, fio.get()));

    q.finish();
#else

	// HW function
	hw_resize((data_t*)fii.get(), (data_t*)fio.get());

#endif

	// Save output image
	ret = fio.save(img_out.c_str());
	if(ret != 0){
		std::cerr << "[ERROR] Failed to save image" << std::endl;
		return -1;
	}

	// FreeImage
	fii.deinit_api();

	std::cout << "............................................." << std::endl;

	return 0;
}

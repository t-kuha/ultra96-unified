//
//  fimg.cpp
//

#include "fimg.h"

#include <iostream>
#include <string.h>		// memcpy

#define DISPERRORINFO(ERRSTR)	std::cout << "[ERROR]" << (ERRSTR) << std::endl;


// Constructor
fimg::fimg()
{
    bmp_ = NULL;
//    fmt_ = FIF_UNKNOWN;
}

// Destructor
fimg::~fimg()
{
	clear();
}

// Initialization
void fimg::init_api()
{
    FreeImage_Initialise();
}

// De-initialization
void fimg::deinit_api()
{
	FreeImage_DeInitialise();
}

// API info
void fimg::get_version(std::string& version)
{
	//std::cout << "FreeImage version: " << FreeImage_GetVersion() << std::endl;
    version = std::string(FreeImage_GetVersion());
}

//
int fimg::load(const char* src)
{
    if(src == NULL){
    	DISPERRORINFO("Invalid input...");
        return -1;
    }
    
    FREE_IMAGE_FORMAT fmt = FreeImage_GetFileType(src);
    if(fmt == FIF_UNKNOWN){
    	DISPERRORINFO("Unknown file type...");
        return -1;
    }
    
    if(bmp_ != NULL){
        // Unload existing data
        FreeImage_Unload(bmp_);
		bmp_ = NULL;
    }
    
    // Load
    bmp_ = FreeImage_Load(fmt, src);
    if(bmp_ == NULL){
    	DISPERRORINFO("FreeImage_Load() failed...");
        return -1;
    }
    
    return 0;
}

// Save image (as 8-bit/ch)
int fimg::save(const char* dst)
{
	// Check input
    if(dst == NULL){
		DISPERRORINFO("Invalid input...")
        return -1;
    }
    
	// Check bitmap data
	if(bmp_ == NULL){
		DISPERRORINFO("fiBmp_ is NULL...")
		return -1;
	}

    // Determine file type from extension
	FREE_IMAGE_FORMAT fmt = FreeImage_GetFIFFromFilename(dst);
    if(fmt == FIF_UNKNOWN){
		DISPERRORINFO("Could not determine image format...")
        return -1;
    }

	// Convert to standard FreeImage bitmap
	/*_fiBmp = FreeImage_ConvertToStandardType(_fiBmp);
	if(_fiBmp == NULL){
		// Failure
		DISPERRORINFO("Failed to convert Image Type...")
		return -1;
	}*/
    
    // Save
    BOOL ret = FreeImage_Save(fmt, bmp_, dst);
    if(ret == false){
        return -1;
    }
    
    return 0;
}

int fimg::allocate(unsigned int width, unsigned int height, unsigned int bpp)
{
	// Check input
	if( (width == 0) || (height == 0) ){
		return -1;
	}

	// Release existing data
	if(bmp_ != NULL){
		FreeImage_Unload(bmp_);
		bmp_ = NULL;
	}

	// Allocate bitmap
	bmp_ = FreeImage_Allocate(width, height, bpp);

	return (bmp_ == NULL) ? -1 : 0;
}

int fimg::allocate(FREE_IMAGE_TYPE type, unsigned int width, unsigned int height, unsigned int bpp)
{
	// Check input
	if( (width == 0) || (height == 0) ){
		return -1;
	}

	// Release existing data
	if(bmp_ != NULL){
		FreeImage_Unload(bmp_);
		bmp_ = NULL;
	}

	// Allocate bitmap
	bmp_ = FreeImage_AllocateT(type, width, height, bpp);

	return (bmp_ == NULL) ? -1 : 0;
}


int fimg::falloc(FREE_IMAGE_TYPE type, unsigned int width, unsigned int height)
{
    // Check input
    if( (width == 0) || (height == 0) ){
        return -1;
    }
//    
//    if(type != FIT_FLOAT){
//        
//    }
   
    unsigned char bpp = 0;
    switch(type){
        case FIT_FLOAT:
            bpp = sizeof(float)*8*1;    break;
        case FIT_RGBF:
            bpp = sizeof(float)*8*3;    break;
        case FIT_RGBAF:
            bpp = sizeof(float)*8*4;    break;
        default:
            return -1;
    }
    
    // Allocate bitmap
    bmp_ = FreeImage_AllocateT(type, width, height, bpp);
    
    return 0;
}


void fimg::clear()
{
   	// Release existing data
    if(bmp_ != NULL){
        FreeImage_Unload(bmp_);
        bmp_ = NULL;
    }
}

// Type conversion
// Have to preserve channel structure
int fimg::toFloat()
{
    // Check pixel
    if(FreeImage_HasPixels(bmp_) == false){
        DISPERRORINFO("No pixels in the bitmap...")
        return -1;
    }
    
    // incompatible type
    if(getFreeImageType() != FIT_BITMAP){
        // Unnecessary
        DISPERRORINFO("Unnecessary to convert (already in FIT_BITMAP)...")
        return -1;
    }

    // Figure out num. of channel & FreeImage Type
    unsigned int numCh = 1;
    FREE_IMAGE_TYPE fitype = FIT_UNKNOWN;
    switch(bpp()){
        case 1:
        case 4:
        case 8:
        case 16:
            numCh = 1;
            fitype = FIT_FLOAT;
            break;
        case 24:
            numCh = 3;
            fitype = FIT_RGBF;
            break;
        case 32:
            numCh = 4;
            fitype = FIT_RGBAF;
            break;
        default:
            return -1;
    }
    
    unsigned int width = cols();
    unsigned int height = rows();
    unsigned int numElem = width*height*numCh;   // Pixels count x Num. of Channel
    
    unsigned char* psrc = (unsigned char*)FreeImage_GetBits(bmp_);
    if(psrc == NULL){
        DISPERRORINFO("FreeImage_GetBits() failed...")
        return -1;
    }
    
    // Store data after type conversion
    float* tmpBuf = new float [numElem];

    // Convert
    float* pdst = tmpBuf; // For loop
    unsigned char* pline = NULL;
    
    for(unsigned int i = 0; i < height; i++){
        pline = (unsigned char*)FreeImage_GetScanLine(bmp_, i);
        for(unsigned int j = 0; j < width*numCh; j++){
            *pdst = (float)(pline[j]/255.0);
            pdst++;
        }
    }
    
    // Release & Create new one
    FreeImage_Unload(bmp_);
    
    bmp_ = FreeImage_AllocateT(fitype, width, height, sizeof(float)*8*numCh);
    if(bmp_ == NULL){
        // Error
    	delete [] tmpBuf;
        return -1;
    }
    
    // Set data
    set(tmpBuf, numElem*sizeof(float));
    
    // Release memory
    delete [] tmpBuf;

	return (bmp_ == NULL) ? -1 : 0;
}


// Convert float image to int
int fimg::toUint8()
{
	// Check pixel
	if(FreeImage_HasPixels(bmp_) == false){
		DISPERRORINFO("No pixels in the bitmap...")
		return -1;
	}

	if(getFreeImageType() == FIT_BITMAP){
		// Unnecessary
		DISPERRORINFO("Unnecessary to convert (already in FIT_BITMAP)...")
		return 0;
	}

    // Figure out num.of channel
    unsigned int numCh = 0;
    switch(getFreeImageType()){
        case FIT_FLOAT:
            numCh = 1;
            break;
        case FIT_RGBF:
            numCh = 3;
            break;
        case FIT_RGBAF:
            numCh = 4;
            break;
        default:
            // Incompatible type
            DISPERRORINFO("Incompatible FreeImage Type...")
            return -1;
    }
    
    
    unsigned int width = cols();
    unsigned int height = rows();
    unsigned int numElem = width*height*numCh;
    
    //
    float* tmpBuf = new float [numElem];
    memcpy(tmpBuf, get(), numElem*sizeof(float));

    // Release & Create new one
    FreeImage_Unload(bmp_);
    
    bmp_ = FreeImage_Allocate(width, height, 8*numCh);
    if(bmp_ == NULL){
        // Error
    	delete [] tmpBuf;
        return -1;
    }
    
    // Convert
    float* psrc = tmpBuf;
    for(unsigned int i = 0; i < height; i++){
        unsigned char* pline = FreeImage_GetScanLine(bmp_, i);
        for(unsigned int j = 0; j < width*numCh; j++){
            float tmp = (float)( (*psrc)*255.0 );
            pline[j] = (tmp > 255.0) ? 255 : (unsigned char) tmp;
            pline[j] = (tmp < 0) ? 0 : (unsigned char) tmp;
            psrc++;
        }
    }

    delete [] tmpBuf;

	return 0;
}


// Getter
unsigned int fimg::type()
{
//	FREE_IMAGE_TYPE fiImgType = FreeImage_GetImageType(_fiBmp);
	
	unsigned int ret = 0;	// Return: image type

	switch(FreeImage_GetImageType(bmp_)){
	case FIT_UNKNOWN:
		// Unknown format (returned value only, never use it as input value)
		ret = 0;	break;
	case FIT_BITMAP:
		// Standard image: 1-, 4-, 8-, 16-, 24-, 32-bit
		ret = 1;	break;
	case FIT_UINT16:
		// Array of unsigned short: unsigned 16-bit
		ret = 2;	break;
	case FIT_INT16:
		// Array of short: signed 16-bit
		ret = 3;	break;
	case FIT_UINT32:
		// Array of unsigned long: unsigned 32-bit
		ret = 4;	break;
	case FIT_INT32:
		// Array of long: signed 32-bit
		ret = 5;	break;
	case FIT_FLOAT:
		// Array of float: 32-bit IEEE floating point
		ret = 6;	break;
	case FIT_DOUBLE:
		// Array of double: 64-bit IEEE floating point
		ret = 7;	break;
	case FIT_COMPLEX:
		// Array of FICOMPLEX: 2 x 64-bit IEEE floating point
		ret = 8;	break;
	case FIT_RGB16:
		// 48-bit RGB image: 3 x unsigned 16-bit
		ret = 9;	break;
	case FIT_RGBA16:
		// 64-bit RGBA image: 4 x unsigned 16-bit
		ret = 10;	break;
	case FIT_RGBF:
		// 96-bit RGB float image: 3 x 32-bit IEEE floating point
		ret = 11;	break;
	case FIT_RGBAF:
		// 128-bit RGBA float image: 4 x 32-bit IEEE floating point
		ret = 12;	break;
	}

	return ret;
}

unsigned int fimg::cols()
{
    return FreeImage_GetWidth(bmp_);
}

unsigned int fimg::rows()
{
    return FreeImage_GetHeight(bmp_);
}

unsigned int fimg::pitch()
{
	return FreeImage_GetPitch(bmp_);
}

unsigned int fimg::bpp()
{
    return FreeImage_GetBPP(bmp_);
}

FREE_IMAGE_TYPE fimg::getFreeImageType()
{
	return FreeImage_GetImageType(bmp_);
}

unsigned int fimg::getDataSizeInByte()
{
	//
	return rows()*pitch();
}

//unsigned int getNumChannel()
//{
//	return 0;
//}
//
//unsigned char* fimg::getImgDataPtr()
//{
//    return FreeImage_GetBits(_fiBmp);
//}

void* fimg::get()
{
    return (void*)FreeImage_GetBits(bmp_);
}

void* fimg::lineDataPtr(int line)
{
    return (void*)FreeImage_GetScanLine(bmp_, line);
}

void fimg::set(void* ptr, unsigned int size_in_byte)
{
	// Check input
	if(ptr == NULL){
		return;
	}

	if( size_in_byte != getDataSizeInByte()){
		DISPERRORINFO("Data size of source does not match destination...")
		return;
	}

	// Copy
	memcpy(FreeImage_GetBits(bmp_), ptr, size_in_byte);
}

bool fimg::isEmpty()
{
	return (FreeImage_HasPixels(bmp_) == false) ? true : false;
}

// General info
void fimg::show_info()
{
	unsigned int nImageWidth    = FreeImage_GetWidth(bmp_);
	unsigned int nImageHeight   = FreeImage_GetHeight(bmp_);
	unsigned int nPitch         = FreeImage_GetPitch(bmp_);
	unsigned int nBPP           = FreeImage_GetBPP(bmp_);

	std::ostream& rOutputStream = std::cout;

	rOutputStream << "Size:  " << nImageWidth << " x " << nImageHeight << "\n";
	rOutputStream << "Pitch: " << nPitch << "\n";

	rOutputStream << "Color Type: ";
	switch (FreeImage_GetColorType(bmp_)){
	case FIC_MINISWHITE:
		// Monochrome bitmap (1-bit) : first palette entry is white. 
		// Palletised bitmap (4 or 8-bit) : the bitmap has an inverted greyscale palette
		rOutputStream << "Monochrome bitmap (1-bit) or Palletised bitmap (4 or 8-bit); inverted greyscale palette\n";
		break;
	case FIC_MINISBLACK:
		// Monochrome bitmap (1-bit) : first palette entry is black. 
		// Palletised bitmap (4 or 8-bit) and single channel non standard bitmap: the bitmap has a greyscale palette
		rOutputStream << "Monochrome bitmap (1-bit) or Palletised bitmap (4 or 8-bit)\n";
		break;
	case FIC_RGB:
		// High-color bitmap (16, 24 or 32 bit), RGB16 or RGBF
		rOutputStream << "High-color bitmap (16, 24 or 32 bit), RGB16 or RGBF\n";
		break;
	case FIC_PALETTE:
		// Palettized bitmap (1, 4 or 8 bit)
		rOutputStream << "Palettized bitmap (1, 4 or 8 bit)\n";
		break;
	case FIC_RGBALPHA:
		// High-color bitmap with an alpha channel (32 bit bitmap, RGBA16 or RGBAF)
		rOutputStream << "High-color bitmap with an alpha channel\n";
		break;
	case FIC_CMYK:
		// CMYK bitmap (32 bit only)
		rOutputStream << "CMYK bitmap (32 bit only)\n";	
		break;
	default:
		rOutputStream << "Unknown pixel format.\n";
	}

	rOutputStream << "Image Type: ";
	switch(FreeImage_GetImageType(bmp_)){
	case FIT_BITMAP:
		// Standard image: 1-, 4-, 8-, 16-, 24-, 32-bit
		rOutputStream << "Standard image\n";
		break;
	case FIT_UINT16:
		// Array of unsigned short: unsigned 16-bit
		rOutputStream << "Array of unsigned short\n";
		break;
	case FIT_INT16: 
		// Array of short: signed 16-bit
		rOutputStream << "Array of short\n";
		break;
	case FIT_UINT32:
		// Array of unsigned long: unsigned 32-bit
		rOutputStream << "Array of unsigned long\n";
		break;
	case FIT_INT32:
		// Array of long: signed 32-bit
		rOutputStream << "Array of long\n";
		break;
	case FIT_FLOAT:
		// Array of float: 32-bit IEEE floating point
		rOutputStream << "Array of float\n";
		break;
	case FIT_DOUBLE: 
		// Array of double: 64-bit IEEE floating point
		rOutputStream << "Array of double\n";
		break;
	case FIT_COMPLEX: 
		// Array of FICOMPLEX: 2 x 64-bit IEEE floating point
		rOutputStream << "Array of FICOMPLEX\n";
		break;
	case FIT_RGB16:
		// 48-bit RGB image: 3 x unsigned 16-bit
		rOutputStream << "48-bit RGB image\n";
		break;
	case FIT_RGBA16:
		// 64-bit RGBA image: 4 x unsigned 16-bit
		rOutputStream << "64-bit RGBA image\n";
		break;
	case FIT_RGBF:
		// 96-bit RGB float image: 3 x 32-bit IEEE floating point
		rOutputStream << "96-bit RGB float image\n";
		break;
	case FIT_RGBAF:
		// 128-bit RGBA float image: 4 x 32-bit IEEE floating point
		rOutputStream << "28-bit RGBA float image\n";
		break;
	default:
		// FIT_UNKNOWN: Unknown format (returned value only, never use it as input value)
		rOutputStream << "Unknown format\n";
		break;
	}

	rOutputStream << "Bits Per Pixel: " << nBPP << std::endl;
}

// Show pixel value at the specified location
int fimg::showPixelValue(unsigned int x, unsigned int y)
{
	bool ret = false;
	
	if(this->bpp() <= 8){
		unsigned char pixval = 0;
		ret = FreeImage_GetPixelIndex(bmp_, x, y, &pixval);

		if(ret == false){
			// Error
			DISPERRORINFO("FreeImage_GetPixelIndex() failed...")
			return -1;
		}

		printf("Pixel Value (%d, %d) = [%d]\n", x, y, pixval);		
	}else{
		RGBQUAD rgb = {0, 0, 0, 0};
		ret = FreeImage_GetPixelColor(bmp_, x, y, &rgb);

		if(ret == false){
			// Error
			DISPERRORINFO("FreeImage_GetPixelColor() failed...")
			return -1;
		}
		
		printf("Pixel Value (%d, %d) = [%d %d %d]\n", x, y, rgb.rgbRed, rgb.rgbGreen, rgb.rgbBlue);
	}

	return 0;
}

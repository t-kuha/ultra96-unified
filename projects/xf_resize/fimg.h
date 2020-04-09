//
//  fimg.h
//

#ifndef __FIMG_H__
#define __FIMG_H__

#include "FreeImage.h"

#include <string>			// std::string


// FreeImage wrapper class
class fimg
{
public:
	// Constructor & Destructor
    fimg();
    ~fimg();
    
    // Initialization & De-initialization
    void init_api();
    void deinit_api();
    
    // API info
    void get_version(std::string& version);
   
	// General info about this object
	void show_info();

    // Image I/O
    int load(const char* src);
    int save(const char* dst);
    int allocate(unsigned int width, unsigned int height, unsigned int bpp);
	int allocate(FREE_IMAGE_TYPE type, unsigned int width, unsigned int height, unsigned int bpp);
    
    int falloc(FREE_IMAGE_TYPE type, unsigned int width, unsigned int height);
    
    void clear();

    // Getter
	unsigned int type();
	unsigned int cols();	// Width
    unsigned int rows();	// Height
	unsigned int pitch();
    unsigned int bpp();		// Bit depth
	unsigned int getDataSizeInByte();
	
	//unsigned int getNumChannel();
	FREE_IMAGE_TYPE getFreeImageType();
    //unsigned char* getImgDataPtr();

	// Get & set pixel data
	void* get();
	void set(void* ptr, unsigned int size_in_byte);

	void* lineDataPtr(int line);

	int showPixelValue(unsigned int x, unsigned int y);

	bool isEmpty();

	// Setter


	// Type conversion
	int toFloat();  // uint8 -> float
    int toUint8();  // float -> uint8

private:
    FIBITMAP*			bmp_;
//    FREE_IMAGE_FORMAT	fmt_;
};

#endif // __FIMG_H__

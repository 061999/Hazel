#include "stb_image.h"
#include "Image.h"

Image::Image(const char * path)
{
	data = stbi_load( path , &width , &height , &channel , 4 );
}

Image::~Image()
{
	stbi_image_free( data );
}

int Image::GetWidth()
{
	return width;
}

int Image::GetHeight()
{
	return height;
}

int Image::GetLineWidth()
{
	return 4 * width * sizeof( unsigned char );
}

unsigned char * Image::GetData()
{
	return data;
}
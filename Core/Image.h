#pragma once
class Image
{
public:
	Image(const char * path);
	~Image();
	int GetWidth();
	int GetHeight();
	int GetLineWidth();
	unsigned char * GetData();
private:
	int width , height , channel;
	unsigned char * data;

};


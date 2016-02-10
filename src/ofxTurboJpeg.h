#pragma once

#include "ofMain.h"

#include "turbojpeg.h"

class ofxTurboJpeg
{

public:

	ofxTurboJpeg();
	~ofxTurboJpeg();

	void save(ofImage* img, string path, int jpegQuality = 90);
	void save(string path, const ofPixels& img, int jpegQuality = 90);
	void save(string path, ofImage& img, int jpegQuality = 90);

	bool load(string path, ofPixels &pix);
	bool load(string path, ofImage &img);
	bool load(const ofBuffer& buf, ofPixels &pix);
	bool load(const ofBuffer& buf, ofImage &img);

	template <class T>
	unsigned char* compress(T& img, int jpegQuality, unsigned long* size)
	{
		if (img.getWidth() == 0) return NULL;

		int pitch = 0, flags = 0, jpegsubsamp = 0;
		*size = 0;

		unsigned int bpp = img.getPixels().getNumChannels();

		int w = img.getWidth();
		int h = img.getHeight();
		unsigned char* data = img.getPixels().getData();

		unsigned char* output = (unsigned char*) malloc(sizeof(char) * w * h * bpp);
		tjCompress(handleCompress, data, w, pitch, h, bpp,
				   output, size, jpegsubsamp, jpegQuality, flags);

		return output;
	}

private:
	void save(ofBuffer &buf, const ofPixels& img, int jpegQuality = 90);

	tjhandle handleCompress;
	tjhandle handleDecompress;
};

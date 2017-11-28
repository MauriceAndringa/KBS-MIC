/* 
* testBMPfile.cpp
*
* Created: 27-11-2017 09:30:21
* Author: wsvdy
*/

#include <TFT.h>
#include "OpenBMPFile.h"

// default constructor
OpenBMPFile::OpenBMPFile()
{
} //testBMPfile

void OpenBMPFile::openFile(char *file, int16_t x, int16_t y)
{
	int h, w;
	uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
	uint8_t pad;
	/*BMP_Header *bmp_hd;
	//BMP_DIPHeader *bmp_dip;
	
	
	//BMP Header
	//bmpImage.read(&buf, sizeof(BMP_Header));
	//bmp_hd = (BMP_Header*)&buf[0];
	
	//BMP DIP-Header
	//bmpImage.read(&buf, sizeof(BMP_DIPHeader));
	//bmp_dip = (BMP_DIPHeader*)&buf[0];*/
	
	bmpImage = SD.open(file, FILE_READ);
	//textFile = SD.open("test.txt" , FILE_WRITE);
	
	
	dataStartingOffset = readNbytesInt(&bmpImage, 0x0A, 4);
	
	int32_t width	= readNbytesInt(&bmpImage, 0x12, 4);
	int32_t height	= readNbytesInt(&bmpImage, 0x16, 4);
	
	/*Serial.println(width);
	Serial.println(height);
	
	int16_t pixelSize = readNbytesInt(&bmpImage, 0x1C, 2);
	
	if(pixelSize != 24){
		Serial.println("Image is not 24 bpp");
		while(1);
	} */
	
	bmpImage.seek(dataStartingOffset);	//skip bitmap header
	
	pad = width % 4;
	
	for(h=(y+height-1); h >= y; h--){	//for every line
		for(w=x; w < (x+width); w++){	//for every pixel in line
			bmpImage.read(&buf, 3);
			FC.screenBrightness();
			LCD.drawPixel(w,h,RGB(buf[2], buf[1], buf[0]));
		}
		if(pad){
			bmpImage.read(&buf, pad);
		}
	}
	
	/*for(int32_t i = height; i >= 0; i--){
		for(int32_t j = 0; j < width; j++){
			bmpImage.read(&buf, 3);
			FC.screenBrightness();
			
			
			B = bmpImage.read();
			G = bmpImage.read();
			R = bmpImage.read();
			textFile.print("R");
			textFile.print(R);
			textFile.print("G");
			textFile.print(G);
			textFile.print("B");
			textFile.print(B);
			textFile.print(" "); // debug
			LCD.drawPixel(,i,RGB(buf[2], buf[1], buf[0]));	
		}
		if(pad){
			bmpImage.read(&buf, pad);
		}
	}*/
	
	/*for(int32_t i = 0; i < height; i++){
		for(int32_t j = 0; j < width; j++){
			bmpImage.read(&buf, 3);
			
			/*
			B = bmpImage.read();
			G = bmpImage.read();
			R = bmpImage.read();
			/*textFile.print("R");
			textFile.print(R);
			textFile.print("G");
			textFile.print(G);
			textFile.print("B");
			textFile.print(B);
			textFile.print(" ");*/ // debug
			/*LCD.drawPixel(j,i,RGB(buf[2], buf[1], buf[0]));			
		}
		if(pad){
			bmpImage.read(&buf, pad);
		}
	}*/
	
	bmpImage.close();
	//textFile.close();
	
	//Serial.println("done writing");
}

int32_t OpenBMPFile::readNbytesInt(File *p_file, int position, byte nBytes)
{
	 if (nBytes > 4)
		return 0;

	 p_file->seek(position);

	 int32_t weight = 1;
	 int32_t result = 0;
	 for (; nBytes; nBytes--)
	 {
		 result += weight * p_file->read();
		 weight <<= 8;
	 }
	 return result;
}

// default destructor
OpenBMPFile::~OpenBMPFile()
{
} //~testBMPfile

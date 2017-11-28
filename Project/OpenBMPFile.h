/* 
* testBMPfile.h
*
* Created: 27-11-2017 09:30:21
* Author: wsvdy
*/


#ifndef __TESTBMPFILE_H__
#define __TESTBMPFILE_H__


class OpenBMPFile
{
//variables
public:
	File bmpImage;
	File textFile;
protected:
private:
	uint32_t dataStartingOffset;

//functions
public:
	OpenBMPFile();
	~OpenBMPFile();
	void openFile(char *file, int16_t x, int16_t y);
protected:
private:
	OpenBMPFile( const OpenBMPFile &c );
	OpenBMPFile& operator=( const OpenBMPFile &c );
	int32_t readNbytesInt(File *p_file, int position, byte nBytes);

}; //testBMPfile

#endif //__TESTBMPFILE_H__

#ifndef FILE_DETECTION_FILE_WRITER_H

#define FILE_DETECTION_FILE_WRITER_H

#include "File.h"

namespace FileDetection
{
	class FileWriter abstract
	{
	public:

		/*
		* Write the file in the parameter
		* If the file already exist , overwrite it
		* Return:
		* whether file writing success
		*/
		virtual bool write(const File& file) const = 0;

	};
}

#endif
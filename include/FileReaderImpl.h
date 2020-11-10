#ifndef FILE_DETECTION_FILE_READER_IMPL_H

#define FILE_DETECTION_FILE_READER_IMPL_H

#include "FileReader.h"

namespace FileDetection
{
	class FileReaderImpl : public FileReader
	{
	public:
		
		std::vector<std::string> read(const std::string&
			location) const override;
	};
}

#endif

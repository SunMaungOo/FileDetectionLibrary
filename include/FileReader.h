#ifndef FILE_DETECTION_FILE_READER_H

#define FILE_DETECTION_FILE_READER_H

#include <string>
#include <vector>

namespace FileDetection
{
	class FileReader abstract
	{
	public:

		virtual std::vector<std::string> read(const std::string& 
			location) const = 0;

	};
}

#endif
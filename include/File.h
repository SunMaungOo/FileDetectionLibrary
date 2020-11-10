#ifndef FILE_DETECTION_FILE_H

#define FILE_DETECTION_FILE_H

#include <string>
#include <vector>

namespace FileDetection
{
	class File abstract
	{

	public:

		/*
		* Return name of the file
		*/
		virtual std::string get_name() const = 0;

		/*
		* Return location of the file
		*/
		virtual std::string get_location() const = 0;

		virtual std::vector<std::string> get_content() const = 0;

	};

}

#endif


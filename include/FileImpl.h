#ifndef FILE_DETECTION_FILE_IMPL_H

#define FILE_DETECTION_FILE_IMPL_H

#include "File.h"
#include <string>
#include <vector>

namespace FileDetection
{
	class FileImpl : public File
	{
	public:

		FileImpl(const std::string& name,
			const std::string& location,
			const std::vector<std::string> content);

		std::string get_name() const override;

		std::string get_location() const override;

		std::vector<std::string> get_content() const override;

	private:

		std::string pname;

		std::string plocation;

		std::vector<std::string> pcontent;

	};
}

#endif


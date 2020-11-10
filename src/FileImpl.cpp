#include "FileImpl.h"

namespace FileDetection
{

	FileImpl::FileImpl(const std::string& name,
		const std::string& location,
		const std::vector<std::string> content)
		:pname{name},
		plocation{location},
		pcontent{content}
	{
	}
	std::string FileImpl::get_name() const
	{
		return pname;
	}
	std::string FileImpl::get_location() const
	{
		return plocation;
	}
	std::vector<std::string> FileImpl::get_content() const
	{
		return pcontent;
	}
}

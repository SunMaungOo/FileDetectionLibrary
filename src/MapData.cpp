#include "MapData.h"

namespace FileDetection
{
	MapData::MapData(const std::string& hash,
		const std::vector<std::string>& file_locations)
		:phash{hash},
		pfile_locations{file_locations}
	{
	}
	std::string MapData::get_hash() const
	{
		return phash;
	}
	std::vector<std::string> MapData::get_file_locations() const
	{
		return pfile_locations;
	}
}
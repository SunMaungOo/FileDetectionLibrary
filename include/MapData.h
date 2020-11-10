#ifndef FILE_DETECTION_MAP_DATA_H

#define FILE_DETECTION_MAP_DATA_H

#include <string>
#include <vector>

namespace FileDetection
{
	class MapData final
	{

	public:

		/*
		* hash : Hash of the file location
		* file_location : File locations which have the same hash
		*/
		MapData(const std::string& hash,
			const std::vector<std::string>& file_locations);

		std::string get_hash() const;

		std::vector<std::string> get_file_locations() const;


	private:

		std::string phash;

		std::vector<std::string> pfile_locations;
	};
}

#endif


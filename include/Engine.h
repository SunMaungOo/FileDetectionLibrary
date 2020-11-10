#ifndef FILE_DETECTION_ENGINE_H

#define FILE_DETECTION_ENGINE_H

#include "File.h"
#include "MapData.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <vector>

namespace FileDetection
{
	class Engine
	{
	public:

		/*
		* base_dir_location : Location we are working in
		* special_dir_name : special folder name in base_dir_location
		* where we save the file required
		*/
		void generate(const std::string& base_dir_location,
			const std::string& special_dir_name) const;

		/*
		* Return :
		* tuple<AddedList,ChangedList,RemovedList>
		* 
		* The list contain file location
		*/
		std::tuple<std::unordered_set<std::string>,
			std::unordered_set<std::string>,
			std::unordered_set<std::string>> detect(const std::string& base_dir_location,
			const std::string& special_dir_name) const;

	private:

		/*
		* Remove the directory if it exist along
		* with every file in the directory
		* 
		* dir_location : Location of dir to remove
		*/
		void remove_dir(const std::string& dir_location) const;

		/*
		* Get unique key from multimap
		*/
		std::unordered_set<std::string> get_unique_keys(
			std::unordered_multimap<std::string,
			File*> map) const;

		/*
		* Create map data by using the file in special folder
		* 
		*/
		std::vector<MapData> get_map_data(const std::vector<
			std::unique_ptr<File>>& hash_files) const;

		/*
		* Return:
		* tuple<AddedList,ChangedList,RemovedList>
		* 
		* The list contain file location
		*/
		std::tuple<std::unordered_set<std::string>,
			std::unordered_set<std::string>,
			std::unordered_set<std::string>> algorithm(const std::vector<MapData>& cache_data,
			const std::vector<MapData>& base_file) const;

	};
}

#endif


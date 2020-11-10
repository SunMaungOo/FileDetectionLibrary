#include "Engine.h"
#include "FileUtils.h"
#include "FileReaderImpl.h"
#include "FileImpl.h"
#include "FileWriterImpl.h"
#include "UnorderedInserter.h"
#include "Sets.h"
#include <iostream>
#include <filesystem>

namespace FileDetection
{

	void Engine::generate(const std::string& base_dir_location,
		const std::string& special_dir_name) const
	{
		std::string special_folder_location = base_dir_location +
			"/" + special_dir_name;

		remove_dir(special_folder_location);

		auto files = std::move(get_files(base_dir_location,
			FileReaderImpl()));

		std::unordered_multimap<std::string, 
			File*> grouped_file = std::move(group_hash(files));

		std::filesystem::create_directory(special_folder_location);

		FileWriterImpl file_writer;

		std::unordered_set<std::string> unique_keys = std::move(
			get_unique_keys(grouped_file));


		std::for_each(unique_keys.cbegin(),
			unique_keys.cend(),
			[&special_folder_location,
			&grouped_file,
			&file_writer](const auto& key) {

				std::string name = key;
	
				std::string location = special_folder_location + "/"+key;

				std::vector<std::string> contents;

				auto iter = grouped_file.equal_range(key);

				std::for_each(iter.first,
					iter.second,
					[&contents](const auto& pair) {
						
						//save file location which have
						//the same hash

						contents.push_back((pair.second)->get_location());

					});

				file_writer.write(FileImpl{name,
					location,
					contents});
			});
		
	}


	std::tuple<std::unordered_set<std::string>,
		std::unordered_set<std::string>,
		std::unordered_set<std::string>> Engine::detect(const std::string& base_dir_location,
		const std::string& special_dir_name) const
	{
		std::string special_folder_location = base_dir_location +
			"/" + special_dir_name;

		if (!std::filesystem::exists(special_folder_location)) {
			return std::make_tuple(std::unordered_set<std::string>(),
				std::unordered_set<std::string>(),
				std::unordered_set<std::string>());
		}

		auto hash_files = std::move(get_files(special_folder_location,
			FileReaderImpl(),
			false));

		std::vector<MapData> cache_data = std::move(get_map_data(hash_files));

		auto base_files = std::move(get_files(base_dir_location,
			FileReaderImpl()));

		std::vector<MapData> added_files;

		std::transform(base_files.cbegin(),
			base_files.cend(),
			std::back_inserter(added_files),
			[](const auto& file) {

				//By logic, the file should only have 1 file location

				std::vector<std::string> file_location;
				file_location.push_back(file->get_location());

				//hash the file and save the file location of hash file

				return MapData(get_hash(*file),
					file_location);
			});

		return algorithm(cache_data, added_files);

	}

	void Engine::remove_dir(const std::string& dir_location) const
	{
		if (std::filesystem::exists(dir_location)) {

			std::filesystem::remove_all(dir_location);

		}
	}


	std::unordered_set<std::string> Engine::get_unique_keys(
		std::unordered_multimap<std::string,
		File*> map) const
	{
		std::unordered_set<std::string> unique_keys;

		std::for_each(map.cbegin(),
			map.cend(),
			[&unique_keys](const auto& pair) {

				unique_keys.insert(pair.first);

			});

		return unique_keys;
	}



	std::vector<MapData> Engine::get_map_data(const std::vector<
		std::unique_ptr<File>>& hash_files) const
	{
		std::vector<MapData> map_data;
		
		std::transform(hash_files.cbegin(),
			hash_files.cend(),
			std::back_inserter(map_data),
			[](const auto& file) {

				return MapData(file->get_name(),
					file->get_content());
			});

		return map_data;
	}

	std::tuple<std::unordered_set<std::string>,
		std::unordered_set<std::string>,
		std::unordered_set<std::string>> Engine::algorithm(const std::vector<MapData>& cache_data,
		const std::vector<MapData>& base_file) const
	{
		//added_list , changed_list , removed_list

		std::unordered_set<std::string> added_file_locations;

		std::transform(base_file.cbegin(),
			base_file.cend(),
			unordered_inserter(&added_file_locations),
			[](const MapData& map_data) {

				return map_data.get_file_locations()[0];
			});


		//<file location,hash>
		std::unordered_map<std::string, std::string> tmp_added_list;

		std::transform(base_file.cbegin(),
			base_file.cend(),
			unordered_inserter(&tmp_added_list),
			[](const MapData& map_data) {
				
				return std::make_pair(map_data.get_file_locations()[0],
					map_data.get_hash());
			});

		std::unordered_set<std::string> tmp;

		std::unordered_set<std::string> added_list;

		//<file location>
		std::unordered_set<std::string> changed_list;

		std::for_each(cache_data.cbegin(),
			cache_data.cend(),
			[&tmp_added_list,
			&tmp,
			&changed_list](const MapData& cache_file) {

				std::string cache_hash = std::move(cache_file.get_hash());

				std::vector<std::string> cache_file_location = std::move(
					cache_file.get_file_locations());

				std::for_each(cache_file_location.cbegin(),
					cache_file_location.cend(),
					[&tmp_added_list,
					&tmp,
					&cache_hash,
					&changed_list](const auto& file_location) {

						tmp.insert(file_location);

						bool found_file = tmp_added_list.find(file_location)!=tmp_added_list.end();

						if (found_file) {

							std::string found_file_cache = tmp_added_list[file_location];

							tmp_added_list.erase(file_location);

							if (found_file_cache != cache_hash) {

								changed_list.insert(file_location);

							}
							
						}

					});

			});

		
		//Extracting file location from
		//tmp_added_list is added list

		std::transform(tmp_added_list.cbegin(),
			tmp_added_list.cend(),
			unordered_inserter(&added_list),
			[](const auto& pair) {
				return pair.first;
			});

		
		auto combined_set = std::move(sets_combine(added_list, 
			changed_list));
		
		auto unchanged_and_removed_list = std::move(set_substract(tmp,
			combined_set));

		auto removed_list = std::move(set_substract(unchanged_and_removed_list,
			added_file_locations));
		
		
		return std::make_tuple(added_list,
			changed_list,
			removed_list);
	}

}

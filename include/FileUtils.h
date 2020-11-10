#ifndef FILE_DETECTION_FILE_UTILS_H

#define FILE_DETECTION_FILE_UTILS_H

#include "File.h"
#include "FileReader.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <filesystem>

namespace FileDetection
{
	/*
	* Get the hash of the file
	* Return : hash of the file
	*/
	std::string get_hash(const File& file);

	std::string get_prefix_content();

	/*
	* Group the file which have the same hash
	* Return :
	* Key : file hash
	* Value : file
	*/
	std::unordered_multimap<std::string,File*> group_hash(const 
		std::vector<File*>& files);

	std::unordered_multimap<std::string, File*> group_hash(const
		std::vector<std::unique_ptr<File>>& files);

	//Need to replace dir_location with Dir abstract class for testing
	/*
	* 
	* dir_location : Dir location to read file recursively
	* reader : Which read the content of the file
	* is_ignore_special_folder : whether to ignore file in our special folder
	*/
	std::vector<std::unique_ptr<File>> get_files(const std::string& dir_location,
		const FileReader& reader,
		bool is_ignore_special_folder=true);

}

#endif


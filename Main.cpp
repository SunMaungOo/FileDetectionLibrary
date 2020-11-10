#include "FileUtils.h"
#include "File.h"
#include "FileReaderImpl.h"
#include "FileWriterImpl.h"
#include "FileImpl.h"
#include "Engine.h"
#include "Constant.h"
#include <iostream>
#include <string>

void display(std::tuple<std::unordered_set<std::string>,
	std::unordered_set<std::string>,
	std::unordered_set<std::string>> result)
{
	auto added_list = std::get<0>(result);

	auto changed_list = std::get<1>(result);

	auto removed_list = std::get<2>(result);

	std::cout << "Added\n";

	for (const auto& add : added_list) {
		std::cout << add << "\n";
	}

	std::cout << "====================\n";
	std::cout << "Changed\n";

	for (const auto& changed : changed_list) {
		std::cout << changed << "\n";
	}

	std::cout << "====================\n";
	std::cout << "Removed\n";

	for (const auto& removed : removed_list) {
		std::cout << removed << "\n";
	}

	std::cout << "====================\n";
}

int main(int argc,char* argv[])
{
	if (argc != 3) {
		return 0;
	}

	std::string command = argv[1];

	std::string path = argv[2];

	if (path == "") {
		return 0;
	}

	FileDetection::Engine engine{};

	if (command == "save") {

		engine.generate(path,
			FileDetection::get_special_folder_name());

	}
	else if (command == "detect") {

		display(engine.detect(path,
			FileDetection::get_special_folder_name()));
	}
	
	return 0;
}


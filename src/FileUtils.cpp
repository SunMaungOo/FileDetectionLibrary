#include "FileUtils.h"
#include "picosha2.h"
#include "FileImpl.h"
#include "Constant.h"
#include <sstream>
#include <algorithm>
#include <memory>
#include <iostream>


namespace FileDetection
{
    std::string FileDetection::get_hash(const File& file)
    {
        std::stringstream builder;
        builder << get_prefix_content();

        const std::vector<std::string>& file_content = file.get_content();

        std::for_each(file_content.cbegin(),
            file_content.cend(),
            [&builder](const auto& data) {
                builder << data;
            });

        std::string content = std::move(builder.str());

        return picosha2::hash256_hex_string(content.begin(),
            content.end());
    }

    std::string FileDetection::get_prefix_content()
    {
        return "SMO_FILE_DETECTOR";
    }

    std::unordered_multimap<std::string, File*> group_hash(const std::vector<File*>& files) {

        std::unordered_multimap<std::string, File*> grouped;

        std::for_each(files.cbegin(),
            files.cend(),
            [&grouped](const auto& file) {
                
                // (File*)& -> File*
                // reference to File pointer -> File pointer
                std::string hash = std::move(get_hash(*file));

                //Do some weird template magic

                grouped.insert(std::make_pair(hash,file));

            });

        return grouped;
    }

    std::unordered_multimap<std::string, File*> group_hash(const
        std::vector<std::unique_ptr<File>>& files) {

        std::vector<File*> vec;

        std::for_each(files.cbegin(),
            files.cend(),
            [&vec](const std::unique_ptr<File>& file) {
                vec.push_back(file.get());
            });
        

        return group_hash(vec);
    }

    std::vector<std::unique_ptr<File>> get_files(const std::string& dir_location,
        const FileReader& reader,
        bool is_ignore_special_folder)
    {
        std::vector<std::unique_ptr<File>> files;

        for (auto& entry : std::filesystem::recursive_directory_iterator(dir_location)) {

            auto file_name = std::move(entry.path().filename().string());

 
            //exclude directory name

            if (entry.is_directory()) {
                continue;
            }

            if (is_ignore_special_folder) {


                std::string last_folder_path = std::move(entry.path()
                    .parent_path()
                    .filename().string());

                //exclude the file from
                //internal folder the program used

                if (last_folder_path == get_special_folder_name()) {
                    continue;
                }
            }



            std::string file_location = std::move(entry.path().string());

            std::vector<std::string> contents = reader.read(file_location);

            files.push_back(std::make_unique<FileImpl>(file_name,
                file_location,
                contents));
        }


        return files;
    }

}

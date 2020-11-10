#include "FileReaderImpl.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace FileDetection
{

    std::vector<std::string> FileReaderImpl::read(const std::string&
        location) const
    {
        std::vector<std::string> contents;

        if (!std::filesystem::exists(location)) {
            return contents;
        }

        std::ifstream file{ location };

        if (!file.is_open()) {
            return contents;
        }

        std::string line;

        while (std::getline(file, line)) {
            contents.push_back(line);
        }

        if (file.is_open()) {
            file.close();
        }

        return contents;
    }
}

#include "FileWriterImpl.h"
#include <fstream>

namespace FileDetection
{
    bool FileWriterImpl::write(const File& file) const
    {
        std::ofstream output{ file.get_location(),
            std::ios::out | std::ios::trunc };
 
        if (!output.is_open()) {
            return false;
        }
       
        for (const auto& line : file.get_content()) {
            output << line << "\n";
        }

        output.close();

        return true;
    }
}

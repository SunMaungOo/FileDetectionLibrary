#ifndef FILE_DETECTION_FILE_WRITER_IMPL_H

#define FILE_DETECTION_FILE_WRITER_IMPL_H

#include "FileWriter.h"

namespace FileDetection
{
	class FileWriterImpl : public FileWriter
	{
	public:

		virtual bool write(const File& file) const override;
	};
}

#endif

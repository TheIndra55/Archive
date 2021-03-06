#include "../Archive/archive.hpp"

#ifdef _WIN32
#define ARCHIVE_EXPORT __declspec(dllexport)
#else
#define ARCHIVE_EXPORT __attribute__((visibility("default")))
#endif

extern "C"
{

ARCHIVE_EXPORT Archive* archive_open(char* file)
{
	auto archive = new Archive(file);
	return archive;
}

ARCHIVE_EXPORT bool archive_file_exists(Archive* archive, char* file)
{
	return archive->FileExists(file);
}

ARCHIVE_EXPORT int archive_get_file_size(Archive* archive, char* file)
{
	return archive->GetFileSize(file);
}

ARCHIVE_EXPORT void archive_close(Archive* archive)
{
	archive->~Archive();
	delete[] archive;
}

ARCHIVE_EXPORT ArchiveFile* archive_get_files(Archive* archive, int* num)
{
	// new since else memory will be gone before function exits
	auto files = new std::vector<ArchiveFile>;
	
	for (auto& file : archive->GetFiles())
	{
		files->push_back(file.second);
	}

	*num = static_cast<int>(files->size());
	return &(*files)[0];
}

ARCHIVE_EXPORT int archive_read_file(Archive* archive, char* file, char** buf)
{
	if (!archive->FileExists(file))
	{
		return -1;
	}
	
	auto size = archive->GetFileSize(file);
	auto buffer = new char[size];

	archive->ReadFile(file, buffer);

	*buf = buffer;
	return size;
}

ARCHIVE_EXPORT void archive_cleanup_native_memory(void* ptr)
{
	delete[] ptr;
}

}
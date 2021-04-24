#pragma once

#include <fstream>
#include <cstdint>
#include <string>
#include <unordered_map>

#define ARCHIVE_MAGIC 5521732 //DAT<nul>
#define ARCHIVE_VERSION 1

struct ArchiveHeader
{
	uint16_t version;
	uint32_t num_files;
};

struct ArchiveFile
{
	uint32_t name; // hash of the file path
	uint32_t offset;
	uint32_t size;
	uint32_t reserved; // reserved for future compression
};

class Archive
{
public:
	Archive(const char* file);
	~Archive() noexcept;

	bool ReadFile(const char* file, void* data);
	bool ReadFile(int hash, void* data);
	bool FileExists(const char* file) const noexcept;
	int GetFileSize(const char* file) const noexcept;
	std::unordered_map<uint32_t, ArchiveFile>& GetFiles() noexcept;

private:
	int Hash(const char* file) const noexcept;
	void ReadHeader();

	ArchiveHeader m_header;

	std::ifstream m_stream;
	std::unordered_map<uint32_t, ArchiveFile> m_files;
};

uint32_t jenkins_one_at_a_time_hash(const char* key, size_t length);
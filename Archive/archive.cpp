#include <iostream>
#include <cstring>

#include "archive.hpp"

// Opens an archive from a file
Archive::Archive(const char* file) 
	: m_header{}, m_stream(file, std::ios::binary)
{
	ReadHeader();
}

Archive::~Archive() noexcept
{
	m_stream.close();
}

// Reads a file from the archive, returns whether the file was found
bool Archive::ReadFile(const char* file, void* data)
{
	auto hash = Hash(file);

	return ReadFile(hash, data);
}

bool Archive::ReadFile(int hash, void* data)
{
	if (m_files.find(hash) == m_files.end())
	{
		return false;
	}

	auto info = m_files.find(hash)->second;

	if (info.reserved != -1)
	{
		throw std::runtime_error("compressed files are not supported");
	}

	m_stream.seekg(info.offset);
	m_stream.read(reinterpret_cast<char*>(data), info.size);
	return true;
}

// Gets whether a file exists in the archive
bool Archive::FileExists(const char* file) const noexcept
{
	auto hash = Hash(file);

	return m_files.find(hash) != m_files.end();
}

// Gets the size of a file in the archive
int Archive::GetFileSize(const char* file) const noexcept
{
	auto hash = Hash(file);

	if (m_files.find(hash) == m_files.end())
	{
		return 0;
	}

	return m_files.find(hash)->second.size;
}

// Gets all the files in the archive
std::unordered_map<uint32_t, ArchiveFile>& Archive::GetFiles() noexcept
{
	return m_files;
}

// Gets the hash from a file path
int Archive::Hash(const char* file) const noexcept
{
	// to be replaced by crc32 once I get to statically link Zlib
	return jenkins_one_at_a_time_hash(file, strlen(file));
}

// Reads the archive header into the class
void Archive::ReadHeader()
{
	// read archive version
	uint32_t magic;
	m_stream.read(reinterpret_cast<char*>(&magic), sizeof(uint32_t));
	if (magic != ARCHIVE_MAGIC)
	{
		throw std::runtime_error("Archive does not match ARCHIVE_MAGIC, got " + std::to_string(magic));
	}
	
	// read basic archive header
	m_stream.read(reinterpret_cast<char*>(&m_header), sizeof(ArchiveHeader));
	if (m_header.version != ARCHIVE_VERSION)
	{
		throw std::runtime_error("Archive does not match ARCHIVE_VERSION, code is at " + std::to_string(ARCHIVE_VERSION));
	}

	// read all files
	for (unsigned int i = 0; i < m_header.num_files; i++)
	{
		ArchiveFile file{};
		m_stream.read(reinterpret_cast<char*>(&file), sizeof(ArchiveFile));

		m_files.insert(std::make_pair(file.name, file));
	}
}

// https://en.wikipedia.org/wiki/Jenkins_hash_function#one_at_a_time
uint32_t jenkins_one_at_a_time_hash(const char* key, size_t length) {
	size_t i = 0;
	uint32_t hash = 0;
	while (i != length) {
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}
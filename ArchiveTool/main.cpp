#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <list>

#include "../Archive/archive.hpp"

#define PREFIX_ERROR "\033[91merror:\033[0m "

int PackArchive(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << PREFIX_ERROR << "No arguments specified" << std::endl
			<< "Usage:" << std::endl
			<< "ArchiveTool [archive.dat]" << std::endl
			<< "ArchiveTool pack [input file...]" << std::endl;
		return 1;
	}

	if (strcmp(argv[1], "pack") == 0)
	{
		// archive file
		return PackArchive(argc, argv);
	}

	// unarchive file
	if (!std::filesystem::is_regular_file(argv[1]))
	{
		std::cout << PREFIX_ERROR << argv[1] << ": not found" << std::endl;
		return 1;
	}

	try
	{
		Archive archive(argv[1]);

		std::filesystem::path p{ std::string(argv[1]) };

		// create a folder with the filename (without ext)
		auto folder = p.parent_path() / p.stem();
		std::filesystem::create_directory(folder);

		// loop trough all files in the archive and extract them
		for (auto const& x : archive.GetFiles())
		{
			auto file = x.second;
			char* buffer = new char[file.size];

			archive.ReadFile(file.name, buffer);

			auto name = folder / std::to_string(file.name);

			std::ofstream of(name, std::ios::binary);
			of.write(buffer, file.size);
			of.close();

			delete[] buffer;
		}
	}
	catch (std::exception& e)
	{
		std::cout << PREFIX_ERROR << "Cannot extract archive: " << e.what() << std::endl;
		system("pause");
		return 1;
	}

	return 0;
}

// simple function to write archive file, not included in Archive lib for now
int PackArchive(int argc, char* argv[])
{
	if (argc == 2)
	{
		// totally not based on C compiler
		std::cout << PREFIX_ERROR << "No input files specified" << std::endl;
		return 1;
	}

	// check if all input files exists and push them to list
	std::list<std::string> files;
	for (int i = 2; i < argc; i++)
	{
		if (!std::filesystem::is_regular_file(argv[i]))
		{
			std::cout << PREFIX_ERROR << argv[i] << ": not found" << std::endl;
			return 1;
		}

		files.push_back(std::string(argv[i]));
	}

	std::ofstream of("archive.dat", std::ios::binary);

	// write header
	ArchiveHeader header{ 1, files.size() };
	uint32_t magic = ARCHIVE_MAGIC;
	of.write(reinterpret_cast<char*>(&magic), sizeof(uint32_t));
	of.write(reinterpret_cast<char*>(&header), sizeof(ArchiveHeader));

	// seek over the header
	auto pos = of.tellp();
	of.seekp(files.size() * sizeof(ArchiveFile), std::ios_base::cur);

	// write all files
	std::list<ArchiveFile> file_info;
	
	for (auto const& file : files)
	{
		auto size = std::filesystem::file_size(file);
		auto offset = of.tellp();

		std::ifstream ifs(file, std::ios::binary);

		char* data = new char[static_cast<uint32_t>(size)];
		ifs.read(data, size);
		of.write(data, size);

		delete[] data;

		auto name = file.c_str();
		ArchiveFile info{ jenkins_one_at_a_time_hash(name, strlen(name)), static_cast<uint32_t>(offset), static_cast<uint32_t>(size), 0xFFFFFFFF };
		file_info.push_back(info);

		ifs.close();
	}

	// seek back to header
	of.seekp(pos, std::ios_base::beg);

	// write all  file headers
	for (auto &info : file_info)
	{
		of.write(reinterpret_cast<char*>(&info), sizeof(ArchiveFile));
	}

	of.close();

	return 0;
}
# Archive

A simple archive file format to be used in applications, this repo contains the code for reading archive files and ArchiveTool to pack/unpack archive files.

## Example

```cpp
Archive archive("game.dat");

auto size = archive.GetFileSize("player.obj");
auto data = char[size];

archive.ReadFile("player.obj", data);
```

## Build

There are no project files in the repo only premake5.lua, you can use premake5 to [generate project files](https://github.com/premake/premake-core/wiki/Using-Premake#using-premake-to-generate-project-files) for your toolset.

## ArchiveTool

ArchiveTool can be used to pack/unpack archive files without writing code, usage:
```
ArchiveTool [archive.dat]        -- unpack an archive file
ArchiveTool pack [input file...] -- pack an archive file with all files specified
```

![TVNYuaTZYV](https://user-images.githubusercontent.com/15322107/115471478-59990180-a238-11eb-838d-16b72f865f3b.gif)

## Limitations

* File names are lost after packing (they will be hashed so you can still use file names in your code)

## Future goals

* File compression
* Improved file reading (reading files in chunks, queuing io operations)

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Archive.Managed
{
    public class Archive
    {
        private IntPtr _instance;

        public Archive(string file)
        {
            _instance = InteropMethods.ArchiveOpen(file);
        }

        ~Archive()
        {
            InteropMethods.ArchiveClose(_instance);
            _instance = IntPtr.Zero;
        }

        public bool FileExists(string file)
        {
            return InteropMethods.ArchiveFileExists(_instance, file);
        }

        public int GetFileSize(string file)
        {
            return InteropMethods.ArchiveGetFileSize(_instance, file);
        }

        public IReadOnlyList<ArchiveFile> GetFiles()
        {
            int num = 0;
            var ptr = InteropMethods.ArchiveGetFiles(_instance, ref num);
            var files = new ArchiveFile[num];

            var size = Marshal.SizeOf(typeof(ArchiveFile));
            for(int i = 0; i < num; i++)
            {
                files[i] = Marshal.PtrToStructure<ArchiveFile>(IntPtr.Add(ptr, i * size));
            }

            // free memory allocated by interop
            InteropMethods.Cleanup(ptr);

            return files.ToList();
        }

        public byte[] ReadFile(string file)
        {
            IntPtr buf = IntPtr.Zero;
            var size = InteropMethods.ArchiveReadFile(_instance, file, ref buf);

            if(size == -1)
            {
                // TODO should we use this exception type?
                throw new FileNotFoundException();
            }

            var data = new byte[size];
            Marshal.Copy(buf, data, 0, size);

            InteropMethods.Cleanup(buf);
            return data;
        }
    }
}

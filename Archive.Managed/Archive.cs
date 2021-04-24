using System;
using System.Collections.Generic;
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
                IntPtr ins = new IntPtr(ptr.ToInt64() + i * size);
                files[i] = Marshal.PtrToStructure<ArchiveFile>(ins);
            }

            // TODO cleanup memory located by C interop
            return files.ToList();
        }
    }
}

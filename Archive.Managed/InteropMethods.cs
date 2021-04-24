using System;
using System.Runtime.InteropServices;

namespace Archive.Managed
{
    internal class InteropMethods
    {
        [DllImport("Archive.Interop", EntryPoint = "archive_open")]
        public static extern IntPtr ArchiveOpen(string file);

        [DllImport("Archive.Interop", EntryPoint = "archive_file_exists")]
        public static extern bool ArchiveFileExists(IntPtr archive, string file);

        [DllImport("Archive.Interop", EntryPoint = "archive_get_file_size")]
        public static extern int ArchiveGetFileSize(IntPtr archive, string file);

        [DllImport("Archive.Interop", EntryPoint = "archive_get_files")]
        public static extern IntPtr ArchiveGetFiles(IntPtr archive, ref int num);

        [DllImport("Archive.Interop", EntryPoint = "archive_close")]
        public static extern void ArchiveClose(IntPtr archive);
    }
}

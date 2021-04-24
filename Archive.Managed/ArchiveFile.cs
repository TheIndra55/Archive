using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Archive.Managed
{
    public struct ArchiveFile
    {
        public int name;
        public int offset;
        public int size;
        public int reserved;
    }
}

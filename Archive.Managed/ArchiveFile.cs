namespace Archive.Managed
{
    public struct ArchiveFile
    {
        public int Name;
        public int Offset;
        public int Size;
        internal int Reserved;
    }
}

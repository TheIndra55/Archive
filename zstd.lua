project "zstd"
	kind "StaticLib"
	
	-- taken from build/VS2010/libzstd/libzstd.vcxproj
	files {
		"vendor/zstd/lib/common/pool.c",
		"vendor/zstd/lib/common/debug.c",
		"vendor/zstd/lib/common/threading.c",
		"vendor/zstd/lib/common/entropy_common.c",
		"vendor/zstd/lib/compress/hist.c",
		"vendor/zstd/lib/common/error_private.c",
		"vendor/zstd/lib/common/xxhash.c",
		"vendor/zstd/lib/common/zstd_common.c",
		"vendor/zstd/lib/common/fse_decompress.c",
		"vendor/zstd/lib/compress/fse_compress.c",
		"vendor/zstd/lib/compress/huf_compress.c",
		"vendor/zstd/lib/compress/zstd_compress.c",
		"vendor/zstd/lib/compress/zstd_compress_literals.c",
		"vendor/zstd/lib/compress/zstd_compress_sequences.c",
		"vendor/zstd/lib/compress/zstd_compress_superblock.c",
		"vendor/zstd/lib/compress/zstd_fast.c",
		"vendor/zstd/lib/compress/zstd_double_fast.c",
		"vendor/zstd/lib/compress/zstd_lazy.c",
		"vendor/zstd/lib/compress/zstd_opt.c",
		"vendor/zstd/lib/compress/zstd_ldm.c",
		"vendor/zstd/lib/compress/zstdmt_compress.c",
		"vendor/zstd/lib/decompress/huf_decompress.c",
		"vendor/zstd/lib/decompress/zstd_decompress.c",
		"vendor/zstd/lib/decompress/zstd_decompress_block.c",
		"vendor/zstd/lib/decompress/zstd_ddict.c",
		"vendor/zstd/lib/dictBuilder/cover.c",
		"vendor/zstd/lib/dictBuilder/fastcover.c",
		"vendor/zstd/lib/dictBuilder/divsufsort.c",
		"vendor/zstd/lib/dictBuilder/zdict.c",	
	}
	
    filter "configurations:Debug"
        defines { "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        symbols "On"
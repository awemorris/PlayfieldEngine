@echo off

echo Making target directories...
rd /s /q libroot > NUL 2>&1
mkdir libroot
mkdir libroot\include
mkdir libroot\lib

echo Building zlib...
cd zlib
prospero-clang.exe -c -O2 adler32.c
prospero-clang.exe -c -O2 infback.c
prospero-clang.exe -c -O2 trees.c
prospero-clang.exe -c -O2 compress.c
prospero-clang.exe -c -O2 inffast.c
prospero-clang.exe -c -O2 uncompr.c
prospero-clang.exe -c -O2 crc32.c
prospero-clang.exe -c -O2 inflate.c
prospero-clang.exe -c -O2 deflate.c
prospero-clang.exe -c -O2 inftrees.c
prospero-clang.exe -c -O2 zutil.c
prospero-llvm-ar.exe rcs libz.a adler32.o infback.o trees.o compress.o inffast.o uncompr.o crc32.o inflate.o deflate.o inftrees.o zutil.o
copy /Y zlib.h ..\libroot\include\
copy /Y zconf.h ..\libroot\include\
copy /Y libz.a ..\libroot\lib\
cd ..

echo Building libpng...
cd libpng
copy scripts\pnglibconf.h.prebuilt pnglibconf.h
prospero-clang.exe -c -O2 -I../libroot/include pngget.c
prospero-clang.exe -c -O2 -I../libroot/include pngread.c
prospero-clang.exe -c -O2 -I../libroot/include pngrutil.c
prospero-clang.exe -c -O2 -I../libroot/include pngtrans.c
prospero-clang.exe -c -O2 -I../libroot/include pngwtran.c
prospero-clang.exe -c -O2 -I../libroot/include png.c
prospero-clang.exe -c -O2 -I../libroot/include pngmem.c
prospero-clang.exe -c -O2 -I../libroot/include pngrio.c
prospero-clang.exe -c -O2 -I../libroot/include pngset.c
prospero-clang.exe -c -O2 -I../libroot/include pngwio.c
prospero-clang.exe -c -O2 -I../libroot/include pngwutil.c
prospero-clang.exe -c -O2 -I../libroot/include pngerror.c
prospero-clang.exe -c -O2 -I../libroot/include pngpread.c
prospero-clang.exe -c -O2 -I../libroot/include pngrtran.c
prospero-clang.exe -c -O2 -I../libroot/include pngwrite.c
prospero-llvm-ar.exe rcs libpng.a pngget.obj pngread.obj pngrutil.obj pngtrans.obj pngwtran.obj png.obj pngmem.obj pngrio.obj pngset.obj pngwio.obj pngwutil.obj pngerror.obj pngpread.obj pngrtran.obj pngwrite.obj
mkdir ..\libroot\include\png
copy /Y *.h ..\libroot\include\png\
copy libpng.a ..\libroot\lib\
cd ..

echo Building jpeg...
cd jpeg
copy jconfig.txt jconfig.h
prospero-clang.exe -c -O2 cdjpeg.c
prospero-clang.exe -c -O2 jaricom.c
prospero-clang.exe -c -O2 jcapimin.c
prospero-clang.exe -c -O2 jcapistd.c
prospero-clang.exe -c -O2 jcarith.c
prospero-clang.exe -c -O2 jccoefct.c
prospero-clang.exe -c -O2 jccolor.c
prospero-clang.exe -c -O2 jcdctmgr.c
prospero-clang.exe -c -O2 jchuff.c
prospero-clang.exe -c -O2 jcinit.c
prospero-clang.exe -c -O2 jcmainct.c
prospero-clang.exe -c -O2 jcmarker.c
prospero-clang.exe -c -O2 jcmaster.c
prospero-clang.exe -c -O2 jcomapi.c
prospero-clang.exe -c -O2 jcparam.c
prospero-clang.exe -c -O2 jcprepct.c
prospero-clang.exe -c -O2 jcsample.c
prospero-clang.exe -c -O2 jctrans.c
prospero-clang.exe -c -O2 jdapimin.c
prospero-clang.exe -c -O2 jdapistd.c
prospero-clang.exe -c -O2 jdarith.c
prospero-clang.exe -c -O2 jdatadst.c
prospero-clang.exe -c -O2 jdatasrc.c
prospero-clang.exe -c -O2 jdcoefct.c
prospero-clang.exe -c -O2 jdcolor.c
prospero-clang.exe -c -O2 jddctmgr.c
prospero-clang.exe -c -O2 jdhuff.c
prospero-clang.exe -c -O2 jdinput.c
prospero-clang.exe -c -O2 jdmainct.c
prospero-clang.exe -c -O2 jdmarker.c
prospero-clang.exe -c -O2 jdmaster.c
prospero-clang.exe -c -O2 jdmerge.c
prospero-clang.exe -c -O2 jdpostct.c
prospero-clang.exe -c -O2 jdsample.c
prospero-clang.exe -c -O2 jdtrans.c
prospero-clang.exe -c -O2 jerror.c
prospero-clang.exe -c -O2 jfdctflt.c
prospero-clang.exe -c -O2 jfdctfst.c
prospero-clang.exe -c -O2 jfdctint.c
prospero-clang.exe -c -O2 jidctflt.c
prospero-clang.exe -c -O2 jidctfst.c
prospero-clang.exe -c -O2 jidctint.c
prospero-clang.exe -c -O2 jmemansi.c
prospero-clang.exe -c -O2 jmemmgr.c
prospero-clang.exe -c -O2 jquant1.c
prospero-clang.exe -c -O2 jquant2.c
prospero-clang.exe -c -O2 jutils.c
prospero-clang.exe -c -O2 transupp.c
prospero-llvm-ar.exe rcs libjpeg.a cdjpeg.obj jaricom.obj jcapimin.obj jcapistd.obj jcarith.obj jccoefct.obj jccolor.obj jcdctmgr.obj jchuff.obj jcinit.obj jcmainct.obj jcmarker.obj jcmaster.obj jcomapi.obj jcparam.obj jcprepct.obj jcsample.obj jctrans.obj jdapimin.obj jdapistd.obj jdarith.obj jdatadst.obj jdatasrc.obj jdcoefct.obj jdcolor.obj jddctmgr.obj jdhuff.obj jdinput.obj jdmainct.obj jdmarker.obj jdmaster.obj jdmerge.obj jdpostct.obj jdsample.obj jdtrans.obj jerror.obj jfdctflt.obj jfdctfst.obj jfdctint.obj jidctflt.obj jidctfst.obj jidctint.obj jmemansi.obj jmemmgr.obj jquant1.obj jquant2.obj jutils.obj transupp.obj
mkdir ..\libroot\include\jpeg
copy /Y *.h ..\libroot\include\jpeg\
copy libjpeg.a ..\libroot\lib\
cd ..

echo Building bzip2...
cd bzip2
prospero-clang.exe -c -O2 blocksort.c
prospero-clang.exe -c -O2 compress.c
prospero-clang.exe -c -O2 decompress.c
prospero-clang.exe -c -O2 huffman.c
prospero-clang.exe -c -O2 randtable.c
prospero-clang.exe -c -O2 bzlib.c
prospero-clang.exe -c -O2 crctable.c
prospero-llvm-ar.exe rcs libbz2.a blocksort.obj compress.obj decompress.obj huffman.obj randtable.obj bzlib.obj crctable.obj
copy /Y bzlib.h ..\libroot\include\
copy libbz2.lib ..\libroot\lib\
cd ..

echo Building libwebp...
cd libwebp
prospero-clang.exe -c -O2 -I./ src/dec/alpha_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/buffer_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/frame_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/idec_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/io_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/quant_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/tree_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/vp8_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/vp8l_dec.c
prospero-clang.exe -c -O2 -I./ src/dec/webp_dec.c
prospero-clang.exe -c -O2 -I./ src/demux/anim_decode.c
prospero-clang.exe -c -O2 -I./ src/demux/demux.c
prospero-clang.exe -c -O2 -I./ src/dsp/alpha_processing.c
prospero-clang.exe -c -O2 -I./ src/dsp/alpha_processing_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/alpha_processing_sse41.c
prospero-clang.exe -c -O2 -I./ src/dsp/alpha_processing_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/cost.c
prospero-clang.exe -c -O2 -I./ src/dsp/cost_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/cost_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/cpu.c
prospero-clang.exe -c -O2 -I./ src/dsp/dec.c
prospero-clang.exe -c -O2 -I./ src/dsp/dec_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/dec_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/dec_sse41.c
prospero-clang.exe -c -O2 -I./ src/dsp/dec_clip_tables.c
prospero-clang.exe -c -O2 -I./ src/dsp/enc.c
prospero-clang.exe -c -O2 -I./ src/dsp/filters.c
prospero-clang.exe -c -O2 -I./ src/dsp/filters_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/filters_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_sse41.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_enc.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_enc_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_enc_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/lossless_enc_sse41.c
prospero-clang.exe -c -O2 -I./ src/dsp/rescaler.c
prospero-clang.exe -c -O2 -I./ src/dsp/rescaler_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/rescaler_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/ssim.c
prospero-clang.exe -c -O2 -I./ src/dsp/ssim_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/upsampling.c
prospero-clang.exe -c -O2 -I./ src/dsp/upsampling_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/upsampling_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/upsampling_sse41.c
prospero-clang.exe -c -O2 -I./ src/dsp/yuv.c
prospero-clang.exe -c -O2 -I./ src/dsp/yuv_neon.c
prospero-clang.exe -c -O2 -I./ src/dsp/yuv_sse2.c
prospero-clang.exe -c -O2 -I./ src/dsp/yuv_sse41.c
prospero-clang.exe -c -O2 -I./ src/enc/alpha_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/analysis_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/backward_references_cost_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/backward_references_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/config_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/cost_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/filter_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/frame_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/histogram_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/iterator_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/near_lossless_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/picture_csp_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/picture_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/picture_psnr_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/picture_rescale_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/picture_tools_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/predictor_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/quant_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/syntax_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/token_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/tree_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/vp8l_enc.c
prospero-clang.exe -c -O2 -I./ src/enc/webp_enc.c
prospero-clang.exe -c -O2 -I./ src/mux/anim_encode.c
prospero-clang.exe -c -O2 -I./ src/mux/muxedit.c
prospero-clang.exe -c -O2 -I./ src/mux/muxinternal.c
prospero-clang.exe -c -O2 -I./ src/mux/muxread.c
prospero-clang.exe -c -O2 -I./ src/utils/bit_reader_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/bit_writer_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/color_cache_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/filters_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/huffman_encode_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/huffman_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/quant_levels_dec_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/quant_levels_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/random_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/rescaler_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/thread_utils.c
prospero-clang.exe -c -O2 -I./ src/utils/utils.c
prospero-llvm-ar.exe rcs libwebp.a alpha_dec.obj buffer_dec.obj frame_dec.obj idec_dec.obj io_dec.obj quant_dec.obj tree_dec.obj vp8_dec.obj vp8l_dec.obj webp_dec.obj anim_decode.obj demux.obj alpha_processing.obj cost.obj cost_neon.obj cost_sse2.obj cpu.obj dec.obj dec_neon.obj dec_sse2.obj dec_sse41.obj dec_clip_tables.obj enc.obj filters.obj filters_neon.obj filters_sse2.obj lossless.obj lossless_neon.obj lossless_sse2.obj lossless_sse41.obj lossless_enc.obj lossless_enc_neon.obj lossless_enc_sse2.obj lossless_enc_sse41.obj rescaler.obj rescaler_neon.obj rescaler_sse2.obj ssim.obj ssim_sse2.obj upsampling.obj upsampling_neon.obj upsampling_sse2.obj upsampling_sse41.obj yuv.obj yuv_neon.obj yuv_sse2.obj yuv_sse41.obj alpha_enc.obj analysis_enc.obj backward_references_cost_enc.obj backward_references_enc.obj config_enc.obj cost_enc.obj filter_enc.obj frame_enc.obj histogram_enc.obj iterator_enc.obj near_lossless_enc.obj picture_csp_enc.obj picture_enc.obj picture_psnr_enc.obj picture_rescale_enc.obj picture_tools_enc.obj predictor_enc.obj quant_enc.obj syntax_enc.obj token_enc.obj tree_enc.obj vp8l_enc.obj webp_enc.obj anim_encode.obj muxedit.obj muxinternal.obj muxread.obj bit_reader_utils.obj bit_writer_utils.obj color_cache_utils.obj filters_utils.obj huffman_encode_utils.obj huffman_utils.obj quant_levels_dec_utils.obj quant_levels_utils.obj random_utils.obj rescaler_utils.obj thread_utils.obj utils.obj alpha_processing_sse2.obj alpha_processing_sse41.obj alpha_processing_neon.obj
mkdir ..\libroot\include\webp
copy /Y src\webp\* ..\libroot\include\webp\
copy libwebp.a ..\libroot\lib\
cd ..

echo Building libogg...
cd libogg
prospero-clang.exe -c -O2 -I./include src/bitwise.c
prospero-clang.exe -c -O2 -I./include src/framing.c
prospero-llvm-ar.exe rcs libogg.a bitwise.obj framing.obj
mkdir ..\libroot\include\ogg
xcopy /Y include\ogg ..\libroot\include\ogg
copy libogg.a ..\libroot\lib\
cd ..

echo Building libvorbis...
cd libvorbis
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/analysis.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/bitrate.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/block.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/codebook.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/envelope.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/floor0.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/floor1.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/info.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/lookup.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/lpc.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/lsp.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/mapping0.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/mdct.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/psy.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/registry.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/res0.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/sharedbook.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/smallft.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/synthesis.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/vorbisenc.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/vorbisfile.c
prospero-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/window.c
prospero-llvm-ar.exe rcs libvorbis.a analysis.obj bitrate.obj block.obj codebook.obj envelope.obj floor0.obj floor1.obj info.obj lookup.obj lpc.obj lsp.obj mapping0.obj mdct.obj psy.obj registry.obj res0.obj sharedbook.obj smallft.obj synthesis.obj vorbisenc.obj window.obj
prospero-llvm-ar.exe rcs libvorbisfile.a vorbisfile.obj
mkdir ..\libroot\include\vorbis
xcopy /Y include\vorbis ..\libroot\include\vorbis
copy libvorbis.a ..\libroot\lib\
copy libvorbisfile.a ..\libroot\lib\
cd ..

echo Building freetype...
cd freetype
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftadvanc.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbase.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbbox.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbdf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbitmap.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftcalc.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftcid.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftcolor.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftdbgmem.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftdebug.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fterrors.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftfntfmt.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftfstype.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftgasp.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftgloadr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftglyph.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftgxval.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fthash.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftinit.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftlcdfil.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftmac.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftmm.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftotval.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftoutln.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftpatent.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftpfr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftpsprop.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftrfork.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftsnames.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftstream.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftstroke.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftsynth.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftsystem.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fttrigon.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fttype1.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftutil.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftwinfnt.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/md5.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bdf/bdf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bdf/bdfdrivr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bdf/bdflib.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bzip2/ftbzip2.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcache.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcbasic.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftccache.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftccmap.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcglyph.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcimage.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcmanag.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcmru.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcsbits.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cff.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffcmap.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffdrivr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffgload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffparse.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidgload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidparse.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidriver.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/type1cid.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvalid.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvbase.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvcommn.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvgdef.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvgpos.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvgsub.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvjstf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvmath.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvmod.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrcmap.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrdrivr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrgload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrsbit.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/afmparse.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/cffdecode.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psarrst.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psaux.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psauxmod.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psblues.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psconv.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/pserror.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psfont.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psft.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/pshints.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psintrp.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psread.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psstack.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/t1decode.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/t1cmap.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshalgo.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshglob.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshinter.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshmod.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshrec.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psnames/psmodule.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psnames/psnames.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/raster/ftraster.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftbsdf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftsdf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftsdfcommon.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftsdfrend.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/pngshim.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/sfdriver.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/sfobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttbdf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttcmap.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttcolr.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttcpal.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttkern.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttmtx.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttpost.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttsbit.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttsvg.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/sfwoff.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/smooth/ftgrays.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/smooth/ftsmooth.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/svg/ftsvg.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/truetype.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttdriver.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttgload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttgxvar.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttinterp.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttobjs.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttpload.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/winfonts/winfnt.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/adler32.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/crc32.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/ftgzip.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/inffast.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/inftrees.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/zutil.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/lzw/ftlzw.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pcf/pcf.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/autofit/autofit.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/type1/type1.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/type42/type42.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/raster/raster.c
prospero-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/svg/svg.c
prospero-llvm-ar.exe rcs libfreetype.a ftadvanc.obj ftbase.obj ftbbox.obj ftbdf.obj ftbitmap.obj ftcalc.obj ftcid.obj ftcolor.obj ftdbgmem.obj ftdebug.obj fterrors.obj ftfntfmt.obj ftfstype.obj ftgasp.obj ftgloadr.obj ftglyph.obj ftgxval.obj fthash.obj ftinit.obj ftlcdfil.obj ftmac.obj ftmm.obj ftotval.obj ftoutln.obj ftpatent.obj ftpfr.obj ftpsprop.obj ftrfork.obj ftsnames.obj ftstream.obj ftstroke.obj ftsynth.obj ftsystem.obj fttrigon.obj fttype1.obj ftutil.obj ftwinfnt.obj md5.obj bdfdrivr.obj bdflib.obj ftbzip2.obj ftcbasic.obj ftccache.obj ftccmap.obj ftcglyph.obj ftcimage.obj ftcmanag.obj ftcmru.obj ftcsbits.obj cffcmap.obj cffdrivr.obj cffgload.obj cffload.obj cffobjs.obj cffparse.obj cidgload.obj cidload.obj cidobjs.obj cidparse.obj type1cid.obj otvalid.obj otvbase.obj otvcommn.obj otvgdef.obj otvgpos.obj otvgsub.obj otvjstf.obj otvmath.obj pfrcmap.obj pfrdrivr.obj pfrgload.obj pfrload.obj pfrobjs.obj pfrsbit.obj afmparse.obj cffdecode.obj psarrst.obj psauxmod.obj psblues.obj psconv.obj pserror.obj psfont.obj psft.obj pshints.obj psintrp.obj psobjs.obj psread.obj psstack.obj pshalgo.obj pshglob.obj pshmod.obj pshrec.obj psmodule.obj t1decode.obj t1cmap.obj ftraster.obj ftbsdf.obj ftsdf.obj ftsdfcommon.obj ftsdfrend.obj pngshim.obj sfdriver.obj sfobjs.obj ttbdf.obj ttcmap.obj ttcolr.obj ttcpal.obj ttkern.obj ttload.obj ttmtx.obj ttpost.obj ttsbit.obj ttsvg.obj sfwoff.obj ftgrays.obj ftsmooth.obj ftsvg.obj ttdriver.obj ttgload.obj ttgxvar.obj ttinterp.obj ttobjs.obj ttpload.obj winfnt.obj adler32.obj crc32.obj ftgzip.obj inffast.obj inftrees.obj zutil.obj ftlzw.obj pcf.obj autofit.obj type1.obj type42.obj raster.obj
mkdir ..\libroot\include\freetype
mkdir ..\libroot\include\freetype\config
xcopy /Y include\freetype ..\libroot\include\freetype
xcopy /Y include\freetype\config ..\libroot\include\freetype\config
copy /Y include\ft2build.h ..\libroot\include\
copy libfreetype.a ..\libroot\lib\
cd ..

echo Building Noct2D...
cd objs
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -Isrc src/platform/halwrap.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -Isrc -I./libroot/include src/platform/glyph.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -Isrc -I./libroot/include src/platform/wave.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -Isrc -I./libroot/include src/platform/image.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -DYY_NO_UNISTD_H -Isrc src/lang/lexer.yy.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/parser.tab.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/ast.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/hir.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/lir.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/runtime.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/interpreter.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/intrinsics.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/lang/jit-common.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/noctvm/main.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/noctvm/api.c
prospero-clang.exe -c -O2 -DUNICODE -D_UNICODE -Isrc src/noctvm/vm.c
cd ..

echo Merging libraries...
cd objs
prospero-clang.exe x ../libroot/lib/zlib.lib
prospero-clang.exe x ../libroot/lib/libpng.lib
prospero-clang.exe x ../libroot/lib/jpeg.lib
prospero-clang.exe x ../libroot/lib/libwebp.lib
prospero-clang.exe x ../libroot/lib/libogg.lib
prospero-clang.exe x ../libroot/lib/libvorbisfile.lib
prospero-clang.exe x ../libroot/lib/libvorbis.lib
prospero-clang.exe x ../libroot/lib/freetype.lib
cd ..
prospero-llvm-ar.exe rcs libnoctvm.a objs/*.o

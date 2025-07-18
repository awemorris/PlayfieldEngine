@echo off

echo Making target directories...
rd /s /q libroot > NUL 2>&1
mkdir libroot
mkdir libroot\include
mkdir libroot\lib

echo Building zlib...
cd zlib
nx-clang.exe -c -O2 adler32.c
nx-clang.exe -c -O2 infback.c
nx-clang.exe -c -O2 trees.c
nx-clang.exe -c -O2 compress.c
nx-clang.exe -c -O2 inffast.c
nx-clang.exe -c -O2 uncompr.c
nx-clang.exe -c -O2 crc32.c
nx-clang.exe -c -O2 inflate.c
nx-clang.exe -c -O2 deflate.c
nx-clang.exe -c -O2 inftrees.c
nx-clang.exe -c -O2 zutil.c
nx-ar.exe rcs libz.a adler32.o infback.o trees.o compress.o inffast.o uncompr.o crc32.o inflate.o deflate.o inftrees.o zutil.o
copy /Y zlib.h ..\libroot\include\
copy /Y zconf.h ..\libroot\include\
copy /Y libz.a ..\libroot\lib\
cd ..

echo Building libpng...
cd libpng
copy scripts\pnglibconf.h.prebuilt pnglibconf.h
nx-clang.exe -c -O2 -I../libroot/include pngget.c
nx-clang.exe -c -O2 -I../libroot/include pngread.c
nx-clang.exe -c -O2 -I../libroot/include pngrutil.c
nx-clang.exe -c -O2 -I../libroot/include pngtrans.c
nx-clang.exe -c -O2 -I../libroot/include pngwtran.c
nx-clang.exe -c -O2 -I../libroot/include png.c
nx-clang.exe -c -O2 -I../libroot/include pngmem.c
nx-clang.exe -c -O2 -I../libroot/include pngrio.c
nx-clang.exe -c -O2 -I../libroot/include pngset.c
nx-clang.exe -c -O2 -I../libroot/include pngwio.c
nx-clang.exe -c -O2 -I../libroot/include pngwutil.c
nx-clang.exe -c -O2 -I../libroot/include pngerror.c
nx-clang.exe -c -O2 -I../libroot/include pngpread.c
nx-clang.exe -c -O2 -I../libroot/include pngrtran.c
nx-clang.exe -c -O2 -I../libroot/include pngwrite.c
nx-ar.exe rcs libpng.a pngget.obj pngread.obj pngrutil.obj pngtrans.obj pngwtran.obj png.obj pngmem.obj pngrio.obj pngset.obj pngwio.obj pngwutil.obj pngerror.obj pngpread.obj pngrtran.obj pngwrite.obj
mkdir ..\libroot\include\png
copy /Y *.h ..\libroot\include\png\
copy libpng.a ..\libroot\lib\
cd ..

echo Building jpeg...
cd jpeg
copy jconfig.txt jconfig.h
nx-clang.exe -c -O2 cdjpeg.c
nx-clang.exe -c -O2 jaricom.c
nx-clang.exe -c -O2 jcapimin.c
nx-clang.exe -c -O2 jcapistd.c
nx-clang.exe -c -O2 jcarith.c
nx-clang.exe -c -O2 jccoefct.c
nx-clang.exe -c -O2 jccolor.c
nx-clang.exe -c -O2 jcdctmgr.c
nx-clang.exe -c -O2 jchuff.c
nx-clang.exe -c -O2 jcinit.c
nx-clang.exe -c -O2 jcmainct.c
nx-clang.exe -c -O2 jcmarker.c
nx-clang.exe -c -O2 jcmaster.c
nx-clang.exe -c -O2 jcomapi.c
nx-clang.exe -c -O2 jcparam.c
nx-clang.exe -c -O2 jcprepct.c
nx-clang.exe -c -O2 jcsample.c
nx-clang.exe -c -O2 jctrans.c
nx-clang.exe -c -O2 jdapimin.c
nx-clang.exe -c -O2 jdapistd.c
nx-clang.exe -c -O2 jdarith.c
nx-clang.exe -c -O2 jdatadst.c
nx-clang.exe -c -O2 jdatasrc.c
nx-clang.exe -c -O2 jdcoefct.c
nx-clang.exe -c -O2 jdcolor.c
nx-clang.exe -c -O2 jddctmgr.c
nx-clang.exe -c -O2 jdhuff.c
nx-clang.exe -c -O2 jdinput.c
nx-clang.exe -c -O2 jdmainct.c
nx-clang.exe -c -O2 jdmarker.c
nx-clang.exe -c -O2 jdmaster.c
nx-clang.exe -c -O2 jdmerge.c
nx-clang.exe -c -O2 jdpostct.c
nx-clang.exe -c -O2 jdsample.c
nx-clang.exe -c -O2 jdtrans.c
nx-clang.exe -c -O2 jerror.c
nx-clang.exe -c -O2 jfdctflt.c
nx-clang.exe -c -O2 jfdctfst.c
nx-clang.exe -c -O2 jfdctint.c
nx-clang.exe -c -O2 jidctflt.c
nx-clang.exe -c -O2 jidctfst.c
nx-clang.exe -c -O2 jidctint.c
nx-clang.exe -c -O2 jmemansi.c
nx-clang.exe -c -O2 jmemmgr.c
nx-clang.exe -c -O2 jquant1.c
nx-clang.exe -c -O2 jquant2.c
nx-clang.exe -c -O2 jutils.c
nx-clang.exe -c -O2 transupp.c
nx-ar.exe rcs libjpeg.a cdjpeg.obj jaricom.obj jcapimin.obj jcapistd.obj jcarith.obj jccoefct.obj jccolor.obj jcdctmgr.obj jchuff.obj jcinit.obj jcmainct.obj jcmarker.obj jcmaster.obj jcomapi.obj jcparam.obj jcprepct.obj jcsample.obj jctrans.obj jdapimin.obj jdapistd.obj jdarith.obj jdatadst.obj jdatasrc.obj jdcoefct.obj jdcolor.obj jddctmgr.obj jdhuff.obj jdinput.obj jdmainct.obj jdmarker.obj jdmaster.obj jdmerge.obj jdpostct.obj jdsample.obj jdtrans.obj jerror.obj jfdctflt.obj jfdctfst.obj jfdctint.obj jidctflt.obj jidctfst.obj jidctint.obj jmemansi.obj jmemmgr.obj jquant1.obj jquant2.obj jutils.obj transupp.obj
mkdir ..\libroot\include\jpeg
copy /Y *.h ..\libroot\include\jpeg\
copy libjpeg.a ..\libroot\lib\
cd ..

echo Building bzip2...
cd bzip2
nx-clang.exe -c -O2 blocksort.c
nx-clang.exe -c -O2 compress.c
nx-clang.exe -c -O2 decompress.c
nx-clang.exe -c -O2 huffman.c
nx-clang.exe -c -O2 randtable.c
nx-clang.exe -c -O2 bzlib.c
nx-clang.exe -c -O2 crctable.c
nx-ar.exe rcs libbz2.a blocksort.obj compress.obj decompress.obj huffman.obj randtable.obj bzlib.obj crctable.obj
copy /Y bzlib.h ..\libroot\include\
copy libbz2.lib ..\libroot\lib\
cd ..

echo Building libwebp...
cd libwebp
nx-clang.exe -c -O2 -I./ src/dec/alpha_dec.c
nx-clang.exe -c -O2 -I./ src/dec/buffer_dec.c
nx-clang.exe -c -O2 -I./ src/dec/frame_dec.c
nx-clang.exe -c -O2 -I./ src/dec/idec_dec.c
nx-clang.exe -c -O2 -I./ src/dec/io_dec.c
nx-clang.exe -c -O2 -I./ src/dec/quant_dec.c
nx-clang.exe -c -O2 -I./ src/dec/tree_dec.c
nx-clang.exe -c -O2 -I./ src/dec/vp8_dec.c
nx-clang.exe -c -O2 -I./ src/dec/vp8l_dec.c
nx-clang.exe -c -O2 -I./ src/dec/webp_dec.c
nx-clang.exe -c -O2 -I./ src/demux/anim_decode.c
nx-clang.exe -c -O2 -I./ src/demux/demux.c
nx-clang.exe -c -O2 -I./ src/dsp/alpha_processing.c
nx-clang.exe -c -O2 -I./ src/dsp/alpha_processing_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/alpha_processing_sse41.c
nx-clang.exe -c -O2 -I./ src/dsp/alpha_processing_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/cost.c
nx-clang.exe -c -O2 -I./ src/dsp/cost_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/cost_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/cpu.c
nx-clang.exe -c -O2 -I./ src/dsp/dec.c
nx-clang.exe -c -O2 -I./ src/dsp/dec_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/dec_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/dec_sse41.c
nx-clang.exe -c -O2 -I./ src/dsp/dec_clip_tables.c
nx-clang.exe -c -O2 -I./ src/dsp/enc.c
nx-clang.exe -c -O2 -I./ src/dsp/filters.c
nx-clang.exe -c -O2 -I./ src/dsp/filters_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/filters_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_sse41.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_enc.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_enc_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_enc_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/lossless_enc_sse41.c
nx-clang.exe -c -O2 -I./ src/dsp/rescaler.c
nx-clang.exe -c -O2 -I./ src/dsp/rescaler_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/rescaler_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/ssim.c
nx-clang.exe -c -O2 -I./ src/dsp/ssim_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/upsampling.c
nx-clang.exe -c -O2 -I./ src/dsp/upsampling_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/upsampling_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/upsampling_sse41.c
nx-clang.exe -c -O2 -I./ src/dsp/yuv.c
nx-clang.exe -c -O2 -I./ src/dsp/yuv_neon.c
nx-clang.exe -c -O2 -I./ src/dsp/yuv_sse2.c
nx-clang.exe -c -O2 -I./ src/dsp/yuv_sse41.c
nx-clang.exe -c -O2 -I./ src/enc/alpha_enc.c
nx-clang.exe -c -O2 -I./ src/enc/analysis_enc.c
nx-clang.exe -c -O2 -I./ src/enc/backward_references_cost_enc.c
nx-clang.exe -c -O2 -I./ src/enc/backward_references_enc.c
nx-clang.exe -c -O2 -I./ src/enc/config_enc.c
nx-clang.exe -c -O2 -I./ src/enc/cost_enc.c
nx-clang.exe -c -O2 -I./ src/enc/filter_enc.c
nx-clang.exe -c -O2 -I./ src/enc/frame_enc.c
nx-clang.exe -c -O2 -I./ src/enc/histogram_enc.c
nx-clang.exe -c -O2 -I./ src/enc/iterator_enc.c
nx-clang.exe -c -O2 -I./ src/enc/near_lossless_enc.c
nx-clang.exe -c -O2 -I./ src/enc/picture_csp_enc.c
nx-clang.exe -c -O2 -I./ src/enc/picture_enc.c
nx-clang.exe -c -O2 -I./ src/enc/picture_psnr_enc.c
nx-clang.exe -c -O2 -I./ src/enc/picture_rescale_enc.c
nx-clang.exe -c -O2 -I./ src/enc/picture_tools_enc.c
nx-clang.exe -c -O2 -I./ src/enc/predictor_enc.c
nx-clang.exe -c -O2 -I./ src/enc/quant_enc.c
nx-clang.exe -c -O2 -I./ src/enc/syntax_enc.c
nx-clang.exe -c -O2 -I./ src/enc/token_enc.c
nx-clang.exe -c -O2 -I./ src/enc/tree_enc.c
nx-clang.exe -c -O2 -I./ src/enc/vp8l_enc.c
nx-clang.exe -c -O2 -I./ src/enc/webp_enc.c
nx-clang.exe -c -O2 -I./ src/mux/anim_encode.c
nx-clang.exe -c -O2 -I./ src/mux/muxedit.c
nx-clang.exe -c -O2 -I./ src/mux/muxinternal.c
nx-clang.exe -c -O2 -I./ src/mux/muxread.c
nx-clang.exe -c -O2 -I./ src/utils/bit_reader_utils.c
nx-clang.exe -c -O2 -I./ src/utils/bit_writer_utils.c
nx-clang.exe -c -O2 -I./ src/utils/color_cache_utils.c
nx-clang.exe -c -O2 -I./ src/utils/filters_utils.c
nx-clang.exe -c -O2 -I./ src/utils/huffman_encode_utils.c
nx-clang.exe -c -O2 -I./ src/utils/huffman_utils.c
nx-clang.exe -c -O2 -I./ src/utils/quant_levels_dec_utils.c
nx-clang.exe -c -O2 -I./ src/utils/quant_levels_utils.c
nx-clang.exe -c -O2 -I./ src/utils/random_utils.c
nx-clang.exe -c -O2 -I./ src/utils/rescaler_utils.c
nx-clang.exe -c -O2 -I./ src/utils/thread_utils.c
nx-clang.exe -c -O2 -I./ src/utils/utils.c
nx-ar.exe rcs libwebp.a alpha_dec.obj buffer_dec.obj frame_dec.obj idec_dec.obj io_dec.obj quant_dec.obj tree_dec.obj vp8_dec.obj vp8l_dec.obj webp_dec.obj anim_decode.obj demux.obj alpha_processing.obj cost.obj cost_neon.obj cost_sse2.obj cpu.obj dec.obj dec_neon.obj dec_sse2.obj dec_sse41.obj dec_clip_tables.obj enc.obj filters.obj filters_neon.obj filters_sse2.obj lossless.obj lossless_neon.obj lossless_sse2.obj lossless_sse41.obj lossless_enc.obj lossless_enc_neon.obj lossless_enc_sse2.obj lossless_enc_sse41.obj rescaler.obj rescaler_neon.obj rescaler_sse2.obj ssim.obj ssim_sse2.obj upsampling.obj upsampling_neon.obj upsampling_sse2.obj upsampling_sse41.obj yuv.obj yuv_neon.obj yuv_sse2.obj yuv_sse41.obj alpha_enc.obj analysis_enc.obj backward_references_cost_enc.obj backward_references_enc.obj config_enc.obj cost_enc.obj filter_enc.obj frame_enc.obj histogram_enc.obj iterator_enc.obj near_lossless_enc.obj picture_csp_enc.obj picture_enc.obj picture_psnr_enc.obj picture_rescale_enc.obj picture_tools_enc.obj predictor_enc.obj quant_enc.obj syntax_enc.obj token_enc.obj tree_enc.obj vp8l_enc.obj webp_enc.obj anim_encode.obj muxedit.obj muxinternal.obj muxread.obj bit_reader_utils.obj bit_writer_utils.obj color_cache_utils.obj filters_utils.obj huffman_encode_utils.obj huffman_utils.obj quant_levels_dec_utils.obj quant_levels_utils.obj random_utils.obj rescaler_utils.obj thread_utils.obj utils.obj alpha_processing_sse2.obj alpha_processing_sse41.obj alpha_processing_neon.obj
mkdir ..\libroot\include\webp
copy /Y src\webp\* ..\libroot\include\webp\
copy libwebp.a ..\libroot\lib\
cd ..

echo Building libogg...
cd libogg
nx-clang.exe -c -O2 -I./include src/bitwise.c
nx-clang.exe -c -O2 -I./include src/framing.c
nx-ar.exe rcs libogg.a bitwise.obj framing.obj
mkdir ..\libroot\include\ogg
xcopy /Y include\ogg ..\libroot\include\ogg
copy libogg.a ..\libroot\lib\
cd ..

echo Building libvorbis...
cd libvorbis
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/analysis.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/bitrate.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/block.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/codebook.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/envelope.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/floor0.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/floor1.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/info.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/lookup.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/lpc.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/lsp.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/mapping0.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/mdct.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/psy.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/registry.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/res0.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/sharedbook.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/smallft.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/synthesis.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/vorbisenc.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/vorbisfile.c
nx-clang.exe -c -O2 -I./include -I./lib -I../libroot/include lib/window.c
nx-ar.exe rcs libvorbis.a analysis.obj bitrate.obj block.obj codebook.obj envelope.obj floor0.obj floor1.obj info.obj lookup.obj lpc.obj lsp.obj mapping0.obj mdct.obj psy.obj registry.obj res0.obj sharedbook.obj smallft.obj synthesis.obj vorbisenc.obj window.obj
nx-ar.exe rcs libvorbisfile.a vorbisfile.obj
mkdir ..\libroot\include\vorbis
xcopy /Y include\vorbis ..\libroot\include\vorbis
copy libvorbis.a ..\libroot\lib\
copy libvorbisfile.a ..\libroot\lib\
cd ..

echo Building freetype...
cd freetype
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftadvanc.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbase.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbbox.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbdf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftbitmap.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftcalc.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftcid.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftcolor.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftdbgmem.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftdebug.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fterrors.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftfntfmt.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftfstype.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftgasp.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftgloadr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftglyph.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftgxval.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fthash.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftinit.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftlcdfil.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftmac.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftmm.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftotval.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftoutln.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftpatent.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftpfr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftpsprop.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftrfork.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftsnames.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftstream.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftstroke.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftsynth.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftsystem.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fttrigon.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/fttype1.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftutil.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/ftwinfnt.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/base/md5.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bdf/bdf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bdf/bdfdrivr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bdf/bdflib.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/bzip2/ftbzip2.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcache.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcbasic.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftccache.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftccmap.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcglyph.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcimage.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcmanag.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcmru.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cache/ftcsbits.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cff.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffcmap.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffdrivr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffgload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cff/cffparse.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidgload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidparse.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/cidriver.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/cid/type1cid.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvalid.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvbase.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvcommn.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvgdef.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvgpos.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvgsub.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvjstf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvmath.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/otvalid/otvmod.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrcmap.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrdrivr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrgload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pfr/pfrsbit.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/afmparse.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/cffdecode.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psarrst.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psaux.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psauxmod.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psblues.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psconv.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/pserror.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psfont.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psft.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/pshints.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psintrp.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psread.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/psstack.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/t1decode.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psaux/t1cmap.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshalgo.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshglob.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshinter.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshmod.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pshinter/pshrec.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psnames/psmodule.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/psnames/psnames.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/raster/ftraster.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftbsdf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftsdf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftsdfcommon.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sdf/ftsdfrend.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/pngshim.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/sfdriver.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/sfobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttbdf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttcmap.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttcolr.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttcpal.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttkern.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttmtx.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttpost.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttsbit.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/ttsvg.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/sfnt/sfwoff.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/smooth/ftgrays.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/smooth/ftsmooth.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/svg/ftsvg.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/truetype.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttdriver.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttgload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttgxvar.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttinterp.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttobjs.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/truetype/ttpload.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/winfonts/winfnt.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/adler32.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/crc32.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/ftgzip.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/inffast.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/inftrees.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/gzip/zutil.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/lzw/ftlzw.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/pcf/pcf.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/autofit/autofit.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/type1/type1.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/type42/type42.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/raster/raster.c
nx-clang.exe -c -O2 -DFT2_BUILD_LIBRARY -Dft_memcpy=memcpy -I./include -I../libroot/include src/svg/svg.c
nx-ar.exe rcs libfreetype.a ftadvanc.obj ftbase.obj ftbbox.obj ftbdf.obj ftbitmap.obj ftcalc.obj ftcid.obj ftcolor.obj ftdbgmem.obj ftdebug.obj fterrors.obj ftfntfmt.obj ftfstype.obj ftgasp.obj ftgloadr.obj ftglyph.obj ftgxval.obj fthash.obj ftinit.obj ftlcdfil.obj ftmac.obj ftmm.obj ftotval.obj ftoutln.obj ftpatent.obj ftpfr.obj ftpsprop.obj ftrfork.obj ftsnames.obj ftstream.obj ftstroke.obj ftsynth.obj ftsystem.obj fttrigon.obj fttype1.obj ftutil.obj ftwinfnt.obj md5.obj bdfdrivr.obj bdflib.obj ftbzip2.obj ftcbasic.obj ftccache.obj ftccmap.obj ftcglyph.obj ftcimage.obj ftcmanag.obj ftcmru.obj ftcsbits.obj cffcmap.obj cffdrivr.obj cffgload.obj cffload.obj cffobjs.obj cffparse.obj cidgload.obj cidload.obj cidobjs.obj cidparse.obj type1cid.obj otvalid.obj otvbase.obj otvcommn.obj otvgdef.obj otvgpos.obj otvgsub.obj otvjstf.obj otvmath.obj pfrcmap.obj pfrdrivr.obj pfrgload.obj pfrload.obj pfrobjs.obj pfrsbit.obj afmparse.obj cffdecode.obj psarrst.obj psauxmod.obj psblues.obj psconv.obj pserror.obj psfont.obj psft.obj pshints.obj psintrp.obj psobjs.obj psread.obj psstack.obj pshalgo.obj pshglob.obj pshmod.obj pshrec.obj psmodule.obj t1decode.obj t1cmap.obj ftraster.obj ftbsdf.obj ftsdf.obj ftsdfcommon.obj ftsdfrend.obj pngshim.obj sfdriver.obj sfobjs.obj ttbdf.obj ttcmap.obj ttcolr.obj ttcpal.obj ttkern.obj ttload.obj ttmtx.obj ttpost.obj ttsbit.obj ttsvg.obj sfwoff.obj ftgrays.obj ftsmooth.obj ftsvg.obj ttdriver.obj ttgload.obj ttgxvar.obj ttinterp.obj ttobjs.obj ttpload.obj winfnt.obj adler32.obj crc32.obj ftgzip.obj inffast.obj inftrees.obj zutil.obj ftlzw.obj pcf.obj autofit.obj type1.obj type42.obj raster.obj
mkdir ..\libroot\include\freetype
mkdir ..\libroot\include\freetype\config
xcopy /Y include\freetype ..\libroot\include\freetype
xcopy /Y include\freetype\config ..\libroot\include\freetype\config
copy /Y include\ft2build.h ..\libroot\include\
copy libfreetype.a ..\libroot\lib\
cd ..

echo Building NoctVM...
cd objs
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../../src ../../../src/platform/halwrap.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../../src -I../libroot/include ../../../src/platform/glyph.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../../src -I../libroot/include ../../../src/platform/wave.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -DUSE_UNITY -DUSE_CSHARP -DUSE_DLL -I../../../src -I../libroot/include ../../../src/platform/image.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -DYY_NO_UNISTD_H -I../../../src ../../../src/lang/lexer.yy.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/parser.tab.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/ast.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/hir.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/lir.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/runtime.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/interpreter.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/intrinsics.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/lang/jit-common.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/noctvm/main.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/noctvm/api.c
nx-clang.exe -c -O2 -DUNICODE -D_UNICODE -I../../../src ../../../src/noctvm/vm.c
cd ..

echo Merging libraries...
cd objs
nx-clang.exe x ../libroot/lib/zlib.lib
nx-clang.exe x ../libroot/lib/libpng.lib
nx-clang.exe x ../libroot/lib/jpeg.lib
nx-clang.exe x ../libroot/lib/libwebp.lib
nx-clang.exe x ../libroot/lib/libogg.lib
nx-clang.exe x ../libroot/lib/libvorbisfile.lib
nx-clang.exe x ../libroot/lib/libvorbis.lib
nx-clang.exe x ../libroot/lib/freetype.lib
cd ..
nx-ar.exe rcs libnoctvm.a objs/*.o

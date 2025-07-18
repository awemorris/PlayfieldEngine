#!/bin/sh

function do_build() {
    mkdir -p libroot
    mkdir -p libroot/include
    mkdir -p libroot/lib-$1

    echo 'Building zlib.lib'
    rm -rf zlib
    tar xzf ../../external/StratoHAL/lib/archive/zlib-1.3.1.tar.gz
    mv zlib-1.3.1 zlib
    cd zlib
    clang-cl -target $1 /nologo /c /MT /O2 adler32.c
    clang-cl -target $1 /nologo /c /MT /O2 infback.c
    clang-cl -target $1 /nologo /c /MT /O2 trees.c
    clang-cl -target $1 /nologo /c /MT /O2 compress.c
    clang-cl -target $1 /nologo /c /MT /O2 inffast.c
    clang-cl -target $1 /nologo /c /MT /O2 uncompr.c
    clang-cl -target $1 /nologo /c /MT /O2 crc32.c
    clang-cl -target $1 /nologo /c /MT /O2 inflate.c
    clang-cl -target $1 /nologo /c /MT /O2 deflate.c
    clang-cl -target $1 /nologo /c /MT /O2 inftrees.c
    clang-cl -target $1 /nologo /c /MT /O2 zutil.c
    llvm-lib /nologo /OUT:zlib.lib adler32.obj infback.obj trees.obj compress.obj inffast.obj uncompr.obj crc32.obj inflate.obj deflate.obj inftrees.obj zutil.obj
    cp zlib.h ../libroot/include/
    cp zconf.h ../libroot/include/
    cp zlib.lib ../libroot/lib-$1/
    cd ..
    rm -rf zlib

    echo 'Building libpng.lib'
    rm -rf libpng
    tar xzf ../../external/StratoHAL/lib/archive/libpng-1.6.43.tar.gz
    mv libpng-1.6.43 libpng
    cd libpng
    cp scripts/pnglibconf.h.prebuilt pnglibconf.h
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngget.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngread.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngrutil.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngtrans.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngwtran.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include png.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngmem.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngrio.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngset.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngwio.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngwutil.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngerror.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngpread.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngrtran.c
    clang-cl -target $1 /nologo /c /MT /O2 /I../libroot/include pngwrite.c
    llvm-lib /nologo /OUT:libpng.lib pngget.obj pngread.obj pngrutil.obj pngtrans.obj pngwtran.obj png.obj pngmem.obj pngrio.obj pngset.obj pngwio.obj pngwutil.obj pngerror.obj pngpread.obj pngrtran.obj pngwrite.obj
    mkdir ../libroot/include/png
    cp *.h ../libroot/include/png/
    cp libpng.lib ../libroot/lib-$1/
    cd ..
    rm -rf libpng

    echo 'Building libjpeg.lib'
    rm -rf jpeg
    tar xzf ../../external/StratoHAL/lib/archive/jpegsrc.v9e.tar.gz
    mv jpeg-9e jpeg
    cd jpeg
    cp jconfig.txt jconfig.h
    clang-cl -target $1 /nologo /c /MT /O2 cdjpeg.c
    clang-cl -target $1 /nologo /c /MT /O2 jaricom.c
    clang-cl -target $1 /nologo /c /MT /O2 jcapimin.c
    clang-cl -target $1 /nologo /c /MT /O2 jcapistd.c
    clang-cl -target $1 /nologo /c /MT /O2 jcarith.c
    clang-cl -target $1 /nologo /c /MT /O2 jccoefct.c
    clang-cl -target $1 /nologo /c /MT /O2 jccolor.c
    clang-cl -target $1 /nologo /c /MT /O2 jcdctmgr.c
    clang-cl -target $1 /nologo /c /MT /O2 jchuff.c
    clang-cl -target $1 /nologo /c /MT /O2 jcinit.c
    clang-cl -target $1 /nologo /c /MT /O2 jcmainct.c
    clang-cl -target $1 /nologo /c /MT /O2 jcmarker.c
    clang-cl -target $1 /nologo /c /MT /O2 jcmaster.c
    clang-cl -target $1 /nologo /c /MT /O2 jcomapi.c
    clang-cl -target $1 /nologo /c /MT /O2 jcparam.c
    clang-cl -target $1 /nologo /c /MT /O2 jcprepct.c
    clang-cl -target $1 /nologo /c /MT /O2 jcsample.c
    clang-cl -target $1 /nologo /c /MT /O2 jctrans.c
    clang-cl -target $1 /nologo /c /MT /O2 jdapimin.c
    clang-cl -target $1 /nologo /c /MT /O2 jdapistd.c
    clang-cl -target $1 /nologo /c /MT /O2 jdarith.c
    clang-cl -target $1 /nologo /c /MT /O2 jdatadst.c
    clang-cl -target $1 /nologo /c /MT /O2 jdatasrc.c
    clang-cl -target $1 /nologo /c /MT /O2 jdcoefct.c
    clang-cl -target $1 /nologo /c /MT /O2 jdcolor.c
    clang-cl -target $1 /nologo /c /MT /O2 jddctmgr.c
    clang-cl -target $1 /nologo /c /MT /O2 jdhuff.c
    clang-cl -target $1 /nologo /c /MT /O2 jdinput.c
    clang-cl -target $1 /nologo /c /MT /O2 jdmainct.c
    clang-cl -target $1 /nologo /c /MT /O2 jdmarker.c
    clang-cl -target $1 /nologo /c /MT /O2 jdmaster.c
    clang-cl -target $1 /nologo /c /MT /O2 jdmerge.c
    clang-cl -target $1 /nologo /c /MT /O2 jdpostct.c
    clang-cl -target $1 /nologo /c /MT /O2 jdsample.c
    clang-cl -target $1 /nologo /c /MT /O2 jdtrans.c
    clang-cl -target $1 /nologo /c /MT /O2 jerror.c
    clang-cl -target $1 /nologo /c /MT /O2 jfdctflt.c
    clang-cl -target $1 /nologo /c /MT /O2 jfdctfst.c
    clang-cl -target $1 /nologo /c /MT /O2 jfdctint.c
    clang-cl -target $1 /nologo /c /MT /O2 jidctflt.c
    clang-cl -target $1 /nologo /c /MT /O2 jidctfst.c
    clang-cl -target $1 /nologo /c /MT /O2 jidctint.c
    clang-cl -target $1 /nologo /c /MT /O2 jmemansi.c
    clang-cl -target $1 /nologo /c /MT /O2 jmemmgr.c
    clang-cl -target $1 /nologo /c /MT /O2 jquant1.c
    clang-cl -target $1 /nologo /c /MT /O2 jquant2.c
    clang-cl -target $1 /nologo /c /MT /O2 jutils.c
    clang-cl -target $1 /nologo /c /MT /O2 transupp.c
    llvm-lib /nologo /OUT:jpeg.lib cdjpeg.obj jaricom.obj jcapimin.obj jcapistd.obj jcarith.obj jccoefct.obj jccolor.obj jcdctmgr.obj jchuff.obj jcinit.obj jcmainct.obj jcmarker.obj jcmaster.obj jcomapi.obj jcparam.obj jcprepct.obj jcsample.obj jctrans.obj jdapimin.obj jdapistd.obj jdarith.obj jdatadst.obj jdatasrc.obj jdcoefct.obj jdcolor.obj jddctmgr.obj jdhuff.obj jdinput.obj jdmainct.obj jdmarker.obj jdmaster.obj jdmerge.obj jdpostct.obj jdsample.obj jdtrans.obj jerror.obj jfdctflt.obj jfdctfst.obj jfdctint.obj jidctflt.obj jidctfst.obj jidctint.obj jmemansi.obj jmemmgr.obj jquant1.obj jquant2.obj jutils.obj transupp.obj
    mkdir ../libroot/include/jpeg
    cp *.h ../libroot/include/jpeg/
    cp jpeg.lib ../libroot/lib-$1/
    cd ..
    rm -rf jpeg

    echo 'Building libbz2.lib'
    rm -rf bzip2
    tar xzf ../../external/StratoHAL/lib/archive/bzip2-1.0.6.tar.gz
    mv bzip2-1.0.6 bzip2
    cd bzip2
    clang-cl -target $1 /nologo /c /MT /O2 blocksort.c
    clang-cl -target $1 /nologo /c /MT /O2 compress.c
    clang-cl -target $1 /nologo /c /MT /O2 decompress.c
    clang-cl -target $1 /nologo /c /MT /O2 huffman.c
    clang-cl -target $1 /nologo /c /MT /O2 randtable.c
    clang-cl -target $1 /nologo /c /MT /O2 bzlib.c
    clang-cl -target $1 /nologo /c /MT /O2 crctable.c
    llvm-lib /nologo /OUT:libbz2.lib blocksort.obj compress.obj decompress.obj huffman.obj randtable.obj bzlib.obj crctable.obj
    cp bzlib.h ../libroot/include/
    cp libbz2.lib ../libroot/lib-$1/
    cd ..
    rm -rf bzip2

    echo 'Building libwebp.lib'
    rm -rf libvorbis
    tar xzf ../../external/StratoHAL/lib/archive/libwebp-1.3.2.tar.gz
    mv libwebp-1.3.2 libwebp
    cd libwebp
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/alpha_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/buffer_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/frame_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/idec_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/io_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/quant_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/tree_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/vp8_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/vp8l_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dec/webp_dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/demux/anim_decode.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/demux/demux.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/alpha_processing.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/alpha_processing_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/alpha_processing_sse41.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/alpha_processing_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/cost.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/cost_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/cost_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/cpu.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/dec.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/dec_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/dec_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/dec_sse41.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/dec_clip_tables.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/filters.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/filters_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/filters_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_sse41.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_enc_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_enc_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/lossless_enc_sse41.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/rescaler.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/rescaler_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/rescaler_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/ssim.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/ssim_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/upsampling.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/upsampling_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/upsampling_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/upsampling_sse41.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/yuv.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/yuv_neon.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/yuv_sse2.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/dsp/yuv_sse41.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/alpha_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/analysis_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/backward_references_cost_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/backward_references_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/config_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/cost_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/filter_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/frame_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/histogram_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/iterator_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/near_lossless_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/picture_csp_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/picture_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/picture_psnr_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/picture_rescale_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/picture_tools_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/predictor_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/quant_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/syntax_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/token_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/tree_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/vp8l_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/enc/webp_enc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/mux/anim_encode.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/mux/muxedit.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/mux/muxinternal.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/mux/muxread.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/bit_reader_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/bit_writer_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/color_cache_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/filters_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/huffman_encode_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/huffman_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/quant_levels_dec_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/quant_levels_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/random_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/rescaler_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/thread_utils.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./ src/utils/utils.c
    llvm-lib /nologo /OUT:libwebp.lib alpha_dec.obj buffer_dec.obj frame_dec.obj idec_dec.obj io_dec.obj quant_dec.obj tree_dec.obj vp8_dec.obj vp8l_dec.obj webp_dec.obj anim_decode.obj demux.obj alpha_processing.obj cost.obj cost_neon.obj cost_sse2.obj cpu.obj dec.obj dec_neon.obj dec_sse2.obj dec_sse41.obj dec_clip_tables.obj enc.obj filters.obj filters_neon.obj filters_sse2.obj lossless.obj lossless_neon.obj lossless_sse2.obj lossless_sse41.obj lossless_enc.obj lossless_enc_neon.obj lossless_enc_sse2.obj lossless_enc_sse41.obj rescaler.obj rescaler_neon.obj rescaler_sse2.obj ssim.obj ssim_sse2.obj upsampling.obj upsampling_neon.obj upsampling_sse2.obj upsampling_sse41.obj yuv.obj yuv_neon.obj yuv_sse2.obj yuv_sse41.obj alpha_enc.obj analysis_enc.obj backward_references_cost_enc.obj backward_references_enc.obj config_enc.obj cost_enc.obj filter_enc.obj frame_enc.obj histogram_enc.obj iterator_enc.obj near_lossless_enc.obj picture_csp_enc.obj picture_enc.obj picture_psnr_enc.obj picture_rescale_enc.obj picture_tools_enc.obj predictor_enc.obj quant_enc.obj syntax_enc.obj token_enc.obj tree_enc.obj vp8l_enc.obj webp_enc.obj anim_encode.obj muxedit.obj muxinternal.obj muxread.obj bit_reader_utils.obj bit_writer_utils.obj color_cache_utils.obj filters_utils.obj huffman_encode_utils.obj huffman_utils.obj quant_levels_dec_utils.obj quant_levels_utils.obj random_utils.obj rescaler_utils.obj thread_utils.obj utils.obj alpha_processing_sse2.obj alpha_processing_sse41.obj alpha_processing_neon.obj
    cp -R src/webp ../libroot/include/webp/
    cp libwebp.lib ../libroot/lib-$1/
    cd ..
    rm -rf libwebp

    echo 'Building libogg.lib'
    rm -rf libogg
    tar xzf ../../external/StratoHAL/lib/archive/libogg-1.3.3.tar.gz
    mv libogg-1.3.3 libogg
    cd libogg
    clang-cl -target $1 /nologo /c /MT /O2 /I./include src/bitwise.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include src/framing.c
    llvm-lib /nologo /OUT:libogg.lib bitwise.obj framing.obj
    cp -R include/ogg ../libroot/include/ogg
    cp libogg.lib ../libroot/lib-$1/
    cd ..
    rm -rf libogg

    echo 'Building libvorbis.lib'
    rm -rf libvorbis
    tar xzf ../../external/StratoHAL/lib/archive/libvorbis-1.3.7.tar.gz
    mv libvorbis-1.3.7 libvorbis
    cd libvorbis
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/analysis.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/bitrate.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/block.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/codebook.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/envelope.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/floor0.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/floor1.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/info.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/lookup.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/lpc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/lsp.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/mapping0.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/mdct.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/psy.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/registry.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/res0.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/sharedbook.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/smallft.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/synthesis.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/vorbisenc.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/vorbisfile.c
    clang-cl -target $1 /nologo /c /MT /O2 /I./include /I./lib /I../libroot/include lib/window.c
    llvm-lib /nologo /OUT:libvorbis.lib analysis.obj bitrate.obj block.obj codebook.obj envelope.obj floor0.obj floor1.obj info.obj lookup.obj lpc.obj lsp.obj mapping0.obj mdct.obj psy.obj registry.obj res0.obj sharedbook.obj smallft.obj synthesis.obj vorbisenc.obj window.obj
    llvm-lib /nologo /OUT:libvorbisfile.lib vorbisfile.obj
    cp -R include/vorbis ../libroot/include/vorbis
    cp libvorbis.lib ../libroot/lib-$1/
    cp libvorbisfile.lib ../libroot/lib-$1/
    cd ..
    rm -rf libvorbis

    echo 'Building freetype.lib'
    rm -rf freetype
    tar xzf ../../external/StratoHAL/lib/archive/freetype-2.13.3.tar.gz
    mv freetype-2.13.3 freetype
    cd freetype
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftadvanc.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbase.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbbox.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbdf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftbitmap.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftcalc.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftcid.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftcolor.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftdbgmem.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftdebug.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fterrors.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftfntfmt.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftfstype.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftgasp.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftgloadr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftglyph.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftgxval.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fthash.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftinit.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftlcdfil.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftmac.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftmm.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftotval.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftoutln.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftpatent.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftpfr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftpsprop.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftrfork.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftsnames.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftstream.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftstroke.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftsynth.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftsystem.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fttrigon.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/fttype1.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftutil.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/ftwinfnt.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/base/md5.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bdf/bdf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bdf/bdfdrivr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bdf/bdflib.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/bzip2/ftbzip2.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcache.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcbasic.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftccache.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftccmap.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcglyph.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcimage.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcmanag.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcmru.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cache/ftcsbits.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cff.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffcmap.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffdrivr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffgload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cff/cffparse.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidgload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidparse.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/cidriver.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/cid/type1cid.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvalid.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvbase.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvcommn.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvgdef.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvgpos.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvgsub.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvjstf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvmath.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/otvalid/otvmod.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrcmap.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrdrivr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrgload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pfr/pfrsbit.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/afmparse.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/cffdecode.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psarrst.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psaux.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psauxmod.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psblues.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psconv.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/pserror.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psfont.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psft.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/pshints.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psintrp.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psread.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/psstack.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/t1decode.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psaux/t1cmap.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshalgo.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshglob.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshinter.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshmod.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pshinter/pshrec.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psnames/psmodule.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/psnames/psnames.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/raster/ftraster.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftbsdf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftsdf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftsdfcommon.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sdf/ftsdfrend.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/pngshim.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/sfdriver.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/sfobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttbdf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttcmap.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttcolr.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttcpal.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttkern.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttmtx.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttpost.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttsbit.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/ttsvg.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/sfnt/sfwoff.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/smooth/ftgrays.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/smooth/ftsmooth.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/svg/ftsvg.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/truetype.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttdriver.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttgload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttgxvar.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttinterp.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttobjs.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/truetype/ttpload.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/winfonts/winfnt.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/adler32.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/crc32.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/ftgzip.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/inffast.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/inftrees.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/gzip/zutil.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/lzw/ftlzw.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/pcf/pcf.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/autofit/autofit.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/type1/type1.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/type42/type42.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/raster/raster.c
    clang-cl -target $1 /nologo /c /O2 /MT /DFT2_BUILD_LIBRARY /Dft_memcpy=memcpy /I./include /I../libroot/include src/svg/svg.c
    llvm-lib /nologo /OUT:freetype.lib ftadvanc.obj ftbase.obj ftbbox.obj ftbdf.obj ftbitmap.obj ftcalc.obj ftcid.obj ftcolor.obj ftdbgmem.obj ftdebug.obj fterrors.obj ftfntfmt.obj ftfstype.obj ftgasp.obj ftgloadr.obj ftglyph.obj ftgxval.obj fthash.obj ftinit.obj ftlcdfil.obj ftmac.obj ftmm.obj ftotval.obj ftoutln.obj ftpatent.obj ftpfr.obj ftpsprop.obj ftrfork.obj ftsnames.obj ftstream.obj ftstroke.obj ftsynth.obj ftsystem.obj fttrigon.obj fttype1.obj ftutil.obj ftwinfnt.obj md5.obj bdfdrivr.obj bdflib.obj ftbzip2.obj ftcbasic.obj ftccache.obj ftccmap.obj ftcglyph.obj ftcimage.obj ftcmanag.obj ftcmru.obj ftcsbits.obj cffcmap.obj cffdrivr.obj cffgload.obj cffload.obj cffobjs.obj cffparse.obj cidgload.obj cidload.obj cidobjs.obj cidparse.obj type1cid.obj otvalid.obj otvbase.obj otvcommn.obj otvgdef.obj otvgpos.obj otvgsub.obj otvjstf.obj otvmath.obj pfrcmap.obj pfrdrivr.obj pfrgload.obj pfrload.obj pfrobjs.obj pfrsbit.obj afmparse.obj cffdecode.obj psarrst.obj psauxmod.obj psblues.obj psconv.obj pserror.obj psfont.obj psft.obj pshints.obj psintrp.obj psobjs.obj psread.obj psstack.obj pshalgo.obj pshglob.obj pshmod.obj pshrec.obj psmodule.obj t1decode.obj t1cmap.obj ftraster.obj ftbsdf.obj ftsdf.obj ftsdfcommon.obj ftsdfrend.obj pngshim.obj sfdriver.obj sfobjs.obj ttbdf.obj ttcmap.obj ttcolr.obj ttcpal.obj ttkern.obj ttload.obj ttmtx.obj ttpost.obj ttsbit.obj ttsvg.obj sfwoff.obj ftgrays.obj ftsmooth.obj ftsvg.obj ttdriver.obj ttgload.obj ttgxvar.obj ttinterp.obj ttobjs.obj ttpload.obj winfnt.obj adler32.obj crc32.obj ftgzip.obj inffast.obj inftrees.obj zutil.obj ftlzw.obj pcf.obj autofit.obj type1.obj type42.obj raster.obj
    cp -R include/freetype ../libroot/include/freetype
    cp -R include/ft2build.h ../libroot/include/
    cp freetype.lib ../libroot/lib-$1/
    cd ..
    rm -rf freetype
}

rm -rf libroot
mkdir libroot
mkdir libroot/include
mkdir libroot/lib

echo '[x86]'
do_build "i686-pc-windows-msvc"

echo '[x64]'
do_build "x86_64-pc-windows-msvc"

echo '[arm64]'
do_build "aarch64-pc-windows-msvc"

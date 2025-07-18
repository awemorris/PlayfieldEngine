# Extract library archive.
file(ARCHIVE_EXTRACT
  INPUT       ${CMAKE_CURRENT_SOURCE_DIR}/lib/archive/freetype-2.13.3.tar.gz
  DESTINATION ${CMAKE_BINARY_DIR}
)

# Rename it to "freetype".
file(GLOB LIBPNG_EXTRACTED_DIR ${CMAKE_BINARY_DIR}/freetype-*)
file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/freetype)
file(RENAME ${LIBPNG_EXTRACTED_DIR} ${CMAKE_BINARY_DIR}/freetype)

# Source list.
add_library(freetype OBJECT
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftadvanc.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftbase.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftbbox.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftbdf.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftbitmap.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftcalc.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftcid.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftcolor.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftdbgmem.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftdebug.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/fterrors.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftfntfmt.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftfstype.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftgasp.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftgloadr.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftglyph.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftgxval.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/fthash.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftinit.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftlcdfil.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftmac.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftmm.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftotval.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftoutln.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftpatent.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftpfr.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftpsprop.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftrfork.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftsnames.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftstream.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftstroke.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftsynth.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftsystem.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/fttrigon.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/fttype1.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftutil.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/ftwinfnt.c
  ${CMAKE_BINARY_DIR}/freetype/src/base/md5.c
  ${CMAKE_BINARY_DIR}/freetype/src/bdf/bdf.c
  ${CMAKE_BINARY_DIR}/freetype/src/bdf/bdfdrivr.c
  ${CMAKE_BINARY_DIR}/freetype/src/bdf/bdflib.c
  ${CMAKE_BINARY_DIR}/freetype/src/bzip2/ftbzip2.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcache.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcbasic.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftccache.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftccmap.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcglyph.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcimage.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcmanag.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcmru.c
  ${CMAKE_BINARY_DIR}/freetype/src/cache/ftcsbits.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cff.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cffcmap.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cffdrivr.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cffgload.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cffload.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cffobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/cff/cffparse.c
  ${CMAKE_BINARY_DIR}/freetype/src/cid/cidgload.c
  ${CMAKE_BINARY_DIR}/freetype/src/cid/cidload.c
  ${CMAKE_BINARY_DIR}/freetype/src/cid/cidobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/cid/cidparse.c
  ${CMAKE_BINARY_DIR}/freetype/src/cid/cidriver.c
  ${CMAKE_BINARY_DIR}/freetype/src/cid/type1cid.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvalid.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvbase.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvcommn.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvgdef.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvgpos.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvgsub.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvjstf.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvmath.c
  ${CMAKE_BINARY_DIR}/freetype/src/otvalid/otvmod.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfr.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfrcmap.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfrdrivr.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfrgload.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfrload.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfrobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/pfr/pfrsbit.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/afmparse.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/cffdecode.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psarrst.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psaux.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psauxmod.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psblues.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psconv.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/pserror.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psfont.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psft.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/pshints.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psintrp.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psread.c
  ${CMAKE_BINARY_DIR}/freetype/src/psaux/psstack.c
  ${CMAKE_BINARY_DIR}/freetype/src/pshinter/pshalgo.c
  ${CMAKE_BINARY_DIR}/freetype/src/pshinter/pshglob.c
  ${CMAKE_BINARY_DIR}/freetype/src/pshinter/pshinter.c
  ${CMAKE_BINARY_DIR}/freetype/src/pshinter/pshmod.c
  ${CMAKE_BINARY_DIR}/freetype/src/pshinter/pshrec.c
  ${CMAKE_BINARY_DIR}/freetype/src/psnames/psmodule.c
  ${CMAKE_BINARY_DIR}/freetype/src/psnames/psnames.c
  ${CMAKE_BINARY_DIR}/freetype/src/raster/ftraster.c
  ${CMAKE_BINARY_DIR}/freetype/src/sdf/ftbsdf.c
  ${CMAKE_BINARY_DIR}/freetype/src/sdf/ftsdf.c
  ${CMAKE_BINARY_DIR}/freetype/src/sdf/ftsdfcommon.c
  ${CMAKE_BINARY_DIR}/freetype/src/sdf/ftsdfrend.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/pngshim.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/sfdriver.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/sfobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttbdf.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttcmap.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttcolr.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttcpal.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttkern.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttload.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttmtx.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttpost.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttsbit.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/ttsvg.c
  ${CMAKE_BINARY_DIR}/freetype/src/sfnt/sfwoff.c
  ${CMAKE_BINARY_DIR}/freetype/src/smooth/ftgrays.c
  ${CMAKE_BINARY_DIR}/freetype/src/smooth/ftsmooth.c
  ${CMAKE_BINARY_DIR}/freetype/src/svg/ftsvg.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/truetype.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/ttdriver.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/ttgload.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/ttgxvar.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/ttinterp.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/ttobjs.c
  ${CMAKE_BINARY_DIR}/freetype/src/truetype/ttpload.c
  ${CMAKE_BINARY_DIR}/freetype/src/winfonts/winfnt.c
  ${CMAKE_BINARY_DIR}/freetype/src/lzw/ftlzw.c
  ${CMAKE_BINARY_DIR}/freetype/src/pcf/pcf.c
  ${CMAKE_BINARY_DIR}/freetype/src/autofit/autofit.c
  ${CMAKE_BINARY_DIR}/freetype/src/type1/type1.c
  ${CMAKE_BINARY_DIR}/freetype/src/type42/type42.c
  ${CMAKE_BINARY_DIR}/freetype/src/raster/raster.c
  ${CMAKE_BINARY_DIR}/freetype/src/svg/svg.c
  ${CMAKE_BINARY_DIR}/freetype/src/gzip/ftgzip.c
)

target_include_directories(freetype PUBLIC
  ${CMAKE_BINARY_DIR}/freetype/include
)
set(FREETYPE_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/freetype/include)

target_compile_definitions(freetype PRIVATE
  FT2_BUILD_LIBRARY
  FT_CONFIG_OPTION_SYSTEM_ZLIB
  ft_memcpy=memcpy
)

target_link_libraries(freetype PRIVATE
  brotlidec
  brotlicommon
  z
)

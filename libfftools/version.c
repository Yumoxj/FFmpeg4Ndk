#include "config.h"
#include "fftools.h"
#include "libavutil/avassert.h"
#include "version.h"

#include "libavutil/ffversion.h"
const char fftools_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

unsigned fftools_version(void)
{
    av_assert0(LIBFFTOOLS_VERSION_MICRO >= 100);
    return LIBFFTOOLS_VERSION_INT;
}

const char *fftools_configuration(void)
{
    return FFMPEG_CONFIGURATION;
}

const char *fftools_license(void)
{
#define LICENSE_PREFIX "libfftools license: "
    return &LICENSE_PREFIX FFMPEG_LICENSE[sizeof(LICENSE_PREFIX) - 1];
}

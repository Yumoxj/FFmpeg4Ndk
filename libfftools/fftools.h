#ifndef FFTOOLS_H
#define FFTOOLS_H

#include "libfftools/version_major.h"
#ifndef HAVE_AV_CONFIG_H
#include "libfftools/version.h"
#endif

unsigned fftools_version(void);
const char *fftools_configuration(void);
const char *fftools_license(void);

int ff_tools_ffmpeg(int argc, char **argv);

#endif /* FFTOOLS_H */
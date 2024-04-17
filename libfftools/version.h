#ifndef FFTOOLS_VERSION_H
#define FFTOOLS_VERSION_H

#include "libavutil/version.h"

#include "version_major.h"

#define LIBFFTOOLS_VERSION_MINOR   6
#define LIBFFTOOLS_VERSION_MICRO 100

#define LIBFFTOOLS_VERSION_INT AV_VERSION_INT(LIBFFTOOLS_VERSION_MAJOR, \
                                               LIBFFTOOLS_VERSION_MINOR, \
                                               LIBFFTOOLS_VERSION_MICRO)
#define LIBFFTOOLS_VERSION     AV_VERSION(LIBFFTOOLS_VERSION_MAJOR, \
                                           LIBFFTOOLS_VERSION_MINOR, \
                                           LIBFFTOOLS_VERSION_MICRO)
#define LIBFFTOOLS_BUILD       LIBFFTOOLS_VERSION_INT

#define LIBFFTOOLS_IDENT       "fftools" AV_STRINGIFY(LIBFFTOOLS_VERSION)

#endif /* fftools_VERSION_H */

#ifndef FFTOOLS_H
#define FFTOOLS_H

#include "libfftools/version_major.h"
#ifndef HAVE_AV_CONFIG_H
#include "libfftools/version.h"
#endif

#include <stdbool.h>
#include <stdio.h>

unsigned fftools_version(void);
const char *fftools_configuration(void);
const char *fftools_license(void);

bool fftools_init(void(*onFirstInit)(void));
void fftools_deinit(void);
void fftools_set_msg_callback(void(*msg_callback)(const char *msg, int level));
int fftools_jni_set_java_vm(void *vm, void *log_ctx);
int fftools_ffmpeg(int argc, char **argv);
const char* fftools_ffmpeg_version(void);

#endif /* FFTOOLS_H */
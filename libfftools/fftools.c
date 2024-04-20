#include "fftools.h"
#include "libavutil/ffversion.h"

#include <pthread.h>
#include "libavutil/thread.h"
#include "libavcodec/jni.h"
#include "ffmpeg.h"

static AVMutex mutex = AV_MUTEX_INITIALIZER;
static pthread_mutex_t g_init_mtx = PTHREAD_MUTEX_INITIALIZER;
static int g_ref_cnt = 0;
static int g_log_level_default = AV_LOG_VERBOSE;

static void(*g_msg_callback)(const char *msg, int level) = NULL;

#define LINE_SZ 1024

static void sanitize(char *line)
{
    while(*line)
    {
        if(*line < 0x08 || (*line > 0x0D && *line < 0x20))
            *line='?';
        line++;
    }
}

static void fftools_log_default_callback(void* ptr, int level, const char* fmt, va_list vl)
{
    static int print_prefix = 1;
    static int count;
    static char prev[LINE_SZ];
    char line[LINE_SZ];

    if (level > av_log_get_level())
        return;

    ff_mutex_lock(&mutex);

    if (av_log_format_line2(ptr, level, fmt, vl, line, sizeof(line), &print_prefix) < 0)
        return;

    if (print_prefix && (av_log_get_flags() & AV_LOG_SKIP_REPEATED) && !strcmp(line, prev) &&
        *line && line[strlen(line) - 1] != '\r'){
        count++;
        goto end;
    }

    if (count > 0) {
        snprintf(line, LINE_SZ, "    Last message repeated %d times", count);
        count = 0;
    }

    sanitize(line);

    if (g_msg_callback != NULL)
    {
        g_msg_callback(line, level);
    }

end:
    ff_mutex_unlock(&mutex);
}

bool fftools_init(void(*onFirstInit)(void))
{
    bool ret = true;

    pthread_mutex_lock(&g_init_mtx);

    if (g_ref_cnt == 0) {
        av_log_set_flags(AV_LOG_SKIP_REPEATED);
        av_log_set_level(g_log_level_default);
        av_log_set_callback(fftools_log_default_callback);

        if (NULL != onFirstInit) {
            onFirstInit();
        }
    }

    g_ref_cnt ++;

    pthread_mutex_unlock(&g_init_mtx);

    return ret;
}

void fftools_deinit(void)
{
    pthread_mutex_lock(&g_init_mtx);

    if (g_ref_cnt > 0)
    {
        g_ref_cnt --;
    }

    pthread_mutex_unlock(&g_init_mtx);
}

void fftools_set_msg_callback(void(*msg_callback)(const char *msg, int level))
{
    pthread_mutex_lock(&g_init_mtx);

    g_msg_callback = msg_callback;

    pthread_mutex_unlock(&g_init_mtx);
}

int fftools_jni_set_java_vm(void *vm, void *log_ctx)
{
    return av_jni_set_java_vm(vm, log_ctx);
}

int fftools_ffmpeg(int argc, char **argv)
{
    pthread_mutex_lock(&g_init_mtx);

    int ret = ffmpeg_handle(argc, argv);

    pthread_mutex_unlock(&g_init_mtx);
    return ret;
}

const char* fftools_ffmpeg_version(void)
{
    return "FFmpeg version " FFMPEG_VERSION;
}
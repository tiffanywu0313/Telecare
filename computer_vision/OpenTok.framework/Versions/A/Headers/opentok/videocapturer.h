/** @file */
#ifndef VIDEOCAPTURER_H
#define VIDEOCAPTURER_H

#include "config.h"
#include "videoframe.h"

OTC_BEGIN_DECL

struct otc_video_capturer_settings {
    int format;
    int width;
    int height;
    int fps;
    int expected_capture_delay;
    otc_bool_t mirror_on_local_render;
};

typedef struct otc_video_capturer otc_video_capturer;

struct otc_video_capturer_cb
{
    void *user_data;

    otc_bool_t (*init)(const otc_video_capturer *capturer, void *user_data);

    otc_bool_t (*destroy)(const otc_video_capturer *capturer, void *user_data);

    otc_bool_t (*start)(const otc_video_capturer *capturer, void *user_data);

    otc_bool_t (*stop)(const otc_video_capturer *capturer, void *user_data);

    otc_bool_t (*capture_settings)(const otc_video_capturer *capturer,
                                   void *user_data,
                                   struct otc_video_capturer_settings *settings);
    
    void *reserved;
};


OTC_DECL(otc_status_t) otc_video_capturer_provide_frame(const otc_video_capturer *capturer,
                                                        int rotation,
                                                        const otc_video_frame *cframe);


OTC_END_DECL

#endif // VIDEOCAPTURER_H

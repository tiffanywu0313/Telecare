/** @file */
#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include <stdlib.h>

#include "config.h"

OTC_BEGIN_DECL

struct otc_audio_device_settings {
    int sampling_rate;
    int num_channels;
};

typedef struct otc_audio_device otc_audio_device;

struct otc_audio_device_cb
{
    void *user_data;

    otc_bool_t (*init)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*destroy)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*init_capturer)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*destroy_capturer)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*start_capturer)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*stop_capturer)(const otc_audio_device *audio_device, void *user_data);

    int (*get_estimated_capture_delay)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*get_capture_settings)(const otc_audio_device *audio_device,
                                   void *user_data,
                                   struct otc_audio_device_settings *settings);


    otc_bool_t (*init_renderer)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*destroy_renderer)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*start_renderer)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*stop_renderer)(const otc_audio_device *audio_device, void *user_data);

    int (*get_estimated_render_delay)(const otc_audio_device *audio_device, void *user_data);

    otc_bool_t (*get_render_settings)(const otc_audio_device *audio_device,
                                   void *user_data,
                                   struct otc_audio_device_settings *settings);

    
    void *reserved;
};


OTC_DECL(size_t) otc_audio_device_read_render_data(int16_t *buffer,
                                                    size_t number_of_samples);

OTC_DECL(otc_status_t) otc_audio_device_write_capture_data(const int16_t *buffer,
                                                           size_t number_of_samples);

OTC_DECL(otc_status_t) otc_set_audio_device(const struct otc_audio_device_cb *audio_device_cb);


OTC_END_DECL

#endif // AUDIODEVICE_H

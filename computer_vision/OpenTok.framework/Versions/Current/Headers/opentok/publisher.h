/** @file */
#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "config.h"
#include "stream.h"

OTC_BEGIN_DECL

// forward declaration
#ifndef OTC_SESSION_FWD_DECL
#define OTC_SESSION_FWD_DECL
typedef struct otc_session otc_session;
#endif

/**
* A publisher captures an audio-video stream from the device's microphone and camera. Create a Publisher instance
* by calling the {@link otc_publisher_new} function.
*/
typedef struct otc_publisher otc_publisher;

//TODO: Add comments

enum otc_publisher_error
{
    OTC_PUBLISHER_SUCCESS = 0,
    OTC_PUBLISHER_SESSION_DISCONNECTED = 1010,
    OTC_PUBLISHER_INTERNAL_ERROR = 2000,
    OTC_PUBLISHER_WEBRTC_ERROR = 1610,
    OTC_PUBLISHER_TIMED_OUT = 1541,
    OTC_PUBLISHER_UNABLE_TO_PUBLISH = 1500,
};

struct otc_publisher_cb
{
    void *user_data;
    
    
    /*
     PLEASE ADD COMMENTS HERE
     */
    void (*on_stream_created)(otc_publisher *publisher, 
                              void *user_data, 
                              const otc_stream *stream);
    
    /*
     PLEASE ADD COMMENTS HERE
     */
    void (*on_stream_destroyed)(otc_publisher *publisher, 
                                void *user_data, 
                                const otc_stream *stream);
    
    /*
     PLEASE ADD COMMENTS HERE
     */
    void (*on_render_frame)(otc_publisher *publisher, 
                            void *user_data, 
                            const otc_video_frame *frame);
    /*
     PLEASE ADD COMMENTS HERE
     */
    void (*on_error)(otc_publisher *publisher,
                     void *user_data,
                     const char* error_string,
                     enum otc_publisher_error error_code);
    
    void *reserved;
};

#define OTC_DEFAULT_VIDEO_CAPTURER NULL

typedef struct otc_publisher_settings otc_publisher_settings;

/**
 * Creates a new otc_publisher_settings instance. Use the 
 * {@link otc_publisher_new_ex} method
 * to create a publisher with settings.
 *
 * @return A new otc_publisher_settings instance
 */
OTC_DECL(otc_publisher_settings *) otc_publisher_settings_new();

/**
 * Deletes an otc_publisher_settings instance.
 *
 * @param settings the otc_publisher_settings object to be affected
 * @return A new otc_publisher_settings instance
 */
OTC_DECL(otc_status_t) otc_publisher_settings_delete(otc_publisher_settings *settings);

/**
 * Sets the desired name for a publisher to be constructed with 
 * {@link otc_publisher_new_ex}
 *
 * @param settings the otc_publisher_settings object to be affected
 * @param name the name for a publisher to be constructed with 
 * {@link otc_publisher_new_ex}
 * @return A new otc_publisher_settings instance
 */
OTC_DECL(otc_status_t) otc_publisher_settings_set_name(otc_publisher_settings *settings,
                                                       const char *name);

/**
 * Sets the desired capturer for a publisher to be constructed with 
 * {@link otc_publisher_new_ex}.
 *
 * @param settings the otc_publisher_settings object to be affected
 * @param capturer the capturer for a publisher to be constructed with 
 * {@link otc_publisher_new_ex}
 * @return A new otc_publisher_settings instance
 */
OTC_DECL(otc_status_t) otc_publisher_settings_set_capturer(otc_publisher_settings *settings,
                                                           const struct otc_video_capturer_cb *capturer);

/**
 * Enables an audio track for a publisher to be constructed with 
 * {@link otc_publisher_new_ex}
 *
 * @param settings the otc_publisher_settings object to be affected
 * @param enabled enable/disable the existence of an audio track for 
 * a publisher to be constructed with {@link otc_publisher_new_ex}
 * @return A new otc_publisher_settings instance
 */
OTC_DECL(otc_status_t) otc_publisher_settings_set_audio_track(otc_publisher_settings *settings,
                                                              otc_bool_t enabled);

/**
 * Enables a video track for a publisher to be constructed with 
 * {@link otc_publisher_new_ex}
 *
 * @param settings the otc_publisher_settings object to be affected
 * @param enabled enable/disable the existence of an video track for 
 * a publisher to be constructed with {@link otc_publisher_new_ex}
 * @return A new otc_publisher_settings instance
 */
OTC_DECL(otc_status_t) otc_publisher_settings_set_video_track(otc_publisher_settings *settings,
                                                              otc_bool_t enabled);


/**
* Creates a new Publisher instance. Use the {@link otc_session_publish} method
* to start streaming from this Publisher into a session.
* <p>
* Publishers cannot be reused
* 
* @param name The name of the publisher
* @param capturer use this parameter if you want to provide a custom capturer. Use NULL if you prefer to use webrtc's default
* @param callbacks struct with publisher callback function pointers
*
* @return a new Publisher instance
*/
OTC_DECL(otc_publisher *) otc_publisher_new(const char *name, 
                                            const struct otc_video_capturer_cb *capturer,
                                            const struct otc_publisher_cb *callbacks);


/**
 * Creates a new Publisher instance. Use the {@link otc_session_publish} method
 * to start streaming from this Publisher into a session.
 * <p>
 * Publishers cannot be reused
 *
 * @param callbacks struct with publisher callback function pointers
 * @param settings the settings struct containing the desired settings for the publisher
 * @param error the returned error code
 * @return a new Publisher instance
 */
OTC_DECL(otc_publisher *) otc_publisher_new_ex(const struct otc_publisher_cb *callbacks,
                                               otc_publisher_settings *settings,
                                               int *error);

/**
* Releases this object, including all hardware resources bound to it.
*
* @param publisher the publisher which will me affected
*/
OTC_DECL(otc_status_t) otc_publisher_delete(otc_publisher *publisher);

/**
* Returns the stream associated with the publisher
*
* @param publisher the publisher which will me affected
* @return the stream associated with the publisher
*/
OTC_DECL(otc_stream *) otc_publisher_get_stream(otc_publisher *publisher);

/**
* Whether to publish video or not. By default, streams publish both audio and video.
*
* @param publisher the publisher which will me affected
* @param publish_video Whether to publish video (true) or not (false)
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_publisher_set_publish_video(otc_publisher *publisher, 
                                                       otc_bool_t publish_video);

/**
* Whether to publish audio or not. By default, streams publish both audio and video.
*
* @param publisher the publisher which will me affected
* @param publish_audio Whether to publish audio (true) or not (false)
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_publisher_set_publish_audio(otc_publisher *publisher, 
                                                       otc_bool_t publish_audio);

/**
* Returns true if the Publisher is publishing video; false if it is not.
* 
* @param publisher the publisher which will me affected
* @return true/false if the publisher is publishing video 
*/
OTC_DECL(otc_bool_t) otc_publisher_get_publish_video(const otc_publisher *publisher);

/**
* Returns true if the Publisher is publishing audio; false if it is not.
* @param publisher the publisher which will me affected
* @return true/false if the publisher is publishing audio
*/
OTC_DECL(otc_bool_t) otc_publisher_get_publish_audio(const otc_publisher *publisher);

/**
* Returns the {@link Session} associated this instance.
*
* @param publisher the publisher which will me affected
* @return The {@link Session} associated this instance.
*/
OTC_DECL(otc_session *) otc_publisher_get_session(otc_publisher *publisher);

/**
 * sets the max audio bitrate for the publisher
 *
 * @param publisher the publisher which will me affected
 * @param bitrate the desired bitrate
 */
OTC_DECL(void) otc_publisher_set_max_audio_kbps(otc_publisher* publisher, 
                                                uint32_t bitrate);


/**
 * queries a unique identifier for this publisher
 *
 * @param publisher the publisher which is to be queried
 * @return A unique identifier for this publisher
 */
OTC_DECL(const char *) otc_publisher_get_publisher_id(const otc_publisher* publisher);

/**
 * sets the publishers video type
 *
 * @param publisher the publisher to be affected
 * @param video_type the video type of the publisher
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t)
otc_publisher_set_video_type(struct otc_publisher* publisher,
                             enum otc_publisher_video_type video_type);
/**
 * query the video type of the publisher
 *
 * @param publisher the publisher to be queried
 * @return the video type of the publisher
 */
OTC_DECL(enum otc_publisher_video_type)
otc_publisher_get_video_type(const struct otc_publisher* publisher);


OTC_END_DECL

#endif // PUBLISHER_H

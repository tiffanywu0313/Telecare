/** @file */
#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "config.h"
#include "stream.h"
#include "error.h"

OTC_BEGIN_DECL

// forward declaration
#ifndef OTC_SESSION_FWD_DECL
#define OTC_SESSION_FWD_DECL
typedef struct otc_session otc_session;
#endif

/**
* Consumes audio and video of a publisher in the OpenTok session. Subscribers are created
* by passing a valid otc_stream instance into {@link otc_subscriber_new}
* and can connect to receive media with {@link otc_session_subscribe}.
*/
typedef struct otc_subscriber otc_subscriber;

enum otc_video_reason
{
    OTC_VIDEO_REASON_PUBLISH_VIDEO = 1,
    OTC_VIDEO_REASON_SUBSCRIBE_TO_VIDEO = 2,
    OTC_VIDEO_REASON_QUALITY = 3
};

enum otc_subscriber_error
{
    OTC_SUBSCRIBER_SUCCESS = 0,
    OTC_SUBSCRIBER_TIMED_OUT = 1542,
    OTC_SUBSCRIBER_SESSION_DISCONNECTED = 1541,
    OTC_SUBSCRIBER_WEBRTC_ERROR = 1600,
    OTC_SUBSCRIBER_SERVER_CANNOT_FIND_STREAM = 1604,
    OTC_SUBSCRIBER_STREAM_LIMIT_EXCEEDED = 1605,
    OTC_SUBSCRIBER_INTERNAL_ERROR = 2000,
};

struct otc_audio_stats {
  uint64_t packets_lost;
  uint64_t packets_received;
  uint64_t bytes_received;
  double timestamp;
};

struct otc_video_stats {
  uint64_t packets_lost;
  uint64_t packets_received;
  uint64_t bytes_received;
  double timestamp;
};

// callbacks
struct otc_subscriber_cb
{
    void *user_data;

    /**
    * Invoked when the instance has successfully connected to the stream and begins playing media.
    *
    * @param subscriber The instance invoking this call.
    * @param user_data pointer to user custom data bound to this struct
    * @param stream The stream associated with this event
    */
    void (*on_connected)(otc_subscriber *subscriber,
                         void *user_data, 
                         const otc_stream *stream);

    /**
    * Invoked when the video receiving has been stopped
    *
    * @param subscriber The instance invoking this call.
    * @param user_data pointer to user custom data bound to this struct
    * @param stream The stream associated with this event    
    */
    void (*on_stream_disconnected)(otc_subscriber *subscriber,
                                   void *user_data);
    
    /**
     * Invoked when the video has resumed on the subscriber
     *
     * @param subscriber The instance invoking this call.
     * @param user_data pointer to user custom data bound to this struct
     * @param stream The stream associated with this event
     */
    void (*on_stream_reconnected)(otc_subscriber *subscriber,
                                  void *user_data);
    
    /**
    * Invoked everytime a frame is ready to be renderer.
    * @param subscriber The instance invoking this call.
    * @param user_data pointer to user custom data bound to this struct
    * @param frame The video frame
    */
    void (*on_render_frame)(otc_subscriber *subscriber,
                            void *user_data, 
                            const otc_video_frame *frame);
        
    /**
    * Invoked when the subscriber had his video disconnected.
    *
    * @param subscriber The instance invoking this call.
    * @param reason Gives more details about why the video has been disabled.
    */
    void (*on_video_disabled)(otc_subscriber* subscriber,
                              void *user_data,
                              enum otc_video_reason reason);
    
    /**
    * Invoked everytime a frame is ready to be renderer.
    *
    * @param subscriber The instance invoking this call.
    * @param reason Gives more details about why the video has been enabled
    */
    void (*on_video_enabled)(otc_subscriber* subscriber,
                             void *user_data,
                             enum otc_video_reason reason);

    // TO DO - onError callback
  
    void (*on_error)(otc_subscriber* subscriber,
                     void *user_data,
                     const char* error_string,
                     enum otc_subscriber_error error);
  

    void (*on_video_disable_warning)(otc_subscriber* subscriber,
                             void *user_data);

    void (*on_video_disable_warning_lifted)(otc_subscriber* subscriber,
                                      void *user_data);

    void(*on_audio_network_stats)(otc_subscriber* subscriber,
                                  struct otc_audio_stats audio_stats);

    void(*on_video_network_stats)(otc_subscriber* subscriber,
                                  struct otc_video_stats video_stats);

    
    void *reserved;
};

/**
* Creates a new Subscriber for a given Stream. To begin subscribing to this Subscriber, pass it into the
* {@link otc_session_subscribe} method.
*
* @param stream The Stream object corresponding to the stream you will subscribe to.
* @param callbacks Struct with function pointers of the subscriber's callbacks.
*
* @return The new Subscriber instance.
*/
OTC_DECL(otc_subscriber *) otc_subscriber_new(const otc_stream *stream,
                                              const struct otc_subscriber_cb *callbacks);

/**
* Releases this object, including all hardware and UI resources bound to it.
*
* @param subscriber the publisher which will be affected
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_subscriber_delete(otc_subscriber *subscriber);


/**
* query the subscriber for the stream its associated with
*
* @return The stream that this instance is bound to
*/
OTC_DECL(otc_stream *) otc_subscriber_get_stream(otc_subscriber *subscriber);

/**
* Subscribe to the stream's video.
* Setting this property has no effect if the Stream hasVideo property is set to NO.
*
* @param subscriber the subscriber to be affected
* @param subscribe_to_video enable/disable subscribing to video
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_subscriber_set_subscribe_to_video(otc_subscriber *subscriber,
                                                             otc_bool_t subscribe_to_video);

/**
* Subscribe to the stream's audio.
* Setting this property has no effect if the Stream hasAudio property is set to NO.
*
* @param subscriber the subscriber to be affected
* @param subscribe_to_audio enable/disable subscribing to audio
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_subscriber_set_subscribe_to_audio(otc_subscriber *subscriber,
                                                             otc_bool_t subscribe_to_audio);

/**
* Returns subscribed to the stream's video
*
* @param subscriber the subscriber being queried
* @return subscribed to the stream's video
*/
OTC_DECL(otc_bool_t) otc_subscriber_get_subscribe_to_video(const otc_subscriber *subscriber);

/**
* Returns  subscribed to the stream's audio
*
* @param subscriber the subscriber being queried
* @return subscribed to the stream's audio
*/
OTC_DECL(otc_bool_t) otc_subscriber_get_subscribe_to_audio(const otc_subscriber *subscriber);

/**
* Returns the session that created this instance
* @see otc_subscriber_new
*
* @param subscriber the subscriber being queried
* @return the session that created this instance
*/
OTC_DECL(otc_session *) otc_subscriber_get_session(otc_subscriber *subscriber);

/**
 * Set a preferred video resolution for the subscriber
 *
 * @param subscriber the subscriber to be affected
 * @param preferred_width the preferred width of the subscriber
 * @param preferred_height the preferred height of the subscriber
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_set_preferred_resolution(otc_subscriber *subscriber,
                                                               uint32_t preferred_width, uint32_t preferred_height);
/**
 * returns the preferred video resolution
 *
 * @param subscriber the subscriber being queried
 * @param preferred_width the preferred width of the subscriber
 * @param preferred_height the preferred height of the subscriber
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_get_preferred_resolution(const otc_subscriber *subscriber, uint32_t *preferred_width, uint32_t *preferred_height);

/**
 * set a preferred framerate for the subscriber
 *
 * @param subscriber the subscriber to be affected
 * @param preferred_framerate the preferred framerate of the publisher
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_set_preferred_framerate(otc_subscriber *subscriber,
                                                               float preferred_framerate);

/**
 * returns the preferred framerate for the subscriber
 *
 * @param subscriber the subscriber being queried
 * @param preferred_framerate the returned the preferred framerate associated with the subscriber
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_get_preferred_framerate(const otc_subscriber *subscriber,
                                                              float *preferred_framerate);


/**
 * query a unique identifier for this subscriber
 *
 * @param subscriber the subscriber to be queried
 * @return a unique identifier for this subscriber
 */
OTC_DECL(const char *) otc_subscriber_get_subscriber_id(const otc_subscriber* subscriber);


OTC_END_DECL

#endif // SUBSCRIBER_H

/** @file */
#ifndef SESSION_H
#define SESSION_H

#include "capabilities.h"
#include "config.h"
#include "publisher.h"
#include "subscriber.h"
#include "stream.h"

OTC_BEGIN_DECL

/**
* @struct otc_session
* The first step in using the OpenTok C SDK is to initialize
* a Session instance by calling the {@link otc_session_new} method.
* <p>
* When you create the Session instance, you pass in the OpenTok session ID, token, and API key.
* You get an API key when you
* <a href="https://dashboard.tokbox.com/users/sign_in">sign up</a> for an OpenTok account.
* For test purposes, you can generate test session IDs and tokens using the
* <a href="https://dashboard.tokbox.com">OpenTok dashboard</a>.
* Use the <a href="http://www.tokbox.com/opentok/docs/server/server_side_libraries.html">OpenTok
* server-side libraries</a> to generate session IDs and tokens in your shipping app.
* <p>
*
* @see <a href="http://www.tokbox.com/opentok/api/tools//documentation/overview/session_creation.html">Session Creation</a>
* @see <a href="http://www.tokbox.com/opentok/api/tools/documentation/overview/token_creation.html">Token Creation</a>
*/

// opaque struct
#ifndef OTC_SESSION_FWD_DECL
#define OTC_SESSION_FWD_DECL
typedef struct otc_session otc_session;
#endif

struct otc_session_network_stats
{
    int upload_bits_per_second;
    int download_bits_per_second;
    float packet_loss_ratio;
    int round_trip_time_milliseconds;
};

struct otc_signal_options
{
  otc_bool_t retry_after_reconnect;
};

enum otc_session_network_stats_result
{
    OTC_NETWORK_STATS_RESULT_ERROR = 0,
    OTC_NETWORK_STATS_RESULT_OK
};

enum otc_session_error
{
    OTC_SESSION_SUCCESS = 0,
    OTC_SESSION_AUTHORIZATION_FAILURE = 1004,
    OTC_SESSION_INVALID_SESSION = 1005,
    OTC_SESSION_CONNECTION_FAILED = 1006,
    OTC_SESSION_NULL_OR_INVALID_PARAMETER = 1011,
    OTC_SESSION_NOT_CONNECTED = 1010,
    OTC_SESSION_ILLEGAL_STATE = 1015,
    OTC_SESSION_NO_MESSAGING_SERVER = 1503,
    OTC_SESSION_CONNECTION_REFUSED = 1023,
    OTC_SESSION_STATE_FAILED = 1020,
    OTC_SESSION_CONNECTION_TIMED_OUT = 1021,
    OTC_SESSION_INTERNAL_ERROR = 2000,
    OTC_SESSION_INVALID_SIGNAL_TYPE = 1461,
    OTC_SESSION_SIGNAL_DATA_TOO_LONG = 1413,
    OTC_SESSION_SIGNAL_TYPE_TOO_LONG = 1414,
    OTC_SESSION_CONNECTION_DROPPED = 1022,
    OTC_SESSION_SUBSCRIBER_NOT_FOUND = 1112,
    OTC_SESSION_PUBLISHER_NOT_FOUND = 1113,
    OTC_SESSION_BLOCKED_COUNTRY = 1026,
    OTC_SESSION_CONNECTION_LIMIT_EXCEEDED = 1027,
    OTC_SESSION_UNEXPECTED_GET_SESSION_INFO_REPONSE = 2001,
    OTC_SESSION_UNABLE_TO_FORCE_UNPUBLISH = 1530,
    OTC_SESSION_FORCE_UNPUBLISH_OR_INVALID_STREAM = 1535,
    OTC_SESSION_UNABLE_TO_FORCE_DISCONNECT = 1520,
};

// callbacks
struct otc_session_cb
{
    void *user_data;

    /**
    * Invoked after the {@link otc_session_connect} method successfully connects the instance
    * to an OpenTok session.
    */
    void (*on_connected)(otc_session *session, void *user_data);

    /**
    * Invoked when the instance is no longer connected to its OpenTok session.
    */
    void (*on_disconnected)(otc_session *session, void *user_data);

    void (*on_connection_created)(otc_session *session,
                                  const otc_connection *connection,
                                  void *user_data);
    
    void (*on_connection_dropped)(otc_session *session,
                                  const otc_connection *connection,
                                  void *user_data);
    
    /**
    * Invoked when a there is a new stream this OpenTok session.
    * @see otc_subscriber_new
    *
    * @param stream A descriptor of the new stream, which can be used to create a otc_subscriber.
    */
    void (*on_stream_received)(otc_session *session,
                               void *user_data,
                               const otc_stream *stream);

    /**
    * Invoked when a publisher leaves this OpenTok session.
    *
    * @param stream A descriptor of the dropped stream, which can be used to identify a otc_subscriber.
    */
    void (*on_stream_dropped)(otc_session *session,
                              void *user_data,
                              const otc_stream *stream);
    /*ADD COMMENTS*/
    void (*on_stream_has_audio_changed)(otc_session *session,
                                        void *user_data,
                                        const otc_stream *stream,
                                        otc_bool_t has_audio);
    
    /*ADD COMMENTS*/
    void (*on_stream_has_video_changed)(otc_session *session,
                                        void *user_data,
                                        const otc_stream *stream,
                                        otc_bool_t has_video);
    
    /*ADD COMMENTS*/
    void (*on_stream_video_dimensions_changed)(otc_session *session,
                                               void *user_data,
                                               const otc_stream *stream,
                                               int width,
                                               int height);
    /**
    * Invoked when something goes wrong when connecting or connected to the session.
    * After this callback is invoked, the Session should be treated as dead and unavailable.
    * Do not attempt to reconnect or invoke further instructions on the session.
    * @param exception An exception describing the cause for error.
    */
    void (*on_error)(otc_session *session,
                     void *user_data,
                     const char* error_string,
                     enum otc_session_error error);

    void (*on_signal_received)(otc_session *session,
                               void *user_data,
                               const char *type,
                               const char *signal,
                               const otc_connection *connection);

    void (*on_reconnection_start)(otc_session *session, void *user_data);

    void (*on_reconnection_success)(otc_session *session, void *user_data);
    
    void (*on_archive_started)(otc_session *session,
                               void *user_data,
                               const char* archive_id,
                               const char* name);
    
    void (*on_archive_stopped)(otc_session *session,
                               void *user_data,
                               const char* archive_id);
    
    void *reserved;
};

/**
* Use this factory method to create a Session instance.
* @param session_id The OpenTok session ID this instance should connect to.
* For test purposes, you can generate test session using the
* <a href="https://dashboard.tokbox.com">OpenTok dashboard</a>.
* Use the <a href="http://www.tokbox.com/opentok/docs/server/server_side_libraries.html">OpenTok
* server-side libraries</a> to generate session IDs in your shipping app.
* For test purposes, you can generate test tokens using the
* <a href="https://dashboard.tokbox.com">OpenTok dashboard</a>.
* Use the <a href="http://www.tokbox.com/opentok/docs/server/server_side_libraries.html">OpenTok
* server-side libraries</a> to generate tokens in your shipping app.
* <a href="https://dashboard.tokbox.com/users/sign_in">sign up</a> for an OpenTok account.
*
* @return A new Session object.
*/
OTC_DECL(otc_session *) otc_session_new(const char *apikey,
                                        const char *session_id,
                                        const struct otc_session_cb *callbacks);



typedef struct otc_session_settings otc_session_settings;

/**
 * creates a new otc_session_settings instance. Use the {@link otc_session_new_ex} method
 * to create a session with settings.
 *
 * @return a new otc_session_settings_new instance
 */
OTC_DECL(otc_session_settings *) otc_session_settings_new();

/**
 * deletes an otc_session_settings instance. 
 *
 * @param settings the otc_session_settings object to be affected
 * @return an error in the event of an error otherwise OTC_SESSION_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_settings_delete(otc_session_settings *settings);

/**
 * enables the suppression of connection events
 *
 * @param settings the otc_session_settings object to be affected
 * @param suppress enable/disable of suppression of connection events.
 * @return an error in the event of an error otherwise OTC_SESSION_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_settings_set_connection_events_suppressed(otc_session_settings *settings,
                                                       otc_bool_t suppress);

/**
 * Use this factory method to create a Session instance.
 * @param session_id The OpenTok session ID this instance should connect to.
 * For test purposes, you can generate test session using the
 * <a href="https://dashboard.tokbox.com">OpenTok dashboard</a>.
 * Use the <a href="http://www.tokbox.com/opentok/docs/server/server_side_libraries.html">OpenTok
 * server-side libraries</a> to generate session IDs in your shipping app.
 * For test purposes, you can generate test tokens using the
 * <a href="https://dashboard.tokbox.com">OpenTok dashboard</a>.
 * Use the <a href="http://www.tokbox.com/opentok/docs/server/server_side_libraries.html">OpenTok
 * server-side libraries</a> to generate tokens in your shipping app.
 * <a href="https://dashboard.tokbox.com/users/sign_in">sign up</a> for an OpenTok account.
 *
 * @return a new Session object.
 */
OTC_DECL(otc_session *) otc_session_new_ex(const char *apikey,
                                        const char *session_id,
                                        const struct otc_session_cb *callbacks,
                                        otc_session_settings *settings);


/**
* releases this object.
*
* @param session the session which will me affected
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_delete(otc_session *session);

/**
* connects to the OpenTok session provided by {@link otc_session_new} using the provided authentication token.
* <p>
* When the session connects, the {@link on_connected} callback is called.
* <p>
* If the session fails to connect, the {@link on_error}
* callback is called.
* <p>
* @param session the otc_session object to be affected
* @param token the connection token to be used to establish a connection
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_connect(otc_session *session,
                                           const char *token);

/**
* Disconnects from this session. All Subscriber and Publisher instances will be disconnected.
* <p>
* When the session disconnects, the {@link #on_disconnected} callback is called.
* <p>
* @param session the otc_session object to be affected
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_disconnect(otc_session *session);


/**
* Starts a otc_publisher streaming to the session.
*
* @param session the desired otc_session which to publish to
* @param publisher the publisher which to publish to the session
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_publish(otc_session *session,
                                           otc_publisher *publisher);

/**
* Disconnects the otc_publisher from the session.
*
* @param session the desired otc_session which to unpublish from
* @param publisher the publisher to unpublish
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_unpublish(otc_session *session,
                                             otc_publisher *publisher);

/**
* Starts subscribing to a subscriber's audio-video stream in this session.
* @see on_stream_received
* <p>
* @param session the desired otc_session which to subscribe to
* @param subscriber The subscriber to subscribe to
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_subscribe(otc_session *session,
                                             otc_subscriber *subscriber);

/**
* Stops subscribing (receiving a stream) to a specified subscriber in the session.
* <p>
* @param session the desired otc_session which to unsubscribe from
* @param subscriber the subcriber you want to stop subscribing to.
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_session_unsubscribe(otc_session *session,
                                               otc_subscriber *subscriber);

/**
 * sends a signal to all connections in the session
 * <p>
 * @param session the desired otc_session to send a signal to
 * @param type the type/name of the signal to send
 * @param signal the data of that signal
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_send_signal(otc_session *session,
                                               const char *type,
                                               const char *signal);
/**
 * sends a signal to a connection in the session
 * <p>
 * @param session the desired otc_session to send a signal to
 * @param type the type/name of the signal to send
 * @param signal the data of that signal
 * @param connection the connection to send the signal to
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_send_signal_to_connection(otc_session *session,
                                               const char *type,
                                               const char *signal,
                                               const otc_connection *connection);
/**
 * sends a signal to a connection with particular options
 * <p>
 * @param session the desired otc_session to send a signal to
 * @param type the type/name of the signal to send
 * @param signal the data of that signal
 * @param signal_options the options related to the signal to send
 * @param connection the connection to send the signal to
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t)
otc_session_send_signal_with_options(otc_session *session,
                                     const char *type,
                                     const char *signal,
                                     struct otc_signal_options signal_options,
                                     const otc_connection *connection);
/**
 * get the connection object associated with this session
 * <p>
 * @param session the desired otc_session of which the returned connection object is from
 * @return the connection object associated with this session
 */
OTC_DECL(otc_connection *) otc_session_get_connection(const otc_session *session);

/**
 * Get the capabilities of the session. All Capabilities properties are undefined 
 * until on_connected has been called.
 * <p>
 * @param session the otc_session to query
 * @return the struct of session capabilities
 */
OTC_DECL(struct otc_capabilities) otc_session_capabilities(const otc_session *session);


OTC_END_DECL

#endif // SESSION_H

#ifndef INTERNAL_H
#define INTERNAL_H

#include "config.h"
#include "publisher.h"
#include "session.h"
#include "subscriber.h"

OTC_BEGIN_DECL

OTC_DECL(otc_status_t) otc_session_connect_to_host(otc_session *session,
                                                  const char *hostname,
                                                  const char *server_path,
                                                  int port,
                                                  otc_bool_t ssl,
                                                  const char *token);

OTC_DECL(otc_status_t) otc_session_reconnect(otc_session *session);

OTC_DECL(void) otc_session_ice_restart(otc_session *session);

/**
 * force a disconnection of a connection
 * <p>
 * @param session the otc_session that the connection is part of
 * @param connection the connection to disconnect
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_force_disconnect(otc_session *session,
                                                    otc_connection *connection);

/**
 * force unpublishing from a stream
 * <p>
 * @param session the otc_session that the stream is part of
 * @param stream the stream to disconnect
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_force_unpublish(otc_session *session,
                                                   otc_stream *stream);
/**
 * query if a session is in the process of reconnecting
 * <p>
 * @param session the otc_session in question
 * @param value the true/false value regarding if the session is reconnecting
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_session_is_reconnecting(otc_session *session,
                                                   otc_bool_t *value);

/**
 * enable connection reconnection and renegotiation on session
 * <p>
 * @param session the otc_session to be affected
 * @param reconnection enable/disable reconnections
 * @param renegotiation enable/disable renegotiation
 */
OTC_DECL(void) otc_session_set_reconnection_enabled(otc_session *session,
                                                    otc_bool_t reconnection,
                                                    otc_bool_t renegotiation);





OTC_DECL(void) otc_get_sdk_version(char* buf, int nSize);

typedef void (*otc_create_codec_factories_callback)();

OTC_DECL(void) otc_set_create_codec_factories_callback(otc_create_codec_factories_callback callback);

/**
 * Has a H264 built-in decoder/encoder. Used for testing on Linux and Mac.
 * In order to enable H264 with internal webrtc h264 implementation (e.g. Linux)
 * "h264" hoolock property should be true.
 */
OTC_DECL(void) otc_set_h264_as_priority_codec(otc_bool_t h264_as_default);

OTC_DECL(void) otc_session_set_video_codecs_enabled (struct otc_session* session,
                                                    const char *priority_video_codec,
                                                    const char enable_h264,
                                                    const char enable_vp9);

enum otc_client_candidates {
    otc_client_candidates_default = 0,
    otc_client_candidates_all = 1,
    otc_client_candidates_relayed = 2
};

OTC_DECL(void) otc_session_set_client_candidates(struct otc_session* session, enum otc_client_candidates client_candidates);

OTC_DECL(void) otc_session_restore_client_candidates_to_original(struct otc_session* session);

OTC_DECL(const char *) otc_session_get_client_candidates(struct otc_session* session);

OTC_DECL(void) otc_session_set_gcm_crypto_suites(struct otc_session* session, otc_bool_t gcm_crypto_suites);

OTC_DECL(void) otc_session_restore_gcm_crypto_suites_to_original(struct otc_session* session);

OTC_DECL(const otc_bool_t) otc_session_get_gcm_crypto_suites(struct otc_session* session);

struct timeval;
/**
 * @todo TODO Doc this
 * caller must free output values
 */

OTC_DECL(otc_status_t) otc_publisher_get_stat(otc_publisher* publisher,
                                              const char* peer_id,
                                              int64_t peer_priority,
                                              const char* sz_key,
                                              char** sz_value_out,
                                              struct timeval** last_updated_out);


/**
 * sets the max video bitrate for the publisher
 *
 * @param publisher the publisher which will me affected
 * @param bitrate the desired bitrate
 */
OTC_DECL(void) otc_publisher_set_max_video_kbps(otc_publisher* publisher,
                                                uint32_t bitrate);

/**
 * query the simulcast streams associated with a publisher. The caller
 * must free the output array.
 *
 * @param publisher the publisher which is to be queried
 * @param peer_id the id of the peer connection
 * @param num_ssrcs_out is set to the number of simulcast stream ids returned
 * @param ssrcs_out array of simulcast stream ids
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_publisher_get_streams(const otc_publisher* publisher,
                                                 const char* peer_id,
                                                 int64_t peer_priority,
                                                 size_t* num_ssrcs_out,
                                                 int64_t** ssrcs_out);

/**
 * query the audio simulcast streams associated with a publisher. The caller
 * must free the output array.
 *
 * @param publisher the publisher which is to be queried
 * @param peer_id the id of the peer connection
 * @param num_ssrcs_out is set to the number of simulcast stream ids returned
 * @param ssrcs_out array of simulcast stream ids
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_publisher_get_audio_streams(const otc_publisher* publisher,
                                                       const char* peer_id,
                                                       int64_t peer_priority,
                                                       size_t* num_ssrcs_out,
                                                       int64_t** ssrcs_out);

/**
 * query the video simulcast streams associated with a publisher. The caller
 * must free the output array.
 *
 * @param publisher the publisher which is to be queried
 * @param peer_id the id of the peer connection
 * @param num_ssrcs_out is set to the number of simulcast stream ids returned
 * @param ssrcs_out array of simulcast stream ids
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_publisher_get_video_streams(const otc_publisher* publisher,
                                                       const char* peer_id,
                                                       int64_t peer_priority,
                                                       size_t* num_ssrcs_out,
                                                       int64_t** ssrcs_out);

/**
 * @todo TODO Doc this
 * caller must free output values
 */

OTC_DECL(otc_status_t) otc_publisher_get_stream_stat(otc_publisher* publisher,
                                                     const char* peer_id,
                                                     int64_t peer_priority,
                                                     int64_t ssrc,
                                                     const char* sz_key,
                                                     char** sz_value_out,
                                                     struct timeval** last_updated_out);

OTC_DECL(void) otc_publisher_generate_arbitrary_error(otc_publisher* publisher,
                                                           int errorcode);

/**
 * Query the simulcast streams associated with a subscriber. The caller must free output values.
 *
 * @param subscriber subscriber to be queried
 * @param num_ssrcs_out the returned number of simulcast stream ids
 * @param ssrcs_out the array of simulcast stream ids
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_get_streams(const otc_subscriber* subscriber,
                                                  size_t* num_ssrcs_out,
                                                  int64_t** ssrcs_out);

/**
 * Query the audio simulcast streams associated with a subscriber. The caller must free output values.
 *
 * @param subscriber subscriber to be queried
 * @param num_ssrcs_out the returned number of simulcast stream ids
 * @param ssrcs_out the array of simulcast stream ids
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_get_audio_streams(const otc_subscriber *subscriber,
                                                        size_t* num_ssrcs_out,
                                                        int64_t** ssrcs_out);

/**
 * Query the video simulcast streams associated with a subscriber. The caller must free output values.
 *
 * @param subscriber subscriber to be queried
 * @param num_ssrcs_out the returned number of simulcast stream ids
 * @param ssrcs_out the array of simulcast stream ids
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_subscriber_get_video_streams(const otc_subscriber *subscriber,
                                                        size_t* num_ssrcs_out,
                                                        int64_t** ssrcs_out);

/**
 * @todo TODO Doc this
 * caller must free output values
 */

OTC_DECL(otc_status_t) otc_subscriber_get_stat(otc_subscriber* subscriber,
                                               const char* sz_key,
                                               char** sz_value_out,
                                               struct timeval** last_updated_out);

/**
 * @todo TODO Doc this
 * caller must free output values
 */

OTC_DECL(otc_status_t) otc_subscriber_get_stream_stat(otc_subscriber* subscriber,
                                                      int64_t ssrc,
                                                      const char* sz_key,
                                                      char** sz_value_out,
                                                      struct timeval** last_updated_out);

OTC_DECL(void) otc_subscriber_generate_arbitrary_error(otc_subscriber* subscriber,
                                                       int errorcode);

/**
 * query the video simulcast streams associated with a publisher. The caller
 * must free the output array.
 *
 * @param publisher the publisher which is to be queried
 * @param peer_id the id of the peer connection
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_publisher_get_peer_id_and_priority(const otc_publisher* publisher,
                                                       const char** peer_id,
                                                       int64_t* peer_priority);

/**
 * Used by QA only for performace testing !
 * In order to reduce unnecessary load in some tests, and therefore reduce costs, 
 * we discard frames right before decoding them. Should be called after calling otc_init.
 */
OTC_DECL(void) otc_fake_video_factories(otc_bool_t encoder, otc_bool_t decoder);
OTC_DECL(int) otc_fake_decoder_number_frames_decoded();
OTC_DECL(int) otc_fake_encoder_number_frames_encoded();
OTC_DECL(int) otc_fake_encoder_kbps(const char* codec_type);

OTC_END_DECL

#endif // INTERNAL_H

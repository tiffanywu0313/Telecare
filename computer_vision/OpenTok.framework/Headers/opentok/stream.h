/** @file */
#ifndef STREAM_H
#define STREAM_H

#include "config.h"
#include "connection.h"

OTC_BEGIN_DECL

/**
* Used to describe a stream bound to an OpenTok session. The {@link on_stream_received}
* callback notifies you of new streams in the session:
* <p>
* The {@link on_stream_dropped} method notifies when streams are unpublished the session.
* @author charley
*
*/
typedef struct otc_stream otc_stream;

enum otc_publisher_video_type {
    OTC_PUBLISHER_VIDEO_TYPE_CAMERA = 1,
    OTC_PUBLISHER_VIDEO_TYPE_SCREEN = 2,
};

/**
* Gets a unique identifier for this stream.
* @param stream the stream being queried
* @return A unique identifier for this stream.
*/
OTC_DECL(const char *) otc_stream_get_id(const otc_stream *stream);

/**
* The name of the stream. It can specify a published stream's name.
* @param stream the stream being queried
* @return name of the stream
*/
OTC_DECL(const char *) otc_stream_get_name(const otc_stream *stream);

/**
* Whether this stream has video (true) or not (false).
* @param stream the stream being queried
* @return true or false indicating if the stream has video.
*/
OTC_DECL(otc_bool_t) otc_stream_has_video(const otc_stream *stream);

/**
* Whether this stream has audio (true) or not (false).
* @param stream the stream being queried
* @return true or false indicating if the stream has audio.
*/
OTC_DECL(otc_bool_t) otc_stream_has_audio(const otc_stream *stream);

/**
* Make a copy of this object. In session callbacks where a stream is sent by parameters, you need to copy the stream
* if you plan to keep the instance longer than the life of the callback.
*
* @param stream The stream to be copied
* @return the copied stream
*/
OTC_DECL(otc_stream *) otc_stream_copy(const otc_stream *stream);

/**
* Releases this object, including all hardware resources bound to it.
*
* @param stream the stream which will me affected
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_stream_delete(otc_stream *stream);

/**
* query the width in pixels of the video stream
*
* @param stream the stream which to query
* @return the pixel width of the stream
*/
OTC_DECL(int) otc_stream_get_video_width(const otc_stream *stream);

/**
* query the height in pixels of the video stream
*
* @param stream the stream which to query
* @return the pixel height of the stream
*/
OTC_DECL(int) otc_stream_get_video_height(const otc_stream *stream);

/**
* query the creation time of the stream
*
* @param stream the stream which to query
* @return the creation time of the stream
*/
OTC_DECL(int64_t) otc_stream_get_creation_time(const otc_stream *stream);

/**
* query the video type of the stream
*
* @param stream the stream which to query
* @return the video type of the stream
*/
OTC_DECL(enum otc_publisher_video_type) otc_stream_get_video_type(const otc_stream *stream);

/**
* get the connection associated with the stream
*
* @param stream the stream in question
* @return the connection associated with the stream
*/
OTC_DECL(const otc_connection *) otc_stream_get_connection(const otc_stream * stream);


OTC_END_DECL

#endif // STREAM_H

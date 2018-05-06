/** @file */
#ifndef VIDEOFRAME_H
#define VIDEOFRAME_H

#ifndef _WIN32
#include <unistd.h>
#endif

#include "config.h"

OTC_BEGIN_DECL

/**
* Represents a single video frame coming from any stream
*/
typedef struct otc_video_frame otc_video_frame;

enum otc_video_frame_format
{
    OTC_VIDEO_FRAME_FORMAT_UNKNOWN = 0,
    OTC_VIDEO_FRAME_FORMAT_YUV420P = 1,
    OTC_VIDEO_FRAME_FORMAT_NV12 = 2,
    OTC_VIDEO_FRAME_FORMAT_NV21 = 3,
    OTC_VIDEO_FRAME_FORMAT_YUY2 = 4,
    OTC_VIDEO_FRAME_FORMAT_UYVY = 5,
    OTC_VIDEO_FRAME_FORMAT_ARGB32 = 6,
    OTC_VIDEO_FRAME_FORMAT_BGRA32 = 7,
    OTC_VIDEO_FRAME_FORMAT_RGB24 = 8,
    OTC_VIDEO_FRAME_FORMAT_MJPEG = 10,
    OTC_VIDEO_FRAME_FORMAT_MAX, //Try to add new values before this
    OTC_VIDEO_FRAME_FORMAT_COMPRESSED = 255
};

enum otc_video_frame_planes_
{
    OTC_VIDEO_FRAME_PLANE_Y = 0,
    OTC_VIDEO_FRAME_PLANE_U = 1,
    OTC_VIDEO_FRAME_PLANE_V = 2,

    OTC_VIDEO_FRAME_PLANE_PACKED = 0,
    OTC_VIDEO_FRAME_PLANE_UV_INTERLEAVED = 1,
    OTC_VIDEO_FRAME_PLANE_VU_INTERLEAVED = 1,
};

#define OTC_VIDEO_FRAME_MAX_METADATA_SIZE 32

/** 
* Create video frame with given parameters.
*/
OTC_DECL(otc_video_frame *) otc_video_frame_new_I420(int width, int height,
                                                     const uint8_t *y_plane, int y_stride,
                                                     const uint8_t *u_plane, int u_stride,
                                                     const uint8_t *v_plane, int v_stride);


OTC_DECL(otc_video_frame *) otc_video_frame_new(int format, int width, int height, const uint8_t *buffer);

OTC_DECL(otc_video_frame *) otc_video_frame_new_MJPEG(int width, int height, const uint8_t *buffer, size_t size);
OTC_DECL(otc_video_frame *) otc_video_frame_new_compressed(int width, int height, const uint8_t *buffer, size_t size);



OTC_DECL(otc_video_frame *) otc_video_frame_new_from_planes(int format, int width, int height,
                                                            const uint8_t **planes, int *strides);

OTC_DECL(otc_video_frame *) otc_video_frame_new_I420_from_planes(int format, int width, int height,
                                                                 const uint8_t **planes, int *strides);


/**
 * Create video frame wrapping existing memory (NO COPY)
 */

typedef void(*otc_video_frame_memory_release_cb)(const uint8_t *buffer, void *arg);

OTC_DECL(otc_video_frame *) otc_video_frame_new_contiguous_memory_wrapper(int format, int width, int height, otc_bool_t is_shallow_copyable,
                                                                          const uint8_t *buffer, size_t size, otc_video_frame_memory_release_cb release_cb, void *arg);


struct otc_video_frame_planar_memory_cb
{
    void *user_data;
    
    // Obligatory callbacks
    const uint8_t *(*get_plane)(void *user_data, int plane);
    int (*get_plane_stride)(void *user_data, int plane);
    
    // Optional callback, it can be null
    void (*release)(void *user_data);

    void *reserved; // Must be initialized to zero;
};

OTC_DECL(otc_video_frame *) otc_video_frame_new_planar_memory_wrapper(int format, int width, int height, otc_bool_t is_shallow_copyable,
                                                                      struct otc_video_frame_planar_memory_cb *memory_cb);

OTC_DECL(otc_video_frame *) otc_video_frame_new_I420_wrapper(int width, int height,
                                                     const uint8_t *y_plane, int y_stride,
                                                     const uint8_t *u_plane, int u_stride,
                                                     const uint8_t *v_plane, int v_stride);

OTC_DECL(otc_video_frame *) otc_video_frame_new_NV21_wrapper(int width, int height,
                                                             const uint8_t *y_plane, int y_stride,
                                                             const uint8_t *uv_plane, int uv_stride);

OTC_DECL(otc_video_frame *) otc_video_frame_new_NV12_wrapper(int width, int height,
                                                             const uint8_t *y_plane, int y_stride,
                                                             const uint8_t *uv_plane, int uv_stride);

OTC_DECL(otc_bool_t) otc_video_frame_is_packed(const otc_video_frame *frame);

OTC_DECL(otc_bool_t) otc_video_frame_is_contiguous(const otc_video_frame *frame);

OTC_DECL(otc_status_t) otc_video_frame_set_native_handle(otc_video_frame *frame, void *handle);

OTC_DECL(void *) otc_video_frame_get_native_handle(const otc_video_frame *frame);

OTC_DECL(const uint8_t *) otc_video_frame_get_buffer(const otc_video_frame *frame);

OTC_DECL(size_t) otc_video_frame_get_buffer_size(const otc_video_frame *frame);

OTC_DECL(int64_t) otc_video_frame_get_timestamp(const otc_video_frame *frame);

OTC_DECL(void) otc_video_frame_set_timestamp(otc_video_frame *frame, int64_t timestamp);

/**
* Get the width of the given frame
*/
OTC_DECL(int) otc_video_frame_get_width(const otc_video_frame *frame);

/**
* Get the height of the given frame
*/
OTC_DECL(int) otc_video_frame_get_height(const otc_video_frame *frame);

/**
* Get the number of planes of the given frame. Typically you will find here 3 for a YUV fame and 1 for a RGBA/BGRA fame
*/
OTC_DECL(size_t) otc_video_frame_get_num_planes(const otc_video_frame *frame);

/**
* Get the video format of the given frame. It will be one of {@link otc_video_frame_format} struct.
*/
OTC_DECL(int) otc_video_frame_get_format(const otc_video_frame *frame);

/**
* Get the binary data of one of the planes of the frame
*/
OTC_DECL(const uint8_t *) otc_video_frame_get_plane(const otc_video_frame *frame, int plane);


/**
* Get the size of a plane in the video frame
*/
OTC_DECL(size_t) otc_video_frame_get_plane_size(const otc_video_frame *frame, int plane);


OTC_DECL(int) otc_video_frame_get_plane_stride(const otc_video_frame *frame, int plane);

/**
* Get the width of a plane in the video frame
*/
OTC_DECL(int) otc_video_frame_get_plane_width(const otc_video_frame *frame, int plane);

/**
* Get the height of a plane in the video frame
*/
OTC_DECL(int) otc_video_frame_get_plane_height(const otc_video_frame *frame, int plane);


OTC_DECL(otc_video_frame *) otc_video_frame_copy(const otc_video_frame *frame);

OTC_DECL(otc_video_frame *) otc_video_frame_mutable_copy(const otc_video_frame *frame);

/**
* Convert the given frame. All the video frames provided by the callbacks are bound to this callback.
* If you plan to save the frame yo use it later, you'll need to copy it.
* In addition to that, if you want to convert a video frame to a different format, you'll use this method also
* If the destination format is the same as the source, a shallow copy (no buffer copy) will be made if possible.
* 
* @param format format of the video frame which will be returned. A member of {@link otc_video_frame_format}
* @param frame the video frame to be copied
* @return A copy of the video frame in the specified format. Bear in mind that you will need to destroy this frame later by yourself.
*/
OTC_DECL(otc_video_frame *) otc_video_frame_convert(int format, const otc_video_frame *frame);

OTC_DECL(otc_status_t) otc_video_frame_convert_inplace(int format, uint8_t **planes, const int *strides, const otc_video_frame *input_frame);

/**
* Free resources associated with the frame
*/
OTC_DECL(otc_status_t) otc_video_frame_delete(otc_video_frame *frame);

/**
* Set the metadata associated to the video frame.
*
* @param frame the video frame to be modified.
* @param data the metadata buffer to be copied into the frame.
* @param size the size of the metadata buffer to be copied. The maximum size allowed is 32 bytes.
*
* @return an error in the event of an error otherwise OTC_SUCCESS
*/
OTC_DECL(otc_status_t) otc_video_frame_set_metadata(otc_video_frame *frame, const uint8_t *data, size_t size);

/**
* Get the metadata associated to the video frame.
*
* @param frame the video frame to be used.
* @param size output parameter: the size of the metadata buffer associated to this frame.
*
* @return a pointer to the internal metadata buffer in the video frame or a null pointer if there is no metadata
*         associated with it. This pointer will get invalidated after destroying the frame.
*/
OTC_DECL(const uint8_t *) otc_video_frame_get_metadata(const otc_video_frame *frame, size_t *size);


OTC_END_DECL

#endif // VIDEOFRAME_H

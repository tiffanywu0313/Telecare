#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#ifndef _WIN32
#include <sys/time.h>
#endif

#ifdef _WIN32
#define LIBOPENTOK_DLL_EXPORTED  __declspec(dllexport)
#else
#define LIBOPENTOK_DLL_EXPORTED __attribute__((__visibility__("default")))
#endif

#if defined(__cplusplus)
#define OTC_DECL(type)		LIBOPENTOK_DLL_EXPORTED type
#define OTC_DEF(type)		type
#define OTC_BEGIN_DECL		extern "C" {
#define OTC_END_DECL		}
#else
#define OTC_DECL(type)		extern LIBOPENTOK_DLL_EXPORTED type
#define OTC_DEF(type)		type
#define OTC_BEGIN_DECL
#define OTC_END_DECL
#endif

typedef int otc_bool_t;
typedef long long otc_time_t;
typedef int otc_status_t;

enum otc_constants_
{
    OTC_SUCCESS = 0,

    OTC_FALSE = 0,

    OTC_TRUE = !OTC_FALSE,

    
};

enum otc_error_codes
{
    OTC_ERR_INVALID_PARAM = 1,

    OTC_ERR_FATAL = 2,
    
    /**
     * The connection to the OpenTok messaging server was dropped.
     * Check the network connection.
     */
    OTC_CONNECTION_DROPPED = 1022,
    
    /**
     * Subscriber timed out while attempting to connect to the stream.
     * Try resubscribing to the stream.
     */
    OTC_CONNECTION_TIMED_OUT = 1542,
    
    /**
     * Cannot unpublish: An unknown Publisher instance was passed into
     * the Session.unpublish() method.
     */
    OTC_UNKNOWN_PUBLISHER_INSTANCE = 2003,
    /**
     * Cannot unsubscribe: An unknown Subscriber instance was passed into
     * the Session.unsubscribe() method.
     */
    OTC_UNKNOWN_SUBSCRIBER_INSTANCE = 2004,
    /** There was an error in the video capturer */
    OTC_VIDEO_CAPTURE_FAILED = 3000,
    /** There was an error in acquiring video from the camera. */
    OTC_CAMERA_FAILED = 3010,
    /** There was an error in the video renderer. * */
    OTC_VIDEO_RENDER_FAILED = 4000,
    
};

#endif // CONFIG_H

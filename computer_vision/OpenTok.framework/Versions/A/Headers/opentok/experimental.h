#ifndef EXPERIMENTAL_H
#define EXPERIMENTAL_H

#include "config.h"
#include "publisher.h"
#include "subscriber.h"

OTC_BEGIN_DECL
/*
 BEGIN EXPERIMENTAL SECTION
 */

#define OTC_STATS_KEY_ACTIVECONNECTION "googActiveConnection"
#define OTC_STATS_KEY_ACTUALENCBITRATE "googActualEncBitrate"
#define OTC_STATS_KEY_AUDIOOUTPUTLEVEL "audioOutputLevel"
#define OTC_STATS_KEY_AUDIOINPUTLEVEL "audioInputLevel"
#define OTC_STATS_KEY_AVAILABLERECEIVEBANDWIDTH "googAvailableReceiveBandwidth"
#define OTC_STATS_KEY_AVAILABLESENDBANDWIDTH "googAvailableSendBandwidth"
#define OTC_STATS_KEY_BUCKETDELAY "googBucketDelay"
#define OTC_STATS_KEY_BYTESRECEIVED "bytesReceived"
#define OTC_STATS_KEY_BYTESSENT "bytesSent"
#define OTC_STATS_KEY_CHANNELID "googChannelId"
#define OTC_STATS_KEY_CODECNAME "googCodecName"
#define OTC_STATS_KEY_COMPONENT "googComponent"
#define OTC_STATS_KEY_CONTENTNAME "googContentName"
#define OTC_STATS_KEY_ECHOCANCELLATIONQUALITYMIN "googEchoCancellationQualityMin"
#define OTC_STATS_KEY_ECHODELAYMEDIAN "googEchoCancellationEchoDelayMedian"
#define OTC_STATS_KEY_ECHODELAYSTDDEV "googEchoCancellationEchoDelayStdDev"
#define OTC_STATS_KEY_ECHORETURNLOSS "googEchoCancellationReturnLoss"
#define OTC_STATS_KEY_ECHORETURNLOSSENHANCEMENT "googEchoCancellationReturnLossEnhancement"
#define OTC_STATS_KEY_FIRSRECEIVED "googFirsReceived"
#define OTC_STATS_KEY_FIRSSENT "googFirsSent"
#define OTC_STATS_KEY_FRAMEHEIGHTRECEIVED "googFrameHeightReceived"
#define OTC_STATS_KEY_FRAMEHEIGHTSENT "googFrameHeightSent"
#define OTC_STATS_KEY_FRAMERATERECEIVED "googFrameRateReceived"
#define OTC_STATS_KEY_FRAMERATEDECODED "googFrameRateDecoded"
#define OTC_STATS_KEY_FRAMERATEOUTPUT "googFrameRateOutput"
#define OTC_STATS_KEY_FRAMERATEINPUT "googFrameRateInput"
#define OTC_STATS_KEY_FRAMERATESENT "googFrameRateSent"
#define OTC_STATS_KEY_FRAMEWIDTHRECEIVED "googFrameWidthReceived"
#define OTC_STATS_KEY_FRAMEWIDTHSENT "googFrameWidthSent"
#define OTC_STATS_KEY_INITIATOR "googInitiator"
#define OTC_STATS_KEY_JITTERRECEIVED "googJitterReceived"
#define OTC_STATS_KEY_LOCALADDRESS "googLocalAddress"
#define OTC_STATS_KEY_NACKSRECEIVED "googNacksReceived"
#define OTC_STATS_KEY_NACKSSENT "googNacksSent"
#define OTC_STATS_KEY_PACKETSRECEIVED "packetsReceived"
#define OTC_STATS_KEY_PACKETSSENT "packetsSent"
#define OTC_STATS_KEY_PACKETSLOST "packetsLost"
#define OTC_STATS_KEY_READABLE "googReadable"
#define OTC_STATS_KEY_REMOTEADDRESS "googRemoteAddress"
#define OTC_STATS_KEY_RETRANSMITBITRATE "googRetransmitBitrate"
#define OTC_STATS_KEY_RTT "googRtt"
#define OTC_STATS_KEY_TARGETENCBITRATE "googTargetEncBitrate"
#define OTC_STATS_KEY_TRANSMITBITRATE "googTransmitBitrate"
#define OTC_STATS_KEY_TRANSPORTID "transportId"
#define OTC_STATS_KEY_TRANSPORTTYPE "googTransportType"
#define OTC_STATS_KEY_TRACKID "googTrackId"
#define OTC_STATS_KEY_SSRC "ssrc"
#define OTC_STATS_KEY_WRITABLE "googWritable"
#define OTC_STATS_KEY_CANDIDATEPAIR "googCandidatePair"
#define OTC_STATS_KEY_LOCALCANDIDATETYPE "googLocalCandidateType"
#define OTC_STATS_KEY_REMOTECANDIDATETYPE "googRemoteCandidateType"
#define OTC_STATS_KEY_LOCALRELAYPROTOCOL "kStatsOPENTOK_29718_LocalRelayProtocol"
#define OTC_STATS_KEY_REMOTERELAYPROTOCOL "kStatsOPENTOK_29718_RemoteRelayProtocol"
#define OTC_STATS_KEY_LOCALCANDIDATEPRIORITY "localcandidate.priority"

typedef char* (*PUB_SDP_CALLBACK_TRANSFORM)(struct otc_publisher* publisher,
                                            void* user_data, const char* sdp_orig, int current_status);
typedef void (*PUB_SDP_CALLBACK_DEALLOC)(char* sdp_to_deallocate);
/**
 * Sets a callback that will be executed whenever when SDP is created or used
 * to set a local/remote description.
 *
 * @param transform_func The callback method that will be called.  Return NULL
 * from this callback to do nothing to the SDP; otherwise allocate and
 * return a char* for the SDP.  The pointer returned from transform_func
 * will later be passed to deallocator_func for de-allocation.
 * @param deallocator_func The pointer returned from transform_func will be
 * passed back to this method; your implementation should de-allocate
 * sdp_to_deallocate in a way appropriate to the way it was allocated in
 * transform_func.
 * @todo TODO We need to map current_status from the OTKit enum; how to do this
 * maintanably?  Right now we are just casting to int, see private
 * otk_common_media_enums.h for values.
 * @todo Should this join the other publisher callbacks?
 */
OTC_DECL(void) otc_publisher_set_sdp_transformer
(struct otc_publisher* publisher,
 PUB_SDP_CALLBACK_TRANSFORM transform_func,
 PUB_SDP_CALLBACK_DEALLOC deallocator_func);

enum otc_simulcast_level {
  otc_SimulcastLevelNone = 0,
  otc_SimulcastLevelVGA = 1,
  otc_SimulcastLevel720p = 2,
  otc_SimulcastLevelNumLevels /* This should remain last in this enum. */
};

/**
 * @todo TODO Doc this
 */
OTC_DECL(void) otc_publisher_set_simulcast_level
(struct otc_publisher* publisher, enum otc_simulcast_level level);

typedef char* (*SUB_SDP_CALLBACK_TRANSFORM)(struct otc_subscriber* subscriber,
                                            void* user_data, const char* sdp_orig, int current_status);
typedef void (*SUB_SDP_CALLBACK_DEALLOC)(char* sdp_to_deallocate);
/**
 * Sets a callback that will be executed whenever when SDP is created or used
 * to set a local/remote description.
 *
 * @param transform_func The callback method that will be called.  Return NULL
 * from this callback to do nothing to the SDP; otherwise allocate and
 * return a char* for the SDP.  The pointer returned from transform_func
 * will later be passed to deallocator_func for de-allocation.
 * @param deallocator_func The pointer returned from transform_func will be
 * passed back to this method; your implementation should de-allocate
 * sdp_to_deallocate in a way appropriate to the way it was allocated in
 * transform_func.
 * @todo TODO We need to map current_status from the OTKit enum; how to do this
 * maintanably?  Right now we are just casting to int, see private
 * otk_common_media_enums.h for values.
 * @todo Should this join the other subscriber callbacks?
 */
OTC_DECL(void) otc_subscriber_set_sdp_transformer
(struct otc_subscriber* subscriber,
 SUB_SDP_CALLBACK_TRANSFORM transform_func,
 SUB_SDP_CALLBACK_DEALLOC deallocator_func);

/*
 END EXPERIMENTAL SECTION
 */

OTC_END_DECL

#endif // EXPERIMENTAL_H

//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBConfigurationManager.h
//
// Description:
//     Defines the SfBConfigurationManager class that holds various
//     application level parameters.
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SfBConfigurationManager : NSObject

/** Maximum number of video channels to watch concurrently
 *
 * The request may be effectively capped by platform static or runtime limit.
 * If number of participants sending video is greater than this limit,
 * the most active participants will offer a subscription. Follow the
 * participant.video.canSubscribe changes.
 */
@property (readwrite) uint32_t maxVideoChannels;

/** If set, audio service will be disabled while not on Wi-Fi network
 *
 * Default is NO.
 *
 * @note even if set to NO (allow any network connection), server policy may
 * prevent this.
 */
@property (readwrite, nonatomic) BOOL requireWifiForAudio;

/** If set, video service will be disabled while not on Wi-Fi network
 *
 * Default is YES.
 *
 * @note even if set to NO (allow any network connection), server policy may
 * prevent this.
 */
@property (readwrite, nonatomic) BOOL requireWifiForVideo;

/**
 * If set, certain preview features will be enabled in the SDK.
 * E.g. For OnPrem topologies, setting this flag to true will enable Audio/Video callflows.
 * This flag should be set immediately after you get the application instance.
 */
@property (readwrite) BOOL enablePreviewFeatures;

/**
 * Notify that user has accepted the Video license.
 *
 * This is required to proceed with features that potentially use video codecs.
 * Until this method is called, any attempt to use those features will fail.
 */
- (void)setEndUserAcceptedVideoLicense;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

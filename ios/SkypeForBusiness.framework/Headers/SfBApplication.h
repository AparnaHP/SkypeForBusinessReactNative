//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBApplication.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

@class SfBAlert;
@protocol SfBAlertDelegate;
@class SfBAnonymousSession;
@class SfBConfigurationManager;
@class SfBDevicesManager;

NS_ASSUME_NONNULL_BEGIN

/**
 * This class is the top-level entry point for the App SDK.  It provides
 * access to all entities and services.
 */
@interface SfBApplication : NSObject

@property (readonly) SfBConfigurationManager *configurationManager;
@property (readonly) SfBDevicesManager *devicesManager;

/** Application global alerts delegate.
 *
 * Conversation specific alerts are exposed through SfBConversation object.
 * Everything else goes into this delegate.
 */
@property (weak, readwrite, nullable) id<SfBAlertDelegate> alertDelegate;

/** @return Shared application instance or @a nil if initialization fails
 */
+ (nullable instancetype)sharedApplication;

/** Joins a meeting anonymously as a 'guest', without requiring sign-in to
 * a Skype for Business account
 *
 * @param meetingUri The meeting URI to join.
 * @param displayName Name of the guest user, which will be visible in all
 * Skype for Business clients that also join the meeting.
 * @return A session containing single conversation that represents this meeting.
 * Observe [SfBConversation state] property to determine when connection to
 * the meeting is fully established.
 *
 * @note This method is intended to be used on-prem only. For online meetings
 * use another method and provide discover URL and authorization token instead
 * of meeting URI.
 *
 * @note This method can be called repeatedly at any time. It automatically
 * disconnects any existing meetings.
 */
- (nullable SfBAnonymousSession *)joinMeetingAnonymousWithUri:(NSURL *)meetingUri
                                                  displayName:(NSString *)displayName
                                                        error:(NSError **)error;

/** Joins a meeting anonymously as a 'guest', without requiring sign-in to
 * a Skype for Business account
 *
 * @param discoverUrl The discover URL to join.
 * @param authToken The authorization token.
 * @param displayName Name of the guest user, which will be visible in all
 * Skype for Business clients that also join the meeting.
 * @return A session containing single conversation that represents this meeting.
 * Observe [SfBConversation state] property to determine when connection to
 * the meeting is fully established.
 *
 * @note This method can be called repeatedly at any time. It automatically
 * disconnects any existing meetings.
 */
- (nullable SfBAnonymousSession *)joinMeetingAnonymousWithDiscoverUrl:(NSURL *)discoverUrl
                                                            authToken:(NSString *)authToken
                                                          displayName:(NSString *)displayName
                                                                error:(NSError **)error;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

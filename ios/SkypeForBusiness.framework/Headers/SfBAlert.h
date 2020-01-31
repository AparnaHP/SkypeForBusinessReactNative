//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBAlert.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, SfBAlertType) {
    SfBAlertTypeMessaging = 101,

    SfBAlertTypeUcwaObjectModel = 200,
    SfBAlertTypeAutoDiscovery = 201,

    SfBAlertTypeSignIn = 300,
    SfBAlertTypeSignOut = 301,
    SfBAlertTypeConnectivity = 302,

    SfBAlertTypeConferencing = 500,
    SfBAlertTypeParticipantMute = 504,
    SfBAlertTypeParticipantUnmute = 505,
    SfBAlertTypeConferenceUnexpectedDisconnect = 514,

    SfBAlertTypeVideo = 600,
    SfBAlertTypeVideoOverWiFiBlocked = 602,
    SfBAlertTypeVideoGenericError = 603,

    SfBAlertTypeVoice = 700,
    SfBAlertTypeCallFailed = 708,

    SfBAlertTypeConferenceIsRecording = 1004,

    SfBAlertTypeCommunication = 1100,

    SfBAlertTypeCommon = 1200
};

typedef NS_ENUM(int, SfBAlertLevel) {
    SfBAlertLevelError,
    SfBAlertLevelWarning,
    SfBAlertLevelInfo
};

/** Asynchronous exceptional condition.
 *
 * Alerts are exceptional conditions that could not be exposed as a return value
 * or an error coming from some function. Possible sources:
 * <li> Asynchronous operation successfully initiated but failed later.
 * <li> Incoming network error that cannot be handled transparently.
 */
@interface SfBAlert : NSObject

/** Identifies the particular event that resulted in an alert.
 */
@property (readonly) SfBAlertType type;

@property (readonly) SfBAlertLevel level;

/** Reason for the alert.
 */
@property (readonly) NSError *error;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

@protocol SfBAlertDelegate

/** Called when new alert appears in the context where this delegate is attached.
 *
 * Each alert is passed to a delegate once and dismissed unconditionally.
 * If no delegate is attached, alerts are accumulated and reported as soon
 * as delegate is set. Accumulated alerts of the same category and type
 * are coalesced, only the last one will be reported.
 */
- (void)didReceiveAlert:(SfBAlert *)alert;

@end

NS_ASSUME_NONNULL_END

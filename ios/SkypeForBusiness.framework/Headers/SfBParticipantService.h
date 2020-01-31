//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBParticipantService.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, SfBParticipantServiceState) {
    SfBParticipantServiceStateDisconnected,
    SfBParticipantServiceStateConnecting,
    SfBParticipantServiceStateConnected
};

/** This base interface represents the communications capabilties of a
 * participant in the conversation for a specific service (such as chat
 * messaging, audio and video).
 */
@interface SfBParticipantService : NSObject

@property (readonly) SfBParticipantServiceState state;

@end

NS_ASSUME_NONNULL_END

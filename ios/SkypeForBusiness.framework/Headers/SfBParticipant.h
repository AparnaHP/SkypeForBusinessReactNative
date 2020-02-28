//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBParticipant.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

typedef NS_ENUM(int, SfBParticipantRole) {
    SfBParticipantRoleAttendee,
    SfBParticipantRoleLeader
};

typedef NS_ENUM(int, SfBParticipantState) {
    SfBParticipantStateInLobby,
    SfBParticipantStateConnected
};

@class SfBParticipantAudio;
@class SfBParticipantChat;
@class SfBParticipantVideo;
@class SfBPerson;

NS_ASSUME_NONNULL_BEGIN

/** This interface represents a participant (local or remote) in the
 * conversation. It contains a set of “services” that respresent each aspect
 * of this participant's communication into the conversation: e.g. a service
 * for chat messaging, a service for audio, a service for video etc.
 */
@interface SfBParticipant : NSObject

@property (readonly) SfBParticipantState state;
@property (readonly) SfBParticipantRole role;

@property (readonly) SfBParticipantChat *chat;
@property (readonly) SfBParticipantAudio *audio;
@property (readonly) SfBParticipantVideo *video;

@property (readonly) SfBPerson *person;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

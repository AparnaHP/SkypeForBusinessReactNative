//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBConversation.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

@class SfBAlert;
@protocol SfBAlertDelegate;
@class SfBAudioService;
@class SfBChatService;
@class SfBHistoryService;
@class SfBParticipant;
@class SfBVideoService;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, SfBConversationState) {
    SfBConversationStateIdle,
    SfBConversationStateEstablishing,
    SfBConversationStateInLobby,
    SfBConversationStateEstablished
};

/**
 * This interface represents a communication between one or more participants
 * created via a Skype for Business meeting or by ad hoc user action. It is 
 * managed via a set of “services” local to this endpoint.
 * Services are fixed and cannot be added or removed.  There is one service
 * that manages each aspect of this endpoint's communication into the
 * conversation: e.g. for chat messaging, a service for audio, a service for
 * video etc.
 * There is also a service that manages the history of previous events that 
 * occured during this conversation.
 */
@interface SfBConversation : NSObject

@property (readonly) SfBConversationState state;

/** Remote participants in the conversation.
 * The local (self) participant is not included in this collection.
 */
@property (readonly) NSArray<SfBParticipant *> *remoteParticipants;

/** The local or self participant in the conversation.
 *
 * @note This object represents state of participant as visible to others.
 * To inspect or configure local state, it may also be necessary to use the
 * interfaces that directly control the communication this endpoint sends 
 * into the converation: e.g. ChatService, AudioService and VideoService.
 */
@property (readonly) SfBParticipant *selfParticipant;

 /** The participant who is currently speaking.
  */
 @property (readonly, nullable) SfBParticipant *dominantSpeaker;

/** Manages all previous activity in this conversation.
 */
@property (readonly) SfBHistoryService *historyService;

/** Controls the local chat messages that this endpoint sends into the
 * conversation.
 */
@property (readonly) SfBChatService *chatService;

/** Controls the local audio that this endpoint sends into the conversation.
 */
@property (readonly) SfBAudioService *audioService;

/** Controls the local video that this endpoint sends into the conversation.
 */
@property (readonly) SfBVideoService *videoService;

/** The subject or topic of the conversation.
 */
@property (readonly) NSString *subject;

/** Leave the conversation
 *
 * No further actions are possible. Previous state, such as subject and
 * history will remain readable.
 */
- (BOOL)leave:(NSError **)error;
@property (readonly) BOOL canLeave;

/** Delegate for alerts specific to this conversation.
 */
@property (weak, readwrite, nullable) id<SfBAlertDelegate> alertDelegate;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

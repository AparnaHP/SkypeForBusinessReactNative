//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBChatService.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>
#import <SkypeForBusiness/SfBConversationService.h>

NS_ASSUME_NONNULL_BEGIN

@class SfBMessageActivityItem;

/** This interface controls the local chat messages that the SDK provides into
 * the conversation. 
 * Received chat messages are available via the HistoryService.
 * The results of some operations on this interface may be visible in changes 
 * to the ParticipantChat belonging to the conversation's selfParticipant. 
 */
@interface SfBChatService : SfBConversationService

/** Sends a message asynchronously into the conversation.
 *
 * @param text The message to be sent.
 * @return The sent message. Observe its status property to determine if the message delivery
 * to the server succeeds or fails.
 */
- (nullable SfBMessageActivityItem *)sendMessage:(NSString *)text error:(NSError **)error;
@property (readonly) BOOL canSendMessage;

/** Sends an indication that the local user is typing into the conversation..
 */
- (BOOL)sendIsTyping:(NSError **)error;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

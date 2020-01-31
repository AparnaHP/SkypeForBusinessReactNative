//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBParticipantChat.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>
#import <SkypeForBusiness/SfBParticipantService.h>

NS_ASSUME_NONNULL_BEGIN

/** This interface represents the chat messaging capabilities of a participant
 * in the conversation.
 */
@interface SfBParticipantChat : SfBParticipantService

@property (readonly) BOOL isTyping;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

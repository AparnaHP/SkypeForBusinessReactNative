//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBAnonymousSession.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SfBConversation;

/** A session whose scope is limited by a single anonymous conversation.
 */
@interface SfBAnonymousSession : NSObject

/** The conversation
 *
 * Leaving this conversation will automatically terminate the session.
 */
@property (readonly) SfBConversation *conversation;

@end

NS_ASSUME_NONNULL_END

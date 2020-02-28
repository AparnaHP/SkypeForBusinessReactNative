//----------------------------------------------------------------
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Module name: SfBConversationService.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** This base interface defines common operations to control the local
 * communications services (such as chat messaging, audio and video) that this
 * endpoint provides into the conversation.  The results of some operations on
 * (sublcasses of) this interface may be visible in changes to (subclasses of)
 * the ParticipantService(s) belonging to the conversation's selfParticipant. 
 */
@interface SfBConversationService : NSObject

/** Starts the service.
 * It is recommended to check canStart before calling start on the service.
 */
- (BOOL)start:(NSError **)error;
@property (readonly) BOOL canStart;

/** Stops the service.
 * It is recommended to check canStop before calling stop on the service.
 */
- (BOOL)stop:(NSError **)error;
@property (readonly) BOOL canStop;

@end

NS_ASSUME_NONNULL_END

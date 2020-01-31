//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBParticipant.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SfBPerson : NSObject

/** SIP URI
 */
@property (readonly) NSURL *sipUri;

/** Display name of the participant.
 */
@property (readonly) NSString *displayName;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

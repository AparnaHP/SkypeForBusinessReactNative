//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBHistoryService.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>
#import <SkypeForBusiness/SfBConversationActivityItem.h>

NS_ASSUME_NONNULL_BEGIN

/** This interface manages items that have occurred in the conversation such as
 * previous messages sent or received, or participants joined or left, etc.
 */
@interface SfBHistoryService : NSObject

@property (readonly) NSArray<SfBConversationActivityItem *> *activityItems;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

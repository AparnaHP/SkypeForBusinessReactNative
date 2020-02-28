//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBConversationActivityItem.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

@class SfBPerson;

typedef NS_ENUM(int, SfBActivityType) {
    SfBActivityTypeParticipantJoined,
    SfBActivityTypeParticipantLeft,
    SfBActivityTypeMessage,
    SfBActivityTypeUnknown
};

typedef NS_ENUM(int, SfBMessageStatus) {
    SfBMessageStatusPending,
    SfBMessageStatusFailed,
    SfBMessageStatusSucceeded
};

typedef NS_ENUM(int, SfBMessageDirection) {
    SfBMessageDirectionIncoming,
    SfBMessageDirectionOutgoing
};

typedef NS_ENUM(int, SfBMessageFormat) {
    SfBMessageFormatText
};

NS_ASSUME_NONNULL_BEGIN

/** This base interface represents a previous activity that occurred in the
 * conversation such as a previous message sent or received, or a participant
 * joined or left, etc.
 */
@interface SfBConversationActivityItem : NSObject

@property (readonly) SfBActivityType type;
@property (readonly) NSDate *timestamp;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

/**
 * This interface represents a message sent or received in the conversation.
 */
@interface SfBMessageActivityItem : SfBConversationActivityItem

@property (readonly) SfBMessageStatus status;

@property (readonly) SfBMessageDirection direction;

/** Sender of the message.  In some cases, this information is not available.
 */
@property (readonly, nullable) SfBPerson *sender;

@property (readonly) NSString *text;
@property (readonly) SfBMessageFormat format;

@end

/**
 * This interface represents the event of a person joining or leaving a conversation.
 */
@interface SfBParticipantActivityItem : SfBConversationActivityItem

@property (readonly) SfBPerson *person;

@end

NS_ASSUME_NONNULL_END

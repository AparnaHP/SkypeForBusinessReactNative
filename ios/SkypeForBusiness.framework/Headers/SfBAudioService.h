//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBAudioService.h
//----------------------------------------------------------------

#import <SkypeForBusiness/SfBConversationService.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, SfBAudioServiceMuteState) {
    /// Microphone and media stream are unmuted
    SfBAudioServiceMuteStateUnmuted,
    /// Microphone is muted
    SfBAudioServiceMuteStateMuted,
    /// Microphone is unmuted, media stream unmuting is in progress
    SfBAudioServiceMuteStateUnmuting
};

/** This interface controls the local audio that this endpoint sends into
 * the conversation. The results of some operations on this interface may
 * be visible in changes to the ParticipantAudio belonging to the
 * conversation's selfParticipant.
 */
@interface SfBAudioService : SfBConversationService

@property (readonly) BOOL isOnHold;

/** Holds or resumes the local endpoint's audio - and video - communications.
 *
 * @param hold Holds if true, resumes otherwise.
 */
- (BOOL)setHold:(BOOL)hold error:(NSError **)error;
@property (readonly) BOOL canSetHold;

/** Self audio mute state.
 *
 * This property reflects both the state of microphone and the state of media stream.
 */
@property (readonly) SfBAudioServiceMuteState muted;

/** Toggle self audio mute.
 *
 * Under normal circumstances, this method instantly switches the muted state
 * to `Unmuting` when `Muted`, or to `Muted` otherwise.
 *
 * `Unmuting` eventually becomes `Unmuted`, once network requests are processed.
 */
- (BOOL)toggleMute:(NSError **)error;
@property (readonly) BOOL canToggleMute;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

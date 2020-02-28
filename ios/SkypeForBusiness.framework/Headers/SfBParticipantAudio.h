//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBParticipantAudio.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>
#import <SkypeForBusiness/SfBParticipantService.h>

NS_ASSUME_NONNULL_BEGIN

/** This interface represents the audio capabilities of a participant in the
 * conversation.
 */
@interface SfBParticipantAudio : SfBParticipantService

@property (readonly) BOOL isSpeaking;

@property (readonly) BOOL isOnHold;

/** Whether the participant's audio can be heard by other participants in the
 * conversation.
 *
 * @see [SfBAudioService muted] for an aggregate state of self audio, including
 * both media streams and microphone.
 */
 
@property (readonly) BOOL isMuted;

/** Controls whether this participant's audio can be heard by other
 * participants in the conversation.
 *
 * This action may may not be available if the local participant does not have
 * the 'leader' role in the conversation. This may even apply to this setting 
 * for the local participant itself (the conversation's selfParticipant).  In
 * particular, it may not always be possible to un-mute until a remote 'leader'
 * enables this.
 *
 * @param muted Mutes if true, umutes otherwise.
 *
 * @see [SfBAudioService toggleMute:] to control self audio as this method does not
 * control microphone state, only the media streams.
 */
- (BOOL)setMuted:(BOOL)muted error:(NSError **)error;

/** Checks if the participant can be muted / un-muted.
 *
 * As explained above, a number of different factors may determine this.
 */
@property (readonly) BOOL canSetMuted;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

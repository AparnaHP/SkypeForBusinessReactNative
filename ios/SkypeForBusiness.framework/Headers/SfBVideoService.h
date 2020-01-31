//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBVideoService.h
//----------------------------------------------------------------

#import <SkypeForBusiness/SfBConversationService.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class SfBCamera;
@class UIView;

@interface SfBVideoPreview : NSObject

@property (readonly) CGSize dimensions;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

/** This interface controls the local video that this endpoint sends into the
 * conversation. The results of some operations on this interface may be
 * visible in changes to the ParticipantVideo belonging to the conversation's
 * selfParticipant. 
 */
@interface SfBVideoService : SfBConversationService

@property (readonly, nullable) SfBCamera *activeCamera;

/** Switches the local endpoint's outgoing video to use the specified camera.
 * To obtain the list of available cameras, see DevicesManager.
 */
- (BOOL)setActiveCamera:(SfBCamera *)camera error:(NSError **)error;
@property (readonly) BOOL canSetActiveCamera;

/** Whether the local endpoint's outgoing video is paused or is being sent into
 * the conversation.
 *
 * Actual state is reflected in selfParticipant.video.isPaused.
 * It may take time to propagate after setPaused is called.
 */
- (BOOL)setPaused:(BOOL)paused error:(NSError **)error;
@property (readonly) BOOL canSetPaused;

/** Register a view where the preview of local video is rendered.
 *
 * Unlike SfBVideoStream, image is refreshed automatically.
 */
- (nullable SfBVideoPreview *)showPreviewOnView:(UIView *)renderTarget error:(NSError **)error;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

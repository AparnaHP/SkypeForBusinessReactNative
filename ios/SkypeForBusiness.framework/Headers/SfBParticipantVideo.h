//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBParticipantVideo.h
//----------------------------------------------------------------

#import <SkypeForBusiness/SfBParticipantService.h>
#import <CoreGraphics/CGGeometry.h>

NS_ASSUME_NONNULL_BEGIN

@class CAEAGLLayer;

typedef NS_ENUM(int, SfBVideoStreamAutoFitMode) {
    SfBVideoStreamAutoFitModeFit,
    SfBVideoStreamAutoFitModeCrop
};

/**
 * This interface represents an incoming video stream from a participant.
 */
@interface SfBVideoStream : NSObject

@property (readonly) CGSize dimensions;

/** Render current video frame on the target surface.
 *
 * GLKViewController or CADisplayLink can help to sync the view updates
 * with display refresh.
 */
- (BOOL)render:(NSError **)error;

- (BOOL)setAutoFitMode:(SfBVideoStreamAutoFitMode)mode error:(NSError **)error;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

/**
 * This interface represents the video capabilities of a participant in the conversation.
 */
@interface SfBParticipantVideo : SfBParticipantService

/** Whether the participant's video is paused or is being sent into the conversation.
  * When paused, a participant may still see other participants.
  */
@property (readonly) BOOL isPaused;

/** Register a layer for rendering video.
 *
 * You can obtain an CAEAGLLayer from GLKView. Alternatively, you may have any
 * UIView with overridden layer class. Once render target is registered, you
 * must call render method to draw each video frame.
 */
- (nullable SfBVideoStream *)subscribe:(CAEAGLLayer *)renderTarget error:(NSError **)error;
@property (readonly) BOOL canSubscribe;

/** Remove any binding to UI elements
 *
 * This invalidates any SfBVideoStream attached to this object before,
 * allows to release UI objects and stops receiving video stream.
 */
- (BOOL)unsubscribe:(NSError **)error;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

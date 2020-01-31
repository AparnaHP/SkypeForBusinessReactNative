//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBDevicesManager.h
//----------------------------------------------------------------

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, SfBSpeakerEndpoint) {
    SfBSpeakerEndpointLoudspeaker = 1,
    SfBSpeakerEndpointNonLoudspeaker = 2,
};

/** This interface represents a local device audio ouput.
 * It may contain both an internal speaker and its corresponding
 * loudspeaker.  
 */
@interface SfBSpeaker : NSObject

/** The current active audio output endpoint.
 */
@property (readwrite) SfBSpeakerEndpoint activeEndpoint;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

typedef NS_ENUM(int, SfBCameraType) {
    SfBCameraTypeUnknown = 1,
    SfBCameraTypeExternal,
    SfBCameraTypeFrontFacing,
    SfBCameraTypeBackFacing
};

/** This interface represents a local device camera.
 */
@interface SfBCamera : NSObject

@property (readonly) SfBCameraType type;

@property (readonly) NSString *description;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

/** This interface manages local audio and video devices.
 */
@interface SfBDevicesManager : NSObject

/** The current active audio output (potentially containing multiple
 * endpoints).
 */
@property (readonly) SfBSpeaker *selectedSpeaker;

/** Gets the list of available cameras on the device.  The active camera for a
* conversation is set in its VideoService. 
 */
 @property (readonly) NSArray<SfBCamera *> *cameras;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END

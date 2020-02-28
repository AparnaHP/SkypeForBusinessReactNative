//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Module name: SfBError.h
//
// Description:
//      Defines NSError constants for errors reported from SkypeForBusiness.
//
//----------------------------------------------------------------

#import <Foundation/NSString.h>

OBJC_EXTERN NSString *const SfBErrorDomain;

OBJC_EXTERN NSString *const SfBErrorSeverityKey;

OBJC_EXTERN NSString *const SfBErrorSeveritySuccess;
OBJC_EXTERN NSString *const SfBErrorSeverityWarning;
OBJC_EXTERN NSString *const SfBErrorSeverityError;

typedef NS_ENUM(NSInteger, SfBError) {
    SfBErrorInvalidArgument = 0x20000003,
    SfBErrorActionNotAvailable = 0x23080001,
    SfBErrorVideoLicenseNotAccepted = 0x2307001a
};

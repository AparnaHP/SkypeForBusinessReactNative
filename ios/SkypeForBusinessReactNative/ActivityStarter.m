//
//  ChangeViewBridge.m
//
//  Created by Aparna Prasad on 6/28/19.
//  Copyright © 2019 Facebook. All rights reserved.
//

#import "ActivityStarter.h"
#import <React/RCTLog.h>
#import "SkypeForBusinessReactNative-Bridging-Header.h"

@implementation ActivityStarter

RCT_EXPORT_MODULE();

RCT_EXPORT_METHOD(loadSkypeForBusiness:(NSString *)url name:(NSString *)name)
{
  
  RCTLogInfo(@"Loading native funtion %@ at %@", url, name);
  NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
  [userDefaults setObject:url forKey:@"userMeetingUrl"];
  [userDefaults setObject:name forKey:@"userDisplayName"];
  [userDefaults synchronize];
  
  UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
  UINavigationController *videoView=[storyboard instantiateViewControllerWithIdentifier:@"navigationController"] ;
  UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
  [keyWindow.rootViewController presentViewController:videoView animated:YES completion:nil];
}

@end

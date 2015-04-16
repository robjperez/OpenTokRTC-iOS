//
//  AppDelegate.m
//  webrtcDemoiOS
//
//  Created by Song Zheng on 8/14/13.
//  Copyright (c) 2013 Song Zheng. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import "RoomViewController.h"

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    NSURL *url = launchOptions[UIApplicationLaunchOptionsURLKey];
    ViewController *vc = (ViewController *)((UINavigationController *)self.window.rootViewController).topViewController;
    
    if (url != nil) {
        vc.preloadRoomName = [url host];
    }
    
    return YES;
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    UIViewController *uvc = ((UINavigationController *)self.window.rootViewController).topViewController;
    if ([uvc isKindOfClass:[ViewController class]]) {
        ViewController *vc = (ViewController *)uvc;
        vc.roomNameTxtField.text = [url host];
        [vc performSegueWithIdentifier:@"startChat" sender:vc];
    }
    return YES;
}
							
- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end

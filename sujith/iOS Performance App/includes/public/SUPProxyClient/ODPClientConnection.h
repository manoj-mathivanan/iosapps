//  ODPClientConnection.h
//  SUPProxyClient
/***************************************************************/
//  Created by M, Pramod on 1/10/12.
//  Copyright (c) Sybase, An SAP Company. All rights reserved.
/***************************************************************/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma mark -
#pragma mark Push Delegate Methods

/*!
 @protocol ODPPushDelegate
 @abstract   Protocol for classes implementing push listener.
 @discussion  All classes implementing the push delegate should use this protocol and this class should be passed to the delegate variable of the client connection class object.
 */

@protocol ODPPushDelegate <NSObject>

@required

/**
 * Notifies the listener with the data been pushed from the back-end.
 * <pre>
 *  Usage
 * <code>
 *  -(IBAction)buttonsPressed:(UIButton*)button{
 *      [ODPClientConnection registerForPayloadPush:self];
 *  }
 *
 *  -(void)pushNotificationReceived:(NSDictionary*)data{
 *  {
 *      NSLog(@"Data : %@", [data objectForKey:@"Data"]);
 *  }
 * </code>
 * </pre>
 */

- (void) pushNotificationReceived:(NSDictionary*)data;

@end

#pragma mark -


/*!
 @class ODPClientConnection
 @abstract   Consists of methods used to interact with the underlying client to register connection settings, online payload push and APNS push notifications.
 @discussion Application can register for push (payload) from the back-end gateway, when the client is online, or for APNS when the application is closed or client is offline.              
 */
@interface ODPClientConnection : NSObject


#pragma mark Class methods

/**
 * Get an instance of the ODPClientConnection class.
 * @param applicationId Application ID of the application.
 * @return Singleton instance of the ODPClientConnection class.
 * <pre>
 *  Usage
 * <code>
 *  ODPClientConnection* clientConnection = [ODPClientConnection getInstance:@"ApplicationId"];
 * </code>
 * </pre>
 */

+(ODPClientConnection*)getInstance:(NSString*)applicationId;

/**
 * For a device to switch connection between SUP servers, this API is invoked before registering a user with new server. This ensures that the server public keys are removed from the SUP client SDK which enables connectivity to new SUP server.
 * <pre>
 *  Usage
 * <code>
 *  [ODPClientConnection clearServerVerificationKey];
 * </code>
 * </pre>
 */

+(void)clearServerVerificationKey;

/**
 * Provides information about the class that has implemented the push delegate listener. Has to be called whenever the application desires to get the pushed data from backend.
 * @param delegate Instance of the class that has implemented the push listener delegate.
 * <pre>
 *  Usage
 * <code>
 *  [ODPClientConnection registerForPayloadPush:self];
 * </code>
 * </pre>
 */

+(void)registerForPayloadPush:(id<ODPPushDelegate>)delegate;

// NOT TO BE USED BY THE APPLICATION. FOR INTERNAL USE ONLY //

+(id<ODPPushDelegate>)getPushDelegate;


#pragma mark Instance methods

// NOT TO BE USED BY THE APPLICATION. FOR INTERNAL USE ONLY //

-(void)setConnectionPropertiesWithHost:(NSString*)hostName port:(NSInteger)portNum farm:(NSString*)farmId user:(NSString*)userName code:(NSString*)activationCode;

// NOT TO BE USED BY THE APPLICATION. FOR INTERNAL USE ONLY //

-(void)startClient;

/**
 * Stops all the client network traffic and the state of the client is set to sleep
 * <pre>
 *  Usage
 * <code>
 *  ODPClientConnection* clientConnection = [ODPClientConnection getInstance:@"ApplicationId"];
 *  [clientConnection stopClient];
 * </code>
 * </pre>
 */
-(void)stopClient;

#pragma mark Function calls for APNS registration

/**
 * Registers the applicaton for APNS push notification.
 * @param application Application object received as a part of the delegate has to be passed to the function call.
 * <pre>
 *  Usage
 * <code>
 *  - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions 
 *  {    
 *      [ODPClientConnection setupForPush:application];
 *  }
 * </code>
 * </pre>
 */

+(void)setupForPush:(UIApplication*)application;

/**
 * Registers for push notification using device token as a parameter. After the application is registered for APNS push notification, pass the device token received to SUP server. The device token must be sent to server to send the notification through APNS.
 * @param application Application object received as a part of the delegate.
 * @param devToken Device token received from the APNS gateway after the application has registered for APNS.
 * <pre>
 *  Usage
 * <code>
 *  - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
 *  {    
 *      [ODPClientConnection deviceTokenForPush:application deviceToken:deviceToken];
 *  }
 * </code>
 * </pre>
 */

+(void)deviceTokenForPush:(UIApplication*)application deviceToken:(NSData *)devToken;

/**
 * Reports an error if push registration to APNS fails.
 * @param application Application object received as a part of the delegate.
 * @param err Error object received as a part of the delegate.
 * <pre>
 *  Usage
 * <code>
 *  - (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
 *  {    
 *      [ODPClientConnection pushRegistrationFailed:application errorInfo:error];
 *  }
 * </code>
 * </pre>
 */


+(void)pushRegistrationFailed:(UIApplication*)application errorInfo:(NSError *)err;

/**
 * Notify the application of the incoming push notification.
 * @param application Application object received as a part of the delegate.
 * @param userInfo User information dictionary with additional data about the push notification.
 * <pre>
 *  Usage
 * <code>
 *  - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
 *  {    
 *      [ODPClientConnection pushNotification:application notifyData:userInfo];
 *  }
 * </code>
 * </pre>
 */

+(void)pushNotification:(UIApplication*)application notifyData:(NSDictionary *)userInfo;

@end

#pragma mark -
#pragma mark Exception class definition

// NOT TO BE USED BY THE APPLICATION. FOR INTERNAL USE ONLY //

@interface ODPClientConnectionException:NSException{
    
@private
    NSString* errorCode;
    NSString* errorText;
}

-(id)initWithName:(NSString *)aName reason:(NSString *)aReason code:(NSString*)errorCode text:(NSString*)errorText;
-(NSString*)errorCode;
-(NSString*)errorText;

@end
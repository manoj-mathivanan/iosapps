//  ODPUserManager.h
//  SUPProxyClient
/***************************************************************/
//  Created by M, Pramod on 1/10/12.
//  Copyright (c) Sybase, An SAP Company. All rights reserved.
/***************************************************************/

#import <Foundation/Foundation.h>

#pragma mark - User Manager delegate defining the listener methods

/*!
 @protocol ODPUserManagerDelegate
 @abstract   Protocol for classes implementing notification listeners.
 @discussion  Protocol for classes implementing notification listeners. This class should be passed to the delegate variable of the user manager class object.
 */

@protocol ODPUserManagerDelegate<NSObject>
@required

/**
 * Called when the user registration is successful. This is true in case of asynchronous user registration only.
 * <pre>
 *  Usage
 * <code>
 *  -(IBAction)buttonsPressed:(UIButton*)button{
 *      ODPUserManager* userManager = [ODPUserManager getInstance:@"applicationid"];
 *      [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farm" error:nil];
 *      [userManager setDelegate:self];
 *      [userManager registerUserWithUser:@"username" activationCode:@"act.code" error:nil flag:NO];
 *  }
 *
 *  -(void)userRegistrationSuccessful
 *  {
 *      // Successful post-processing
 *  }
 * </code>
 * </pre>
 */

-(void)userRegistrationSuccessful;

/**
 * Called when the user registration has failed and the reason for failure is propogated through an error object. This is true in case of asynchronous user registration only.
 * <pre>
 *  Usage
 * <code>
 *  -(IBAction)buttonsPressed:(UIButton*)button{
 *      ODPUserManager* userManager = [ODPUserManager getInstance:@"applicationid"];
 *      [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farm" error:nil];
 *      [userManager setDelegate:self];
 *      [userManager registerUserWithUser:@"username" activationCode:@"act.code" error:nil flag:NO];
 *  }
 *
 *  -(void)userRegistrationFailed:(NSError*)error
 *  {
 *      // Error handling using the error object
 *  }
 * </code>
 * </pre>
 */

-(void)userRegistrationFailed:(NSError*)error userManager:(id)userManager;
@end


/*!
 @class ODPUserManager
 @abstract   Consists of methods for registering and de-registering users.
 @discussion  All the function calls in this class have various ways of provisioning settings on to the client and register the user with the help of these settings. We can also check if a user is registered and delete the user as and when necessary
 
 
 <br/><br/>
 <b>Error codes for registration</b>
 <br/><br/>
 
 515     -	Error retrieving the public key from the server.
 <br/>
 516	 -	Error sending request to the server.
 <br/>
 514     -  Unable to start traveler session.
 <br/>
 516	 -	Resetting communications or communications cancelled during send.
 <br/>
 558	 -	Cannot connect to server.
 <br/>
 563	 -	Bad credentials.
 <br/>
 571	 -	Server response timeout that occurs normally without ill effects.
 <br/>
 578	 -	Wrong user for device.
 <br/>
 579	 -	Wrong device for code.
 <br/>
 581	 -	Activation code check failed.
 <br/>
 584     -  Wrong public key. 
 <br/>
 580	 -	Activation code is invalid.
 <br/>
 6400	 -	Communication error that occurs normally without ill effects.
 <br/>
 6600	 -	COMMERR_USER_CANCELLED                     	                  	
 <br/>
 14801	 -	MCLERR_CALL_INIT_INSTANCE_FIRST
 <br/>
 14802	 -	MCLERR_CONNECTION_SETTINGS_INCOMPLETE
 <br/>
 14803	 -	MCLERR_INIT_INSTANCE_FAILED     
 <br/>
 14804	 -	MCLERR_SET_CONFIG_PROPERTY_FAILED   
 <br/>
 14805	 -	MCLERR_NULL_PROPERTY_VALUE              
 <br/>
 14806	 -	MCLERR_START_CLIENT_FAILED                 
 <br/>
 14807	 -	MCLERR_SHUTDOWN_CLIENT_FAILED              
 <br/>
 14809	 -	MCLERR_MOOBECT_CREATE_FAILURE              
 <br/>
 14810	 -	MCLERR_OPERATION_INVALID_FOR_STATE         
 <br/>
 14811	 -	MCLERR_OBJECT_REGISTRATION_FAILURE         
 <br/>
 14812	 -	MCLERR_INVALID_PARAMETER_TYPE               
 <br/>
 14813	 -	MCLERR_COULD_NOT_REACH_MMS_SERVER              
 <br/>
 14814	 -	MCLERR_MMS_AUTHENTICATION_FAILED               
 <br/>
 14815	 -	MCLERR_READ_FAILURE                            
 <br/>
 14816	 -	MCLERR_WRITE_FAILURE                           
 
 <br/><br/>
 <b>Auto registration errors</b>
 <br/><br/>
 
 14850	 -	MCLERR_AUTO_REG_TEMPLATE_NOT_FOUND   
 <br/>
 14851	 -	MCLERR_AUTO_REG_NOT_ENABLED               
 <br/>
 14852	 -	MCLERR_AUTO_REG_REGISTRATION_NOT_FOUND   
 <br/>
 14853	 -	MCLERR_AUTO_REG_WRONG_USER_FOR_DEVICE    
 <br/>
 14854	 -	MCLERR_AUTO_REG_USER_NAME_TOO_LONG       
 <br/>
 14855	 -	MCLERR_AUTO_REG_DEVICE_ALREADY_REGISTERED 
 <br/>
 14899	 -	MCLERR_UNKNOWN_ERROR                       
 <br/>
 
 
 70000	 -	One or more input fields are empty.
 <br/>
 70001	 -	User is already registered or the previous user has not been deleted.
 <br/>
 70002	 -	User to be deleted is not registered.
 <br/>
 70003	 -	User registration timed out.
 <br/>
 70004	 -	All delegate methods have not been implemented.
 <br/>
 70005   -  SUP internal parsing error. 
 <br/>
 70006   -  Empty response string received from the server.
 <br/>
 70007   -  Customization Bundle not available.
 
 <br/><br/>
 <b>Error codes for request response</b>
 <br/><br/>
 
 71000	 -	URL is empty.
 <br/>
 71001	 -	Application identifier is null. User is not registered.
 <br/>
 71002	 -	Internal error. JSON parsing has failed.
 <br/>
 */

@interface ODPUserManager : NSObject{
    
    NSString* _hostName;
    NSInteger _portNumber;
    NSString* _farmId;
    
    id<ODPUserManagerDelegate> delegate;
}

/**
 Host name for which the user should be registered.    
 */

@property(nonatomic, readonly) NSString* _hostName;

/**
 Port of the server is open for the incoming requests from the client.
 */

@property(nonatomic, readonly) NSUInteger _portNumber;

/**
 Relay server farm to which SUP server belongs. It is important only when connecting via relay server. 
 */

@property(nonatomic, readonly) NSString* _farmId;

/**
 Push delegate adhering to the ODPUserManagerDelegate protocol to be implemented by the client to get the push data.
 */

@property(nonatomic, assign, setter = setDelegate:, getter = getDelegate) id<ODPUserManagerDelegate> delegate;


/**
 * Initialize the application. Gets the singleton instance or object of the UserManager class.
 * @param applicationId Application ID of the application trying to establish the connection.
 * @return Instance of ODPUserManager class
 * <pre>
 *  Usage
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 * </code>
 * </pre>
 */

+(ODPUserManager*)getInstance:(NSString*)applicationId;

/**
 * Provides connection properties to the UserManager class before registration or changes the connection settings after the user is registered.
 * @param hostName Host name or IP Address of the SUP server.
 * @param portNumber Port number of the SUP server with which the client communicates.
 * @param farmId Relay server farm ID to which the SUP server belongs. Relevant only during registration through relay server.
 * @param error Double pointer to the error object if the function returns an error. This is relevant while making changes to connection settings after the user has been registered.
 * @return BOOL indicating if the operation is successful or not.
 * <pre>
 *  Usage (Connection settings before user registration)
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farmid" error:nil];
 * </code>
 * </pre>
 * <pre>
 *  <br/>
 *  Usage (Connection settings change after user registration)
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  NSError* error = nil;
 *  [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farmid" error:&error];
 * </code>
 * </pre>
 */

-(BOOL)setConnectionProfileWithHost:(NSString*)hostName port:(NSInteger)portNumber farm:(NSString*)farmId error:(NSError**)error;

/**
 * Registers the client with a previous manually white-listed user on SCC. You can register the user
synchronously or ansynchronously.
 * @param userName User Name that is white-listed on SCC.
 * @param activationCode Activation code of the user created in SCC.
 * @param error Pointer to the error object if the function returns an error.
 * @param isSynchronous Flag to indicate if the user registration is synchronous or ansynchronous.
 * @return BOOL indicating if the user registration has been successful. Significant in case of synchronous registration only.
 * <pre>
 *  Usage (Synchronous registration)
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farmid" error:nil];
 *  NSError* error = nil;
 *  if ([userManager registerUser:@"username" activationCode:@"actcode" error:&error isSyncFlag:YES]) 
 *  {
 *      // Further processing
 *  } else 
 *  {
 *      // Error handling using the error object defined above
 *  }
 * </code>
 * </pre>
 * <pre>
 *  <br/>
 *  Usage (Asynchronous Registration)
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farmid" error:nil];
 *  [userManager setDelegate:self];         // The class implementing the listener methods should adhere to <ODPUserManagerDelegate> protocol
 *  [userManager registerUser:@"username" activationCode:@"actcode" error:nil isSyncFlag:NO];
 * </code>
 * </pre>
 */

-(BOOL)registerUser:(NSString*)userName activationCode:(NSString*)activationCode error:(NSError**)error isSyncFlag:(BOOL)isSynchronous;

/**
 * Registers the client with the server by automatically creating a user with the help of a pre-defined authentication mechanism.
 * @param userName User Name authorized by a predefined security provider.
 * @param securityConfig Security configuration name authenticating the user against an authentication provider.
 * @param loginPassword Password for the user (certificate string in case of certificate registration). 
 * @param error Pointer to the error object if the function returns an error.
 * @param isSynchronous Flag to indicate if the user registration is synchronous or ansynchronous.
 * @return BOOL indicating if the user registration has been successful. Significant in case of synchronous registration only.
 * <pre>
 *  Usage (Synchronous registration)
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farmid" error:nil];
 *  NSError* error = nil;
 *  if ([userManager registerUser:@"username" securityConfig:@"securityconfig" password:@"password" error:&error isSyncFlag:YES]) 
 *  {
 *      // Further processing
 *  } else 
 *  {
 *      // Error handling using the error object defined above
 *  }
 * </code>
 * </pre>
 * <pre>
 *  <br/>
 *  Usage (Asynchronous Registration)
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  [userManager setConnectionProfileWithHost:@"hostname" port:5001 farm:@"farmid" error:nil];
 *  [userManager setDelegate:self];         // The class implementing the listener methods should adhere to <ODPUserManagerDelegate> protocol
 *  [userManager registerUser:@"username" securityConfig:@"securityconfig" password:@"password" error:nil isSyncFlag:NO];
 * </code>
 * </pre>
 */

-(BOOL)registerUser:(NSString*)userName securityConfig:(NSString*)securityConfig password:(NSString*)loginPassword error:(NSError**)error isSyncFlag:(BOOL)isSynchronous;

/**
 * Deletes the application connection or user with which the application has established a connection.
 * @param error Pointer to the error object if the function returns an error. 
 * @return BOOL indicating if the user has been deleted or not.
 * <pre>
 *  Usage
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  NSError* error = nil;
 *  if([userManager deleteUserWithError:&error])
 *  {
 *      // Further Processing 
 *  }
 *  else
 *  {
 *      // Further Error processing using error object
 *  }
 * </code>
 * </pre>
 */

-(BOOL)deleteUserWithError:(NSError**)error;

/**
 * Checks if the user is still registered with the server and returns a value accordingly.
 * @return BOOL indicating if the user is registered or not.
 * <pre>
 *  Usage
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  if([userManager isUserRegistered])
 *  {
 *      // Further Processing 
 *  }
 * </code>
 * </pre>
 */

-(BOOL)isUserRegistered;

/*!
 * @method
 * @abstract Enables HTTPS.
 * @param flag Indicates whether HTTPS should be used.
 * <pre>
 *  Usage
 * <code>
 * [ODPUserManager enableHTTPS:YES];
 * </code>
 * </pre>
 */
+(void)enableHTTPS:(BOOL)flag;

/**
 * @method
 * @discussion Sets the URL suffix configured for the relay server.
 * @param _urlSuffix URL suffix to be configured for the relay server.
 * @param error Double pointer to the error object.
 * <pre>
 *  Usage
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
 *  NSError *error =nil,*error1=nil;
 *  [userManager setConnectionProfileWithHost:@"hostName" port:[portNumber intValue] farm:@"farmId" error:&error];
 *  [userManager setRelayServerUrlTemplate:@"urlSuffix" error:&error1];
 *      // Further Processing 
 * </code>
 * </pre>
 */

-(void)setRelayServerUrlTemplate:(NSString*)_urlSuffix error:(NSError**)error;

/**
 * @method
 * @discussion Set the HTTP headers and cookies to the HTTP request made from the client to the server.
 * @param headers HTTP header list as a key-value pair.
 * @param cookies HTTP cookie list as a key-value pair.
 * <pre>
 *  Usage
 * <code>
 *  ODPUserManager* userManager = [ODPUserManager getInstance:@"ApplicationId"];
`*  NSDictionary* headers = [NSDictionary dictionaryWithObject:@"sample value" forKey:@"Sample-Header"];
 *  NSDictionary* cookies = [NSDictionary dictionaryWithObject:@"adfasdJZBFSFJzjbZZBoZFPAKDJPHJZXN" forKey:@"MYSAPSSO2"];
 *  [userManager setHttpHeaders:headers error:cookies];
 *  OR 
 *  [userManager setHttpHeaders:nil error:cookies];     // If there are only cookies to be passed
 *  OR
 *  [userManager setHttpHeaders:headers error:nil];     // If there are only headers to be passed
 *      // Further Processing 
 * </code>
 * </pre>
 */

-(void)setHttpHeaders:(NSDictionary *)headers cookies:(NSDictionary *)cookies error:(NSError**)error;

@end




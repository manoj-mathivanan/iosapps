//  ODPClientListeners.h
//  SUPProxyClient
/***************************************************************/
//  Created by M, Pramod on 1/10/12.
//  Copyright (c) Sybase, An SAP Company. All rights reserved.
/***************************************************************/

#import <Foundation/Foundation.h>

/*!
 @protocol ODPCertificateChallengeListenerDelegate
 @abstract Protocol for classes implementing listeners for certificate challenges.
 @discussion  The SUP library should be able to connect to a relay server via HTTPS (or HTTP) using the iPhone SDKs native connectivity APIs.  If HTTPS is used, and a connection attempt occurs, some negotiation takes place. Depending on what SSL certificate is installed on the server, a different sequence can occur.  A certificate is delivered from the server to the device. If the certificate is trusted by the system or application keychain, then the connection is established.  Otherwise, a MessagingClientLibrary delegate is called, if there is a listener registered to handle it, to determine whether the certificate should be trusted.
 */
@protocol ODPCertificateChallengeListenerDelegate <NSObject>

@required
/**
 * Called when the ODPCertificateChallengeListenerDelegate protocol is implemented by the class. The application should implement this method to receive the certificate information.
 * <pre>
 *  Usage
 * <code>
 * -(void) onCertificateChallenge:(NSString*)certInfo  
 * {
 *      NSLog(@"Cert Info is: %@", certInfo);
 *      [ODPClientListeners certificateChallengeResult:YES];
 * }
 * </code>
 * </pre>
 */
-(void) onCertificateChallenge:(NSString*)certInfo;

@end


/*!
 @protocol ODPHTTPErrorListenerDelegate 
 @abstract Protocol for classes implementing listeners for HTTP error details.
 @discussion  When the client connects to the reverse proxy or relay server through HTTP, during the course of establishing connection, there might be errors. The client can get notified of these errors on implementing this protocol.
 */

@protocol ODPHTTPErrorListenerDelegate <NSObject>

@required
/**
 * Called when the ODPHTTPErrorListenerDelegate protocol is implemented by the class to receive the HTTP error details.
 * The application has to implement the method to receive the error message and the HTTP headers.
 * <pre>
 *  Usage
 * <code>
 *  -(void)onHTTPError:(int)code errorMessage:(NSString*)message httpHeaders:(NSDictionary*)headers
 *  {
 *      // Error handling using the error message and headers
 *  }
 * </code>
 * </pre>
 */
-(void) onHTTPError:(int)code errorMessage:(NSString*)message httpHeaders:(NSDictionary*)headers;

@end


/*!
 @protocol ODPHTTPAuthChallengeListenerDelegate 
 @abstract Protocol for classes implementing listeners for HTTP authentication challenges.
 @discussion  Optionally, the host that the client is connecting to (like a relay server) requires the client to authenticate with it.  The method of authentication to be supported is basic authentication.  On receiving an unauthorized request from a client, the server will respond with a challenge HTTP header: “WWW-Authenticate: Basic realm=”Sybase Relay Server””.  The client should send a user ID and password, separated by a single colon character within a base 64 encoded string for credentials within a subsequent HTTP request.  It will send the same credentials with all subsequent requests until another challenge is received.  While this is  supported across HTTP and HTTPS, basic authentication across HTTP is considered to be non-secure, as the base 64 encoded string is essentially the same thing as plain text.  If a user switches from HTTPS to HTTP, the basic authentication credentials is cleared.
 */

@protocol ODPHTTPAuthChallengeListenerDelegate <NSObject>

@required
/**
 * Called when ODPHTTPAuthChallengeListenerDelegate protocol is implemented by the class.
 * User Name contains the previous value on input.
 * <pre>
 *  Usage
 * <code>
 *  -(void) onHTTPAuthChallenge:(NSString*)host forUser:(NSString*)userName withRealm:(NSString*)realm
 * {
 *      NSLog(@"%@--%@--%@", host, userName, realm);
 *      [ODPClientListeners httpAuthChallengeResult:YES forUser:@"mobile" withPassword:@"Ntwatch@123"];
 * }
 * </code>
 * </pre>
 */ 
-(void) onHTTPAuthChallenge:(NSString*)host forUser:(NSString*)userName withRealm:(NSString*)realm;

@end


/*!
 @protocol ODPClientConnectionStateListener
 @abstract   Protocol for classes implementing listeners for client connection state changes.
 @discussion  Adhere to the protocol and implement the required method to listen to client connection state changes and error codes and notifies if there is a problem with the connection.
 
 <br/><br/>
 <b>Connection Status Codes</b>
 <br/><br/>
 1  --  Connected
 <br/>
 2  --  Disconnected
 <br/>
 3  --  Flight Mode 
 <br/>
 4  --  Out of network coverage
 <br/>
 5  --  Waiting to connect
 <br/>
 6  --  Device Roaming
 <br/>
 7  --  Device Low Storage
 <br/>
 */


@protocol ODPClientConnectionStateListener <NSObject>

@required

/**
 * Called when there is a client connection state change from the underlying layer. Implement the method to handle all connection state change notifications.
 * <pre>
 *  Usage
 * <code>
 *  -(void) onConnectionStateChanged:(NSInteger) connStatus connectionType:(NSInteger)connType error:(NSInteger)errCode errorMsg:(NSString *)errMsg
 * {
 *     NSLog(@"%d--%d--%d--%@", connStatus, connType, errCode, errMsg);
 * }
 * </code>
 * </pre>
 */

-(void) onConnectionStateChanged:(NSInteger) connStatus connectionType:(NSInteger)connType error:(NSInteger)errCode errorMsg:(NSString *)errMsg;

@end

/*!
 @protocol ODPClientConfigurationStateListener
 @abstract   Protocol for classes implementing listeners for client configuration state changes. This can correspond to changing proeprties on the SCC such as host, port, endpoint details etc.
 @discussion  Follow the protocol and implement the required method to listen to property value changes initiated from the server or client.
 <br/><br/>
 <b>Property Ids</b>
 <br/><br/>
 1	~~	  MCL_PROP_ID_CONNECTION_SERVER_NAME
 <br/>		
 2	~~	  MCL_PROP_ID_CONNECTION_SERVER_PORT
 <br/>		
 3	~~	  MCL_PROP_ID_CONNECTION_FARM_ID
 <br/>		
 7	~~	  MCL_PROP_ID_CONNECTION_DOMAIN
 <br/>		
 8	~~	  MCL_PROP_ID_CONNECTION_SYNC_SVR_HOST
 <br/>		
 9	~~	  MCL_PROP_ID_CONNECTION_SYNC_SVR_PORT
 <br/>		
 10	~~	  MCL_PROP_ID_CONNECTION_SYNC_SVR_PROTOCOL
 <br/>		
 11	~~	  MCL_PROP_ID_CONNECTION_SYNC_SVR_URL_SUFFIX
 <br/>		
 12	~~	  MCL_PROP_ID_CONNECTION_SYNC_SVR_STREAM_PARAMS
 <br/>		
 20	~~	  MCL_PROP_ID_CONNECTION_USE_HTTPS
 <br/>		
 10001	~~	  MCL_PROP_ID_CONNECTION_USER_NAME
 <br/>		
 10002	~~	  MCL_PROP_ID_CONNECTION_ACTIVATION_CODE
 <br/>		
 1200	~~	  MCL_PROP_ID_DEVICE_MODEL
 <br/>		
 1201	~~	  MCL_PROP_ID_DEVICE_SUBTYPE
 <br/>		
 1202	~~	  MCL_PROP_ID_DEVICE_PHONE_NUMBER
 <br/>		
 1203	~~	  MCL_PROP_ID_DEVICE_IMSI
 <br/>		
 1302	~~	  MCL_PROP_ID_ADVANCED_MOCA_TRACE_LEVEL
 <br/>		
 1303	~~	  MCL_PROP_ID_ADVANCED_MOCA_TRACE_SIZE
 <br/>		
 1305	~~	  MCL_PROP_ID_ADVANCED_RELAY_SVR_URL_TEMPLATE
 <br/>		
 2300	~~	  MCL_PROP_DEF_CUSTOM_CUSTOM1
 <br/>		
 2301	~~	  MCL_PROP_DEF_CUSTOM_CUSTOM2
 <br/>		
 2302	~~	  MCL_PROP_DEF_CUSTOM_CUSTOM3
 <br/>		
 2303	~~	  MCL_PROP_DEF_CUSTOM_CUSTOM4
 <br/>		
 2400	~~	  MCL_PROP_ID_IPHONE_SEC_MIN_PASSWORD_LENGTH
 <br/>		
 2401	~~	  MCL_PROP_ID_IPHONE_SEC_REQUIRE_STRONG_PASSWORD
 <br/>		
 2402	~~	  MCL_PROP_ID_IPHONE_SEC_IDLE_TIMEOUT
 <br/>		
 2403	~~	  MCL_PROP_ID_IPHONE_SEC_MISSED_PASSWORD_DATA_WIPE
 <br/>		
 2800	~~	  MCL_PROP_ID_SECURITY_E2E_ENCRYPTION_ENABLED
 <br/>		
 2801	~~	  MCL_PROP_ID_SECURITY_E2E_ENCRYPTION_TYPE
 <br/>		
 2802	~~	  MCL_PROP_ID_SECURITY_TLS_TYPE
 <br/>		
 1400	~~	  MCL_PROP_ID_FT_SM_LEVEL
 <br/>		
 3000	~~	  MCL_PROP_ID_PROXY_APPLICATION_ENDPOINT
 <br/>		
 3001	~~	  MCL_PROP_ID_PROXY_PUSH_ENDPOINT
 <br/>		
 10005	~~	  MCL_PROP_ID_CONNECTION_AUTO_REGISTRATION_HINT
 <br/>		
 20000	~~	  MCL_PROP_ID_SETTINGS_EXCHANGE_COMPLETE
 <br/>		
 */


@protocol ODPClientConfigurationStateListener <NSObject>

/**
 * Called when there are client configuration property state changes, from the underlying layer.
 * <pre>
 *  Usage
 * <code>
 *  -(void)onConfigurationChange:(NSInteger)iPropertyID  value:(id)oValue
 * {
 *      NSLog(@"--%d---%@---", iPropertyID, oValue);
 *      if(iPropertyID==kCustResourceBundlePropID)
 * {
 *      //Handle customization resource bundle
 * }
 * }
 * </code>
 * </pre>
 */

-(void) onConfigurationChange:(NSInteger)iPropertyID  value:(id)oValue;

@end


/*!
 @class ODPClientListeners
 @abstract   Consists of methods used to register listeners for notifying client side changes.
 @discussion  Register notification listeners for client state change notifications. The client state changes include connection state changes and configuration property state changes.              
 */

@interface ODPClientListeners : NSObject

#pragma mark - Result notifiers

/*!
 @method
 @abstract Called by application to pass the certificate challenge result from the user.
 @discussion This function is used to tell the communication library the result of whether the certificate should be accepted or not.
 @param challengeResult BOOL indicating whether the certificate should be accepted.
 * <pre>
 *  Usage
 * <code>
 * [ODPClientListeners certificateChallengeResult:YES];
 * </code>
 * </pre>
 */
+(void)certificateChallengeResult:(BOOL)challengeResult;

/*!
 @method
 @abstract Called by application to pass the challenge result from user.
 @discussion This function is used to tell the communication library the result of whether the certificate should be accepted or not.
 @param credentialsSupplied BOOL indicating whether the credentials are supplied.
 @param userName NSString containing the username.
 @param password NSString containing the password.
 * <pre>
 *  Usage
 * <code>
 * [ODPClientListeners httpAuthChallengeResult:YES forUser:@"mobile" withPassword:@"Ntwatch@123"];
 * </code>
 * </pre>
 */
+(void)httpAuthChallengeResult:(BOOL)credentialsSupplied forUser:(NSString *)userName withPassword:(NSString *)password;


# pragma mark - State listener accessors

/*!
 *  Setter for the connection state listener. This is a class method to register the connection state listener with the ODP Client framework
 *  @param listener A listener object whose definition adheres to the appropriate protocol.
 *  <pre>
 *  Usage
 *  <code>
 *  [ODPClientListeners setConnectionStateListenerDelegate:self];       // The class implementing this should ahere to 
    <ODPClientConnectionStateListener> Protocol
 *  </code>
 *  </pre> 
 */

+(void)setConnectionStateListenerDelegate:(id<ODPClientConnectionStateListener>)_listener;

/*!
 *  Get the connection state listener which has been registered with the ODP Client framework.
 *  @return Instance of the object implementing the listener interface.
 *  <pre>
 *  Usage
 *  <code>
 *  id<ODPClientConnectionStateListener> = [ODPClientListeners getConnectionStateListenerDelegate]; 
 *  </code>
 *  </pre> 
 */


+(id<ODPClientConnectionStateListener>)getConnectionStateListenerDelegate;

/*!
 *  Setter for the configuration state listener. This is a class method to register the configuration state listener with the ODP Client framework
 *  @param listener A listener object whose definition adheres to the appropriate protocol.
 *  <pre>
 *  Usage
 *  <code>
 *  [ODPClientListeners setConfigurationStateListenerDelegate:self];       // The class implementing this should ahere to 
    <ODPClientConfigurationStateListener> Protocol
 *  </code>
 *  </pre> 
 */

+(void)setConfigurationStateListenerDelegate:(id<ODPClientConfigurationStateListener>)_listener;

/*!
 *  Get the the configuration state listener which has been registered with the ODP Client framework.
 *  @return Instance of the object implementing the listener interface.
 *  <pre>
 *  Usage
 *  <code>
 *  id<ODPClientConfigurationStateListener> = [ODPClientListeners ODPClientConfigurationStateListener]; 
 *  </code>
 *  </pre> 
 */

+(id<ODPClientConfigurationStateListener>)getConfigurationStateListenerDelegate;

/*!
 @method
 @abstract Setter for the certificate challenge listener.
 @discussion This is a class method to register the certificate challenge listener with the ODP Client framework
 @param listener A listener object whose definition adheres to the appropriate protocol.
 *  <pre>
 *  Usage
 *  <code>
 *  [ODPClientListeners setCertificateChallengeListenerDelegate:self]; 
 *  </code>
 *  </pre>
 */

+(void)setCertificateChallengeListenerDelegate:(id<ODPCertificateChallengeListenerDelegate>)listener;

/*!
 @method
 @abstract Getter for the certificate challenge listener.
 @discussion This is a class method to fetch the certificate challenge listener object.
 @result Instance of the listener object.
 */

+(id<ODPCertificateChallengeListenerDelegate>)getCertificateChallengeListenerDelegate;

/*!
 @method
 @abstract Setter for the basic HTTP authentication challenge listener.
 @discussion This is a class method to register the basic HTTP authentication challenge listener with the ODP Client framework
 @param listener A listener object whose definition adheres to the appropriate protocol.
 *  <pre>
 *  Usage
 *  <code>
 *  [ODPClientListeners setHTTPAuthChallengeListenerDelegate:self];
 *  </code>
 *  </pre>
 */

+(void)setHTTPAuthChallengeListenerDelegate:(id<ODPHTTPAuthChallengeListenerDelegate>)listener;

/*!
 @method
 @abstract Getter for the basic HTTP authentication challenge listener.
 @discussion This is a class method to fetch the basic HTTP authentication challenge listener object.
 @result Instance of the listener object.
 */

+(id<ODPHTTPAuthChallengeListenerDelegate>)getHTTPAuthChallengeListenerDelegate;

/*!
 @method
 @abstract Setter for the HTTP error listener.
 @discussion This is a class method to register the HTTP error listener with the ODP Client framework
 @param listener A listener object whose definition adheres to the appropriate protocol.
 *  <pre>
 *  Usage
 *  <code>
 *  [ODPClientListeners setHTTPErrorListenerDelegate:self];
 *  </code>
 *  </pre>
 */

+(void)setHTTPErrorListenerDelegate:(id<ODPHTTPErrorListenerDelegate>)listener;

/*!
 @method
 @abstract Getter for the HTTP error listener.
 @discussion This is a class method to fetch the HTTP error listener object
 @result Instance of the listener object.
 */

+(id<ODPHTTPErrorListenerDelegate>)getHTTPErrorListenerDelegate;


@end

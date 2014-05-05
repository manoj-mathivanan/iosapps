//  ODPAppSettings.h
//  SUPProxyClient
/***************************************************************/
//  Created by M, Pramod on 1/10/12.
//  Copyright (c) Sybase, An SAP Company. All rights reserved.
/***************************************************************/

#import <Foundation/Foundation.h>

// Attributes defining password policy used by DataVault

@interface PasswordPolicy : NSObject {
    BOOL defaultPasswordAllowed;
    NSInteger minLength;               
    BOOL hasDigits;
    BOOL hasUpper;
    BOOL hasLower;
    BOOL hasSpecial;
    NSInteger expirationDays;               
    NSInteger minUniqueChars;               
    NSInteger lockTimeout;               
    NSInteger retryLimit;               
}

@property (nonatomic, assign, readwrite) BOOL defaultPasswordAllowed;
@property (nonatomic, assign, readwrite) NSInteger minLength;
@property (nonatomic, assign, readwrite) BOOL hasDigits;
@property (nonatomic, assign, readwrite) BOOL hasUpper;
@property (nonatomic, assign, readwrite) BOOL hasLower;
@property (nonatomic, assign, readwrite) BOOL hasSpecial;
@property (nonatomic, assign, readwrite) NSInteger expirationDays;
@property (nonatomic, assign, readwrite) NSInteger minUniqueChars;
@property (nonatomic, assign, readwrite) NSInteger lockTimeout;
@property (nonatomic, assign, readwrite) NSInteger retryLimit;

@end

/*!
 @class ODPAppSettings
 @abstract   Utility class to fetch settings required by the application
 @discussion  This class implements static methods to fetch settings like end-points for application data access and for push and also connection settings like host, port and the farm              
 */

@interface ODPAppSettings : NSObject

/**
 * Fetches the end-point using which the application can start accessing the business data (application end-point)
 * @param error A double pointer to the error object in case the operation results in an error
 * @return Returns the end-point as a string object (URL/URN.)
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  NSString* appEndPoint = [ODPAppSettings getApplicationEndpointWithError:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */

+(NSString*)getApplicationEndpointWithError:(NSError**)error;

/**
 * Fetches the Password Policy set by the Admin in SCC for this Application.
 * @param error A double pointer to the error object in case the operation results in an error
 * @return Returns the structure containing the Password policy
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  PasswordPolicy *dvppStruct = [ODPAppSettings getPasswordPolicy:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */

+(PasswordPolicy*)getPasswordPolicy:(NSError**)error;

/**
 * Fetches the end-point using which the enterprise back-end can push data to the ODP client via the server.
 * This end-point will be registered with the enterprise back-end during the process of subscription
 * @param error A double pointer to the error object in case the operation results in an error
 * @return Returns the end-point as a string object (URL/URN.)
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  NSString* pushEndPoint = [ODPAppSettings getPushEndpointWithError:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */

+(NSString*)getPushEndpointWithError:(NSError**)error;

/**
 * Fetches the server host name against which the user is registered.
 * @param error A double pointer to the error object in case the operation results in an error
 * @return Returns the server host name as a string object
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  NSString* hostName = [ODPAppSettings getServerNameWithError:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */

+(NSString*)getServerNameWithError:(NSError**)error;

/**
 * Fetches the server port number which has been opened up for client to connect to it.
 * @param error A double pointer to the error object in case the operation results in an error
 * @return Returns the server port number as an integer
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  NSInteger portNum = [ODPAppSettings getPortNumberWithError:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */

+(NSInteger)getPortNumberWithError:(NSError**)error;

/**
 * Fetches the farm to which the SAP Mobile Server belongs to. Has significance only when the client is connecting to 
 * the server via a Relay Server.
 * @param error A double pointer to the error object in case the operation results in an error.
 * @return Returns the farm ID as a string object
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  NSString* farmId = [ODPAppSettings getFarmIdWithError:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */

+(NSString*)getFarmIdWithError:(NSError**)error;

/**
 * Checks to see the public key of the SAP Mobile Server is provisioned on the client or not.
 * @return Returns a BOOL indicating whether the key has been provisioned or not.
 * <pre>
 *  Usage
 * <code>
 *  if ([ODPAppSettings isServerKeyProvisioned) {
 *      // Processing.......
 *  }
 * </code>
 * </pre>
 */

+(BOOL)isServerKeyProvisioned;

/**
 * Returns/downloads Customization Resources as binary data.
 * @param customizationResource:  Customization Resource
 * @param userName:               user name
 * @param passWord:               password
 * @param error A double pointer to the error object in case the operation results in an error.
 * @discussion This API returns the Customization Resource zip/jar file as binary data.
 * @return This returns the Customization Resource in the form of binary data.
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  NSData* customResourceBundleData = [ODPAppSettings getCustomizationResourceBundleWithCustomizationResource:customizationResource userName:USERNAME passWord:PASSWORD error:&error];
 *  if (!error) 
 *  {
 *      // Further processing
 *  }
 * </code>
 * </pre>
 */
+(NSData*)getCustomizationResourceBundleWithCustomizationResource:(NSString*) customizationResource userName:(NSString*) userName passWord:(NSString*)passWord error:(NSError**)error;

@end
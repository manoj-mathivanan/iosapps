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
 @abstract   Consists of methods used to retrieve setting details required by the application.
 @discussion  This class implements static methods to fetch settings like end-points for application data access, push and connection settings like host, port, and farm.
 */

@interface ODPAppSettings : NSObject

/**
 * Retrieves the application end-point with which the application can access business data.
 * @param error Double pointer to the error object if the method results in an error.
 * @return End-point as a string object (URL/URN).
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
 * Retrieves the password policy set by the administrator in SCC for the application.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Structure containing the password policy.
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
 * Retrieves the push end-point which the enterprise back-end can use to push data to the ODP client via the server.
 * This end-point will be registered with the enterprise back-end during the process of subscription.
 * @param error Double pointer to the error object if the method results in an error.
 * @return End-point as a string object (URL/URN).
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
 * Retrieves the server host name provisioned in the client.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Server host name as a string object.
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
 * Retrieves the server port number provisioned in the client.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Server port number as an integer.
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
 * Retrieves the farm ID to which the SUP server belongs. This has significance only when the client is connecting to the server via a Relay Server.
 * @param error Double pointer to the error object if the method results in an error.
 * @return Farm ID as a string object.
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
 * Checks if the public key of the SUP server is provisioned on the client.
 * @return BOOL indicating whether the key is provisioned or not.
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
 * Returns or downloads customization resources as binary data.
 * @param customizationResource:  Customization resource name
 * @param userName:               User name.
 * @param passWord:               Password.
 * @param error Double pointer to the error object if the method results in an error.
 * @discussion Returns the customization resource (zip or jar file) as binary data.
 * @return Customization resource as binary data.
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

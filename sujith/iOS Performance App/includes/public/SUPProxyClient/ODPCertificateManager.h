//  ODPCertificateManager.h
//  SUPProxyClient
/***************************************************************/
//  Created by M, Pramod on 1/10/12.
//  Copyright (c) Sybase, An SAP Company. All rights reserved.
/***************************************************************/

#import <Foundation/Foundation.h>

/*!
 @class ODPCertificateManager
 @abstract   Consists of methods to retrieve the provisioned certifice locally or remotely.
 @discussion  This class has a static method to get the certificate as a base-64 encoded string from a local file system. 
*/

@interface ODPCertificateManager : NSObject

/**
 * Retrieves the X.509 certificate stored in the local file system as a base-64 encoded string. 
 * @param filePath Path to the file including the file name and extension.
 * @param certPassword Password for the certificate.
 * @param error Pointer to the error object to be filled by the method during an error.
 * @return x.509 certificate as a base-64 encoded string.
 * <pre>
 *  Usage
 * <code>
 *  NSError* error = nil;
 *  [ODPCertificateManager getSignedCertificateFromFile:@"Filename" password:@"Password" error:&error];
 *  if (!error) {
 *  // Further Processing
 *  }
 * </code>
 * </pre>
 */

+(NSString*)getSignedCertificateFromFile:(NSString *)filePath password:(NSString *)certPassword error:(NSError**)error;


@end

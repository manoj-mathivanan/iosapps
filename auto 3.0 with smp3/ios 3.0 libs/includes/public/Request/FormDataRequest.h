//
//  FormDataRequest.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Request.h"

typedef enum EPostFormat {
    MultipartFormDataPostFormat = 0,	///< Multipart form data
    URLEncodedPostFormat = 1			///< URL-encoded Post format
	
} PostFormat;
/**
 * Composes a form data request
 */
@interface FormDataRequest : Request <NSCopying> {
	PostFormat m_PostFormat; ///< Multipart form data or url-encoded post format
	NSStringEncoding m_StringEncoding; ///< encoding, defaults to UTF8
}

#pragma mark -
#pragma mark Request Setup

//! Adds a POST variable to the request
- (void)addPostValue:(id <NSObject>)value forKey:(NSString *)key;

//! Sets a POST variable for this request, clearing any others with the same key
- (void)setPostValue:(id <NSObject>)value forKey:(NSString *)key;

//! Adds the contents of a local file to the request
- (void)addFile:(NSString *)filePath forKey:(NSString *)key;

/**
 * Adds the contents of a local file to the request
 * @remark You can specify the content-type and file name
 */
- (void)addFile:(id)data withFileName:(NSString *)fileName andContentType:(NSString *)contentType forKey:(NSString *)key;

/**
 * Adds the contents of a local file to the request, clearing any others with the same key
 */
- (void)setFile:(NSString *)filePath forKey:(NSString *)key;

/**
 * Adds the contents of a local file to the request, clearing any others with the same key
 * @remark You can specify the content-type and file name
 */
- (void)setFile:(id)data withFileName:(NSString *)fileName andContentType:(NSString *)contentType forKey:(NSString *)key;

/**
 * Adds the contents of an NSData object to the request
 */
- (void)addData:(NSData *)data forKey:(NSString *)key;

/**
 * Same as above, but you can specify the content-type and file name
 */
- (void)addData:(id)data withFileName:(NSString *)fileName andContentType:(NSString *)contentType forKey:(NSString *)key;

/**
 * Adds the contents of an NSData object to the request, clearing any others with the same key
 */
- (void)setData:(NSData *)data forKey:(NSString *)key;

/**
 * Same as above, but you can specify the content-type and file name
 */
- (void)setData:(id)data withFileName:(NSString *)fileName andContentType:(NSString *)contentType forKey:(NSString *)key;

#pragma mark -
#pragma mark Utilities

- (NSString*)encodeURL:(NSString *)string;

#pragma mark -
#pragma mark Accessors

@property (assign) PostFormat postFormat;
@property (assign) NSStringEncoding stringEncoding;
@end

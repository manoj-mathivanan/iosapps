//
//  RequestBuilder.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "Requesting.h"
#import "CacheDelegate.h"

/**
 * Defines authentication related constants
 */
typedef enum ERequestType {
	ODPRequestType	= 0xFE,  ///< denotes SUPRequest
	HTTPRequestType = 0xFF ///< denotes Request
} RequestType;

typedef enum ETraceLevel {
	LOW	= 1,
	MEDIUM,
    HIGH,
    NONE
} Level;

/**
 * String constant to be used by clients to manage the request type
 * <pre>
 * Usage on client side:
 * <code>
 * [RequestBuilder setRequestType:HttpRequestType];
 * ...
 * // or you can set the value directly, just ensure you are using the proper, unique key
 * NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
 *
 * [defaults setInteger:SUPRequestType forKey:ConnectivityRequestTypeKey];
 * [defaults synchronize];
 * </pre>
 */


@class ODPRequest;
@class Request;
/*
 * Acts as a configuration based runtime switch between Request or SUPRequest
 * @discussion The provided factory methods can return a valid Request, but we cannot guarantee this for SUPRequest \
 * However, as the SUPRequest library and public headers are not bundled with Connectivity lib, we attempt to create the SUPRequest class using NSClassFromString(@"SUPRequest"). \
 * NSClassFromString will work correctly only if: \
 * a) the SUPRequest library and the public header are added to the client project \
 * b) the -ObjC value is added to the Other Linker Flags
 */
@interface RequestBuilder :  NSObject
{
@private
	RequestType m_RequestType;
}

+(void)setDelegate:(id)delegate;

+(id)getDelegate;

+(void)setDidFinishSelector:(SEL)selector;

+(SEL)getDidFinishSelector;

+(void)setDidFailSelector:(SEL)selector;

+(SEL)getDidFailSelector;

+(BOOL)isOfflineEnabled;

+(void)clearPendingRequestsWithError:(NSError*)error;

/**
 * Factory method with url
 * @remark Can instantiate SUPRequest or Request based on the configuration.
 * @discussion Internally the factory method decides which class to be instantiated based on a setting stored in NSUserDefaults.
 * @see (void) setRequestType:(const enum ERequestType) type_in
 */
+ (id<Requesting>)requestWithURL:(NSURL *)newURL;
/**
 * Factory method with url and cache
 * @remark Can instantiate SUPRequest or Request based on the configuration. The cache parameter gets ignored whenever an SUPRequest is created
 * @discussion Request supports the download cache feature; clients might pass a valid download cache object; this paramater is ignored whenever an SUPRequest is created
 * (id<Requesting>)requestWithURL:(NSURL *)newURL
 */
+ (id<Requesting>)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache;
/**
 * Factory method with url, cache and a cache policy
 * @remark Can instantiate SUPRequest or Request based on the configuration. Cache related parameters get ignored whenever an SUPRequest is created.
 * @discussion Request supports the download cache feature; clients might pass a valid download cache object and a cache policy; cache parameters are ignored whenever an SUPRequest is created
 * @see (id<Requesting>)requestWithURL:(NSURL *)newURL
 */
+ (id<Requesting>)requestWithURL:(NSURL *)newURL usingCache:(id <CacheDelegate>)cache andCachePolicy:(ECachePolicy)policy;

/**
 * Helper method to store the request type to be instantiated; the builder decides which class (Request or SUPRequest) should be instantiated based on this value
 */
+ (void) setRequestType:(const enum ERequestType) type_in;
/**
 * Helper method to retrieve the request type to be instantiated from NSUserDefaults
 */
+ (enum ERequestType) retrieveRequestType;

/**
 * Switches traceability status, the default is NO
 * <pre>
 * Usage:
 * <code>
 * // set the request type
 * [RequestBuilder setRequestType:HTTPRequestType];
 * // enable tracing *before* instantiating the request
 * [RequestBuilder enableTracing:YES];
 * // instantiate the request
 * self.request = [RequestBuilder requestWithURL:demoUrl];
 * ...
 * <pre>
 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality
 */
+ (void) enableTracing:(BOOL)value_in;
/**
 * Set the trace level, default is MEDIUM
 * <pre>
 * Usage:
 * <code>
 * // enable tracing *before* instantiating the request
 * [RequestBuilder enableTracing:YES];
 * // set the trace level
 * [RequestBuilder setTraceLevel:HIGH];
 * // instantiate the request
 * self.request = [RequestBuilder requestWithURL:demoUrl];
 * ...
 * <pre>
 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality
 */
+ (void) setTraceLevel:(Level)value_in;

+ (int) getTraceLevel;

/**
 * Enable XCSRF support. It is disabled by default.
 * <pre>
 * Usage:
 * <code>
 * // enable xcsrf *before* instantiating the request
 * [RequestBuilder enableXCSRF:YES];
 * // instantiate the request
 * self.request = [RequestBuilder requestWithURL:demoUrl];
 * ...
 * <pre>
 */
+ (void)enableXCSRF:(BOOL) enable;
/**
 * Returns tracing status (default is NO)
 * @see setTracingEnabled:
 */
+ (BOOL) isTracingEnabled;

/**
 * This is an API to help clear the Queue of all queued requests.
 * <pre>
 * Usage:
 * <code>
 * [RequestBuilder cancelAllRequestsInQueue];
 * <pre>
 */
+ (void)cancelAllRequestsInQueue;


@end


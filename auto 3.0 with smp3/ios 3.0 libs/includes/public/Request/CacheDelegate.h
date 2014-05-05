//
//  CacheDelegate.h
//  Request
//
//  Created by i061647 on 5/27/13.
//  Copyright (c) 2013 i061647. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol Requesting;

/**
 * Supported cache policies
 */
typedef enum
{
	//!
	_DefaultCachePolicy = 0,
    //! do not use the DownloadCache
	_IgnoreCachePolicy = 1,
	//! fetch only if cached content differs from server content
	_ReloadIfDifferentCachePolicy = 2,
	//! fetch only when cache is empty
	_OnlyLoadIfNotCachedCachePolicy = 3,
	//! fetch only when network errors occur
	_UseCacheIfLoadFailsCachePolicy = 4
} ECachePolicy;

/**
 * Supported cache lifetime policies
 */
typedef enum 
{
	//! cache is persisted only for this session
	_CacheForSessionDurationCacheStoragePolicy = 0,
	//! cache persists after the session expires
	_CachePermanentlyCacheStoragePolicy = 1
} ECacheStoragePolicy;

/**
 * Defines default DownloadCache delegate methods
 * Protocol to be adapted by client classes in order to achieve the DownloadCache functionality
 * @remark Clients might consider using the DownloadCache rather than implementing a custom download cache
 */
@protocol CacheDelegate <NSObject>

@required

/**
 * Should return the cache policy that will be used when requests have their cache policy set to DefaultCachePolicy
 */
- (ECachePolicy)defaultCachePolicy;

/**
 * Should Remove cached data for a particular request
 */
- (void)removeCachedDataForRequest:( id<Requesting> )request;

/**
 * Should return YES if the cache considers its cached response current for the request
 * Should return NO if the data is not cached, or (for example) if the cached headers state the request should have expired
 */
- (BOOL)isCachedDataCurrentForRequest:(id<Requesting>)request;

/**
 * Should store the response for the passed request in the cache
 * When a non-zero maxAge is passed, it should be used as the expiry time for the cached response
 */
- (void)storeResponseForRequest:(id<Requesting>)request maxAge:(NSTimeInterval)maxAge;

/**
 * Should return an NSDictionary of cached headers for the passed request, if it is stored in the cache
 */
- (NSDictionary *)cachedHeadersForRequest:(id<Requesting>)request;

/**
 * Should return the cached body of a response for the passed request, if it is stored in the cache
 */
- (NSData *)cachedResponseDataForRequest:(id<Requesting>)request;

/**
 * Same as the above, but returns a path to the cached response body instead
 */
- (NSString *)pathToCachedResponseDataForRequest:(id<Requesting>)request;

/**
 * Clear cached data stored for the passed storage policy
 */
- (void)clearCachedResponsesForStoragePolicy:(ECacheStoragePolicy)cachePolicy;
@end


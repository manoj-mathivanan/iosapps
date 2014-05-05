//
//  SDMHTTPRequest.h
//
//  SDMConnectivity library
//
//  Created by Karoly Nyisztor on Apr 11, 2011
//  Copyright SAP AG 2011. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CFNetwork/CFNetwork.h>

#if __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
#import <UIKit/UIKit.h> // Necessary for background task support
#endif

// !!! switch this on only for special builds meant for internal performance testing
#define ENABLE_PERFORMANCE_MEASUREMENTS 0


#import <stdio.h>
#import "SDMRequesting.h"
#import "SDMHttpRequestDelegate.h"
#import "SDMProgressDelegate.h"
#import "SDMCacheDelegate.h"


/**
 * Defines authentication related constants
 */
typedef enum EAuthenticationState {
	NoAuthenticationNeededYet = 0,  ///< no authentication needed
	HTTPAuthenticationNeeded = 1,   ///< server with basic authentication requests credentials
	ProxyAuthenticationNeeded = 2   ///< proxy authentication required
} AuthenticationState;

/**
 * Defines common error types (connection and internal library malfunction related constants)
 */
typedef enum ENetworkErrorType {
    ConnectionFailureErrorType = 1,		///< Connection Failure
    RequestTimedOutErrorType = 2,		///< Timeout
    AuthenticationErrorType = 3,		///< Authentication problem
    RequestCancelledErrorType = 4,		///< HTTP request cancelled
    UnableToCreateRequestErrorType = 5, ///< Request creation error
    InternalErrorWhileBuildingRequestType  = 6, ///< Denotes an internal library error
    InternalErrorWhileApplyingCredentialsType  = 7, ///< Denotes an internal library error
	FileManagementError = 8,            ///< Issues while storing / loading files
	TooMuchRedirectionErrorType = 9,    ///< Redirection limit exceeded
	UnhandledExceptionError = 10,       ///< This one caught us unprepared
	InternalServerError = 11            ///< response status code 500 received from the server	
} NetworkErrorType;

extern NSString* const NetworkRequestErrorDomain; ///< The error domain that all errors generated by HTTPRequest use

/**
 * Handles Http requests
 * @remark Wrapper around CFNetwork
 * <pre>
 * Features:
 * <ul>
 * <li> Synchronous and asynchronous execution
 * <li> Continues downloading and uploading when app is sent to the background (iOS 4.0+ only)
 * <li> Network Queue for batch http request processing and progress tracking
 * <li> Protected download cache; encrypted offline storage of downloaded content (iOS 4.0+ only)
 * <li> Secure connection (iOS 4.0+ only)
 * <li> Easy to extend
 * <li> Progress tracking
 * </ul>
 * </pre>
 */
@interface SDMHttpRequest : NSOperation <SDMRequesting, NSCopying> {
	
	//! The url for this operation, should include GET params in the query string where appropriate
	NSURL* m_Url; 
	
	//! Will always contain the original url used for making the request (the value of url can change when a request is redirected)
	NSURL* m_OriginalURL;
			
	//! HTTP method to use (GET / POST / PUT / DELETE / HEAD). Defaults to GET
	NSString* m_RequestMethod;
	
	//! The delegate, you need to manage setting and talking to your delegate in your subclasses
	id <SDMHttpRequestDelegate> m_Delegate;
	
	/**
	 * Another delegate that is also notified of request status changes and progress updates
	 * Generally, you will not use this directly, but SDMNetworkQueue sets itself as the queue so it can proxy updates to its own delegates
	 * @remark Will be retained by the request
	 */
	id <SDMHttpRequestDelegate, SDMProgressDelegate> m_Queue;
	
	//! Request body - only used when the whole body is stored in memory (shouldStreamPostDataFromDisk is false)
	NSMutableData* m_PostBody;
		
	/** When true, post body will be streamed from a file on disk, rather than loaded into memory at once (useful for large uploads)
	 * Automatically set to true in FormDataRequests when using setFile:forKey:
     */
	BOOL m_ShouldStreamPostDataFromDisk;
	
	/**
     * Path to file used to store post body (when shouldStreamPostDataFromDisk is true)
	 * You can set this yourself - useful if you want to PUT a file from local disk 
     */
	NSString* m_PostBodyFilePath;
	
	/**
     * Path to a temporary file used to store a deflated post body (when shouldCompressPostBody is YES)
     */
//	NSString* m_CompressedPostBodyFilePath;
	
	/**
     * Set to true when HTTPRequest automatically created a temporary file containing the request body 
     * (when true, the file at postBodyFilePath will be deleted at the end of the request)
     */
	BOOL m_DidCreateTemporaryPostDataFile;	
	
	
	//! Dictionary for custom HTTP request headers
	NSMutableDictionary* m_RequestHeaders;
	
	//! Set to YES when the request header dictionary has been populated, used to prevent this happening more than once
	BOOL m_HaveBuiltRequestHeaders;
	
	//! Will be populated with HTTP response headers from the server
	NSDictionary* m_ResponseHeaders;
	
	//! Can be used to manually insert cookie headers to a request, but it is more likely that sessionCookies will do this for you
	NSMutableArray* m_RequestCookies;
		
	//! If useCookiePersistence is true, network requests will present valid cookies from previous requests
	BOOL m_UseCookiePersistence;
	
	//! If useKeychainPersistence is true, network requests will attempt to read credentials from the keychain, and will save them in the keychain when they are successfully presented
	BOOL m_UseKeychainPersistence;
	
	//! If useSessionPersistence is true, network requests will save credentials and reuse for the duration of the session (until clearSession is called)
	BOOL m_UseSessionPersistence;
	
	//! If allowCompressedResponse is true, requests will inform the server they can accept compressed data, and will automatically decompress gzipped responses. Default is true.
	BOOL m_AllowCompressedResponse;
	
	/**
     * If shouldCompressRequestBody is true, the request body will be gzipped. Default is false.
	 * You will probably need to enable this feature on your webserver to make this work. Tested with apache only.
     */
	BOOL m_ShouldCompressRequestBody;
	
	/**
     * When downloadDestinationPath is set, the result of this request will be downloaded to the file at this location
	 * If downloadDestinationPath is not set, download data will be stored in memory
     */
	NSString* m_DownloadDestinationPath;
	
	//! The location that files will be downloaded to. Once a download is complete, files will be decompressed (if necessary) and moved to downloadDestinationPath
	NSString* m_TemporaryFileDownloadPath;
			
    //! external "finished" indicator, subject of KVO notifications; updates after 'complete'
    BOOL m_Finished;
    
    //! True if our 'cancel' selector has been called
    BOOL m_Cancelled;
    
	/**
     * If an error occurs, error will contain an NSError
	 * If error code is = ConnectionFailureErrorType (1, Connection failure occurred) - inspect [[error userInfo] objectForKey:NSUnderlyingErrorKey] 
     * for more information	
     */
    NSError* m_Error;
	
	//! Username used for authentication
	NSString* m_Username;
   	//! Password used for authentication
	NSString* m_Password;
	
	//! Domain used for NTLM authentication
	NSString* m_Domain;
	
	//! Username used for proxy authentication
	NSString* m_ProxyUsername;
	//! Password used for proxy authentication
    NSString* m_ProxyPassword;
	
	//! Domain used for NTLM proxy authentication
	NSString* m_ProxyDomain;
	
	//! Delegate for displaying upload progress (usually an NSProgressIndicator, but you can supply a different object and handle this yourself)
	id <SDMProgressDelegate> m_UploadProgressDelegate;
	
	//! Delegate for displaying download progress (usually an NSProgressIndicator, but you can supply a different object and handle this yourself)
	id <SDMProgressDelegate> m_DownloadProgressDelegate;
	
	//! Whether we've seen the headers of the response yet
    BOOL m_HaveExaminedHeaders;
	
	//! Data we receive will be stored here. Data may be compressed unless allowCompressedResponse is false - you should use [request responseData] instead in most cases
	NSMutableData* m_RawResponseData;
	
	//! Used for sending requests and receiving responses
    CFHTTPMessageRef m_Request;
	
	//! Used for authentication
    CFHTTPAuthenticationRef m_RequestAuthentication; 
		
	//! Authentication scheme (Basic, Digest, NTLM)
	NSString* m_AuthenticationScheme;
		
	//! Used for proxy authentication
    CFHTTPAuthenticationRef m_ProxyAuthentication;
    //! proxy credentials 
	NSDictionary* m_ProxyCredentials;
	    
	//! Indicates whether a credentials dialog should be presented for authentication
    BOOL m_ShouldPresentAuthenticationDialog;
    
	//! Indicates whether a credentials dialog should be presented for proxy authentication
    BOOL m_ShouldPresentProxyAuthenticationDialog;
    
	//! Authentication scheme for the proxy (Basic, Digest, NTLM)
	NSString* m_ProxyAuthenticationScheme;	
				
	//! Size of the POST payload
	unsigned long long m_PostLength;	
	
	//! Called on the delegate (if implemented) when the request starts. Default is requestStarted:
	SEL m_DidStartSelector;
	
	//! Called on the delegate (if implemented) when the request receives response headers. Default is requestDidReceiveResponseHeaders:
	SEL m_DidReceiveResponseHeadersSelector;

	//! Called on the delegate (if implemented) when the request completes successfully. Default is requestFinished:
	SEL m_DidFinishSelector;
	
	//! Called on the delegate (if implemented) when the request fails. Default is requestFailed:
	SEL m_DidFailSelector;
	
	/**
     * Called on the delegate (if implemented) when the request receives data. Default is request:didReceiveData:
	 * If you set this and implement the method in your delegate, you must handle the data yourself - HTTPRequest will not populate 
     * responseData or write the data to downloadDestinationPath
     */
	SEL m_DidReceiveDataSelector;
	
    ////Auth Challenge
    //! Called on the delegate (if implemented) when the request fails. Default is didReceiveAuthenticationChallenge:response:
    SEL m_DidReceiveAuthChallengeSelector;
	
	//! Number of seconds to wait before timing out - default is DEFAULT_CONNECTION_TIMEOUT_SECONDS
	NSTimeInterval m_TimeOutSeconds;
	
	//! Will be YES when a HEAD request will handle the content-length before this request starts
	BOOL m_ShouldResetUploadProgress;
	BOOL m_ShouldResetDownloadProgress;
	
	//! Used by HEAD requests when showAccurateProgress is YES to preset the content-length for this request
	SDMHttpRequest* m_MainRequest;
	
	/**
     * When NO, this request will only update the progress indicator when it completes
	 * When YES, this request will update the progress indicator according to how much data it has received so far
	 * The default for requests is YES
     */
	BOOL m_ShowAccurateProgress;
		
	//! Prevents the body of the post being built more than once (largely for subclasses)
	BOOL m_HaveBuiltPostBody;
		
	//! Text encoding for responses that do not send a Content-Type with a charset value. Defaults to NSUTF8StringEncoding
	NSStringEncoding m_DefaultResponseEncoding;
		
	//! Tells HTTPRequest not to delete partial downloads, and allows it to use an existing file to resume a download. Defaults to NO.
	BOOL m_AllowResumeForFileDownloads;
	
	//! Custom user information associated with the request
	NSDictionary* m_UserInfo;
	
	//! Use HTTP 1.0 rather than 1.1 (defaults to false)
	BOOL m_UseHTTPVersionOne;
	
	//! When YES, requests will automatically redirect when they get a HTTP 30x header (defaults to YES)
	BOOL m_ShouldRedirect;
		
	//! When NO, requests will not check the secure certificate is valid (use for self-signed certificates during development, DO NOT USE IN PRODUCTION) Default is YES
	BOOL m_ValidatesSecureCertificate;
    
    //! If not nil and the URL scheme is https, CFNetwork configured to supply a client certificate
    SecIdentityRef m_ClientCertificateIdentity;
	NSArray* m_ClientCertificates;
	
	//! Details on the proxy to use - you can set these yourself, but it is probably best to let HTTPRequest detect the system proxy settings
	NSString* m_ProxyHost;
	int m_ProxyPort;
	
	/**
     * HTTPRequest will assume kCFProxyTypeHTTP if the proxy type could not be automatically determined
	 * Set to kCFProxyTypeSOCKS if you are manually configuring a SOCKS proxy
     */
	NSString* m_ProxyType;

	//! URL for a PAC (Proxy Auto Configuration) file. If you want to set this yourself, it is probably best if you use a local file
	NSURL* m_PACurl;
	
	//! See AuthenticationState values above. 0 == default == No authentication needed yet
	AuthenticationState m_AuthenticationNeeded;
	
	/**
     * When YES, HTTPRequests will present credentials from the session store for requests to the same server before being asked for them
	 * This avoids an extra round trip for requests after authentication has succeeded, which is efficient for authenticated requests with large bodies, 
     * or on slower connections
	 * Set to NO to only present credentials when explicitly asked for them
	 * This only affects credentials stored in the session cache when useSessionPersistence is YES. Credentials from the keychain are never presented unless the server asks for them
	 * Default is YES
     */
	BOOL m_ShouldPresentCredentialsBeforeChallenge;
			
	/**
     * Set to allow a request to automatically retry itself on timeout
	 * Default is zero - timeout will stop the request
     */
	int m_RetryCountOnTimeout;
	
	/** 
     * When YES, requests will keep the connection to the server alive for a while to allow subsequent requests to re-use it for a substantial speed-boost
	 * Persistent connections will not be used if the server explicitly closes the connection
	 * Default is YES
	 */
	BOOL m_ShouldAttemptPersistentConnection;

	/** 
     * Number of seconds to keep an inactive persistent connection open on the client side
	 * Default is 60
	 * If we get a keep-alive header, this value is replaced with how long the server told us to keep the connection around
	 * A future date is created from this and used for expiring the connection, this is stored in connectionInfo's expires value
	 */
	NSTimeInterval m_PersistentConnectionTimeoutSeconds;
			
	/**
	 * When set to YES, 301 and 302 automatic redirects will use the original method and and body, according to the HTTP 1.1 standard
	 * Default is NO (to follow the behaviour of most browsers)
	 */
	BOOL m_ShouldUseRFC2616RedirectBehaviour;
		
	/**
	 * An ID that uniquely identifies this request - primarily used for debugging persistent connections
	 */
	NSNumber* m_RequestID;
		
	/**
	 * The download cache that will be used for this request (use [HTTPRequest setDefaultCache:cache] to configure a default cache
	 */
	id <SDMCacheDelegate> m_DownloadCache;
	
	/**
	 * The cache policy that will be used for this request - See CacheDelegate.h for possible values
	 */
	CachePolicy m_CachePolicy;
	
	/**
	 * The cache storage policy that will be used for this request - See CacheDelegate.h for possible values
	 */
	CacheStoragePolicy m_CacheStoragePolicy;
	
	/**
	 * Will be true when the response was pulled from the cache rather than downloaded
	 */
	BOOL m_DidUseCachedResponse;

	/**
	 * Set secondsToCache to use a custom time interval for expiring the response when it is stored in a cache
	 */
	NSTimeInterval m_SecondsToCache;
	
#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
	/**
	 * Flag controlling whether http requests should run in the background (defaults to true)
	 * @remark available since iOS4.0 and above
	 */	
	BOOL m_ShouldContinueInBackground;
	/**
	 * Background task ID used when the request executes in the background
	 */
	UIBackgroundTaskIdentifier m_BackgroundTask;
#endif
	
	NSTimer* m_StatusTimer; ///< timer used to monitor request status changes
	
	// !!! switch this on only for special builds meant for internal performance testing
#if ENABLE_PERFORMANCE_MEASUREMENTS
	//! dictionary holding performance timers assigned to a given request 
	NSMutableDictionary* m_RequestTimerDict;
#endif
	
	/**
	 * SAP Tracing and Business Transaction XML related flag; NO by default
	 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality
	 * data is gathered to compose the Business Transaction XML, which can be uploaded via E2ETraceController sendXML API
	 * @see E2ETraceController	 
	 */
	BOOL m_isTracingEnabled;
	
	//! dictionary holding E2ETraceRequests assigned to a given request 
	NSMutableDictionary* m_RequestE2ETraceReqDict;

	//! dictionary holding E2ETraceSteps assigned to a given request 
	NSMutableDictionary* m_RequestE2ETraceStepDict;

}

#pragma mark -
#pragma mark Initialization and deallocation

/**
 * Should be an HTTP or HTTPS url, may include username and password if appropriate
 */
- (id)initWithURL:(NSURL *)newURL;

//! Convenience constructor with url
+ (id)requestWithURL:(NSURL *)newURL;
//! Convenience constructor with url and cache
+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <SDMCacheDelegate>)cache;
//! Convenience constructor with url, cache and cache policy
+ (id)requestWithURL:(NSURL *)newURL usingCache:(id <SDMCacheDelegate>)cache andCachePolicy:(CachePolicy)policy;

/**
 * Sets the maximum number of SDMHTTPRequest threads which can run at once
 * @throws SDMConnectivityException if max allowed parallel thread is exceeded
 */
+ (void) setMaxConcurrentHTTPRequestCount:(const unsigned char) cnt;
/**
 * Returns the maximum number of SDMHTTPRequest threads which can be executed in parallel
 */
+ (NSInteger) getMaxConcurrentHTTPRequestCount;

#pragma mark -
#pragma mark Request Setup

/**
 * Adds a custom header to the request
 * @see buildRequestHeaders
 */
- (void)addRequestHeader:(NSString *)header value:(NSString *)value;

/**
 * Called during buildRequestHeaders and after a redirect to create a cookie header from request cookies and the global store
 */
- (void)applyCookieHeader;

/**
 * Populates the request headers dictionary. Called before a request is started, or by a HEAD request that needs to borrow them
 */
- (void)buildRequestHeaders;

/*
 * Used to apply authorization header to a request before it is sent (when shouldPresentCredentialsBeforeChallenge is YES)
 */
- (void)applyAuthorizationHeader;

/**
 * Adds data to the post body. Will append to postBody when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true
 */
- (void)appendPostData:(NSData *)data;
/**
 * Adds data to the post body from a file. Will append to postBody when shouldStreamPostDataFromDisk is false, or write to postBodyWriteStream when true
 */
- (void)appendPostDataFromFile:(NSString *)file;

/**
 * Creates the post body
 */
- (void)buildPostBody;

/**
 * Add etag header
 */
- (void)setEtag:(NSString *)etag withMatchType:(EtagMatchType) matchType;

/**
 * Enable XSRF support. It is enabled by default.
 */
+ (void)enableXCSRF:(BOOL) enable;

#pragma mark -
#pragma mark Request Payload
/**
 * Returns the contents of the result as an NSString (not appropriate for binary data - used responseData instead)
 * @see responseData
 */
- (NSString *)responseString;

/**
 * Response data, automatically uncompressed where appropriate
 * see responseString
 */
- (NSData *)responseData;

/**
 * Returns true if the response was gzip compressed
 */
- (BOOL)isResponseCompressed;

#pragma mark -
#pragma mark Request execution

/**
 * Runs a request synchronously, and returns control when the request completes or fails
 */
- (void)startSynchronous;

/**
 * Runs request in the background
 * The client should register callback selector in order to get notified about various events (failure, completion, etc.)
 */
- (void)startAsynchronous;

#pragma mark -
#pragma mark HEAD request

/**
 * Used by NetworkQueue to create a HEAD request appropriate for this request with the same headers (though you can use it yourself)
 */
- (SDMHttpRequest *)HEADRequest;

#pragma mark -
#pragma mark Upload / Download progress

/**
 * Updates the progress delegates
 * @remark Used by SDMNetworkQueue, clients should not invoke them directly
 */
- (void)updateProgressIndicators;

/**
 * Updates upload progress (notifies the queue and/or uploadProgressDelegate of this request)
 */
- (void)updateUploadProgress;

/**
 * Updates download progress (notifies the queue and/or downloadProgressDelegate of this request)
 */
- (void)updateDownloadProgress;

/**
 * Called when authorization is needed, as we only find out we don't have permission to something when the upload is complete
 */
- (void)removeUploadProgressSoFar;

/**
 * Called when we get a content-length header and shouldResetDownloadProgress is true
 */
- (void)incrementDownloadSizeBy:(long long)length;

/**
 * Called when a request starts and shouldResetUploadProgress is true
 * Also called (with a negative length) to remove the size of the underlying buffer used for uploading
 */
- (void)incrementUploadSizeBy:(long long)length;

/**
 * Helper method for interacting with progress indicators to abstract the details of different APIS (NSProgressIndicator and UIProgressView)
 */
+ (void)updateProgressIndicator:(id *)indicator withProgress:(unsigned long long)progress ofTotal:(unsigned long long)total;

/**
 * Helper method used for performing invocations on the main thread (used for progress)
 */
+ (void)performSelector:(SEL)selector onTarget:(id *)target withObject:(id)object amount:(void *)amount;


#pragma mark -
#pragma mark Http Authentication

/**
 * Wakes up (unlocks) the request thread so it can resume the request
 * @remark Should be called by delegates when they have populated the authentication information after an authentication challenge
 */
- (void)retryUsingSuppliedCredentials;

//! Should be called by delegates when they wish to cancel authentication and stop
- (void)cancelAuthentication;
/**
 * Constructs a basic authentication header from the username and password supplied, and adds it to the request headers
 * Used when shouldPresentCredentialsBeforeChallenge is YES
 */
- (void)addBasicAuthenticationHeaderWithUsername:(NSString *)theUsername andPassword:(NSString *)thePassword;

#pragma mark -
#pragma mark CFnetwork Event Handlers
/**
 * Handles network events as they occur
 * @remark Called from ReadStreamClientCallBack when one of the events requested in NETWORK_EVENTS occurs
 */
- (void)handleNetworkEvent:(CFStreamEventType)type;

#pragma mark -
#pragma mark Request Failure Management

/**
 * Called when a request fails, and lets the delegate know via didFailSelector
 */
- (void)failWithError:(NSError *)theError;


#pragma mark -
#pragma mark Client Certificate Handling
//! Sets the identity reference (X.509 certificate + private key) for this request; used for secure connections
- (void)setClientCertificateIdentity:(SecIdentityRef)anIdentity;


#pragma mark 
#pragma mark Keychain Storage

//! Saves credentials for this request to the keychain
- (void)saveCredentialsToKeychain:(NSDictionary *)newCredentials;

//! Saves host credentials to the keychain
+ (void)saveCredentials:(NSURLCredential *)credentials forHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;
//! Saves proxy credentials to the keychain
+ (void)saveCredentials:(NSURLCredential *)credentials forProxy:(NSString *)host port:(int)port realm:(NSString *)realm;

//! Returns host credentials from the keychain
+ (NSURLCredential *)savedCredentialsForHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;
//! Returns proxy credentials from the keychain
+ (NSURLCredential *)savedCredentialsForProxy:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;

//! Deletes host credentials from the keychain
+ (void)removeCredentialsForHost:(NSString *)host port:(int)port protocol:(NSString *)protocol realm:(NSString *)realm;
//! Deletes proxy credentials from the keychain
+ (void)removeCredentialsForProxy:(NSString *)host port:(int)port realm:(NSString *)realm;

#pragma mark -
#pragma mark Session Management

// Dump all session data (authentication and cookies)
+ (void)clearSession;

#pragma mark -
#pragma mark Reachability

//! Returns YES when an iPhone OS device is connected via WWAN, false when connected via WIFI or not connected
+ (BOOL)isNetworkReachableViaWWAN;

#pragma mark -
#pragma mark Concurrent Request Queue

//! Returns the shared queue
+ (NSOperationQueue *)sharedQueue;

#pragma mark -
#pragma mark Cache Management
/**
 * Configures a default download cache which applies for all requests
 * @see SDMDownloadCache
 */
+ (void)setDefaultCache:(id <SDMCacheDelegate>)cache;
/**
 * Returns the default download cache or nil if none set at class level
 */
+ (id <SDMCacheDelegate>)defaultCache;

#pragma mark -
#pragma mark Network Activity
/**
 * Indicates whether there are running requests
 * @return NO, if no requests are currently executing
 */
+ (BOOL)isNetworkInUse;
/**
 * Controls whether the request should take over updating the network activity indicator
 * @remark enabled by default
 */
+ (void)setShouldUpdateNetworkActivityIndicator:(BOOL)shouldUpdate;

//! Shows the network activity spinner
+ (void)showNetworkActivityIndicator;

//! Hides the network activity spinner
+ (void)hideNetworkActivityIndicator;

#pragma mark -
#pragma mark Bandwidth Measurement / Throttling
/**
 * The maximum number of bytes ALL requests can send / receive in a second
 * This is a rough figure. The actual amount used will be slightly more, this does not include HTTP headers
 */
+ (unsigned long)maxBandwidthPerSecond;
//! Sets the maximum number of bytes ALL requests can send / receive in a second
+ (void)setMaxBandwidthPerSecond:(unsigned long)bytes;

//! Returns a rough average (for the last 5 seconds) of how much bandwidth is being used, in bytes
+ (unsigned long)averageBandwidthUsedPerSecond;
/**
 * Perform bandwidth throttling
 */
- (void)performThrottling;

//! Returns YES is bandwidth throttling is currently in use
+ (BOOL)isBandwidthThrottled;

//! Used internally to record bandwidth use, and by InputStreams when uploading. It's probably best if you don't mess with this.
+ (void)incrementBandwidthUsedInLastSecond:(unsigned long)bytes;

/**
 * SDMHTTPRequest can automatically turn throttling on and off as the connection type changes between WWAN and WiFi
 * Set to YES to automatically turn on throttling when WWAN is connected, and automatically turn it off when it isn't
 */
+ (void)setShouldThrottleBandwidthForWWAN:(BOOL)throttle;

//! Turns on throttling automatically when WWAN is connected using a custom limit, and turns it off automatically when it isn't
+ (void)throttleBandwidthForWWANUsingLimit:(unsigned long)limit;

//! Returns the maximum amount of data we can read as part of the current measurement period, and sleeps this thread if our allowance is used up
+ (unsigned long)maxUploadReadLength;

#pragma mark
#pragma mark Mime-type Detection

// Return the mime type for a file
+ (NSString *)mimeTypeForFileAtPath:(NSString *)path;

#pragma mark -
#pragma mark Secure File Storage 
/**
 * Controls whether the download cache should store files using protection
 * @remark Enabled by default, applies to all instances; only available for builds targeting iOS 4.0 or above
 */
+(void) setProtectionEnabled:(BOOL)flag_in;

/**
 * Returns a attributes dictionary used for encrypted file storage or nil is file protection has been explicitely disabled
 * @remark File protection is enabled by default for builds targeting iOS4.0+; change using via SDMHttpRequest +setProtectionEnabled
 * @see setProtectionEnabled:
 */
+(NSDictionary*) fileProtectionAttributes;

/**
 * Returns a mask which determines whether the data should be stored in encrypted form
 * @remark Data will be stored in encrypted form by by default
 */
+(const NSDataWritingOptions) dataWritingOptions;

#pragma mark -
#pragma mark SAP Tracing and Business Transaction XML support
/**
 * Switches traceability status, the default is NO
 * @discussion If tracing is enabled, "SAP-PASSPORT" and "X-CorrelationID" headers are set and filled with values to enable SAP Passport functionality
 * data is gathered to compose the Business Transaction XML, which can be uploaded via E2ETraceController sendXML API
 * @see E2ETraceController
 */
- (void) enableTracing:(BOOL)value_in;

/**
 * Returns tracing status (default is NO)
 * @see setTracingEnabled:
 */
- (BOOL) isTracingEnabled;
/**
 * Posts the SAP E2E Trace XML to the given url
 */
-(void) sendE2ETraceXML:(NSURL *)toBaseURL;

#pragma mark -
#pragma mark Utility Methods

//! Base64 encodes the provided NSData*
+ (NSString*) base64forData:(NSData*)theData;
//! Decodes a base64 encoded string
+ (NSString*) decodeBase64:(NSString*)string_in;

//! Returns a date from a string in RFC1123 format
+ (NSDate *)dateFromRFC1123String:(NSString *)string;

#pragma mark -
#pragma mark Assignable Selectors
/**
 * Clients can chose to register their custom selectors to be invoked
 * @remark Consider implementing the SDMHttpRequestDelegate as an alternative to this approach
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidStartSelector:@selector(serviceDocFetchStarted:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didStartSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * @remark Consider implementing the SDMHttpRequestDelegate as an alternative to this approach
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidFinishSelector:@selector(serviceDocFetchComplete:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didFinishSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * @remark Consider implementing the SDMHttpRequestDelegate as an alternative to this approach
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidFailSelector:@selector(serviceDocFetchFailed:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didFailSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * Default delegate method invoked when incoming data is available.
 * @remark Implement this delegate only if you want to manually process all incoming data yourself (usually not required). This means that responseData / responseString are ignored
 * 
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidReceiveDataSelector:@selector(dataArrived:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didReceiveDataSelector;
/**
 * Clients can chose to register their custom selectors to be invoked
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidReceiveResponseHeadersSelector:@selector(headersReceived:)];
 * ...
 * </code>
 * </pre>
 */
@property (assign) SEL didReceiveResponseHeadersSelector;

#pragma  mark Auth Challenge Selector
/**
 * Clients can chose to register their custom selectors to be invoked
 * <pre>
 * Usage (client side!)
 * <code>
 * // register the client as delegate for this request
 * [m_AsynchRequest setDelegate:self];
 * [m_AsynchRequest setDidReceiveAuthChallengeSelector:@selector(authenticationNeededForRequest:)];
 * ...
 * </code>
 * </pre>
 */
@property(assign) SEL didReceiveAuthChallengeSelector;

#pragma mark -
#pragma mark Accessors

// !!! private properties
@property (retain, readonly) NSString* authenticationRealm;
@property (retain, readonly) NSString* proxyAuthenticationRealm;
@property (assign, readonly) BOOL complete;
@property (retain, readonly) NSArray* responseCookies;
@property (assign) int responseStatusCode; ///< HTTP status code, i.e. 200 = OK, 404 = Not found etc
@property (retain, readonly) NSString* responseStatusMessage;
@property (assign, readonly) unsigned long long contentLength;
@property (assign, readonly) unsigned long long partialDownloadSize;
@property (assign, readonly) unsigned long long totalBytesRead;
@property (assign, readonly) unsigned long long totalBytesSent;
@property (assign, readonly) AuthenticationState authenticationNeeded;
@property (assign, readonly) int authenticationRetryCount;
@property (assign, readonly) int proxyAuthenticationRetryCount;
@property (assign, readonly) BOOL inProgress;
@property (assign, readonly) int retryCount;
@property (assign, readonly) BOOL connectionCanBeReused;
@property (retain, readonly) NSNumber* requestID;
@property (assign, readonly) BOOL didUseCachedResponse;
// private properties end


@property (retain) NSString* username;
@property (retain) NSString* password;
@property (retain) NSString* domain;
@property (retain) NSString* proxyUsername;
@property (retain) NSString* proxyPassword;
@property (retain) NSString* proxyDomain;
@property (retain) NSString* proxyHost;
@property (assign) int proxyPort;
@property (retain) NSString* proxyType;
@property (retain) NSURL* url;
@property (retain) NSURL* originalURL;
@property (assign, nonatomic) id delegate;
@property (retain, nonatomic) id queue;
@property (assign, nonatomic) id uploadProgressDelegate;
@property (assign, nonatomic) id downloadProgressDelegate;
@property (assign) BOOL useKeychainPersistence;
@property (assign) BOOL useSessionPersistence;
@property (retain) NSString* downloadDestinationPath;
@property (retain) NSString* temporaryFileDownloadPath;

@property (retain) NSError* error;
@property (retain) NSDictionary* responseHeaders;
@property (retain) NSMutableDictionary* requestHeaders;
@property (retain) NSMutableArray* requestCookies;
@property (assign) BOOL useCookiePersistence;
@property (retain) NSDictionary* requestCredentials;
@property (retain) NSDictionary* proxyCredentials;
@property (retain) NSMutableData* rawResponseData;
@property (assign) NSTimeInterval timeOutSeconds;
@property (retain) NSString* requestMethod;
@property (retain) NSMutableData* postBody;
@property (assign) unsigned long long postLength;
@property (assign) BOOL shouldResetDownloadProgress;
@property (assign) BOOL shouldResetUploadProgress;
@property (assign) id <SDMRequesting> mainRequest;
@property (assign) BOOL showAccurateProgress;
@property (assign) NSStringEncoding defaultResponseEncoding;
@property (assign, readonly) NSStringEncoding responseEncoding;
@property (assign) BOOL allowCompressedResponse;
@property (assign) BOOL allowResumeForFileDownloads;
@property (retain) NSDictionary *userInfo;
@property (retain) NSString *postBodyFilePath;
@property (assign) BOOL shouldStreamPostDataFromDisk;
@property (assign) BOOL didCreateTemporaryPostDataFile;
@property (assign) BOOL useHTTPVersionOne;
@property (assign) BOOL shouldRedirect;
@property (assign) BOOL validatesSecureCertificate;
@property (assign) BOOL shouldCompressRequestBody;
@property (retain) NSURL* PACurl;
@property (retain) NSString* authenticationScheme;
@property (retain) NSString* proxyAuthenticationScheme;
@property (assign) BOOL shouldPresentAuthenticationDialog;
@property (assign) BOOL shouldPresentProxyAuthenticationDialog;
@property (assign) BOOL shouldPresentCredentialsBeforeChallenge;
@property (assign) BOOL haveBuiltRequestHeaders;
@property (assign, nonatomic) BOOL haveBuiltPostBody;
@property (assign) int retryCountOnTimeout;
@property (assign) BOOL shouldAttemptPersistentConnection;
@property (assign) NSTimeInterval persistentConnectionTimeoutSeconds;
@property (assign) BOOL shouldUseRFC2616RedirectBehaviour;
@property (assign) BOOL shouldAutosetLanguage; ///< controls whether the preferred language has to be passed along the request's header; defaults to YES

/**
 * Configures a default download cache
 * The download cache that will be used for this request
 * 
 * <pre>
 * Sample usage
 * <code> 
 * // assign a download cache instance to the request
 * <b>[m_Request setDownloadCache:[SDMDownloadCache instance]];</b>
 * // apply cache settings as required (see SDMDownloadCache)
 * [[SDMDownloadCache instance] setDefaultCachePolicy:OnlyLoadIfNotCachedCachePolicy];
 *
 * [m_Request setCacheStoragePolicy:CachePermanentlyCacheStoragePolicy];
 * </code>
 * </pre>
 * @see +setDefaultCache, SDMDownloadCache
 */
@property (assign) id <SDMCacheDelegate> downloadCache;
@property (assign) CachePolicy cachePolicy;
@property (assign) CacheStoragePolicy cacheStoragePolicy;


/**
 * Sets a validity interval for cached data
 * <pre>
 * Cached data will be considered as expired if the following conditions are met:
 * <ul>
 * <li> The server has set the "Last-Modified" header
 * <li> Cache Policy is set to "ReloadIfDifferentCachePolicy"
 * </ul>
 * </pre>
 * If these conditions are met, and (secondsToCache > Last-Modified), cached data becomes obsolete.
 * @remark Not all servers set the "Last-Modified" header
 */
@property (assign) NSTimeInterval secondsToCache;
@property (retain) NSArray* clientCertificates;

#if TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_4_0
/**
 * Controls background download/uplod behavior (enabled by default) for builds targeting iOS4.0+
 * @remark Will not work for iOS versions below 4.0
 */
@property (assign, nonatomic) BOOL shouldContinueInBackground;
#endif

@end

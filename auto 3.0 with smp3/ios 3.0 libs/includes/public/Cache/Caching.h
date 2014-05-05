//
//  Caching.h
//  Cache
//
//  Created by M, Pramod on 18/06/13.
//  Copyright (c) 2013 M, Pramod. All rights reserved.
//

#import <Foundation/Foundation.h>

@class  ODataEntry;

typedef enum {
    ServiceDocumentType = 0,
    MetaDocumentType = 1
} DocType;


typedef enum {
    CreatedState = 0,
    UpdatedState = 1,
    DeletedState = 2
} CacheState;

/**
 * Consists of methods to Cache Parsed OData entries. Cache works against the new Parser API <b>(OData*)</b> only. Supports handling delta links and tombstones.
 */

@protocol Caching <NSObject>

/**
 * Property which is used to specify whether the cache is implicitly persistable or not.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  [cacheLocal setIsPersistable:YES];
 *
 *  if ([cacheLocal isPersistable]) 
 *  {
 *      // Do Stuff;
 *  }
 * </pre>
 */
@property(nonatomic, assign) BOOL isPersistable;

/**
 * This is the method that the application will first call to get all the cache metadata initialized.
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns a boolean to indicate the outcome of the operation.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  if (![cacheLocal initializeCacheWithError:&error])
 *  {
 *      NSLog(@"Initialize Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (BOOL)initializeCacheWithError:(NSError**)error;

/**
 * Returns an array of <b>ODataEntry*</b> Objects stored for the given URL key. These are the server versions of the entry only.
 * @param urlKey The URL that was originally used to fetch the entries from the backend and cache it.
 * @param error An uninitialized error object which will be filled in case of error scenarios 
 * @return Returns an array of <b>ODataEntry*</b> objects that were cached.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSArray* cachedEntries = [cacheLocal readEntriesServerForUrlKey:urlKey withError:&error];
 *  if (error)
 *  {
 *      NSLog(@"Read Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (NSArray*)readEntriesServerForUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Returns an array of <b>ODataEntry*</b> Objects stored for the given Entity type and Entry ID. These are the local versions of the entry only.
 * @param entityType The Entity-set to which the entry belongs to. Mostly will be the name of the Collection of the entries. If passed as nil to the method, it will be ignored while querying the cache for entries.
 * @param entryId The Id of the entry which was modified. If passed as nil to the method, it will be ignored while querying the cache for entries.
 * @param error An uninitialized error object which will be filled in case of error scenarios  
 * @return Returns an array of <b>ODataEntry*</b> objects that were cached.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSArray* localEntries = [cacheLocal readEntriesLocalForEntityType:nil forEntryId:nil withError:&error];
 *  if (error) 
 *  {
 *  NSLog(@"Read Local Entry Error: %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (NSArray*)readEntriesLocalForEntityType:(NSString*)entityType forEntryId:(NSString*)entryId withError:(NSError**)error;


/**
 * Merges the passed entries with the current set of Entries (Server version only) in the cache i.e. existing entries will be updated and new entries will be inserted.
 * @param entries The array of <b>ODataEntry*</b> objects which has to merged into the Server version of the cache. 
 * @param urlKey The URL string which was used to get the data from the backend
 * @param error An uninitialized error object which will be filled in case of error scenarios  
 * @return Returns a boolean to indicate the outcome of the operation.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSArray* entries = parseODataEntriesXML(responseData, entitySchema, serviceDoc);
 *  if (![cacheLocal mergeEntries:entries forUrlKey:urlKey withError:&error])
 *  {
 *  NSLog(@"Merge Error: %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (BOOL)mergeEntries:(NSArray*)entries forUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * A new cache entry will be added using this particular method. This method will be mostly called when the application is trying to create entries in the backend via a HTTP POST.
 * @param entry The locally created entry that will be used to fire a POST to the backend.
 * @param error An uninitialized error object which will be filled in case of error scenarios 
 * @return Returns a string that indicates a temporary entry ID assigned to the locally created entry in cache
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* tempEntryId = [cacheLocal addEntry:entry withError:&error];
 *  if (error) {
 *      NSLog(@"Add Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (NSString*)addEntry:(ODataEntry*)entry withError:(NSError**)error;

/**
 * This method call is associated with a HTTP PUT, i.e. a modification on the existing resource of a collection. This will lead to the creation of an entry in the ODataEntryLocal cache and marked as ‘Updated’. 
 * @param entry The locally modified entry that will be used to fire a PUT to the backend.
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns a boolean to indicate the outcome of the operation
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  ODataEntry* updateEntry = updateEntryWithChangedValues();
 *  if ([cacheLocal updateEntry:updateEntry withError:&error]) {
 *      NSLog(@"Update Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)updateEntry:(ODataEntry*)entry withError:(NSError**)error;

/**
 * An entry from Cache can be marked for delete by calling the method. This will be associated with a HTTP DELETE called to delete a resource for a collection in the backend. 
 * @param entryId The ID of the entry that is to be deleted via HTTP DELETE
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns a boolean to indicate the outcome of the operation
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* deletedEntryId = [deletedEntry getEntryID[;
 *  if ([cacheLocal deleteEntryForEntryId:deletedEntryId withError:&error]) {
 *      NSLog(@"Delete Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)deleteEntryForEntryId:(NSString*)entryId withError:(NSError**)error;

/**
 * Clears the cache for the urlKey passed from all the caches, including the delta token and document cache.
 * @param urlKey The URL string against which the entries were cached.
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns a boolean to indicate the outcome of the operation
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  if ([cacheLocal clearCacheForUrlKey:urlKey withError:&error]) {
 *      NSLog(@"Clear Cache Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)clearCacheForUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * This will clear the local entry present in the local Cache based on the entry ID passed.
 * @param entryID The ID for which the entry has to be removed from the local cache.
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns a boolean to indicate the outcome of the operation
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* deleteEntryId = [deleteEntry getEntryID];
 *  if ([cacheLocal clearLocalEntryForEntryId:deleteEntryId withError:&error]) {
 *      NSLog(@"Clear Local Entry Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)clearLocalEntryForEntryId:(NSString *)entryId withError:(NSError**)error;

/**
 * This will return the delta token/delta link for the URL key passed.
 * @param urlKey The URL string against which the entries were cached.
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns the delta token/delta link as a string.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  NSString* deltaLink = [cacheLocal getDeltaLinkForUrlKey:urlKey withError:&error]
 *  if (error) {
 *      NSLog(@"Delta Token Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */

- (NSString *)getDeltaLinkForUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Used to store the service document or the meta data document for further re-use since they for the base on which data parsing can be done.
 * @param document The document object that needs to be cached.
 * @param type The type of the document that needs to be stored. Please refer to the Enum DocType.
 * @param urlKey The URL string that refers to the base URL of the documents.
 * @param error An uninitialized error object which will be filled in case of error scenarios 
 * @return Returns a boolean to indicate the outcome of the operation
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  if ([cacheLocal storeDocument:servDoc forDocType:ServiceDocumentType forUrlKey:urlKey withError:&error]) {
 *      NSLog(@"Store Document Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (BOOL)storeDocument:(id)document forDocType:(DocType)type forUrlKey:(NSString*)urlKey withError:(NSError**)error;

/**
 * Used to read the service document or the meta data document for further re-use since they for the base on which data parsing can be done.
 * @param urlKey The URL string that refers to the base URL of the documents. 
 * @param type The type of the document that needs to be stored. Please refer to the Enum DocType.
 * @param error An uninitialized error object which will be filled in case of error scenarios
 * @return Returns the document object that was cached.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  NSError* error = nil;
 *  id document = [cacheLocal readDocumentForUrlKey:urlKey forDocType:ServiceDocumentType withError:&error];
 *  if (error) {
 *      NSLog(@"Read Document Error : %@@", error);
 *      return;
 *  }
 * </pre>
 */
- (id)readDocumentForUrlKey:(NSString*)urlKey forDocType:(DocType)type withError:(NSError**)error;

/**
 * Used to register for notifications in case of change in the cached data when the merge happens.
 * @param delegate The class object that implements the notification listener method
 * @param listener The name of the listener method
 * @param urlKey The URL string against which the application chooses to listen to notifications.
 * @examples
 * <pre>
 *  id<Caching> cacheLocal = [[Cache alloc] init];
 *  [cacheLocal addNotificationDelegate:self withListener:@selector(notifListener:) forUrlKey:urlKey];
 * </pre>
 */
- (void)addNotificationDelegate:(id)delegate withListener:(SEL)listener forUrlKey:(NSString*)urlKey;
@end

//  Cache.h
//  Copyright (c) 2013 SAP. All rights reserved.


#import <Foundation/Foundation.h>
#import "Caching.h"
#import "ODataEntry.h"

@interface Cache : NSObject<Caching>

@property(nonatomic, assign) BOOL isPersistable;

- (BOOL)initializeCacheWithError:(NSError**)error;
- (NSArray*)readEntriesServerForUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (NSArray*)readEntriesLocalForEntityType:(NSString*)entityType forEntryId:(NSString*)entryId withError:(NSError**)error;
- (BOOL)mergeEntries:(NSArray*)entries forUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (NSString*)addEntry:(ODataEntry*)entry withError:(NSError**)error;
- (BOOL)updateEntry:(ODataEntry*)entry withError:(NSError**)error;
- (BOOL)deleteEntryForEntryId:(NSString*)entryId withError:(NSError**)error;
- (BOOL)clearCacheForUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (BOOL)clearLocalEntryForEntryId:(NSString *)entryId withError:(NSError**)error;
- (NSString *)getDeltaLinkForUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (BOOL)storeDocument:(id)document forDocType:(DocType)type forUrlKey:(NSString*)urlKey withError:(NSError**)error;
- (id)readDocumentForUrlKey:(NSString*)urlKey forDocType:(DocType)type withError:(NSError**)error;
- (void)addNotificationDelegate:(id)delegate withListener:(SEL)listener forUrlKey:(NSString*)urlKey;

@end

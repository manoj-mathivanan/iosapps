//
//  QueueManager.h
//  Database
//
//  Created by Chauhan, Kamlendra Singh on 5/21/13.
//  Copyright (c) 2013 Chauhan, Kamlendra Singh. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Request.h"

@interface QueueManager : NSObject

- (id)init;

- (void)shouldPersist:(BOOL)insert request:(Request*)request;

- (NSString*) getUrl;

- (void)setUrl:(NSString*)url;

- (NSArray*)getQueues;

- (NSArray*)readRequestsFromQueue:(NSString*)queueName;

- (void)clearPendingRequestsWithError:(NSError**)error;


@end

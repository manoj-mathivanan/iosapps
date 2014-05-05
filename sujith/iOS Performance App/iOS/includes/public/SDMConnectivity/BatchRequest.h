//
//  BatchRequest.h
//  SDMConnectivity
//
//  Created by Prathap, Sujith on 4/22/13.
//
//

#import <Foundation/Foundation.h>
#import "SDMHttpRequest.h"

@interface BatchRequest : SDMHttpRequest

{
    //Array that represents the requests that make up the current change list.
    NSMutableArray *currentChangeSet;
    
    //Flag to check if there is an existing changeset or not
    BOOL isChangestCreated;
    
    //An array that contains the keys with represent
    //ordering of Retrieve Requests and Changesets.
    NSMutableArray *orderArray;
    
    //A array with keys which are stored in
    //the orderedArray and an array of requests
    //corresponding to each Retrieve Request
    //or Changelist.
    NSMutableArray *requestArray;
    

    
}

@property(nonatomic,retain)NSMutableArray *currentChangeSet;
@property(nonatomic) BOOL isChangestCreated;
@property(nonatomic,retain)NSMutableArray *orderArray;
@property(nonatomic,retain)NSMutableArray *requestArray;

#pragma mark -
#pragma mark Batch Request

/**
 * Initialize the BatchRequest object
 * <pre>
 * Usage
 * <code>
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * </code>
 * </pre>
 */
- (id)initWithURL:(NSString *)request;

/**
 * Add Retrieve requests to BatchRequest
 * <pre>
 * Usage
 * <code>
 * [SDMRequestBuilder setRequestType:HTTPRequestType];
 * [SDMRequestBuilder enableXCSRF:YES];
 * id<SDMRequesting> request = [SDMRequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"TravelagencyCollection"]];
 * [request setRequestMethod:@"GET"];
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * [batch addRetrieveRequestToBatch:request];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </code>
 * </pre>
 */
- (void)addRetrieveRequestToBatch:(id<SDMRequesting>)request;

/**
 * Add Modifying(POST/PUT/DELETE) requests to BatchRequest
 * <pre>
 * Usage
 * <code>
 * [SDMRequestBuilder setRequestType:HTTPRequestType];
 * [SDMRequestBuilder enableXCSRF:YES];
 * id<SDMRequesting> postRequest = [SDMRequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"TravelagencyCollection"]];
 * [postRequest setRequestMethod:@"POST"];
 * [postRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
 * [postRequest addRequestHeader:@"Content-Length" value:@"1005"];
 * NSMutableData *data = [NSMutableData dataWithData:[postBody1 dataUsingEncoding:NSUTF8StringEncoding]];
 * [postRequest setPostBody:data];
 * NSString *postBody =@"set_the_post_body";
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * [batch addRequestToChangeset:postRequest];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </code>
 * </pre>
 */
- (void)addRequestToChangeset:(id<SDMRequesting>)request;

/**
 * Close a changeSet and add requests to new changeSet
 * <pre>
 * Usage
 * <code>
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * [batch addRequestToChangeset:postRequest1];
 * [batch closeExistingChangeSet];
 * [batch addRequestToChangeset:postRequest2];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </code>
 * </pre>
 */
- (void)closeExistingChangeSet;

@end

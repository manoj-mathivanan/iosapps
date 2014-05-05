//
//  BatchRequest.h
//  Connectivity
//
//  Created by Prathap, Sujith on 4/22/13.
//
//

#import <Foundation/Foundation.h>
#import "Request.h"

/**
 * Consists of methods related to a Batch request. Batch request allows users to combine multiple requests into a single request for processing. Batch request should be used when more than one request is to be retrieved or modifying requests are to be combined.
 */

@interface BatchRequest : Request<NSCoding>

{
    //Array that represents the requests that make up the current change list.
    NSMutableArray *currentChangeSet;
    
    //Flag to check if there is an existing changeset.
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
 * Initialize the BatchRequest object.
 * @param urlString Object of NSString class.
 * @return Returns the instance of the BatchRequest class.
 * @examples
 * <pre>
 *  BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * </pre>
 */
- (id)initWithURL:(NSString *)urlString;

/**
 * Add a Retrieve request to BatchRequest class.
 * @param request Object of Request class.
 * @examples
 * <pre>
 * [RequestBuilder enableXCSRF:YES];
 * id<Requesting> request = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"TravelagencyCollection"]];
 * [request setRequestMethod:@"GET"];
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch addRetrieveRequestToBatch:request withError:&error];
 * if(!error){
 * [batch startSynchronous];
 * }
 * </pre>
 */
- (void)addRetrieveRequestToBatch:(id<Requesting>)request withError:(NSError**)error;

/**
 * Add a Modifying request such as POST/PUT/DELETE to BatchRequest class.
 * @param request Object of Request class.
 * @examples
 * <pre>
 * [RequestBuilder enableXCSRF:YES];
 * id<Requesting> postRequest = [RequestBuilder requestWithURL:[[NSURL alloc] initWithString:@"TravelagencyCollection"]];
 * [postRequest setRequestMethod:@"POST"];
 * [postRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
 * [postRequest addRequestHeader:@"Content-Length" value:@"1005"];
 * [postRequest setPostBody:data];
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * [batch addRequestToChangeset:postRequest];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </pre>
 */
- (void)addRequestToChangeset:(id<Requesting>)request;

/**
 * Close a changeSet and add requests to new changeSet.
 * @param None
 * @examples
 * <pre>
 * BatchRequest *batch = [[BatchRequest alloc] initWithURL:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$batch"];
 * [batch addRequestToChangeset:postRequest1];
 * [batch closeExistingChangeSet];
 * [batch addRequestToChangeset:postRequest2];
 * [batch setUsername:user];
 * [batch setPassword:pass];
 * [batch startSynchronous];
 * </pre>
 */
- (void)closeExistingChangeSet;

@end

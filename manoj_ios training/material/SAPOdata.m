//
//  SAPOdata.m
//  webService
//
//  Created by M, Anil Chopra on 4/19/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "SAPOdata.h"

@implementation SAPOdata

-(void)initialize
{
    //[SDMRequestBuilder enableXCSRF:YES];
    
    NSURL *url = [[NSURL alloc]initWithString:@"http://vmw3815.wdf.sap.corp:50009/sap/opu/odata/IWFND/RMTSAMPLEFLIGHT/CarrierCollection?$format=xml"];
    
    [SDMRequestBuilder setRequestType:HTTPRequestType];
    currentRequest = [SDMRequestBuilder requestWithURL:url usingCache:nil];
    
    
    
   
    currentRequest.username  = @"testusr";
    currentRequest.password  = @"tester";
    
    //set headers
    [currentRequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
//    [currentRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
//    [currentRequest addRequestHeader:@"Accept" value:@"application/xml"];

    
    [currentRequest setDidFailSelector:@selector(oDataFailure:)];
    [currentRequest setDidFinishSelector:@selector(loginSuccessful:)];
	currentRequest.delegate=self;
   [currentRequest setTimeOutSeconds:60];
	[currentRequest startSynchronous];
    
   // NSLog(@"Request %@ finished with error %@",currentRequest.url,currentRequest.error);
    
}


-(void)callService
{
    [self initialize];
}

- (void)oDataFailure:(id<SDMRequesting>)theRequest {
    
	NSLog(@"Request %@ finished with error %@\nresponse %@",theRequest.url,theRequest.error,[theRequest responseString]);

	// Show error message with	[self _errorMessageOfResponse:[theRequest responseString]]
}

- (void)loginSuccessful:(id<SDMRequesting>)theRequest {
	NSLog(@"Svc for Login response %@",theRequest.responseString);
}

@end

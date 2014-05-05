//
//  SAPOdata.h
//  webService
//
//  Created by M, Anil Chopra on 4/19/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import <Foundation/Foundation.h>
// SDM Connectivity
#import "SDMRequesting.h"
#import "SDMRequestBuilder.h"
#import "SDMHttpRequest.h"
// SDM OData parser
#import "SDMParser.h"
#import "SDMParserException.h"
#import "SDMOData.h"


@interface SAPOdata : NSObject<SDMRequesting>

{
    id<SDMRequesting> currentRequest;
}

-(void)callService;
@end

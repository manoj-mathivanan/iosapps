//
//  ViewController.m
//  auto
//
//  Created by i074667 on 6/10/13.
//  Copyright (c) 2013 i074667. All rights reserved.
//

#import "ViewController.h"
#import "SDMParser.h"
#import "SDMODataServiceDocumentParser.h"
#import "SDMODataServiceDocument.h"
#import "SDMODataWorkspace.h"
#import "SDMODataCollection.h"
#import "SDMPerformanceUtil.h"
#import "SMPUserManager.h"
#import "SMPClientConnection.h"

#import "SDMOData.h"
#import "SDMSubscriptionXMLBuilder.h"
#import "SDMRequesting.h"
#import "SDMRequestBuilder.h"

#import "SDMODataEntry.h"
#import "SDMODataPropertyValues.h"

#import "SMPUserManager.h"
#import "SMPAppSettings.h"
#import "SMPClientConnection.h"
#import "SMPClientConnection.h"
#import "SMPUserManager.h"
#import "SMPAppSettings.h"
#import "SDMRequesting.h"
#import "SDMRequestBuilder.h"
#import "SDMODataServiceDocument.h"
#import "SDMODataServiceDocumentParser.h"
#import "SDMODataCollection.h"
#import "SDMParser.h"
#import "SDMODataEntry.h"
#import "SDMODataCollection.h"
#import "SDMODataPropertyValues.h"
#import "SDMOData.h"
#import "SDMODataWorkspace.h"
#import "NSObject+constants.h"



@interface ViewController ()

@end

@implementation ViewController
@synthesize server;
SMPAppSettings *l_appsettingsObj;
SMPClientConnection *l_clientconn;
SMPUserManager *userManager;
NSDate *start;
float req,parse;
NSString *l_response;
NSData *l_responseData;
NSString *putBody;
NSMutableData *data;
UIImage *image;
NSData *postData;
NSFileManager *filemgr;

NSMutableData *imgData;

int i=0,j=0;

-(IBAction)Button:(id)sender
{
    NSError *error1 = nil;
    serverip = server.text;
    [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    l_clientconn = [SMPClientConnection initializeWithAppID:@"ldci2" domain:@"default" secConfiguration:@"ldci2_SC"];
    userManager = [SMPUserManager initializeWithConnection:l_clientconn];    
    [l_clientconn setConnectionProfileWithUrl:serverip];
    NSError *error = nil;
    BOOL registrationflag= [userManager registerUser:@"perfbb" password:@"perfbb" error:&error isSyncFlag:YES];    
    if(registrationflag)
    {
        NSLog(@"registration successful");
        connid= [userManager applicationConnectionID];
    }
    else
    {
        NSLog(@"registration unsuccessful or already registered");
    }
    l_appsettingsObj = [SMPAppSettings initializeWithConnection:l_clientconn userName:@"perfbb" password:@"perfbb"];
    AppEndUrl = [l_appsettingsObj getApplicationEndpointWithError:&error1];
    
    [SDMRequestBuilder enableXCSRF:YES];
    [SDMRequestBuilder setRequestType:HTTPRequestType];

    [mainrequest setUsername:@"perfbb"];
    [mainrequest setPassword:@"perfbb"];
    
    //[mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    //[mainrequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [mainrequest addRequestHeader:@"X-SUP-APPCID" value:connid];
    putBody =[NSString stringWithFormat:@"<?xml version=\"1.0\" encoding=\"utf-8\"?><entry xml:base=\"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/\" xmlns=\"http://www.w3.org/2005/Atom\" xmlns:m=\"http://schemas.microsoft.com/ado/2007/08/dataservices/metadata\" xmlns:d=\"http://schemas.microsoft.com/ado/2007/08/dataservices\"><id>http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('00001403')</id><title type=\"text\">TravelagencyCollection('00001403')</title><updated>2012-07-27T03:32:39Z</updated><category term=\"RMTSAMPLEFLIGHT.Travelagency\" scheme=\"http://schemas.microsoft.com/ado/2007/08/dataservices/scheme\"/><link href=\"TravelagencyCollection('00001403')\" rel=\"edit\" title=\"Travelagency\"/><content type=\"application/xml\"><m:properties><d:agencynum>00001403</d:agencynum><d:NAME>aaaaaaaaaaaaaaaaaaaaaaaaa</d:NAME><d:STREET>zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</d:STREET><d:POSTBOX>aaaaaaaaaa</d:POSTBOX><d:POSTCODE>aaaaaaaaaa</d:POSTCODE><d:CITY>zzzzzzzzzzzzzzzzzzzzzzzzz</d:CITY><d:COUNTRY>DEq</d:COUNTRY><d:REGION>051</d:REGION><d:TELEPHONE>12356789123456789123456789123</d:TELEPHONE><d:URL>http://manoj</d:URL><d:LANGU>D</d:LANGU><d:CURRENCY>EUR</d:CURRENCY><d:mimeType>text/html</d:mimeType></m:properties></content></entry>"];
    data = [NSMutableData dataWithBytes:[putBody cString] length:[putBody length]];
    

}

-(IBAction)Button2:(id)start
{
    filemgr = [NSFileManager defaultManager];
    NSMutableArray *all = [NSMutableArray arrayWithObjects:@"Type			",@"req",@"parser",@"E2E", nil];
    @try {
        for (j=0; j<1; j++) {
            [NSThread sleepForTimeInterval:2.0f];
            NSLog(@"Iteration number: %d",(j+1));
//service document
            
        start = [NSDate date];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:AppEndUrl]];
        [mainrequest startSynchronous];
            if (mainrequest.error) { NSLog(@"%@",([mainrequest responseString])); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        SDMODataServiceDocumentParser *svcdocParser = [[SDMODataServiceDocumentParser alloc] init];
        [svcdocParser parse:l_responseData];
        parse = [start timeIntervalSinceNow] * -1000.0;
        SDMODataServiceDocument *serviceDocument = svcdocParser.serviceDocument;
        NSLog(@"service document success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Service-Document	",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
        /*
//metadata
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/$metadata",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        SDMODataSchema *schema = sdmParseODataSchemaXML(l_responseData, serviceDocument);
        parse = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"metadata success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Metadata          ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
            
//collection 300
        SDMODataCollection *collection = [schema getCollectionByName:@"TravelagencyCollection"];
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/TravelagencyCollection?$format=json&$top=300",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest addRequestHeader:@"Accept-Encoding" value:@"gzip"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        NSArray *entries;
        entries = sdmParseODataEntriesXML(l_responseData , collection.entitySchema ,serviceDocument);
        parse = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"collection 300 success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Collection-300	",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
            
//collection 1000
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/TravelagencyCollection?$format=json&$top=1000",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest addRequestHeader:@"Accept-Encoding" value:@"gzip"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        entries = sdmParseODataEntriesXML(l_responseData , collection.entitySchema ,serviceDocument);
        parse = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"collection 1000 success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Collection-1000	",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
            
//get single data
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/TravelagencyCollection('00001403')",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        NSArray *singleEntry;
        singleEntry = sdmParseODataEntriesXML([mainrequest responseData] , collection.entitySchema ,serviceDocument);
        parse = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"get single record success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Get               ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
            
//update single data
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/TravelagencyCollection('00001403')",AppEndUrl]]];
        [mainrequest setRequestMethod:@"PUT"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
        [mainrequest setPostBody:data];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"update single record success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Update            ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
            
//delete single data
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/TravelagencyCollection('00001403')",AppEndUrl]]];
        [mainrequest setRequestMethod:@"DELETE"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"delete single record success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Delete            ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
        
//add single data
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/TravelagencyCollection",AppEndUrl]]];
        [mainrequest setRequestMethod:@"POST"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
        [mainrequest setPostBody:data];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"add single record success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Add               ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
        */
//upload 100
            postData = [filemgr contentsAtPath:[[NSBundle mainBundle]pathForResource:@"100kb" ofType:@"jpg"]];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/CarrierCollection('LH')/$value",AppEndUrl]]];
        [mainrequest setRequestMethod:@"PUT"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"image/jpeg"];
        [mainrequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
        [mainrequest setPostBody:[NSMutableData dataWithData:postData]];
        start = [NSDate date];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"upload 100kb success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Upload-100		",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];

//download 100
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/CarrierCollection('LH')/$value",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"image/jpeg"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            imgData = [[NSMutableData alloc]initWithData:[mainrequest responseData]]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"download 100kb success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Download-100      ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
   /*
//upload 500
            postData = [filemgr contentsAtPath:[[NSBundle mainBundle]pathForResource:@"500kb" ofType:@"jpg"]];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/CarrierCollection('LH')/$value",AppEndUrl]]];
        [mainrequest setRequestMethod:@"PUT"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"image/jpeg"];
        [mainrequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
        [mainrequest setPostBody:[NSMutableData dataWithData:postData]];
        start = [NSDate date];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"upload 500kb success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Upload-500 		",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
        
//download 500
        start = [NSDate date];
        mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/CarrierCollection('LH')/$value",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"image/jpeg"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            imgData = [[NSMutableData alloc]initWithData:[mainrequest responseData]]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        parse = req;
        NSLog(@"download 500kb success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Download-500      ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];*/
            
            
            for (i=4; i<[all count]; i++) {
                NSMutableArray *row1 = [all objectAtIndex:i];
                NSLog(@"%@  %@      %@      %@", [row1 objectAtIndex:0],[row1 objectAtIndex:1],[row1 objectAtIndex:2],[row1 objectAtIndex:3]);
            }

            
        }

    }
    @catch (NSException *exception) {
        NSLog(@"exception: %@",[exception description]);
    }
    
        
    
}

-(IBAction)Button3:(id)download
{
    start = [NSDate date];
    mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/CarrierCollection('LH')/$value",AppEndUrl]]];
    [mainrequest setRequestMethod:@"GET"];
    [mainrequest addRequestHeader:@"Content-Type" value:@"image/jpeg"];
    [mainrequest startSynchronous];
    if (mainrequest.error) { NSLog(@"Error"); } else {
        imgData = [[NSMutableData alloc]initWithData:[mainrequest responseData]]; }
    req = [start timeIntervalSinceNow] * -1000.0;
    parse = req;
    NSLog(@"download 100kb success");
    NSLog(@"Time taken for download %d",(int)req);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.view endEditing:YES];
}

-(IBAction)Button4:(id)upload
{
    postData = [filemgr contentsAtPath:[[NSBundle mainBundle]pathForResource:@"500kb" ofType:@"jpg"]];
    mainrequest = [SDMRequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/CarrierCollection('LH')/$value",AppEndUrl]]];
    [mainrequest setRequestMethod:@"PUT"];
    [mainrequest addRequestHeader:@"Content-Type" value:@"image/jpeg"];
    [mainrequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [mainrequest setPostBody:[NSMutableData dataWithData:postData]];
    start = [NSDate date];
    [mainrequest startSynchronous];
    if (mainrequest.error) { NSLog(@"Error"); } else {
        l_responseData = [mainrequest responseData]; }
    req = [start timeIntervalSinceNow] * -1000.0;
    parse = req;
    NSLog(@"upload 500kb success");
    NSLog(@"Time taken for upload %d",(int)req);
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

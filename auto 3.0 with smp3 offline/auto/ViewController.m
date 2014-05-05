//
//  ViewController.m
//  auto
//
//  Created by i074667 on 6/10/13.
//  Copyright (c) 2013 i074667. All rights reserved.
//

#import "ViewController.h"
#import "NSObject+constants.h"
#import "SMPClientConnection.h"
#import "SMPUserManager.h"
#import "RequestBuilder.h"
#import "SMPAppSettings.h"
#import "ODataServiceDocument.h"
#import "ODataServiceDocumentParser.h"
#import "ODataParser.h"
#import "ODataEntry.h"
#import "ODataPropertyValues.h"
#import "ODataCollection.h"
#import "ODataDataParser.h"
#import "Caching.h"
#import "Cache.h"
#import "EncryptionKeyManager.h"

@interface ViewController ()

@end

@implementation ViewController
@synthesize server;
SMPAppSettings *l_appsettingsObj;
SMPClientConnection *l_clientconn;
SMPUserManager *userManager;
NSDate *start,*merge_start;
float req,parse,stop,thread,merge_stop;
NSString *l_response;
NSData *l_responseData;
NSString *putBody;
NSMutableData *data;
UIImage *image;
NSData *postData;
NSFileManager *filemgr;
NSString *key;
//id<Caching> storeCache;
ODataFeed *feed;
NSString *deltalink;
ODataServiceDocument *serviceDocument;
ODataServiceDocumentParser *svcdocParser;
ODataSchema *schema;
NSArray *entries;
NSString *URL;
id<Caching> cache;
id<Caching> l_cache;
ODataEntry *singleentry;
NSString *entryid;

NSMutableData *imgData;

int i=0,j=0;

-(IBAction)Button:(id)sender
{
    NSError *error1 = nil;
    serverip = server.text;
    //[mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    /*l_clientconn = [SMPClientConnection initializeWithAppID:@"com.sap.travelapp" domain:@"default" secConfiguration:@"SSO"];
     [l_clientconn setConnectionProfileWithHost:@"10.66.128.223" port:@"5005" farm:0 relayServerUrlTemplate:nil enableHTTP:YES];
     userManager = [SMPUserManager initializeWithConnection:l_clientconn];
     [l_clientconn setConnectionProfileWithUrl:serverip];*/
    
    l_clientconn = [SMPClientConnection initializeWithAppID:@"ldci2" domain:@"default" secConfiguration:@"ldci2_SC"];
    //[l_clientconn setApplicationConnectionID:@"PerfAPPCID"];
    [l_clientconn setConnectionProfileWithHost:serverip port:@"8080" farm:nil relayServerUrlTemplate:nil enableHTTP:YES];
    userManager = [SMPUserManager initializeWithConnection:l_clientconn];
    NSError *error = nil;
    BOOL registrationflag= [userManager registerUser:@"perfbb" password:@"perfbb" error:&error isSyncFlag:YES];
    //registrationflag= [userManager registerUser:@"perfbb" password:@"perfbb" error:&error isSyncFlag:YES];
    
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
    
    [RequestBuilder enableXCSRF:YES];
    [RequestBuilder setRequestType:HTTPRequestType];
    mainrequest = [RequestBuilder requestWithURL:[NSURL URLWithString:AppEndUrl]];
    [mainrequest addRequestHeader:@"X-Requested-With" value:@"SAPDataLibrary-ObjC"];
    [mainrequest setUsername:@"perfbb"];
    [mainrequest setPassword:@"perfbb"];
    
    [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    [mainrequest addRequestHeader:@"X-SUP-APPCID" value:connid];    putBody =[NSString stringWithFormat:@"<?xml version=\"1.0\" encoding=\"utf-8\"?><entry xml:base=\"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/\" xmlns=\"http://www.w3.org/2005/Atom\" xmlns:m=\"http://schemas.microsoft.com/ado/2007/08/dataservices/metadata\" xmlns:d=\"http://schemas.microsoft.com/ado/2007/08/dataservices\"><id>http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('00001403')</id><title type=\"text\">TravelagencyCollection('00001403')</title><updated>2012-07-27T03:32:39Z</updated><category term=\"RMTSAMPLEFLIGHT.Travelagency\" scheme=\"http://schemas.microsoft.com/ado/2007/08/dataservices/scheme\"/><link href=\"TravelagencyCollection('00001403')\" rel=\"edit\" title=\"Travelagency\"/><content type=\"application/xml\"><m:properties><d:agencynum>00001403</d:agencynum><d:NAME>aaaaaaaaaaaaaaaaaaaaaaaaa</d:NAME><d:STREET>zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</d:STREET><d:POSTBOX>aaaaaaaaaa</d:POSTBOX><d:POSTCODE>aaaaaaaaaa</d:POSTCODE><d:CITY>zzzzzzzzzzzzzzzzzzzzzzzzz</d:CITY><d:COUNTRY>DEq</d:COUNTRY><d:REGION>051</d:REGION><d:TELEPHONE>12356789123456789123456789123</d:TELEPHONE><d:URL>http://manoj</d:URL><d:LANGU>D</d:LANGU><d:CURRENCY>EUR</d:CURRENCY><d:mimeType>text/html</d:mimeType></m:properties></content></entry>"];
    data = [NSMutableData dataWithBytes:[putBody cString] length:[putBody length]];
    URL = [NSString stringWithFormat:@"%@/%@",AppEndUrl,@"TravelAgencies_DQ"];
    [cache addNotificationDelegate:self withListener:@selector(notificationListener:) forUrlKey:URL];

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
            
            mainrequest = [RequestBuilder requestWithURL:[NSURL URLWithString:AppEndUrl]];
            [mainrequest addRequestHeader:@"X-Requested-With" value:@"SAPDataLibrary-ObjC"];
            [mainrequest setUsername:@"perfbb"];
            [mainrequest setPassword:@"perfbb"];
            
            [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
           // [mainrequest addRequestHeader:@"X-SUP-APPCID" value:connid];
            start = [NSDate date];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest startSynchronous];
            if (mainrequest.error)
            { NSLog(@"%@",([mainrequest responseString])); }
            else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        svcdocParser = [[ODataServiceDocumentParser alloc] init];
        [svcdocParser parse:l_responseData];
        parse = [start timeIntervalSinceNow] * -1000.0;
        serviceDocument = svcdocParser.serviceDocument;
        NSLog(@"service document success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Service-Document	",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
       
//metadata
        start = [NSDate date];
        mainrequest = [RequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/$metadata",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        schema = parseODataSchemaXML(l_responseData, serviceDocument);
        parse = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"metadata success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Metadata          ",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        [NSThread sleepForTimeInterval:2.0f];
            
//collection 300
        ODataCollection *collection = [schema getCollectionByName:@"TravelAgencies_DQ"];
        ODataDataParser* dataParser = [[ODataDataParser alloc] initWithEntitySchema:collection.entitySchema andServiceDocument: serviceDocument];
        start = [NSDate date];
        mainrequest = [RequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@TravelAgencies_DQ",AppEndUrl]]];
        [mainrequest setRequestMethod:@"GET"];
        [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
        [mainrequest addRequestHeader:@"Accept-Encoding" value:@"gzip"];
        [mainrequest startSynchronous];
        if (mainrequest.error) { NSLog(@"Error"); } else {
            l_responseData = [mainrequest responseData]; }
        req = [start timeIntervalSinceNow] * -1000.0;
        //entries = parseODataEntriesXML(l_responseData , collection.entitySchema ,serviceDocument);
        [dataParser parse:l_responseData];
        feed = [dataParser getFeed];
        parse = [start timeIntervalSinceNow] * -1000.0;
        //[NSThread detachNewThreadSelector:@selector(merge) toTarget:self withObject:nil];
        thread = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"collection success");
        [all addObject:[NSMutableArray arrayWithObjects:@"Collection	",[NSString stringWithFormat:@"%d",(int)req],[NSString stringWithFormat:@"%d",(int)(parse-req)],[NSString stringWithFormat:@"%d",(int)parse], nil]];
        //[NSThread sleepForTimeInterval:2.0f];
            
           
            mainrequest = [RequestBuilder requestWithURL:[NSURL URLWithString:AppEndUrl]];
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

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self.view endEditing:YES];
}


-(IBAction)Button5:(id)merge
{
    @try {
    NSError *error1 = nil;
    start = [NSDate date];
    if(![cache mergeEntries:feed forUrlKey:URL withError:&error1 withCompletionBlock:^(NSNotification *notif){
        NSLog(@"Cache updated");
    }] )
    {
        NSLog(@"Merge error:%@",error1);
        return;
        
    }else{
        stop = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"successfully merged entries time taken = %d",(int)stop);
    }
    deltalink = [cache getDeltaLinkForUrlKey:URL withError:&error1];
    NSLog(@"%@",deltalink);
    }
    @catch (NSException *exception) {
        NSLog(@"%@",[exception description]);
    }
}

-(void)merge{
    
    NSError *error1 = nil;
    merge_start = [NSDate date];
    if(![cache mergeEntries:feed forUrlKey:URL withError:&error1 withCompletionBlock:^(NSNotification *notif){
        NSLog(@"Cache updated");
    }] )
    {
        NSLog(@"Merge error:%@",error1);
        return;
        
    }else{
        merge_stop = [merge_start timeIntervalSinceNow] * -1000.0;
        NSLog(@"successfully merged entries time taken = %d",(int)merge_stop);
    }
    deltalink = [cache getDeltaLinkForUrlKey:URL withError:&error1];
    NSLog(@"%@",deltalink);
    NSLog(@"\nreq-resp= %d\nparse=%d\nthread=%d\nE2E(without merge)=%d\nE2E(total)=%d\nMerge=%d\n",(int)(req),(int)(parse-req),(int)(thread-parse),(int)(thread),((int)(thread)+(int)(merge_stop)),(int)(merge_stop));
    
    
    if(![cache clearCacheForUrlKey:URL withError:&error1])
    {
        NSLog(@"clear cache error:%@",error1);
        return;
    }else{
        NSLog(@"successfully cleared cache for next iteration");
    }
    
}

-(IBAction)Button6:(id)clear
{
    NSError *error1 = nil;
    start = [NSDate date];
    if(![cache clearCacheForUrlKey:URL withError:&error1])
    {
        NSLog(@"clear cache error:%@",error1);
        return;
    }else{
        stop = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"successfully cleared time taken = %d",(int)stop);
    }
}

-(IBAction)Button7:(id)retrieve
{
    NSError *error1 = nil;
    start = [NSDate date];
    entries = [cache readEntriesForUrlKey:URL withError:&error1];
    if(error1)
    {
        NSLog(@"read cache error:%@",error1);
        return;
    }else{
        stop = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"successfully retrieved %d records & time taken = %d",[entries count],(int)stop);
    }
    singleentry = [entries objectAtIndex:0];
    entryid = [singleentry getEntryID];
}

-(IBAction)Button8:(id)server_auto
{
    //UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"read entries failed" message: [NSString stringWithFormat:@"error-->%@",error1]delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
    //[alert show];
    URL = [NSString stringWithFormat:@"%@/%@",AppEndUrl,@"TravelAgencies_DQ"];
    [cache addNotificationDelegate:self withListener:@selector(notificationListener:) forUrlKey:URL];
    //cache
    int ic=0;
    for (ic=0; ic<10; ic++) {
        
        NSError *error1 = nil;
   
        //clear cache
        start = [NSDate date];
        if(![cache clearCacheForUrlKey:URL withError:&error1])
        {
            NSLog(@"clear cache error:%@",error1);
            return;
        }else{
            NSLog(@"clear success");
        }
        stop = [start timeIntervalSinceNow] * -1000.0;
        
        //merge cache
        if(![cache mergeEntries:feed forUrlKey:URL withError:&error1 withCompletionBlock:^(NSNotification *notif){
            NSLog(@"merge success");
        }] )
        {
            NSLog(@"Merge error:%@",error1);
            return;
            
        }

        //deltalink = [cache getDeltaLinkForUrlKey:URL withError:&error1];
        //NSLog(@"%@",deltalink);
        req = [start timeIntervalSinceNow] * -1000.0;

        entries = nil;
        
        //read cache
        entries = [cache readEntriesForUrlKey:URL withError:&error1];
        if(error1)
        {
            NSLog(@"read cache error:%@",error1);
            return;
        }else{
            NSLog(@"%d entries retrieve success",[entries count]);
        }
        
        parse = [start timeIntervalSinceNow] * -1000.0;
        
        singleentry = [entries objectAtIndex:0];
        entryid = [singleentry getEntryID];
        
        //[all addObject:[NSMutableArray arrayWithObjects:@"Cache operation	",[NSString stringWithFormat:@"%d",(int)stop],[NSString stringWithFormat:@"%d",(int)(req-stop)],[NSString stringWithFormat:@"%d",(int)(parse-req)], nil]];
        
        NSLog(@"Store: %d, Retrieve: %d,Clear: %d",(int)(req-stop),(int)(parse-req),(int)stop);
        
    }
}

-(IBAction)Button9:(id)l_update
{
    NSError *errorput = nil;
    ODataEntry *updateentry =singleentry;
    start = [NSDate date];
    if(![l_cache updateEntry:updateentry withError:&errorput])
        
    {
        NSLog(@"error in local cache while put %@",errorput);
    }else{
        stop = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"successfully added to cache for update time taken = %d",(int)stop);
    }
    NSError *errorclear = nil;
    [l_cache clearLocalEntryForEntryId:entryid withError:&errorclear];
    if(!errorclear)
    {
        NSLog(@"cleared entry");
    }else
    {
        NSLog(@"error in local cache while clear %@",errorclear);
    }
}

-(IBAction)Button10:(id)l_delete
{
    ODataEntry *deleteentry =singleentry;
    
    NSError *errordel = nil;
    NSString *deleteentryid = deleteentry.getEntryID;
    start = [NSDate date];
    if(![l_cache deleteEntryForEntryId:deleteentryid withError:&errordel])
        
    {
        NSLog(@"error in local cache while del %@",errordel);
    }else{
        stop = [start timeIntervalSinceNow] * -1000.0;
        NSLog(@"successfully added to cache for delete time taken = %d",(int)stop);
    }
    NSError *errorclear = nil;
    [l_cache clearLocalEntryForEntryId:deleteentryid withError:&errorclear];
    if(!errorclear)
    {
        NSLog(@"cleared entry");
    }else
    {
        NSLog(@"error in local cache while clear %@",errorclear);
    }
}

-(IBAction)Button11:(id)l_add
{
    NSError *errorpost = nil;
    ODataEntry *postentry =singleentry;
    start = [NSDate date];
    NSString *tempid = [l_cache addEntry:postentry withError:&errorpost];
    stop = [start timeIntervalSinceNow] * -1000.0;
    if(!errorpost)
    {
        NSLog(@"successfully added to cache for add time taken = %d",(int)stop);
        NSLog(@"surrogate id%@",tempid);
    }else
    {
        NSLog(@"error in local cache while post %@",errorpost);
    }
    NSError *errorclear = nil;
    [l_cache clearLocalEntryForEntryId:tempid withError:&errorclear];
    if(!errorclear)
    {
        NSLog(@"cleared entry");
    }else
    {
        NSLog(@"error in local cache while clear %@",errorclear);
    }

}

-(IBAction)Button12:(id)delta
{
    ODataCollection *collection = [schema getCollectionByName:@"TravelAgencies_DQ"];
    ODataDataParser* dataParser = [[ODataDataParser alloc] initWithEntitySchema:collection.entitySchema andServiceDocument: serviceDocument];
    start = [NSDate date];
    mainrequest = [RequestBuilder requestWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@",deltalink]]];
    [mainrequest setRequestMethod:@"GET"];
    [mainrequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    [mainrequest addRequestHeader:@"Accept-Encoding" value:@"gzip"];
    [mainrequest startSynchronous];
    if (mainrequest.error) { NSLog(@"Error"); } else {
        l_responseData = [mainrequest responseData]; }
    req = [start timeIntervalSinceNow] * -1000.0;
    //NSArray *entries;
    //entries = parseODataEntriesXML(l_responseData , collection.entitySchema ,serviceDocument);
    [dataParser parse:l_responseData];
    feed = [dataParser getFeed];
    parse = [start timeIntervalSinceNow] * -1000.0;
    NSLog(@"delta link fetch success %d entries",[[dataParser getEntries] count]);
}

-(void)notificationListener:(NSString *)URL
{
    NSLog(@"cache got update");
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Notification listener" message:@"Cache got updated" delegate:self cancelButtonTitle:@"OK" otherButtonTitles: nil];
    //[alert show];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSError *errorcache = nil;
    key = [EncryptionKeyManager getEncryptionKey:&errorcache];
    [EncryptionKeyManager setEncryptionKey:key];
    NSError *error1 = nil;
    cache = [[Cache alloc] init];
    [cache initializeCacheWithError:&error1];
    if(error1)
    {
        NSLog(@"initialize cache error:%@",error1);
        return;
    }
    l_cache = [[Cache alloc] init];
    [l_cache initializeCacheWithError:&error1];
    if(error1)
    {
        NSLog(@"initialize cache error:%@",error1);
        return;
    }
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

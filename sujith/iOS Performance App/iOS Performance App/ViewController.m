//
//  ViewController.m
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#import "ODPRequest.h"
#import "SDMParser.h"
#import "SDMODataServiceDocumentParser.h"
#import "SDMODataServiceDocument.h"
#import "SDMODataWorkspace.h"
#import "SDMODataCollection.h"
#import "SDMPerformanceUtil.h"

//#import "SDMOData.h"
//#import "SDMSubscriptionXMLBuilder.h"


#import "SDMODataEntry.h"
#import "SDMODataPropertyValues.h"


@interface ViewController ()

@end

@implementation ViewController


@synthesize array,m_detailViewController, l_response,l_responseData,agencyNumber,agencyName,country,phone,url;

NSDate *renderingTime;
float totalRenderingTime;
int noOfCellsRendered;
SDMODataCollection *collection;
SDMODataServiceDocument *serviceDocument;
NSDate *serviceDocumentRequestAndParsingTimer, *metadataRequestAndParsingTimer, *collectionRequestAndParsingTimer, *entryRequestAndParsingTimer;
float serviceDocumentRequestAndParsingTime, metadataRequestAndParsingTime, collectionRequestAndParsingTime, entryRequestAndParsingTime;

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self registration];
    renderingTime = [[NSDate alloc] init];
   // agencyNumber=[[NSMutableArray alloc] init];
    
    noOfCellsRendered=0;
    totalRenderingTime=0;
//    array = [[NSMutableArray alloc]init];
//    [array addObject:@"Sujith"];
//    [array addObject:@"Reshma"];
//    [array addObject:@"Ambika"];
//    [array addObject:@"Golden Flame"];
    
//    m_detailViewController =[[DetailsView alloc]initWithNibName:@"DetailsView" bundle:nil];
    
    self.navigationItem.title = @"3 Requests";

     self.navigationItem.rightBarButtonItem   = [[UIBarButtonItem alloc] initWithTitle:@"Populate" style:UIBarButtonItemStylePlain target:self action:@selector(populate)];
    
    self.navigationController.toolbar.translucent = YES;
    self.navigationController.navigationBar.tintColor = [UIColor blackColor];
    self.navigationItem.rightBarButtonItem.tintColor = [UIColor orangeColor];

    
	// Do any additional setup after loading the view, typically from a nib.
}

-(void)populate
{
    agencyNumber=[[NSMutableArray alloc] init];
    agencyName=[[NSMutableArray alloc] init];
    country=[[NSMutableArray alloc] init];
    phone=[[NSMutableArray alloc] init];
    url=[[NSMutableArray alloc] init];
    [m_dataTableView reloadData];
//  [self registration];
    [self request];
    [self parsing];
    
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
   // return 4;
    return [agencyNumber count];
}

// Row display. Implementers should *always* try to reuse cells by setting each cell's reuseIdentifier and querying for available reusable cells with dequeueReusableCellWithIdentifier:
// Cell gets various attributes set automatically based on table (separators) and data source (accessory views, editing controls)

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{

    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"MyCell"];
    if(cell == nil)
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"MyCell"] ;
    
    //cell.textLabel.text = [array objectAtIndex:[indexPath row]];
    if(agencyNumber!=nil)
    {
        cell.textLabel.text = [agencyName objectAtIndex:[indexPath row]];
    }
    
    noOfCellsRendered = noOfCellsRendered + 1;
    renderingTime = [[NSDate date]retain];
    double timePassed_ms2 = [renderingTime timeIntervalSinceNow] * -1000.0;
    NSLog(@"The time for populating the table is %fms",timePassed_ms2);
    totalRenderingTime = totalRenderingTime + timePassed_ms2;
    
    NSLog(@"The rendering time for %d cells is %f ms. \n The average rendering time per cell is %f. \n Individual screen renderingtime is %f ",noOfCellsRendered,totalRenderingTime,(totalRenderingTime/noOfCellsRendered),(totalRenderingTime/noOfCellsRendered)*10);
      cell.selectionStyle = UITableViewCellSelectionStyleGray;
    
    cell.textLabel.textColor = [UIColor whiteColor];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
////    NSLog(@"The row selected is %d, Value is %@",[indexPath row],[agencyNumber objectAtIndex:[indexPath row]]);
////    NSLog(@"\n*********************************Current Selection****************************");
////    NSLog(@"\nAgency Number: %@ \n Agency Name:%@ \n Country: %@ \n Telephone: %@ \n URL: %@ \n\n\n",[agencyNumber objectAtIndex:[indexPath row]],[agencyName objectAtIndex:[indexPath row]],[country objectAtIndex:[indexPath row]],[phone objectAtIndex:[indexPath row]],[url objectAtIndex:[indexPath row]]);
////    NSLog(@"***************************************END*************************************");
    
    NSDate *singleEntryStoringTime = [NSDate date];
    NSUserDefaults *store = [NSUserDefaults standardUserDefaults];
    [store setObject:[NSString stringWithFormat:@"%@",[agencyNumber objectAtIndex:[indexPath row]]] forKey:@"Selection"];
    [store setObject:[NSString stringWithFormat:@"%@",[agencyName objectAtIndex:[indexPath row]]] forKey:@"AgencyName"];
    [store setObject:[NSString stringWithFormat:@"%@",[country objectAtIndex:[indexPath row]]] forKey:@"Country"];
    [store setObject:[NSString stringWithFormat:@"%@",[phone objectAtIndex:[indexPath row]]] forKey:@"Telephone"];
    [store setObject:[NSString stringWithFormat:@"%@",[url objectAtIndex:[indexPath row]]] forKey:@"URL"];
     [store synchronize];
    double singleEntryStorTime = [singleEntryStoringTime timeIntervalSinceNow] * -1000.0;
    NSLog(@"The time for storing a single entry is %fms",singleEntryStorTime);

    
    m_detailViewController =[[DetailsView alloc]initWithNibName:@"DetailsView" bundle:nil];
    [self.navigationController pushViewController:m_detailViewController animated:YES];
    
    entryRequestAndParsingTimer = [NSDate date];
    ODPRequest *postRequest1 = [ODPRequest requestWithURL:[NSURL URLWithString:[NSString stringWithFormat: @"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('%@')",[agencyNumber objectAtIndex:[indexPath row]]]]];
    [postRequest1 setRequestMethod:@"GET"];
    [postRequest1 addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    [postRequest1 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [postRequest1 setUsername:@"perfios"];
    [postRequest1 setPassword:@"perfios"];
    [postRequest1 startSynchronous];
//    NSLog(@"%@",[postRequest1 responseString]);
    entryRequestAndParsingTime = [entryRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
    NSLog(@"The total time for Request Response for an entry is %fms",entryRequestAndParsingTime); //This is Request Response time only. Do not get confused by the name of the timer.


    
    
    NSArray *singleEntry;
    @try {
        NSDate *date2 = [NSDate date];
        //Start of Parsing
        singleEntry = sdmParseODataEntriesXML([postRequest1 responseData] , collection.entitySchema ,serviceDocument);
        double timePassed_ms2 = [date2 timeIntervalSinceNow] * -1000.0;
        NSLog(@"The time for the parsing an entry is %fms",timePassed_ms2);
        
        entryRequestAndParsingTime = [entryRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
        NSLog(@"The total time for Request Response and parsing an entry is %fms",entryRequestAndParsingTime); 
        
        
    }
    @catch (NSException *exception) {
        NSLog(@"%@",[exception description]);
    }
    
////    SDMODataEntry *entry = [singleEntry objectAtIndex:0];
////    SDMODataPropertyValueObject *object1 = [entry getPropertyValueByPath:@"agencynum"];
////    SDMODataPropertyValueObject *object2 = [entry getPropertyValueByPath:@"NAME"];
////    SDMODataPropertyValueObject *object3 = [entry getPropertyValueByPath:@"COUNTRY"];
////    SDMODataPropertyValueObject *object4 = [entry getPropertyValueByPath:@"TELEPHONE"];
////    SDMODataPropertyValueObject *object5 = [entry getPropertyValueByPath:@"URL"];

////    NSLog(@"\nAgency Number: %@ \n Agency Name:%@ \n Country: %@ \n Telephone: %@ \n URL: %@ \n\n\n",object1.rawValue,object2.rawValue,object3.rawValue,object4.rawValue,object5.rawValue);

}

- (void)registration
{
    @try
    {
    ODPUserManager *manager = [ODPUserManager getInstance:@"com.sap.travelapp"];

    //Registration through the relay server
    //[manager setConnectionProfileWithHost:@"10.68.84.243" port:5001 farm:@"pwdf3177" error:nil];
    [manager setConnectionProfileWithHost:@"10.68.139.106" port:5001 farm:@"pwdf3177" error:nil];
    
    //Direct Registration without the relay server
    //[manager setConnectionProfileWithHost:@"10.66.128.223" port:5005 farm:@"0" error:nil];
    
    //My local server
    //[manager setConnectionProfileWithHost:@"10.66.141.166" port:5005 farm:@"0" error:nil];
    
    NSError *error1 = [NSError alloc];
    [manager registerUser:@"perfios" securityConfig:@"SSO" password:@"perfios" error:&error1 isSyncFlag:YES];
    
    
        
    }
    
    @catch (NSException *exception) {
        NSLog(@"exception is %@",[exception description]);
    }
}

- (void)request
{
    //
    serviceDocumentRequestAndParsingTimer = [NSDate date];
    
    [ODPRequest enableXCSRF:YES];
    ODPRequest *l_request = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/"]];
    [l_request setUsername:@"perfios"];
    [l_request setPassword:@"perfios"];
    
    [l_request startSynchronous];
    if (l_request.error) {
        NSLog(@"%@", [l_request.error localizedDescription]);
    }
    else
    {
        l_response = [l_request responseString];
////        NSLog(@"Response String Request:   %@",l_response);
        l_responseData = [l_request responseData];      
////        NSString *xCSRFToken = [headers objectForKey:@"X-CSRF-TOKEN"];
////        NSLog(@"%@",xCSRFToken);
        
        serviceDocumentRequestAndParsingTime = [serviceDocumentRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
        NSLog(@"The total time for Request Response of the service document is %fms",serviceDocumentRequestAndParsingTime); //This is Request Response time only. Do not get confused by the name of the timer.
    }

}

- (void)parsing
{
  
    [SDMPerformanceUtil enableParserPerformanceLog:YES];
    SDMODataServiceDocumentParser *svcdocParser = [[SDMODataServiceDocumentParser alloc] init];
    
    NSDate *date = [NSDate date];
    [svcdocParser parse:l_responseData];
    double timePassed_ms = [date timeIntervalSinceNow] * -1000.0;
    NSLog(@"The time for the parsing the service document is %fms",timePassed_ms);
    
    serviceDocumentRequestAndParsingTime = [serviceDocumentRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
    NSLog(@"The total time for Request Response and parsing the service document is %fms",serviceDocumentRequestAndParsingTime);

    serviceDocument = svcdocParser.serviceDocument;
    
    
    metadataRequestAndParsingTimer = [NSDate date];
    ODPRequest *l_request = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/$metadata"]];
    [l_request setUsername:@"perfios"];
    [l_request setPassword:@"perfios"];
    
    [l_request startSynchronous];
    

    
    if (l_request.error) {
        NSLog(@"%@", [l_request.error localizedDescription]);
    }
    else
    {
        l_response = [l_request responseString];
////        NSLog(@"Response String Metadata:   %@",l_response);
        l_responseData = [l_request responseData];
        
        metadataRequestAndParsingTime = [metadataRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
        NSLog(@"The total time for Request Response of the metadata document is %fms",metadataRequestAndParsingTime);
        //This is Request Response time only. Do not get confused by the name of the timer.

    }

    NSData *metaData = [l_request responseData];
    
    
     NSDate *date1 = [NSDate date];
    SDMODataSchema *schema = sdmParseODataSchemaXML(metaData, serviceDocument);
    double timePassed_ms1 = [date1 timeIntervalSinceNow] * -1000.0;
    NSLog(@"The time for the parsing the metadata is %fms",timePassed_ms1);
    
    metadataRequestAndParsingTime = [metadataRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
    NSLog(@"The total time for Request Response and parsing the metadata document is %fms",metadataRequestAndParsingTime);
    
    
    
    collection = [schema getCollectionByName:@"TravelagencyCollection"];
    
    collectionRequestAndParsingTimer = [NSDate date];
    ODPRequest *l_requestCollection = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection/?$top=300"]];
    [l_requestCollection setUsername:@"perfios"];
    [l_requestCollection setPassword:@"perfios"];
    
    [l_requestCollection startSynchronous];
    
    if (l_requestCollection.error) {
        NSLog(@"%@", [l_requestCollection.error localizedDescription]);
    }
    else
    {
        
////        NSLog(@"Response String Collection:   %@",[l_requestCollection responseString]);
        collectionRequestAndParsingTime = [collectionRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
        NSLog(@"The total time for Request Response for the collections document is %fms",collectionRequestAndParsingTime);
        //This is Request Response time only. Do not get confused by the name of the timer.
    }

    
    NSData *collectionData = [l_requestCollection responseData];
    
    

    NSArray *entries;
    @try {
        NSDate *date2 = [NSDate date];
        entries = sdmParseODataEntriesXML(collectionData , collection.entitySchema ,serviceDocument);
        double timePassed_ms2 = [date2 timeIntervalSinceNow] * -1000.0;
        NSLog(@"The time for the parsing the %d Entries is %fms \n Average Single cell parse time: %fms",entries.count, timePassed_ms2,timePassed_ms2/entries.count);
        
        collectionRequestAndParsingTime = [collectionRequestAndParsingTimer timeIntervalSinceNow] * -1000.0;
        NSLog(@"The total time for Request Response and parsing the collections document is %fms",collectionRequestAndParsingTime);
        [SDMPerformanceUtil enableParserPerformanceLog:NO];
        
    }
    @catch (NSException *exception) {
        NSLog(@"%@",[exception description]);
    }
   
    //agencyNumber = [[NSMutableArray alloc]init];
    //agencyNumber =[NSMutableArray arrayWithArray:entries];
    
    for (int i =0 ; i<entries.count; i++)
    {
        SDMODataEntry *entry = [entries objectAtIndex:i];
       // NSLog(@"%@",[entry getEntryID]);
        SDMODataPropertyValueObject *object1 = [entry getPropertyValueByPath:@"agencynum"];
        SDMODataPropertyValueObject *object2 = [entry getPropertyValueByPath:@"NAME"];
        SDMODataPropertyValueObject *object3 = [entry getPropertyValueByPath:@"COUNTRY"];
        SDMODataPropertyValueObject *object4 = [entry getPropertyValueByPath:@"TELEPHONE"];
        SDMODataPropertyValueObject *object5 = [entry getPropertyValueByPath:@"URL"];
        
        [agencyNumber addObject:object1.rawValue];
        [agencyName addObject:object2.rawValue];
        [country addObject:object3.rawValue];
        [phone addObject:object4.rawValue];
        [url addObject:object5.rawValue];
        
        
       // [agencyNumber addObject:[NSString stringWithFormat:@"%@",[entry getPropertyValueByPath:@"agencynum"]]];
////        NSLog(@"\nAgency Number: %@ \n Agency Name:%@ \n Country: %@ \n Telephone: %@ \n URL: %@ \n\n\n",object1.rawValue,object2.rawValue,object3.rawValue,object4.rawValue,object5.rawValue);
    }
    renderingTime = [[NSDate date]retain];
    [m_dataTableView reloadData];
//    double timePassed_ms2 = [renderingTime timeIntervalSinceNow] * -1000.0;
//    NSLog(@"The time for populating the table is %fms",timePassed_ms2);
    
}
@end

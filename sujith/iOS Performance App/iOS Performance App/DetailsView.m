//
//  DetailsView.m
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "DetailsView.h"
#import "ODPRequest.h"

@interface DetailsView ()

@end

@implementation DetailsView

@synthesize m_postView;
@synthesize field1,field2,field3,field4,field5;
@synthesize textField1,textField2,textField3,textField4,textField5,imageView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    
    
    m_postView = [[PostView alloc] initWithNibName:@"PostView" bundle:nil];
    
    
    NSUserDefaults *standardUserDefaults = [NSUserDefaults standardUserDefaults];
    NSString *agencyNumber = nil;
    NSString *agencyName = nil;
    NSString *country = nil;
    NSString *phone = nil;
    NSString *url = nil;
    
    if (standardUserDefaults) 
    {
        agencyNumber = [standardUserDefaults objectForKey:@"Selection"];
        agencyName = [standardUserDefaults objectForKey:@"AgencyName"];
        country = [standardUserDefaults objectForKey:@"Country"];
        phone = [standardUserDefaults objectForKey:@"Telephone"];
        url = [standardUserDefaults objectForKey:@"URL"];
    }
////    NSLog(@"The Selection is %@",agencyNumber);
    
////    NSLog(@"\n******************************Transfered Selection****************************");
////    NSLog(@"\nAgency Number: %@ \n Agency Name:%@ \n Country: %@ \n Telephone: %@ \n URL: %@ \n\n\n",agencyNumber,agencyName,country,phone,url);
////    NSLog(@"***************************************END**************************************");
    
    textField1.text = agencyNumber;
    textField2.text = agencyName;
    textField3.text = country;
    textField4.text = phone;
    textField5.text = url;
    
    textField1.textColor = [UIColor whiteColor];
    textField2.textColor = [UIColor whiteColor];
    textField3.textColor = [UIColor whiteColor];
    textField4.textColor = [UIColor whiteColor];
    textField5.textColor = [UIColor blackColor];
    
    field1.textColor = [UIColor whiteColor];
    field2.textColor = [UIColor whiteColor];
    field3.textColor = [UIColor whiteColor];
    field4.textColor = [UIColor whiteColor];
    field5.textColor = [UIColor whiteColor];
    
    self.navigationItem.title = @"2 Requests";
    
    self.navigationItem.rightBarButtonItem   = [[UIBarButtonItem alloc] initWithTitle:@"Details" style:UIBarButtonItemStylePlain target:self action:@selector(addEntrySelected:)];
        self.navigationItem.rightBarButtonItem.tintColor = [UIColor orangeColor];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(backButtonSelected:)];
        self.navigationItem.leftBarButtonItem.tintColor = [UIColor orangeColor];
    
    [self request];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(IBAction)backButtonSelected:(id)sender
{
    //[self.view removeFromSuperview];
    [self.navigationController popViewControllerAnimated:YES];
}

-(IBAction)addEntrySelected:(id)sender
{
    //[self.view addSubview:m_postView.view];
     [self.navigationController pushViewController:m_postView animated:YES];
}
-(void)request
{
//    [ODPRequest enableXCSRF:YES];
//    ODPRequest *postRequest1 = [ODPRequest requestWithURL:[NSURL URLWithString:@"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection"]];
//    [postRequest1 setRequestMethod:@"GET"];
//    [postRequest1 addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
//    [postRequest1 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
//    [postRequest1 setUsername:@"perfios"];
//    [postRequest1 setPassword:@"perfios"];
//    [postRequest1 startSynchronous];
//    NSLog(@"%@",[postRequest1 responseString]);
}
-(IBAction)update:(id)sender
{
        [ODPRequest enableXCSRF:YES];
        //ODPRequest *postRequest1 = [ODPRequest requestWithURL:[NSURL URLWithString:@"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection"]];
//        ODPRequest *postRequest1 = [ODPRequest requestWithURL:[NSURL URLWithString:[NSString stringWithFormat: @"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('%@')",textField1.text]]];
//        [postRequest1 setRequestMethod:@"GET"];
//        [postRequest1 addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
//        [postRequest1 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
//        [postRequest1 setUsername:@"perfios"];
//        [postRequest1 setPassword:@"perfios"];
//        [postRequest1 startSynchronous];
//        NSLog(@"First Request ended");
//        NSLog(@"%@",[postRequest1 responseString]);
    
    NSDate *updateTimer = [NSDate date];

    [ODPRequest enableXCSRF:YES];
    ODPRequest *putRequest = [ODPRequest requestWithURL:[NSURL URLWithString:[NSString stringWithFormat: @"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('%@')",textField1.text]]];
    [putRequest setRequestMethod:@"PUT"];
    [putRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    [putRequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [putRequest setUsername:@"perfios"];
    [putRequest setPassword:@"perfios"];
    
    NSString *url = textField5.text;
    NSLog(@"The udpated urls is %@",url);
    
    
    NSString *putBody=[NSString stringWithFormat:@"<?xml version=\"1.0\" encoding=\"utf-8\"?><entry xml:base=\"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/\" xmlns=\"http://www.w3.org/2005/Atom\" xmlns:m=\"http://schemas.microsoft.com/ado/2007/08/dataservices/metadata\" xmlns:d=\"http://schemas.microsoft.com/ado/2007/08/dataservices\"><id>http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('00001403')</id><title type=\"text\">TravelagencyCollection('00001403')</title><updated>2012-07-27T03:32:39Z</updated><category term=\"RMTSAMPLEFLIGHT.Travelagency\" scheme=\"http://schemas.microsoft.com/ado/2007/08/dataservices/scheme\"/><link href=\"TravelagencyCollection('00001403')\" rel=\"edit\" title=\"Travelagency\"/><content type=\"application/xml\"><m:properties><d:agencynum>%@</d:agencynum><d:NAME>aaaaaaaaaaaaaaaaaaaaaaaaa</d:NAME><d:STREET>zzzzzzzzzzzzzzzzzzzzzzzzzzzzzz</d:STREET><d:POSTBOX>aaaaaaaaaa</d:POSTBOX><d:POSTCODE>aaaaaaaaaa</d:POSTCODE><d:CITY>zzzzzzzzzzzzzzzzzzzzzzzzz</d:CITY><d:COUNTRY>DEq</d:COUNTRY><d:REGION>051</d:REGION><d:TELEPHONE>12356789123456789123456789123</d:TELEPHONE><d:URL>%@</d:URL><d:LANGU>D</d:LANGU><d:CURRENCY>EUR</d:CURRENCY><d:mimeType>text/html</d:mimeType></m:properties></content></entry>",textField1.text,url];
    
    NSMutableData *data = [NSMutableData dataWithBytes:[putBody cString] length:[putBody length]];
    [putRequest setPostBody:data];
    [putRequest startSynchronous];
    
    if (putRequest.error) {
        NSLog(@"%@", [putRequest.error localizedDescription]);
    }
    else
    {
////        NSLog(@"Response String:   %@",[putRequest responseString]);
        float updateTime = [updateTimer timeIntervalSinceNow] * -1000.0;;
        NSLog(@"The total time for updating an entry is is %fms",updateTime);

    }

    
    
    }

-(BOOL) textFieldShouldReturn:(UITextField *)textField 
{ 
    [textField resignFirstResponder]; 
    return YES; 
}


@end

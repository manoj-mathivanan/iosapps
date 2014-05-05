//
//  PostView.m
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "PostView.h"
#import "ViewController.h"
#import "ODPRequest.h"
#import "ImageScreen.h"


@interface PostView ()

@end

@implementation PostView

@synthesize field1,field2,field3,field4,field5;
@synthesize textField1,textField2,textField3,textField4,textField5,xcsrfToken,m_imageScreen;



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
    m_imageScreen = [[ImageScreen alloc]initWithNibName:@"ImageScreen" bundle:nil];
    
   self.navigationItem.title = @"2 Requests";
    
   self.navigationItem.rightBarButtonItem   = [[UIBarButtonItem alloc] initWithTitle:@"(Up/Down)load" style:UIBarButtonItemStylePlain target:self action:@selector(upDnSelected:)];
    self.navigationItem.rightBarButtonItem.tintColor = [UIColor orangeColor];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(backButtonSelected:)];
    self.navigationItem.leftBarButtonItem.tintColor = [UIColor orangeColor];
    
    textField1.text = @"00007476";
    textField2.text = @"Sunshine Travel";
    textField3.text = @"US";
    textField4.text = @"12356789123456789123456789123";
    textField5.text = @"http://www.sunshine";
    
    textField1.textColor = [UIColor whiteColor];
    textField2.textColor = [UIColor whiteColor];
    textField3.textColor = [UIColor whiteColor];
    textField4.textColor = [UIColor whiteColor];
    textField5.textColor = [UIColor whiteColor];
    
    field1.textColor = [UIColor whiteColor];
    field2.textColor = [UIColor whiteColor];
    field3.textColor = [UIColor whiteColor];
    field4.textColor = [UIColor whiteColor];
    field5.textColor = [UIColor whiteColor];
    
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
   // [self.view removeFromSuperview];
    [self.navigationController popViewControllerAnimated:YES];
}

-(IBAction)upDnSelected:(id)sender
{
    //[self.view addSubview:m_viewController.view];
    //ViewController *m_viewController =[[ViewController alloc]initWithNibName:@"DetailsView" bundle:nil];
    //[self.navigationController pushViewController:m_viewController animated:YES];
    [self.navigationController pushViewController:m_imageScreen animated:YES];
}

-(IBAction)addEntry:(id)sender
{
//    [ODPRequest enableXCSRF:YES];
//    ODPRequest *postRequest1 = [ODPRequest requestWithURL:[NSURL URLWithString:@"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection"]];
//    [postRequest1 setRequestMethod:@"GET"];
//    [postRequest1 addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
//    [postRequest1 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
//    [postRequest1 setUsername:@"perfios"];
//    [postRequest1 setPassword:@"perfios"];
//    [postRequest1 startSynchronous];
    
////    NSLog(@"%@",[postRequest1 responseString]);
//    [self getXcsrfToken:postRequest1];
    
    NSDate *postTimer = [NSDate date];
    
    [ODPRequest enableXCSRF:YES];
    ODPRequest *postRequest = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection"]];
    [postRequest setRequestMethod:@"POST"];
    [postRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    [postRequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [postRequest setUsername:@"perfios"];
    [postRequest setPassword:@"perfios"];
//    [postRequest addRequestHeader:@"x-csrf-token" value:xcsrfToken];
    
    
    NSString *postBody =@"<?xml version=\"1.0\" encoding=\"utf-8\"?><entry xml:base=\"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/\" xmlns=\"http://www.w3.org/2005/Atom\" xmlns:m=\"http://schemas.microsoft.com/ado/2007/08/dataservices/metadata\" xmlns:d=\"http://schemas.microsoft.com/ado/2007/08/dataservices\"><id>http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('00000055')</id><title type=\"text\">TravelagencyCollection('00000055')</title><updated>2012-07-27T16:30:07Z</updated><category term=\"RMTSAMPLEFLIGHT.Travelagency\" scheme=\"http://schemas.microsoft.com/ado/2007/08/dataservices/scheme\"/><link href=\"TravelagencyCollection('00000055')\" rel=\"edit\" title=\"Travelagency\"/><content type=\"application/xml\"><m:properties><d:agencynum>00007476</d:agencynum><d:NAME>Sunshine Travel</d:NAME><d:STREET>134 West Street</d:STREET><d:POSTBOX/><d:POSTCODE>54323</d:POSTCODE><d:CITY>Rochester</d:CITY><d:COUNTRY>US</d:COUNTRY><d:REGION>NY</d:REGION><d:TELEPHONE>12356789123456789123456789123</d:TELEPHONE><d:URL>http://www.sunshine</d:URL><d:LANGU>E</d:LANGU><d:CURRENCY>USD</d:CURRENCY><d:mimeType>text/html</d:mimeType></m:properties></content></entry>";
    
    NSLog(@"Body %@",postBody);
    
    NSMutableData *data = [NSMutableData dataWithBytes:[postBody cString] length:[postBody length]];
    [postRequest setPostBody:data];
    [postRequest startSynchronous];
    
    if (postRequest.error) {
        NSLog(@"%@", [postRequest.error localizedDescription]);
    }
    else
    {
////        NSLog(@"Response String:   %@",[postRequest responseString]);
        float postTime = [postTimer timeIntervalSinceNow] * -1000.0;;
        NSLog(@"The total time for adding an entry is %fms",postTime);

    }

}

-(BOOL) textFieldShouldReturn:(UITextField *)textField 
{ 
    [textField resignFirstResponder]; 
    return YES; 
}

-(IBAction)deleteEntry:(id)sender
{
//    [ODPRequest enableXCSRF:YES];
//    ODPRequest *postRequest1 = [ODPRequest requestWithURL:[NSURL URLWithString:@"http://ldcig8p.wdf.sap.corp:50018/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection"]];
//    [postRequest1 setRequestMethod:@"GET"];
//    [postRequest1 addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
//    [postRequest1 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
//    [postRequest1 setUsername:@"perfios"];
//    [postRequest1 setPassword:@"perfios"];
//    [postRequest1 startSynchronous];

    NSDate *deleteTimer = [NSDate date];
    
    [ODPRequest enableXCSRF:YES];
    ODPRequest *deleteRequest = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/TravelagencyCollection('00007476')"]];
    [deleteRequest setRequestMethod:@"DELETE"];
    [deleteRequest addRequestHeader:@"Content-Type" value:@"application/atom+xml"];
    [deleteRequest addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [deleteRequest setUsername:@"perfios"];
    [deleteRequest setPassword:@"perfios"];
    [deleteRequest startSynchronous];
    
    if (deleteRequest.error) {
        NSLog(@"%@", [deleteRequest.error localizedDescription]);
    }
    else
    {
////        NSLog(@"Response String:   %@",[deleteRequest responseString]);
        float deleteTime = [deleteTimer timeIntervalSinceNow] * -1000.0;;
        NSLog(@"The total time for delete is %fms",deleteTime);

    }

    
}

-(void)getXcsrfToken:(ODPRequest *)request
{
    NSDictionary *headers = [request responseHeaders];        
    NSString *xCSRFToken = [headers objectForKey:@"X-CSRF-TOKEN"];
    xcsrfToken = xCSRFToken;
    NSLog(@"The token is %@",xCSRFToken);
}

@end

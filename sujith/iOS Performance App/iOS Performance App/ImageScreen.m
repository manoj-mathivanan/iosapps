//
//  ImageScreen.m
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ImageScreen.h"
#import "ODPRequest.h"

@interface ImageScreen ()

@end

@implementation ImageScreen
@synthesize imageView, flag;
UIImageView *imageView1;

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
    flag =YES;
    
    self.navigationItem.title = @"Upload/Download";
    
    self.navigationItem.rightBarButtonItem   = [[UIBarButtonItem alloc] initWithTitle:@"Home" style:UIBarButtonItemStylePlain target:self action:@selector(homeSelected:)];
    self.navigationItem.rightBarButtonItem.tintColor = [UIColor orangeColor];

    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Back" style:UIBarButtonItemStylePlain target:self action:@selector(backButtonSelected:)];
    self.navigationItem.leftBarButtonItem.tintColor = [UIColor orangeColor];

    
    
    // Do any additional setup after loading the view from its nib.
}

-(IBAction)backButtonSelected:(id)sender
{
    // [self.view removeFromSuperview];
    [self.navigationController popViewControllerAnimated:YES];
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

-(IBAction)downloadStart:(id)sender
{
    NSDate *downloadTimer = [NSDate date];
    [imageView1 removeFromSuperview];
    NSLog(@"Download Started");
    
    ODPRequest *postRequest2 = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/CarrierCollection('LH')/$value"]];
    [ODPRequest enableXCSRF:YES];
    [postRequest2 setRequestMethod:@"GET"];
    [postRequest2 addRequestHeader:@"Content-Type" value:@"image/jpeg"];
    [postRequest2 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    
    [postRequest2 setUsername:@"perfios"];
    [postRequest2 setPassword:@"perfios"];
    [postRequest2 startSynchronous];
    
    if (postRequest2.error) {
        NSLog(@"%@", [postRequest2.error localizedDescription]);
    }
    else
    {
//        NSLog(@"Response String:   %@",[postRequest2 responseString]);
        
    }
    
    NSMutableData *imgData = [[NSMutableData alloc]initWithData:[postRequest2 responseData]];
    imageView1 = [[UIImageView alloc] initWithFrame:CGRectMake(61, 68, 186, 149)];
    UIImage *image = [UIImage imageWithData: [NSData dataWithData:imgData]];
    [imageView1 setImage:image];
    [imageView1 startAnimating];
    [imageView addSubview:imageView1];
    
    float downloadTime = [downloadTimer timeIntervalSinceNow] * -1000.0;;
    NSLog(@"The total time for download is %fms",downloadTime);
    
    
    
    
}
-(IBAction)uploadStart:(id)sender
{
    NSDate *uploadTimer = [NSDate date];
    [imageView1 removeFromSuperview];
    
    UIImage *image;
    NSData *postData;
    NSLog(@"Upload Started");
    if(flag)
    {
        //image = [UIImage imageNamed:@"The-Dark-Knight.jpg"];
        image = [UIImage imageNamed:@"witcher2.png"];
        postData = UIImagePNGRepresentation(image);
        //postData = UIImageJPEGRepresentation (image,CGFLOAT_MIN);
        flag = NO;    
    }
    else 
    {
        image = [UIImage imageNamed:@"witcher2.png"];
        postData = UIImagePNGRepresentation(image);
        flag = YES;
        
    }
    
    ODPRequest *postRequest2 = [ODPRequest requestWithURL:[NSURL URLWithString:@"https://ldcig8p.wdf.sap.corp:44318/sap/opu/odata/iwfnd/RMTSAMPLEFLIGHT/CarrierCollection('LH')/$value"]];
    [postRequest2 setRequestMethod:@"PUT"];
    [postRequest2 addRequestHeader:@"Content-Type" value:@"image/jpeg"];
    [postRequest2 addRequestHeader:@"X-Requested-With" value:@"XMLHttpRequest"];
    [postRequest2 setPostBody:[NSMutableData dataWithData:postData]];
    [postRequest2 setUsername:@"perfios"];
    [postRequest2 setPassword:@"perfios"];
    [postRequest2 startSynchronous];
    
    if (postRequest2.error) {
        NSLog(@"%@", [postRequest2.error localizedDescription]);
    }
    else
    {
////        NSLog(@"Response String:   %@",[postRequest2 responseString]);
        
        float uploadTime = [uploadTimer timeIntervalSinceNow] * -1000.0;;
        NSLog(@"The total time for upload is %fms",uploadTime);

    }
    
    
}

-(IBAction)homeSelected:(id)sender
{
    [self.navigationController popToRootViewControllerAnimated:YES];
}


@end

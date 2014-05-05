//
//  AirhornViewController.m
//  Airhorn
//
//  Created by manoj on 4/15/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "AirhornViewController.h"

@interface AirhornViewController ()

@end

@implementation AirhornViewController
@synthesize hornSound;
-(IBAction)Button:(id)sender
{
    [hornSound play];
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    NSError *err = nil;
    NSBundle *bundle = [NSBundle
                        mainBundle];
    NSString *path = [bundle pathForResource: @"hornSound" ofType:@"m4a"];
    NSURL *url = [NSURL fileURLWithPath:path];
    hornSound = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&err];
//    if(err)
//    {
//        NSLog(@"%@",err);
//    }
    [hornSound prepareToPlay];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

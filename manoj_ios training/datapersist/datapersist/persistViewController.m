//
//  persistViewController.m
//  datapersist
//
//  Created by manoj on 4/19/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "persistViewController.h"

@interface persistViewController ()

@end

@implementation persistViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSUserDefaults *user = [NSUserDefaults standardUserDefaults];
    NSLog(@"%d",[user boolForKey:@"switch"]);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)switchonoff:(id)sender
{
    //NSLog(@"Status = %d",((UISwitch *)sender).on);
    NSLog(@"Status = %d",self.onoff.on);
    NSUserDefaults *user = [NSUserDefaults standardUserDefaults];
    [user setBool:self.onoff.on forKey:@"switch"];
    [user synchronize];
}

@end

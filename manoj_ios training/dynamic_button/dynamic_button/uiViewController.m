//
//  uiViewController.m
//  dynamic_button
//
//  Created by manoj on 4/18/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "uiViewController.h"

@interface uiViewController ()

@end

@implementation uiViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    button.frame = CGRectMake(100,100,100,100);
    [button setTitle:@"Submit" forState:UIControlStateNormal];
    button.tag = 1;
    [button addTarget:self action:@selector(actionsubmit:) forControlEvents:UIControlEventAllEvents];
    
    [self.view addSubview:button];
    
    UIView *view1 = [[UIView alloc]initWithFrame:CGRectMake(0, 300, self.view.frame.size.width, 50)];
    
    view1.backgroundColor = [UIColor blueColor];
    view1.tag = 100;
    [self.view addSubview:view1];
    
}
-(void)actionsubmit:(UIButton *)button
{
    NSLog(@"Button tag = %d",[button tag]);
    
    NSLog(@"%@",[self.view viewWithTag:100]);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

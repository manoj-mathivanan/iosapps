//
//  ViewController.h
//  auto
//
//  Created by i074667 on 6/10/13.
//  Copyright (c) 2013 i074667. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

-(IBAction)Button:(id)sender;
-(IBAction)Button2:(id)start;
-(IBAction)Button5:(id)merge;
-(IBAction)Button6:(id)clear;
-(IBAction)Button7:(id)retrieve;
-(IBAction)Button8:(id)server_auto;
-(IBAction)Button9:(id)l_update;
-(IBAction)Button10:(id)l_delete;
-(IBAction)Button11:(id)l_add;
-(IBAction)Button12:(id)delta;
@property(nonatomic,strong)IBOutlet UITextField *server;

@end

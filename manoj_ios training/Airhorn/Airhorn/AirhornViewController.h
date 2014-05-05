//
//  AirhornViewController.h
//  Airhorn
//
//  Created by manoj on 4/15/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface AirhornViewController : UIViewController

-(IBAction)Button:(id)sender;
@property(nonatomic,retain)AVAudioPlayer *hornSound;

@end

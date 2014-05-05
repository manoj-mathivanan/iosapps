//
//  ImageScreen.h
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ImageScreen : UIViewController
{
    IBOutlet UIImageView *imageView;
}


@property(nonatomic,retain) IBOutlet UIImageView *imageView;
@property(nonatomic) BOOL flag;

-(IBAction)downloadStart:(id)sender;
-(IBAction)uploadStart:(id)sender;

@end

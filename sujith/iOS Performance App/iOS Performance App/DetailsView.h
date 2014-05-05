//
//  DetailsView.h
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PostView.h"

@interface DetailsView : UIViewController<UITextFieldDelegate>
{
    PostView *m_postView;
    IBOutlet UINavigationBar *navBar;
}

@property(nonatomic,retain) PostView *m_postView;

//UI Controls
@property(nonatomic,retain)IBOutlet UILabel *field1;
@property(nonatomic,retain)IBOutlet UILabel *field2;
@property(nonatomic,retain)IBOutlet UILabel *field3;
@property(nonatomic,retain)IBOutlet UILabel *field4;
@property(nonatomic,retain)IBOutlet UILabel *field5;

@property(nonatomic,retain)IBOutlet UITextField *textField1;
@property(nonatomic,retain)IBOutlet UITextField *textField2;
@property(nonatomic,retain)IBOutlet UITextField *textField3;
@property(nonatomic,retain)IBOutlet UITextField *textField4;
@property(nonatomic,retain)IBOutlet UITextField *textField5;

@property(nonatomic,retain)IBOutlet UIImageView *imageView;

-(IBAction)backButtonSelected:(id)sender;
-(IBAction)addEntrySelected:(id)sender;
-(IBAction)update:(id)sender;
-(IBAction)imageDwnload:(id)sender;
@end

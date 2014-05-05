//
//  PostView.h
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ImageScreen.h"



@interface PostView : UIViewController<UITextFieldDelegate>
{
    UITextField *textField1;
}

@property(nonatomic,retain) ImageScreen *m_imageScreen;

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

@property(nonatomic,retain)NSString *xcsrfToken;


-(IBAction)backButtonSelected:(id)sender;
-(IBAction)addEntry:(id)sender;
-(IBAction)deleteEntry:(id)sender;
@end

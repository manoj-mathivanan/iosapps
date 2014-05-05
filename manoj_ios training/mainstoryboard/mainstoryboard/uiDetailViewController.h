//
//  uiDetailViewController.h
//  mainstoryboard
//
//  Created by manoj on 4/19/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface uiDetailViewController : UIViewController

@property (strong, nonatomic) id detailItem;

@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;
@end

//
//  ViewController.h
//  iOS Performance App
//
//  Created by Prathap, Sujith on 7/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DetailsView.h"
#import "ODPUserManager.h"

@interface ViewController : UIViewController<UITableViewDelegate, UITableViewDataSource>
{
    DetailsView *m_detailViewController;
    NSString *l_serviceDocument;
    IBOutlet UITableView *m_dataTableView;
    //NSMutableArray *agencyNumber;
}
@property(nonatomic,retain) NSMutableArray *agencyNumber;
@property(nonatomic,retain) NSMutableArray *agencyName;
@property(nonatomic,retain) NSMutableArray *country;
@property(nonatomic,retain) NSMutableArray *phone;
@property(nonatomic,retain) NSMutableArray *url;

@property(nonatomic,retain) NSMutableArray* array;
@property(nonatomic,retain) DetailsView *m_detailViewController;
@property(nonatomic,retain)  NSString *l_response;
@property(nonatomic,retain)  NSData *l_responseData;
@end

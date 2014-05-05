//
//  calViewController.m
//  calculator
//
//  Created by manoj on 4/17/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "calViewController.h"

@interface calViewController ()

@end

@implementation calViewController
@synthesize text;

NSInteger a=0,b=0,z=0,op=0,k=0;
-(IBAction)Button:(id)sender{
    switch ([sender tag]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(k==1)
            {
                text.text = [text.text stringByAppendingString: [NSString stringWithFormat:@"%d", [sender tag] ]];
            }
            else
            {
                k=1;
                text.text = [NSString stringWithFormat:@"%d", [sender tag] ];
            }
            break;
        case 10:
            if(z==1)
            {
                b=[text.text integerValue];
                a=a+b;
                text.text = [NSString stringWithFormat:@"%d", a ];
            }
            else
            {
                z=1;
                a=[text.text integerValue];
            }
            k=1;
             op=10;
            break;
        case 11:
            if(z==1)
            {
                b=[text.text integerValue];
                a=a-b;
                text.text = [NSString stringWithFormat:@"%d", a ];
            }
            else
            {
                z=1;
                a=[text.text integerValue];
            }
            k=1;
            op=11;
            break;
        case 12:
            b=[text.text integerValue];
            a=a*b;
            text.text = [NSString stringWithFormat:@"%d", a ];
            op=12;
            z=0;
            break;
        case 13:
            b=[text.text integerValue];
            a=a/b;
            text.text = [NSString stringWithFormat:@"%d", a ];
            op=13;
            z=0;
            break;
        case 14:
            z=0;
            k=1;
            b=[text.text integerValue];
            switch (op) {
                case 10:
                    a=a+b;
                    break;
                case 11:
                    a=a-b;
                    break;
                case 12:
                    a=a*b;
                    break;
                case 13:
                    a=a/b;
                    break;
                default:
                    break;
            }
            text.text = [NSString stringWithFormat:@"%d", a ];
            break;
        case 15:
            
        {
            NSMutableString *str = [text.text mutableCopy];
            
            NSRange t = NSMakeRange(([str length] - 1), 1);
                    [str deleteCharactersInRange:t];
            
            text.text = str;
            
        }
            break;
        case 16:
            text.text=@"";
            break;
            
        default:
            break;
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

//
//  Tiger.m
//  Inheritance
//
//  Created by manoj on 4/16/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "Tiger.h"

@implementation Tiger
-(NSString *)speak
{
    return @"tiger sound..";
}
-(void)identify
{
    NSLog(@"I say ,'%@', but my ancestor says, '%@',",[self speak],[super speak]);
}
@end

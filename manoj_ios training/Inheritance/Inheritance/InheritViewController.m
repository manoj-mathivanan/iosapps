//
//  InheritViewController.m
//  Inheritance
//
//  Created by manoj on 4/16/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "InheritViewController.h"
#import "SaberToothTigerKitten.h"

@interface InheritViewController ()

@end

@implementation InheritViewController

- (void)viewDidLoad
{
    Feline *afeline = [Feline new];
    Tiger *atiger = [Tiger new];
    SaberToothTiger *asabertooth = [SaberToothTiger new];
    SaberToothTigerKitten *aSTKitten = [SaberToothTigerKitten new];
    Tiger *anImposter= (Tiger *)[SaberToothTigerKitten new];
    
    NSLog(@"The feline says '%@' ",[afeline speak]);
    NSLog(@"The Tiger says '%@' ",[atiger speak]);
    NSLog(@"Tiger identity");
    [atiger identify];
    NSLog(@"The SaberTooth says '%@' ",[asabertooth speak]);
    NSLog(@"SabertoothTiger identity");
    [asabertooth identify];
    NSLog(@"The Saberkitten says '%@' ",[aSTKitten speak]);
    NSLog(@"Saberkitten identity");
    [aSTKitten identify];
    NSLog(@"imposter identity");
    [anImposter identify];

    
    
    
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end

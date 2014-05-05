//
//  ViewController.m
//  tableViewControllerDisplay
//
//  Created by M, Anil Chopra on 4/18/13.
//  Copyright (c) 2013 SAP. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    allData = [[NSMutableArray alloc]initWithObjects:@"First Cell",@"Second Cell",nil];
    
    secondData = [[NSMutableArray alloc]initWithObjects:@" Cell 1",@"Cell 2",@"Cell 3",nil];
    
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
  //  UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:<#(NSString *)#>]
    NSString *reuseIdentifier = @"Cell";
    
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:reuseIdentifier];
     if (cell == nil) {
         
         cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reuseIdentifier];
     }
    
    if(indexPath.section == 0)
    {
       cell.textLabel.text = [allData objectAtIndex:indexPath.row];    
    }
    else
    cell.textLabel.text = [secondData objectAtIndex:indexPath.row];
    return cell;
    
    
    
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 2;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if(section == 0)
     return [allData count];
    else
        return [secondData count];
    
    
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    if(section == 0)
    {
        return @"Header 1";
    }
    else
    {
        return  @"Header 2";
    }

}
@end

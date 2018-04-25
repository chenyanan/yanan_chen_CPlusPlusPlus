//
//  ViewController.m
//  C+++
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#import "ViewController.h"

#import "anotherViewController.h"

#import "TYPE.h"
#import "makemodel.hpp"
#import "SIMPLE.hpp"
#import "GETSET.hpp"
#import "WILLDID.hpp"

#import "Anotherrr.hpp"
#import "SPR.h"

#import "rank.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"push" style:UIBarButtonItemStylePlain target:self action:@selector(pushViewController)];
    
    
//    SIMPLE::make("/Users/chenyanan/Desktop/xixixixi/", "chenyanan", "another", VSTR(), {"_name", "Age", "_birth", "Sex", "_didClick"}, {"STR", "INT", "STR", "PTR", "Vblk"}, "RCT");
//    
//    GETSET::make("/Users/chenyanan/Desktop/xixixixi/", "chenyanan", "anotherr", VSTR(), {"name", "Age", "birth", "Sex", "didClick"}, {"STR", "INT", "STR", "PTR", "Vblk"}, "RCT");
//    
//    WILLDID::make("/Users/chenyanan/Desktop/xixixixi/", "chenyanan", "anotherrr", VSTR(), {"name", "Age", "birth", "Sex", "didClick"}, {"STR", "INT", "STR", "PTR", "Vblk"}, "RCT");
    
//    int hehe[] = {9,8,8,8,8,8,8,3,2};
////    int hehe [] = {9,8,7,6,5,4,3,2,1};
//    int xixi[9];
////    rank1(hehe, 9, xixi);
//    
//    for (int i = 0; i < 9; i++) {
//        printf("xixi[%d] = %d\n", i, xixi[i]);
//    }

    
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)pushViewController {
    anotherViewController *controller = [[anotherViewController alloc] init];
    [self.navigationController pushViewController:controller animated:YES];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end

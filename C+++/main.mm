//
//  main.m
//  C+++
//
//  Created by chenyanan on 2017/1/4.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#include <utility>

int main(int argc, char * argv[]) {
    @autoreleasepool {
        typedef std::pair<int,int> myPairType;
        myPairType lala[2];
        
        lala[0] = std::pair<int,int>(1,1);
        lala[0] = std::pair<int,int>(2,2);
        
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

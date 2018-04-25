//
//  anotherViewController.m
//  C+++
//
//  Created by chenyanan on 2017/1/5.
//  Copyright © 2017年 chenyanan. All rights reserved.
//

#import "anotherViewController.h"
#import "SPR.h"
#import "Another.hpp"
//#import "arrayList.hpp"
//#import "vectorList.hpp"
//
//#import "matrix.hpp"
//#import "chain.hpp"
//#import "stack.hpp"
//#import "queue.hpp"
//
//#import "dictionary.hpp"
//#import "pairNode.hpp"
//#import "sortedChain.hpp"
//#import "skipNode.hpp"
//#import "skipList.hpp"
//#import "hash.hpp"
//#import "hashTable.hpp"
//#import "hashChain.hpp"
//#import "binaryTreeNode.hpp"
//#import "binaryTree.hpp"
//#import "linkedBinaryTree.hpp"
//#import "maxPriorityQueue.hpp"
//#import "maxHblt.hpp"
//#import "maxHeap.hpp"
//#import "bsTree.hpp"
//#import "indexedBSTree.hpp"
//#import "binarySearchTree.hpp"
//#import "dBinarySearchTree.hpp"
//#import "edge.hpp"
//#import "binNode.hpp"
//#import "fastUnionFind.hpp"
//#import "vertexIterator.hpp"
//#import "graph.hpp"
//#import "adjacencyWDigraph.hpp"
//#import "linkedDigraph.hpp"

//#import "selectionSort.hpp"
//#import "bubbleSort.hpp"
//#import "test.hpp"
//#import "anotherText.hpp"
//#import "sortedArray.hpp"
//#import "skipList.hpp"

#include <string>
#include "completeWinnerTree.hpp"

#import "linkedBinaryTree.hpp"

extern const int xixi = 0;

@interface anotherViewController ()
@property (nonatomic, strong) UIButton *myButton;
@property (nonatomic,   copy) Vblk myBlock;
@end

@implementation anotherViewController

- (void)myButtonTapped:(UIButton *)sender {
    
    NSLog(@"before");
    
    _myBlock();
    
    NSLog(@"after");
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self.myButton addTarget:self action:@selector(myButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
    
    SPR<Another> xixi(Another("china", 1, "America", NULL, ^{
        NSLog(@"xixi haha hehe");
    }));
    
    
    _myBlock = ^{
        (*xixi)._didClick();
    };
    
    int player[] = {3,5,6,7,20,8,2,9};
    completeWinnerTree<int> tree(player, 9);
    
    // Do any additional setup after loading the view.
}

- (UIButton *)myButton {
    if (!_myButton) {
        _myButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _myButton.frame = CGRectIntegral(CGRectMake((CGRectGetWidth([UIScreen mainScreen].bounds) - 100.0f) * 0.5f, (CGRectGetHeight([UIScreen mainScreen].bounds) - 100.0f) * 0.5f, 100.0f, 100.0f));
        [_myButton setTitle:@"myButton" forState:UIControlStateNormal];
        [_myButton setTitle:@"myButton" forState:UIControlStateHighlighted];
        [_myButton setBackgroundColor:[UIColor yellowColor]];
        [self.view addSubview:_myButton];
    }
    return _myButton;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    NSLog(@"anotherViewController dealloc");
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end

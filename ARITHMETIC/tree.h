/***********************************************
   function:该问头文件主要写一下简单的树算法
   author：Demon
   Time:2017/11/12
***********************************************/
#pragma once
#include<iostream>
#include<Windows.h>
#include<memory>
using namespace std;
#define TREE_NUM 6
struct tree
{
	int tree_data;
	tree*lchild;
	tree*rchild;
};
struct no_r_struct
{
	tree*link;
	bool flag;
};
using sp_ptr_tree = shared_ptr<tree>;

class handle_tree
{
  public:
	  handle_tree(tree*p,tree*pB,tree*pC,tree*pD,tree*pE,tree*pF);
	  ~handle_tree() { cout << "析构函数执行,智能指针释放" << endl; }

  public:
	  sp_ptr_tree  get_sp_root();
     //递归实现,先,中,后遍历
	 void r_x_tra(tree*p);
	 void r_z_tra(tree*p);
	 void r_h_tra(tree*p);
	 //非递归实现,先，中，后
	 void no_r_x_tra(tree*p);
	 void no_r_z_tra(tree*p);
	 void no_r_h_tra(tree*p);

private:
	tree*stack[TREE_NUM];
	no_r_struct no_r_h_stack[TREE_NUM];
	int top;
	sp_ptr_tree sp_root;
	sp_ptr_tree sp_B;
	sp_ptr_tree sp_C;
	sp_ptr_tree sp_D;
	sp_ptr_tree sp_E;
	sp_ptr_tree sp_F;
};
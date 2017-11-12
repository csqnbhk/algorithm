#include"tree.h"
handle_tree::handle_tree(tree*p,tree*pB, tree*pC, tree*pD, tree*pE, tree*pF)
	        :sp_root(p),sp_B(pB),sp_C(pC),sp_D(pD),sp_E(pE),sp_F(pF)
{
	

	//特别注意这里每个初始化的顺序
	sp_F->lchild = nullptr;
	sp_F->rchild = nullptr;
	sp_F->tree_data = 6;

	sp_E->lchild = nullptr;
	sp_E->rchild = nullptr;
	sp_E->tree_data = 5;

	sp_D->lchild = nullptr;
	sp_D->rchild = nullptr;
	sp_D->tree_data = 4;

	sp_C->lchild = sp_E.get();
	sp_C->rchild = sp_F.get();
	sp_C->tree_data = 3;

	sp_B->lchild = nullptr;
	sp_B->rchild = sp_D.get();
	sp_B->tree_data = 2;

	this->sp_root->lchild = sp_B.get();
	this->sp_root->rchild = sp_C.get();
	this->sp_root->tree_data = 1;

	//
	top = 0;
	
}

sp_ptr_tree handle_tree::get_sp_root()
{
	return this->sp_root;
}
//递归实现，先,中,后遍历
void handle_tree::r_x_tra(tree*p)
{
	if (p != nullptr)
	{
		cout << p->tree_data << "  ";
		r_x_tra(p->lchild);
		r_x_tra(p->rchild);
	}
}
void handle_tree::r_z_tra(tree*p)
{
	if (p != nullptr)
	{
		r_z_tra(p->lchild);
		cout << p->tree_data << "  ";
		r_z_tra(p->rchild);
	}
}
void handle_tree::r_h_tra(tree*p)
{
	if (p != nullptr)
	{
		r_h_tra(p->lchild);
		r_h_tra(p->rchild);
		cout << p->tree_data << "  ";
	}
}
//非递归实现,先，中，后
void handle_tree::no_r_x_tra(tree*p)
{ 
	while (p != nullptr || top != 0)
	{
		while (p != nullptr)
		{
			if (top >= TREE_NUM)
			{
				cout << "栈溢出" << endl;
				return;
			}
			this->stack[top++] = p;
			cout << p->tree_data << "  ";
			p = p->lchild;
		}
		if (top != 0)
		{
			p = this->stack[--top];
			p = p->rchild;
		}

	}
}
void handle_tree::no_r_z_tra(tree*p)
{
	while (p != nullptr || top != 0)
	{
		while (p != nullptr)
		{
			if (top >= TREE_NUM)
			{
				cout << "栈溢出" << endl;
				return;
			}
			this->stack[top++] = p;
			p = p->lchild;

		}
		if (top != 0)
		{
			p = this->stack[--top];
			cout << p->tree_data << "  ";
			p = p->rchild;
		}

	}
}
void handle_tree::no_r_h_tra(tree*p)
{
	if (p == nullptr)
		return;
	bool sign = false;
	while (p != nullptr || top != 0)
	{
		if (p != nullptr)
		{
			++top;
			this->no_r_h_stack[top].link = p;
			this->no_r_h_stack[top].flag = true;
			p = p->lchild;
			
		}
		else
		{
			p = this->no_r_h_stack[top].link;
			sign = this->no_r_h_stack[top].flag;
			--top;
			if (sign == true)
			{
				++top;
				this->no_r_h_stack[top].link = p;
				this->no_r_h_stack[top].flag = false;
				p = p->rchild;
			}
			else
			{
				cout << p->tree_data << "  ";
				p = nullptr;
			}
	   }
	}

	
}
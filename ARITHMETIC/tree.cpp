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
	/*
	 ★★★特别注意：
	 tree*stack[TREE_NUM];声明。this->stack[top]->rchild = p;因为对是整体赋值，所以没问题。
	 no_r_struct*no_r_h_stack[TREE_NUM];这样子申明，赋值时确是这样子this->no_r_h_stack[top]->link = p;
	 对里面成员先赋值,其实该指针还没有初始化。不能这样子搞。
	 注意，对于一个在栈中分配未初始化的指针，赋值时只能整体先赋值,当有了指向的空间，才可以对其成员函数/变量赋值。
	（例如结构体，不能该指针指向的成员先赋值，(而该指针其实没有初始化）否则出现访问冲突

	★★:
	内存中常见异常值的解释（比如0xcccccccc、0xcdcdcdcd和 0xfeeefeee 异常值 ）
	对于0xcccccccc和0xcdcdcdcd，在 Debug 模式下，VC 会把未初始化的栈内存上的指针全部填成 0xcccccccc ，
	当字符串看就是 “烫烫烫烫……”；会把未初始化的堆内存上的指针全部填成 0xcdcdcdcd，当字符串看就是 “屯屯屯屯……”。
	那么调试器为什么要这么做呢？VC的DEBUG版会把未初始化的指针自动初始化为0xcccccccc或0xcdcdcdcd，而不是就让取随机值，
	那是为了方便我们调试程序，如果野指针的初值不确定，那么每次调试同一个程序就可能出现不一样的结果，比如这次程序崩掉，
	下次却能正常运行，这样显然对我们解bug是非常不利的，所以自动初始化的目的是为了让我们一眼就能确定我们使用了未初始化的野指针了。
	对于0xfeeefeee，是用来标记堆上已经释放掉的内存。注意，如果指针指向的内存被释放了，变量变量本身的地址如未做改动，
	还是之前指向的内存的地址。如果该指针是一个类的指针，并且类中包含有指针变量，则内存被释放后（对于C++类，通常是执行delete操作），
	类中的指针变量就会被赋值为0xfeeefeee。如果早调试代码过程中，发现有值为0xfeeefeee的指针，就说明对应的内存被释放掉了，
	我们的代码已经出问题了。

	关于VC 中 debug和Release模式下的变量初始化问题
	大家都知道，debug跟release在初始化变量时所做的操作是不同的，debug是将每个字节位都赋成0xcc，
	而release的赋值近似于随机(我想是直接从内存中分配的，没有初始化过)。这样就明确了，
	如果你的程序中的某个变量没被初始化就被引用，就很有可能出现异常：用作控制变量将导致流程导向不一致；
	用作数组下标将会使程序崩溃；更加可能是造成其他变量的不准确而引起其他的错误。
	所以在声明变量后马上对其初始化一个默认的值是最简单有效的办法，否则项目大了你找都没地方找。
	代码存在错误在debug方式下可能会忽略而不被察觉到，如debug方式下数组越界也大多不会出错，
	在 release中就暴露出来了，这个找起来就比较难了（参考：http://bbs.csdn.net/topics/350212712）

	*/
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
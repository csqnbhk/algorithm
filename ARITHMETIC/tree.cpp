#include"tree.h"
handle_tree::handle_tree(tree*p,tree*pB, tree*pC, tree*pD, tree*pE, tree*pF)
	        :sp_root(p),sp_B(pB),sp_C(pC),sp_D(pD),sp_E(pE),sp_F(pF)
{
	

	//�ر�ע������ÿ����ʼ����˳��
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
//�ݹ�ʵ�֣���,��,�����
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
//�ǵݹ�ʵ��,�ȣ��У���
void handle_tree::no_r_x_tra(tree*p)
{ 
	/*
	 �����ر�ע�⣺
	 tree*stack[TREE_NUM];������this->stack[top]->rchild = p;��Ϊ�������帳ֵ������û���⡣
	 no_r_struct*no_r_h_stack[TREE_NUM];��������������ֵʱȷ��������this->no_r_h_stack[top]->link = p;
	 �������Ա�ȸ�ֵ,��ʵ��ָ�뻹û�г�ʼ�������������Ӹ㡣
	 ע�⣬����һ����ջ�з���δ��ʼ����ָ�룬��ֵʱֻ�������ȸ�ֵ,������ָ��Ŀռ䣬�ſ��Զ����Ա����/������ֵ��
	������ṹ�壬���ܸ�ָ��ָ��ĳ�Ա�ȸ�ֵ��(����ָ����ʵû�г�ʼ����������ַ��ʳ�ͻ

	���:
	�ڴ��г����쳣ֵ�Ľ��ͣ�����0xcccccccc��0xcdcdcdcd�� 0xfeeefeee �쳣ֵ ��
	����0xcccccccc��0xcdcdcdcd���� Debug ģʽ�£�VC ���δ��ʼ����ջ�ڴ��ϵ�ָ��ȫ����� 0xcccccccc ��
	���ַ��������� ���������̡����������δ��ʼ���Ķ��ڴ��ϵ�ָ��ȫ����� 0xcdcdcdcd�����ַ��������� ���������͡�������
	��ô������ΪʲôҪ��ô���أ�VC��DEBUG����δ��ʼ����ָ���Զ���ʼ��Ϊ0xcccccccc��0xcdcdcdcd�������Ǿ���ȡ���ֵ��
	����Ϊ�˷������ǵ��Գ������Ұָ��ĳ�ֵ��ȷ������ôÿ�ε���ͬһ������Ϳ��ܳ��ֲ�һ���Ľ����������γ��������
	�´�ȴ���������У�������Ȼ�����ǽ�bug�Ƿǳ������ģ������Զ���ʼ����Ŀ����Ϊ��������һ�۾���ȷ������ʹ����δ��ʼ����Ұָ���ˡ�
	����0xfeeefeee����������Ƕ����Ѿ��ͷŵ����ڴ档ע�⣬���ָ��ָ����ڴ汻�ͷ��ˣ�������������ĵ�ַ��δ���Ķ���
	����֮ǰָ����ڴ�ĵ�ַ�������ָ����һ�����ָ�룬�������а�����ָ����������ڴ汻�ͷź󣨶���C++�࣬ͨ����ִ��delete��������
	���е�ָ������ͻᱻ��ֵΪ0xfeeefeee���������Դ�������У�������ֵΪ0xfeeefeee��ָ�룬��˵����Ӧ���ڴ汻�ͷŵ��ˣ�
	���ǵĴ����Ѿ��������ˡ�

	����VC �� debug��Releaseģʽ�µı�����ʼ������
	��Ҷ�֪����debug��release�ڳ�ʼ������ʱ�����Ĳ����ǲ�ͬ�ģ�debug�ǽ�ÿ���ֽ�λ������0xcc��
	��release�ĸ�ֵ���������(������ֱ�Ӵ��ڴ��з���ģ�û�г�ʼ����)����������ȷ�ˣ�
	�����ĳ����е�ĳ������û����ʼ���ͱ����ã��ͺ��п��ܳ����쳣���������Ʊ������������̵���һ�£�
	���������±꽫��ʹ������������ӿ�����������������Ĳ�׼ȷ�����������Ĵ���
	�������������������϶����ʼ��һ��Ĭ�ϵ�ֵ�������Ч�İ취��������Ŀ�������Ҷ�û�ط��ҡ�
	������ڴ�����debug��ʽ�¿��ܻ���Զ��������������debug��ʽ������Խ��Ҳ��಻�����
	�� release�оͱ�¶�����ˣ�����������ͱȽ����ˣ��ο���http://bbs.csdn.net/topics/350212712��

	*/
	while (p != nullptr || top != 0)
	{
		while (p != nullptr)
		{
			if (top >= TREE_NUM)
			{
				cout << "ջ���" << endl;
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
				cout << "ջ���" << endl;
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
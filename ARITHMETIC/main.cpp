#include"tree.h"
int main()
{
	tree*tree_A = new tree;
	tree*tree_B = new tree;
	tree*tree_C = new tree;
	tree*tree_D = new tree;
	tree*tree_E = new tree;
	tree*tree_F = new tree;
	shared_ptr<handle_tree> my_handle_tree(new handle_tree(tree_A, tree_B, tree_C, tree_D, tree_E, tree_F));

	cout << "先序遍历如下:" << endl;
	my_handle_tree->r_x_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "中序遍历如下:" << endl;
	my_handle_tree->r_z_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "后序遍历如下:" << endl;
	my_handle_tree->r_h_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "***********************非递归遍历********************" << endl;
	cout << "非递归,先序遍历:" << endl;
	my_handle_tree->no_r_x_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "非递归,中序遍历:" << endl;
	my_handle_tree->no_r_z_tra(my_handle_tree->get_sp_root().get());
	cout << endl;
	
	cout << "非递归,后序遍历:" << endl;
	my_handle_tree->no_r_h_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	return 0;
}
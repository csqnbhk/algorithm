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

	cout << "�����������:" << endl;
	my_handle_tree->r_x_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "�����������:" << endl;
	my_handle_tree->r_z_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "�����������:" << endl;
	my_handle_tree->r_h_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "***********************�ǵݹ����********************" << endl;
	cout << "�ǵݹ�,�������:" << endl;
	my_handle_tree->no_r_x_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	cout << "�ǵݹ�,�������:" << endl;
	my_handle_tree->no_r_z_tra(my_handle_tree->get_sp_root().get());
	cout << endl;
	
	cout << "�ǵݹ�,�������:" << endl;
	my_handle_tree->no_r_h_tra(my_handle_tree->get_sp_root().get());
	cout << endl;

	return 0;
}
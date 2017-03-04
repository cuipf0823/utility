//
//2017/2/25
//记录树的相关操作
//

#ifndef COMMON_TREE_OP_H
#define COMMON_TREE_OP_H

/*
 *  二叉树相关
 */

#include <iostream>

/*
 * 构造二叉树
 * 如：根据前序遍历和中序遍历的结构构造二叉树，使用递归方式
 */
struct BinaryTreeNode
{
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
};

BinaryTreeNode* ConstructCode(int* start_pre_order, int* end_pre_order, int* start_in_order, int* end_in_order)
{
    //前序遍历的第一个数字是根节点的值
    int root_value = start_in_order[0];
    BinaryTreeNode* root = new BinaryTreeNode();
    root->value = root_value;
    root->left = root->right = nullptr;
    std::cout << root->value << '\t';
    if (start_pre_order == end_pre_order)
    {
        if (start_in_order == end_in_order && *start_in_order == *start_pre_order)
        {
            return root;
        }
        else
        {
            //invalid input
            return nullptr;
        }
    }
    //在中序遍历中找到根节点的值
    int* root_in_order = start_in_order;
    while (root_in_order <= end_in_order && *root_in_order != root_value)
    {
        ++root_in_order;
    }

    unsigned long left_length = root_in_order - start_in_order;
    int* left_preorder_end = start_pre_order + left_length;
    if (left_length > 0)
    {
        //构建左子树
        root->left = ConstructCode(start_pre_order + 1, left_preorder_end, start_in_order, root_in_order - 1);
    }

    if (left_length < end_pre_order - start_pre_order)
    {
        //构建右子树
        root->right = ConstructCode(left_preorder_end + 1, end_pre_order, root_in_order + 1, end_in_order);
    }
    return root;
}

BinaryTreeNode* Construct(int* pre_order, int* in_order, int length)
{
    if (pre_order == nullptr || in_order == nullptr || length <= 0)
    {
        return nullptr;
    }
    return ConstructCode(pre_order, pre_order + length - 1, in_order, in_order + length - 1);
}

/*
 * binary tree postorder traversal print
 */
void PostOrderPrint(BinaryTreeNode* root)
{
    if (root != nullptr)
    {
        PostOrderPrint(root->left);
        PostOrderPrint(root->right);
        std::cout << root->value << "\t";
    }
}

/*
 * 二叉树判断是否含有该子树
 * 使用递归更加直观
 */
bool DoseTree1HaveTree2(const BinaryTreeNode* tree1, const BinaryTreeNode* tree2)
{
    if (tree2 == nullptr)
    {
        return true;
    }
    if (tree1 == nullptr)
    {
        return false;
    }
    if (tree1->value != tree2->value)
    {
        return false;
    }
    return DoseTree1HaveTree2(tree1->right, tree2->right) && DoseTree1HaveTree2(tree1->left, tree2->left);
}
bool HasSubTree(const BinaryTreeNode* tree, const BinaryTreeNode* sub_tree)
{
    bool ret = false;
    //根节点判断
    if (tree->value == sub_tree->value)
    {
        ret = DoseTree1HaveTree2(tree, sub_tree);
    }
    //判断左子树
    if (!ret)
    {
        ret = HasSubTree(tree->left, sub_tree);
    }
    //判断右子树
    if (!ret)
    {
        ret = HasSubTree(tree->right, sub_tree);
    }
    return ret;
}

/*
 * 二叉树的镜像
 * 1. 对于根节点不动，具有左右子树的结点，左右子树互换，到叶子结点结束；
 */
void MirrorReverse(BinaryTreeNode* proot)
{
    if (proot == nullptr)
    {
        return;
    }
    if (proot->left == nullptr && proot->right == nullptr)
    {
        return;
    }
    BinaryTreeNode* ptemp = proot->left;
    proot->left = proot->right;
    proot->right = ptemp;
    if (proot->left != nullptr)
    {
        MirrorReverse(proot->left);
    }
    if (proot->right)
    {
        MirrorReverse(proot->right);
    }
}



void TestTreeOP()
{
    int pre_order[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
    int in_order[]  = { 4, 7, 2, 1, 5, 3, 8, 6 };
    int length = sizeof(pre_order) / sizeof(pre_order[0]);
    BinaryTreeNode* post_order = Construct(pre_order, in_order, length);
    PostOrderPrint(post_order);
    //binary tree delete
}

#endif //COMMON_TREE_OP_H

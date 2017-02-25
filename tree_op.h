//
//2017/2/25
//记录树的相关操作
//

#ifndef COMMON_TREE_OP_H
#define COMMON_TREE_OP_H

/*
 *  二叉树相关
 */

#include <tkDecls.h>

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

#endif //COMMON_TREE_OP_H

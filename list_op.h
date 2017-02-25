//
// 2017/2/25.
// 记录链表的相关操作
//

#ifndef COMMON_LIST_OP_H_H
#define COMMON_LIST_OP_H_H

#include <assert.h>
#include <iostream>
#include <stack>

/*
 * 链表相关
 */

struct ListNode
{
    int value;
    ListNode* next;
};

/*
 * 在链表尾部添加新节点
 */
void AddList(ListNode** head, int value)
{
    ListNode* node = new ListNode();
    assert(node != nullptr);
    node->value = value;
    node->next = nullptr;
    if (*head == nullptr)
    {
        *head = node;
    }
    else
    {
        ListNode* tmp_node = *head;
        while (tmp_node->next != nullptr)
        {
            tmp_node = tmp_node->next;
        }
        tmp_node->next = node;
    }
}

/*
 * 链表的删除 时间复杂度O(n)
 */
void RemoveListNode(ListNode** head, int value)
{
    if (head == nullptr || *head == nullptr)
    {
        return;
    }
    ListNode* node_del = nullptr;
    if ((*head)->value == value)
    {
        node_del = *head;
        *head = (*head)->next;
    }
    else
    {
        ListNode* node = *head;
        while (node->next != nullptr && node->next->value != value)
        {
            node = node->next;
        }
        if (node->next != nullptr && node->next->value == value)
        {
            node_del = node->next;
            node->next = node->next->next;
        }
    }
    if (node_del != nullptr)
    {
        delete node_del;
        node_del = nullptr;
    }
}

/*
 * 获取链表的长度
 */

size_t GetListLength(ListNode* head)
{
    size_t len = 0;
    while (head != nullptr)
    {
        ++len;
        head = head->next;
    }
    return len;
}

/*
 * 链表打印
 */
void ListPrint(ListNode* head)
{
    while (head != nullptr)
    {
        std::cout << head->value << '\t';
        head = head->next;
    }
    std::cout << std::endl;
}

void ReversePrintList(ListNode* list)
{
    std::stack<ListNode*> nodes;
    ListNode* node = list;
    while(node != nullptr)
    {
        nodes.push(node);
        node = node->next;
    }
    while (!nodes.empty())
    {
        node = nodes.top();
        std::cout << node->value << '\t';
        nodes.pop();
    }
    std::cout << std::endl;
}

void TestListOP()
{
    ListNode* list = nullptr;
    for (int idx = 0; idx < 8; ++idx)
    {

        AddList(&list, idx);
    }
    ListPrint(list);
    ReversePrintList(list);
};

#endif //COMMON_LIST_OP_H_H

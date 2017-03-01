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
 *  单链表中删除某个元素要求时间复杂度为O(1)
 *  思想：只有一个元素 直接删除
 *       删除结点在尾部，需要遍历
 *       在列表中，next的元素赋值给删除结点，删除next结点即可，效果是一样的
 */
bool DeleteListNode(ListNode** head, ListNode* del_node)
{
    if (head == nullptr || del_node == nullptr)
    {
        //para invaild
        return false;
    }
    if (*head == del_node)
    {
        delete del_node;
        del_node = nullptr;
        *head = nullptr;
    }

    if (del_node->next != nullptr)
    {
        ListNode* node = del_node->next;
        del_node->next = node->next;
        del_node->value = node->value;
        delete node;
        node = nullptr;
    }
    else
    {
        //删除元素在链表尾部，此时只能使用从头开始便利的方式删除了
        ListNode* node = (*head)->next;
        while (node->next != del_node)
        {
            node = node->next;
        }
        node->next = nullptr;
        delete del_node;
        del_node = nullptr;
    }
    return true;
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

/*
 * 获取链表中倒数第K个结点
 * 思想：1. 先获取链表的总长度，再根据总长度和K来获取结点位置，时间复杂度O(n*2),不可取
 *      2. 使用双指针遍历链表（遍历单链表的一种方式）；
 */
ListNode* FindNodeFromTail(ListNode* list, uint32_t k)
{
    if (list == nullptr || k == 0)
    {
        //parameter invalid
        return nullptr;
    }
    ListNode* node = list;
    for (uint32_t index = 1; index < k; ++index)
    {
        if (node->next != nullptr)
        {
            node = node->next;
        }
        else
        {
            return nullptr;
        }
    }
    ListNode* pdata = list;
    while (node->next != nullptr)
    {
        node = node->next;
        pdata = pdata->next;
    }
    return pdata;
}


/*
*  单链表的逆转
*  需要三个指针：1. 指向node一个指针 指向node->next一个指针，指向逆序队列一个指针 
*/
ListNode* ListReverse(ListNode* list)
{
	ListNode* reverse = nullptr;
	ListNode* node = list;
	ListNode* prev = nullptr;
	while (node != nullptr)
	{
		ListNode* pnext = node->next;
		if (pnext == nullptr)
		{
			//注意这里不能漏写
			node->next = prev;
			reverse = node;
		}
		node->next = prev;
		prev = node;
		node = pnext;
	}
	return reverse;
}

/*
* 
*/
ListNode* CombineList(ListNode* list1, ListNode* list2)
{
	if (list1 == nullptr)
	{
		return list2;
	}
	if (list2 == nullptr)
	{
		return list1;
	}
	ListNode* ret = list;
	ListNode* node1 = list1;
	ListNode* node2 = list2;
	ListNode* ret_head = nullptr;
	while (node1 != nullptr && node2 != nullptr)
	{
		if (node1->value < node2->value)
		{
			ret->next = node1;
			node1 = node1->next;
			
			if (ret == nullptr)
			{
				ret = node1;
			}
			else
			{
				ret->next = node1;
				ret = ret->next;
			}
			node1 = node1->next;
		}
		else
		{
			if (ret == nullptr)
			{
				ret = node2;
			}
			else
			{
				ret->next = node2;
				ret = ret->next;
			}
			node2 = node2->next;
		}
	}
	if (node1 == nullptr)
	{
		ret->next = node2;
	}
	if (node2 == nullptr)
	{
		ret->next = node1;
	}
	return ret;
}



void TestListOP()
{
    ListNode* list = nullptr;
	ListNode* list1 = nullptr;
    for (int idx = 0; idx < 8; ++idx)
    {
        AddList(&list, idx + 10);
		AddList(&list1, idx + 2);
    }
	//ListPrint(ListReverse(list));

	ListPrint(list);
	ListPrint(list1);
	ListPrint(CombineList(list, list1));

    //链表删除
    while (list != nullptr)
    {
        ListNode* node = list;
        list = list->next;
        delete node;
        node = nullptr;
    }
};

#endif //COMMON_LIST_OP_H_H

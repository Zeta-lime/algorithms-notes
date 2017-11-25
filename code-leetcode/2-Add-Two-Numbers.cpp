// You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

// You may assume the two numbers do not contain any leading zero, except the number 0 itself.

// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *p_result = new ListNode(0);
        ListNode *p = p_result;
        int carry = 0;
        int value = 0;
        while (l1 || l2)
        {
            // int v = (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
            // value = (v + p->val) % 10;
            // carry = (v + p->val) / 10;
            // 除法消耗时间，改完后46ms->>39ms
            int v = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + p->val;
            carry = v < 10 ? 0 : 1;
            value = carry ? v - 10 : v;
            p->val = value;
            if (l1)
                l1 = l1->next;
            if (l2)
                l2 = l2->next;
            if (l1 || l2 || carry != 0)
            {
                p->next = new ListNode(carry);
                p = p->next;
            }
        }
        return p_result;
    }
};

// 最初的版本
// class Solution
// {
//   public:
//     ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
//     {
//         ListNode *P_result = new ListNode(0) ；
//             ListNode *result = P_result;
//         int carry = 0;
//         int value = 0;
//         while (l1 && l2)
//         {
//             value = (l1->val + l2->val + result->val) % 10;
//             carry = (l1->val + l2->val + result->val) / 10;
//             result->val = value;
//             l1 = l1->next;
//             l2 = l2->next;
//             if (l1 || l2 || carry != 0)
//             {
//                 result->next = new ListNode(carry);
//                 result = result->next;
//             }
//         }
//         while (l1)
//         {
//             value = (l1->val + result->val) % 10;
//             carry = (l1->val + result->val) / 10;
//             result->val = value;
//             l1 = l1->next;
//             if (l1 || carry != 0)
//             {
//                 result->next = new ListNode(carry);
//                 result = result->next;
//             }
//         }
//         while (l2)
//         {
//             value = (l2->val + result->val) % 10;
//             carry = (l2->val + result->val) / 10;
//             result->val = value;
//             l2 = l2->next;
//             if (l2 || carry != 0)
//             {
//                 result->next = new ListNode(carry);
//                 result = result->next;
//             }
//         }
//         return P_result;
//     }
// };

void trimLeftTrailingSpaces(string &input)
{
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
                    return !isspace(ch);
                }));
}

void trimRightTrailingSpaces(string &input)
{
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
                    return !isspace(ch);
                })
                    .base(),
                input.end());
}

vector<int> stringToIntegerVector(string input)
{
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim))
    {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode *stringToListNode(string input)
{
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode *dummyRoot = new ListNode(0);
    ListNode *ptr = dummyRoot;
    for (int item : list)
    {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode *node)
{
    if (node == nullptr)
    {
        return "[]";
    }

    string p;
    while (node)
    {
        p += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + p.substr(0, p.length() - 2) + "]";
}

int main()
{
    string line;
    while (getline(cin, line))
    {
        ListNode *l1 = stringToListNode(line);
        getline(cin, line);
        ListNode *l2 = stringToListNode(line);

        ListNode *ret = Solution().addTwoNumbers(l1, l2);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
    system("pause");
    return 0;
}
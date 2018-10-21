#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

class BST {
    struct node {
        int data;
        struct node* left;
        struct node* right;

        node(int _data) : data(_data) {}
    };

private:
    node* root = NULL;

    struct node* createNode(int data) {
        return new node(data);
    }

    struct node* insertBST(node* cur, int n) {
        if (cur == NULL) {
            cur = new node(n);
        } else if (n < cur->data) {
            cur->left = insertBST(cur->left, n);
        } else {
            cur->right = insertBST(cur->right, n);
        }
        return cur;
    }

    void inorder(node* cur) {
        if (cur != NULL) {
            inorder(cur->left);
            cout << cur->data << ' ';
            inorder(cur->right);
        }
    }

    bool find(node* cur, int v) {
        if (cur == NULL) {
            return false;
        } else if (cur->data == v) {
            return true;
        } else if (v < cur->data) {
            return find(cur->left, v);
        } else {
            return find(cur->right, v);
        }
    }

    int height(node* cur) {
        if (cur == NULL) {
            return 0;
        }

        return std::max(height(cur->right), height(cur->left)) + 1;
    }

    bool isBalanced(node* cur) {
        if (cur == NULL)
            return true;
        else {
            int lh = height(cur->left);
            int rh = height(cur->right);
            return abs(lh - rh) <= 1 && isBalanced(cur->left) && isBalanced(cur->right);
        }
    }

public:
    void insertBST(int n) {
        root = insertBST(root, n);
    }

    void inorder() {
        inorder(root);
    }

    bool find(int v) {
        return find(root, v);
    }

    int height() {
        return height(root);
    }

    int min() {
        if (root == NULL)
            return -1;

        node* mi = root;
        while (mi->left != NULL)
            mi = mi->left;
        return mi->data;
    }

    int max() {
        if (root == NULL)
            return -1;

        node* mx = root;
        while (mx->right != NULL)
            mx = mx->right;
        return mx->data;
    }

    bool isBalanced() {
        return isBalanced(root);
    }
};

int main()
{
    int n, data, v;
    cout << "Enter n:" << '\n';
    cin >> n;
    BST bst;
    for (int i = 0; i < n; i++) {
        cout << "Enter data:" << '\n';
        cin >> data;
        bst.insertBST(data);
    }

    bst.inorder();
    cout << '\n';
    cout << bst.height() << '\n';
    cout << bst.min() << '\n';
    cout << bst.max() << '\n';
    cout << "Enter v:" << '\n';
    cin >> v;
    cout << bst.find(v) << '\n';
    cout << "Enter v:" << '\n';
    cin >> v;
    cout << bst.find(v) << '\n';
    cout << bst.isBalanced() << '\n';
    return 0;
}

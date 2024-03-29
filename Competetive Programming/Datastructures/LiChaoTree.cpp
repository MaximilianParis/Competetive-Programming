#include<bits/stdc++.h>
using namespace std;
//Author: Max Paris

typedef long long ll;
int n, k, l,m;


template<typename T>
struct node {
    node<T>* left = NULL;
    node<T>* right = NULL;
    T a;
    T b;

    T eval(int x) {
        return a * x + b;
    }

    node(T a, T b, node<T>* left, node<T>* right) {
        this->a = a;
        this->b = b;
        this->left = left;
        this->right = right;

    }

    node(T a, T b) {
        this->a = a;
        this->b = b;

    }
};



template<typename T>
struct LiChaoTree {
    node<T>* root = NULL;
    bool(*compare)(node<T>*, node<T>*, int);
    int L;
    int R;
    node<T>* ans;

    LiChaoTree(int L, int R, bool(*compare)(node<T>*, node<T>*, int)) {
        this->L = L;
        this->R = R;
        this->compare = compare;
    }
    int getMiddle(int l, int r) {

        return l + (r - l) / 2;

    }
    node<T>* insert_internal(node<T>* newNode, node<T>* curr, int l, int r) {
        if (l <= r) {

            if (curr == NULL)
                return newNode;

            int mid = getMiddle(l, r);

            if (compare(newNode, curr, mid)) {
                newNode->left = curr->left;
                newNode->right = curr->right;
                if (curr == root)
                    root = newNode;
                curr->left = NULL;
                curr->right = NULL;
                swap(newNode, curr);
            }

            if (compare(newNode, curr, l)) {
                curr->left = insert_internal(newNode, curr->left, l, mid);
            }
            else if (compare(newNode, curr, r))
                curr->right = insert_internal(newNode, curr->right, mid + 1, r);
        }
        return curr;

    }
    void insert(T a, T b) {
        node<T>* newNode = new node<T>(a, b);
        if (root != NULL)
            insert_internal(newNode, root, L, R);
        else
            root = newNode;
    }

    void query_internal(int x, node<T>* curr, int l, int r) {
        if (l <= r && curr != NULL) {
            int mid = getMiddle(l, r);
            if (compare(curr, ans, x))
                ans = curr;

            if (x < mid)
                query_internal(x, curr->left, l, mid);
            else if (x > mid)
                query_internal(x, curr->right, mid + 1, r);


        }
    }

    T query(int x) {
        if (root != NULL) {
            ans = root;
            query_internal(x, root, L, R);
            return ans->eval(x);
        }

        else
            return NULL;
    }




};
bool compare(node<ll>* x1, node<ll>* x2, int x3) {
    return x1->eval(x3) < x2->eval(x3);
}


int main() {
    LiChaoTree<int>(0, 10, compare);
    
    return 0;
}
#include<bits/stdc++.h>
#include <unordered_map>
using namespace std;
//Author: Max Paris

typedef unsigned long long ull;
int n, k, l;

struct AVLNode {
    int cntLeft = 0,  cntRight = 0;
    AVLNode* parent=NULL;
    AVLNode* left = NULL;
    AVLNode* right = NULL;
    ull value;
    int size = 1;
};
struct AVL_Tree {
    AVLNode* root;

    AVL_Tree(ull value) {
        root = new struct AVLNode();
        root->value = value;
    }
    AVL_Tree() {
        root = NULL;

    }
    AVLNode* predecessor(ull x) {
        AVLNode* curr = root;
        return predecessor_Internal(x, curr);
    }

    AVLNode* predecessor_Internal(ull x, AVLNode* curr) {
        if (curr == NULL)
            return NULL;
        else if (curr->value == x) {
            return getMax_Internal(curr->left);
        }
        else if (curr->value > x)
            return predecessor_Internal(x, curr->left);
        else {
            AVLNode* ans = predecessor_Internal(x, curr->right);
            if (ans != NULL)
                return ans;
            else return curr;
        }


    }
    AVLNode* lower_bound(ull x) {
        AVLNode* curr = root;
        return lower_bound_Internal(x, curr);
    }

    AVLNode* lower_bound_Internal(ull x, AVLNode* curr) {
        if (curr == NULL)
            return NULL;
        else if (curr->value == x)
            return curr;
        else if (curr->value > x) {
            AVLNode* ans = lower_bound_Internal(x, curr->left);
            if (ans != NULL)
                return ans;
            else return curr;
        }
        else {
            return lower_bound_Internal(x, curr->right);
        }

    }
    AVLNode* find(ull x) {
        AVLNode* curr = root;
        return find_Internal(x, curr);
    }

    AVLNode* find_Internal(ull x, AVLNode* curr) {
        if (curr == NULL)
            return NULL;
        else if (curr->value == x)
            return curr;
        else if (curr->value > x) {
            return find_Internal(x, curr->left);
        }
        else {
            return find_Internal(x, curr->right);
        }

    }

    void insert(ull x) {
        AVLNode* curr = root;

        if (root != NULL) {
            insert_Internal(x, curr);
        }
        else {
            root = new struct AVLNode();
            root->value = x;
        }
    }
    void updateSize(AVLNode* curr) {
        curr->size = 1;
        if (curr->left != NULL)
            curr->size += curr->left->size;

        if (curr->right != NULL)
            curr->size += curr->right->size;

    }
    void updateBalance(AVLNode* curr) {
        if (curr->left != NULL)
            curr->cntLeft = max(curr->left->cntLeft, curr->left->cntRight) + 1;
        else curr->cntLeft = 0;

        if (curr->right != NULL)
            curr->cntRight = max(curr->right->cntLeft, curr->right->cntRight) + 1;
        else curr->cntRight = 0;
    }
    void rightToLeftRotation(AVLNode* curr) {
        if (curr == root)
            root = curr->right;

        AVLNode* parent = curr->parent;
        AVLNode* rem = curr->right;
        curr->right = curr->right->left;
        if (curr->right != NULL)
            curr->right->parent = curr;
        rem->left = curr;
        curr->parent = rem;
        rem->parent = parent;
        if (parent != NULL) {
            if (parent->right == curr)
                parent->right = rem;
            else
                parent->left = rem;
        }

        updateSize(curr);
        updateBalance(curr);
        updateSize(curr->parent);
        updateBalance(curr->parent);
    }

    void LeftToRightRotation(AVLNode* curr) {
        if (curr == root)
            root = curr->left;

        AVLNode* parent = curr->parent;
        AVLNode* rem = curr->left;
        curr->left = curr->left->right;
        if (curr->left != NULL)
            curr->left->parent = curr;
        rem->right = curr;
        curr->parent = rem;
        rem->parent = parent;
        if (parent != NULL) {
            if (parent->right == curr)
                parent->right = rem;
            else
                parent->left = rem;
        }
        updateSize(curr);
        updateBalance(curr);
        updateSize(curr->parent);
        updateBalance(curr->parent);
    }

    void insert_Internal(ull x, AVLNode* curr) {
        if (curr->value == x)
            return;
        else if (curr->value > x) {
            if (curr->left != NULL)
                insert_Internal(x, curr->left);
            else {
                curr->cntLeft++;
                curr->left = new struct  AVLNode();
                curr->left->parent = curr;
                curr->left->value = x;

            }
        }
        else if (curr->value < x) {
            if (curr->right != NULL)
                insert_Internal(x, curr->right);
            else {
                curr->cntRight++;
                curr->right = new struct  AVLNode();
                curr->right->parent = curr;
                curr->right->value = x;

            }
        }
        updateSize(curr);
        updateBalance(curr);

        if (curr->cntLeft > curr->cntRight + 1) {
            if (curr->left->cntRight < curr->left->cntLeft)
                LeftToRightRotation(curr);
            else {
                rightToLeftRotation(curr->left);
                LeftToRightRotation(curr);
            }
        }
        else if (curr->cntLeft + 1 < curr->cntRight) {
            if (curr->right->cntRight > curr->right->cntLeft)
                rightToLeftRotation(curr);
            else {
                LeftToRightRotation(curr->right);
                rightToLeftRotation(curr);
            }
        }

    }
    AVLNode* getMin(AVLNode* curr) {
        if (curr->left != NULL)
            return getMin(curr->left);
        else return curr;
    }

    void erase(ull x) {
        AVLNode* curr = root;

        if (root != NULL) {
            if (root->value == x && root->size == 1) {

                root = NULL;
            }
            else {
                erase_Internal(x, curr);
            }

        }

    }

    void erase_Internal(ull x, AVLNode* curr) {
        if (curr == NULL)
            return;
        else if (curr->value > x)
            erase_Internal(x, curr->left);
        else if (curr->value < x)
            erase_Internal(x, curr->right);
        else {
            AVLNode* parent = curr->parent;
            if (curr->right != NULL) {

                AVLNode* mn = getMin(curr->right);
                if (mn == curr->right) {
                    mn->parent = parent;
                    if (parent != NULL) {
                        if (parent->left == curr) {
                            parent->left = mn;
                        }
                        else
                            parent->right = mn;
                    }
                    else root = mn;

                    mn->left = curr->left;
                    if (curr->left != NULL)
                        curr->left->parent = mn;
                    curr = mn;

                }
                else {
                    erase_Internal(mn->value, curr);
                    curr->value = mn->value;

                }

            }
            else {
                if (curr == root) {
                    root = curr->left;
                    root->parent = NULL;
                    return;
                }
                else {

                    if (parent->left == curr) {
                        parent->left = curr->left;
                        if (parent->left != NULL)
                            parent->left->parent = parent;
                    }
                    else {
                        parent->right = curr->left;
                        if (parent->right != NULL)
                            parent->right->parent = parent;
                    }
                    return;
                }



            }
        }

        updateSize(curr);
        updateBalance(curr);

        if (curr->cntLeft > curr->cntRight + 1) {
            if (curr->left->cntRight <= curr->left->cntLeft)
                LeftToRightRotation(curr);
            else {
                rightToLeftRotation(curr->left);
                LeftToRightRotation(curr);
            }
        }
        else if (curr->cntLeft + 1 < curr->cntRight) {
            if (curr->right->cntRight >= curr->right->cntLeft)
                rightToLeftRotation(curr);
            else {
                LeftToRightRotation(curr->right);
                rightToLeftRotation(curr);
            }
        }

    }


    AVLNode* getMax_Internal(AVLNode* curr) {
        if (curr->right != NULL)
            return getMax_Internal(curr->right);
        else return curr;
    }

    AVLNode* getMax() {
        AVLNode* curr = root;
        return getMax_Internal(curr);
    }

};

struct node {
    node* left=NULL;
    node* right=NULL;
    node* mx = NULL;
    node* mn = NULL;
    node* sucessor = NULL;
    node* predecessor = NULL;
    node* parent = NULL;
    ull val;
    AVL_Tree* tree = NULL;
    node(ull value) {
        val = value;
        mx = this;
        mn = this;
    }
    node(ull value, AVL_Tree* x):node(value) {
        tree = x;
    }
   
    node(ull value,node* x,node* y){
        parent = x;
        val = value;
        mx = y;
        mn = y;
    }
    
    node(){}
};

struct YFastTrie {
    vector<unordered_map<ull, node*>> prefixes;
    vector<ull> mask;
    int w;
    node* root;
    int mnGroupSize;
    int mxGroupSize;
    ull maxBit;
    YFastTrie(int w) {
        mnGroupSize = max(2,w/4);
        mxGroupSize = 2 * w;
        this->w = w;
        prefixes = vector<unordered_map<ull, node*>>(w);
        root = new struct node();
        mask = vector<ull>(w);
        maxBit = 1 << (w - 1);
        mask[0] = maxBit;
        for (ull i = 1, j = maxBit>>1; i < w; i++, j = j >> 1)
            mask[i] =mask[i - 1]+j;
        
    }
   

    void insert_Key(ull x,node* leaf) {
        node* curr = root;
        if (curr->mn == NULL || curr->mn->val > x)
            curr->mn = leaf;
        if (curr->mx == NULL || curr->mx->val < x)
            curr->mx = leaf;
        ull path_Sum = 0;
        ull rem = 0;
        for (ull i = 0, j = maxBit; i < w-1; i++, j = j >> 1) {
            rem = j;
            if (x & j) {
                path_Sum += j;
                if (curr->right != NULL) 
                    curr = curr->right;
                else {
                    node* next = new struct node(path_Sum,curr,leaf);
                    curr->right = next;
                    prefixes[i][path_Sum] = next;
                    curr = next;
                }
            }
            else {
                if (curr->left != NULL)
                    curr = curr->left;
                else {
                    node* next = new struct node(path_Sum, curr,leaf);
                    curr->left = next;
                    prefixes[i][path_Sum] = next;
                    curr = next;
                }
            }
            if (curr->mn==NULL||curr->mn->val > x)
                curr->mn = leaf;
            if(curr->mx == NULL||curr->mx->val < x)
                curr->mx = leaf;
        }
        rem = rem >> 1;
        if (x & rem) {
            path_Sum += rem;
            curr->right = leaf;
            leaf->parent = curr;
            prefixes[w-1][path_Sum] = leaf;
        }
        else {
            curr->left = leaf;
            leaf->parent = curr;
            prefixes[w - 1][path_Sum] = leaf;
        }
    }

    node* lower_bound_Node(ull x) {
        int l = 0;
        int r = w-1;
        node* ans = NULL;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            ull val = x & mask[mid];
            unordered_map<ull, node*>::iterator res = prefixes[mid].find(val);
                  
            if (res != prefixes[mid].end()) {
                ans = res->second;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        if (ans != NULL) {
            if (x > ans->mx->val)
                return ans->mx->sucessor;
            else if (x == ans->mx->val)
                return  ans->mx;
            else if (x <= ans->mn->val) {
                if (ans->mn->predecessor == NULL || ans->mn->predecessor->val < x)
                    return  ans->mn;
                else
                    return ans->mn->predecessor;
            }
            else return NULL;

        }
        else if (root->mn != NULL && root->mn->val >= x)
            return root->mn;
        else
            return NULL;
            
        

    }
    AVLNode* lower_bound(ull x) {
        node* curr = lower_bound_Node(x);
        if (curr != NULL) {
            AVLNode* ans= curr->tree->lower_bound(x);
            if (ans != NULL)
                return ans;
            else if(curr->sucessor!=NULL){
                return curr->sucessor->tree->lower_bound(x);
            }
        }
        else if (root->mx != NULL) {
            return root->mx->tree->lower_bound(x);
        }

      return NULL;
    }
    AVLNode* predecessor(ull x) {
        node* curr= lower_bound_Node(x);
        if (curr != NULL) {
            AVLNode* ans = curr->tree->predecessor(x);
            if (ans != NULL)
                return ans;
            else if (curr->predecessor != NULL) {
                return curr->predecessor->tree->getMax();
            }
        }
        else if(root->mx!=NULL)
            return root->mx->tree->predecessor(x);


        return NULL;
    }
    void erase_key(node* curr) {
        node* current = curr;
        bool keepErasing = true;
        for (int i = w - 1; i >= 0; i--) {
              node* parent = current->parent;
              if (keepErasing) {
                  prefixes[i].erase(current->val);
                  if (parent->left == current) {
                      parent->left = NULL;
                 }
                  else {
                      parent->right = NULL;
                  }
              }
              else {
                  if (parent->left != NULL && parent->right != NULL) {
                      if (parent->left->mx->val > parent->right->mx->val)
                          parent->mx = parent->left->mx;
                      else  parent->mx = parent->right->mx;

                      if (parent->left->mn->val < parent->right->mn->val)
                          parent->mn = parent->left->mn;
                      else  parent->mn = parent->right->mn;
                  }
                 else if (parent->left != NULL) {
                      parent->mx = parent->left->mx;
                      parent->mn = parent->left->mn;
                  }
                  else {
                      parent->mx = parent->right->mx;
                      parent->mn = parent->right->mn;
                  }
              }

              if (keepErasing&&(parent->left != NULL || parent->right != NULL)) {
                  keepErasing = false;
                  if (parent->left != NULL) {
                      parent->mx = parent->left->mx;
                      parent->mn = parent->left->mn;
                  }
                  else {
                      parent->mx = parent->right->mx;
                      parent->mn = parent->right->mn;
                  }
              }

            current = parent;
       }
        if (root->left == NULL && root->right == NULL) {
            root->mn = NULL;
            root->mx = NULL;
        }
    }
    void splittTree(AVL_Tree* tree, AVL_Tree* treeX2, AVL_Tree* treeX1) {
        ull oldRoot = tree->root->value;
        AVLNode* left = tree->root->left;
        AVLNode* right = tree->root->right;
        left->parent = NULL;
        right->parent = NULL;
        treeX1->root = left;
        treeX2->root = right;
        treeX1->insert(oldRoot);
    }
    pair<node*,node*> insertTwoKeys(node* next) {
        AVL_Tree* tree = next->tree;
        AVL_Tree* treeX2 = new struct AVL_Tree();
        AVL_Tree* treeX1 = new struct AVL_Tree();
        splittTree(tree, treeX2, treeX1);
        node* x1 = new struct node(treeX1->getMax()->value);
        node* x2 = new struct node(treeX2->getMax()->value);
        x1->tree = treeX1;
        x2->tree = treeX2;
        x1->predecessor = next->predecessor;
        if (x1->predecessor != NULL)
            x1->predecessor->sucessor = x1;
        x1->sucessor = x2;
        x2->predecessor = x1;
        x2->sucessor = next->sucessor;
        if (x2->sucessor != NULL)
            x2->sucessor->predecessor = x2;
        insert_Key(x1->val, x1);
        insert_Key(x2->val, x2);
        return { x1,x2 };
    }

    void insert(ull x) {
       
        node* next= lower_bound_Node(x);
        if (next != NULL) {
            if (next->tree->root == NULL||next->tree->root->size < mxGroupSize)
                next->tree->insert(x);
            else if(!next->tree->find(x)){
                erase_key(next);
                pair<node*, node*>nodes= insertTwoKeys(next);
                if (nodes.first->val >= x)
                    nodes.first->tree->insert(x);
                else if(nodes.second->val >= x || nodes.second->sucessor==NULL)
                    nodes.second->tree->insert(x);
                else 
                    nodes.second->sucessor->tree->insert(x);
            }
        }
        else if(root->mx!=NULL){
            next = root->mx;
            if (next->tree->root == NULL||
                next->tree->root->size < mxGroupSize)
                next->tree->insert(x);
            else if (!next->tree->find(x)) {
                erase_key(next);
                pair<node*, node*>nodes = insertTwoKeys(next);
                if (nodes.first->val >= x)
                    nodes.first->tree->insert(x);
                else
                    nodes.second->tree->insert(x);
            }
        }
        else {
            node* leaf = new struct node(x);
            leaf->tree = new struct AVL_Tree(x);
            insert_Key(x, leaf);
          }
    }
    AVL_Tree* merge(node* x1,node* x2) {
        AVL_Tree* treeX1 = x1->tree;
        AVL_Tree* treeX2 = x2->tree;
        int size = treeX1->root->size + treeX2->root->size;
        vector<ull> tem(size);
        int i = 0;
        int* index = &i;
        fill(tem, index, treeX1->root);
        fill(tem, index, treeX2->root);
        int half = size / 2;
        AVL_Tree* ans = new struct AVL_Tree(tem[half]);
        construct(ans,ans->root, 0, half-1, true,tem);
        construct(ans,ans->root, half+1, size-1, false,tem);
        ans->updateSize(ans->root);
        ans->updateBalance(ans->root);
        return ans;
    }
    void construct(AVL_Tree* ans,AVLNode* parent,int l,int r,bool left, vector<ull>& tem) {
        if (r >= l) {
            int mid = l + (r - l) / 2;
            AVLNode* curr=new struct AVLNode();
            curr->value = tem[mid];
            curr->parent = parent;
            if (left)
                parent->left = curr;
            else
                parent->right = curr;
            construct(ans,curr, l, mid - 1, true, tem);
            construct(ans,curr, mid+1,r, false, tem);
            ans->updateSize(curr);
            ans->updateBalance(curr);
            
        }
    }
    void fill(vector<ull>& tem, int* index, AVLNode* curr) {
        if (curr->left != NULL) {
            fill(tem, index, curr->left);
        }
        tem[(*index)++] = curr->value;
        if (curr->right != NULL) {
            fill(tem, index, curr->right);
        }
    }

    void erase(ull x) {
        node* next = lower_bound_Node(x);
        if (next != NULL) {
            if (next->tree->root != NULL) {
                if (next->tree->root->size > mnGroupSize)
                    next->tree->erase(x);
                else if (next->tree->find(x)) {
                    next->tree->erase(x);
                    if (next->sucessor != NULL) {
                        erase_key(next);
                        erase_key(next->sucessor);
                        AVL_Tree* tree = merge(next, next->sucessor);
                        node* curr = new struct node(next->sucessor->val, tree);
                        if (next->predecessor != NULL) {
                            curr->predecessor = next->predecessor;
                            curr->predecessor->sucessor = curr;
                        }
                        if (next->sucessor->sucessor != NULL) {
                            curr->sucessor = next->sucessor->sucessor;
                            curr->sucessor->predecessor = curr;
                        }
                        if (tree->root->size > mxGroupSize) {
                            insertTwoKeys(curr);
                        }
                        else {
                            insert_Key(curr->val, curr);
                        }
                    }
                    else if (next->predecessor != NULL) {
                        erase_key(next->predecessor);
                        erase_key(next);
                        AVL_Tree* tree = merge(next->predecessor, next);
                        node* curr = new struct node(next->val, tree);
                        if (next->predecessor->predecessor != NULL) {
                            curr->predecessor = next->predecessor->predecessor;
                            curr->predecessor->sucessor = curr;
                        }
                        if (tree->root->size > mxGroupSize) {
                            insertTwoKeys(curr);
                        }
                        else {
                            insert_Key(curr->val, curr);
                        }
                    }
                }
            }
        }
        else if (root->mx != NULL) {
            next = root->mx;
            if (next->tree->root != NULL) {
                if (next->tree->root->size > mnGroupSize)
                    next->tree->erase(x);
                else if (next->tree->find(x)) {
                    next->tree->erase(x);
                    if (next->predecessor != NULL) {
                        erase_key(next->predecessor);
                        erase_key(next);
                        AVL_Tree* tree = merge(next->predecessor, next);
                        node* curr = new struct node(next->val, tree);
                        if (next->predecessor->predecessor != NULL) {
                            curr->predecessor = next->predecessor->predecessor;
                            curr->predecessor->sucessor = curr;
                        }
                        if (tree->root->size > mxGroupSize) {
                            insertTwoKeys(curr);
                        }
                        else {
                            insert_Key(curr->val, curr);
                        }
                    }
                }
            }
        }
        
    }
  



};

int main() {
    int w, q;
    scanf("%d%d", &w, &q);
    YFastTrie tree(w);
    while (q--) {
        int x1, x2;
        scanf("%d%d", &x1, &x2);
       
        if (x1 == 1) {
            tree.insert(x2);
        }
        else if (x1 == 0) {
            tree.erase(x2);
        }
        else {
            AVLNode* ans = tree.lower_bound(x2);
            if (ans != NULL) {
                printf("%llu\n", ans->value);
            }
            else {
                printf("-1\n");
            }
        }
    }
   
    return 0;
}
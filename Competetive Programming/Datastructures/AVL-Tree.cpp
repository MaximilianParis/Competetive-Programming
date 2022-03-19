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
        else if(curr->value > x)
            return predecessor_Internal(x,curr->left);
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
            AVLNode* ans = lower_bound_Internal(x,curr->left);
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
            curr->size+= curr->left->size;
        
        if (curr->right != NULL)
            curr->size+= curr->right->size;
      
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
        if(curr->right!=NULL)
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
        if(curr->left!=NULL)
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
       else if(curr->cntLeft+1 < curr->cntRight){
           if(curr->right->cntRight> curr->right->cntLeft)
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
            if (root->value == x&&root->size==1) {
               
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


int main() {
    int w, q;
    scanf("%d%d", &w, &q);
    AVL_Tree* tree=new struct AVL_Tree();
    while (q--) {
        int x1, x2;
        scanf("%d%d", &x1, &x2);
       
        if (x1 == 1) {
            tree->insert(x2);
        }
        else if (x1 == 0) {
            tree->erase(x2);
        }
        else {
            AVLNode* ans = tree->lower_bound(x2);
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
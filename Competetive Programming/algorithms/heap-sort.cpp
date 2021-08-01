#include <bits/stdc++.h>


using namespace std;
typedef long long ll;
bool Alreadysorted = false;
struct node {
    ll data;
    bool fixed;
    struct node* parent;
    struct node* left;
    struct node* right;
};

vector<node*> heap;

struct node* newNode(ll data) {
   
    struct node* node = new struct node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->fixed = false;
    return(node);
}
void transform(node* node,bool above) {
    if (node->left !=NULL&&node->left->data > node->data) {
        if (node->right == NULL || node->left->data >= node->right->data) {
            ll data = node->data;
            node->data = node->left->data;
            node->left->data = data;
           
            node->left->fixed = false;
            if (node->parent != NULL) {
                if (above == true && Alreadysorted == true)
                    node->parent->fixed = true;
                else  node->parent->fixed = false;
            }
        }
        else {
            ll data = node->data;
            node->data = node->right->data;
            node->right->data = data;
           
            node->right->fixed = false;
           
            if (node->parent != NULL) {
                if (above == true&& Alreadysorted==true)
                    node->parent->fixed = true;
                else  node->parent->fixed = false;
            }
         
        }
       
       
       
    }else if(node->right != NULL && node->right->data > node->data){
        ll data = node->data;
        node->data = node->right->data;
        node->right->data = data;
        
        
        
        node->right->fixed = false;
        if (node->parent != NULL) {
            if(above == true && Alreadysorted == true)
            node->parent->fixed = true;
            else  node->parent->fixed = false;
        }
        
        
    }
    node->fixed = true;
   
    
}
void transform_to_Maxheap_dfs(node* node,bool above) {
   
        transform(node,above);
        if (node->left != NULL && !node->left->fixed)
         transform_to_Maxheap_dfs(node->left,true);
        if (node->right != NULL && !node->right->fixed)
            transform_to_Maxheap_dfs(node->right,true);
        
        if (node->parent != NULL && !node->parent->fixed)
            transform_to_Maxheap_dfs(node->parent,false);
    
}

int main() {
    int n;
    cin >> n;
    assert(n > 0);
    heap = vector<node*>(n);
    int curr_root = 0;
    bool left = true;
    int cnt = 0;
  
    for (int i = 0; i < n; i++) {
        ll data;
        cin >> data;
        heap[i] = newNode(data);
        if (i != curr_root) {
            heap[i]->parent = heap[curr_root];
            if (cnt == 1)
                heap[curr_root]->left = heap[i];
            if (cnt == 2)
                heap[curr_root]->right = heap[i], cnt = 0, curr_root++;
            
        }

        cnt++;

    }
 
    vector<ll> ans(n);

    transform_to_Maxheap_dfs(heap[n-1],false);
    Alreadysorted++;

    for (int i = n-1; i >= 0; i--) {
        
        ans[i] = heap[0]->data;
        if (i > 0) {
            heap[0]->data = heap[i]->data;
            heap[0]->fixed = false;
            heap[0]->parent = NULL;
            if ((i + 1) % 2 == 0) {
                heap[i]->parent->left = NULL;
            }
            else {
                heap[i]->parent->right = NULL;
            }
            transform_to_Maxheap_dfs(heap[0],true);
        }
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << " ";
   
    return 0;
}
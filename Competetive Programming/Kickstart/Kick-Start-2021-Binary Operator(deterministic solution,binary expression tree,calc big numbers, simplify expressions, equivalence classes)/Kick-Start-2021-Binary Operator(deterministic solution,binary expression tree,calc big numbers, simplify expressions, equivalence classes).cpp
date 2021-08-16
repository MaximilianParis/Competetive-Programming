#include <bits/stdc++.h>
#include <unordered_map>
//Author: Max Paris
//Problem Link: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000435c44/00000000007ec290
using namespace std;
typedef long long ll;
vector<int> ans;
int cnt3;
bool stop = false;
unordered_map<string, int> equivalenceclasses;
map<string, int> Xi;
int cnt;
vector<string> Ei;
int val;
string findSum(string str1, string str2)
{
   
    if (str1.length() > str2.length())
        swap(str1, str2);

  
    string str = "";

  
    int n1 = str1.length(), n2 = str2.length();

  
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i = 0; i < n1; i++)
    {
      
        int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');

       
        carry = sum / 10;
    }

   
    for (int i = n1; i < n2; i++)
    {
        int sum = ((str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

   
    if (carry)
        str.push_back(carry + '0');

   
    reverse(str.begin(), str.end());

    return str;
}
string multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
        return "0";

    
    vector<int> result(len1 + len2, 0);

    
    int i_n1 = 0;
    int i_n2 = 0;

   
    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        
        i_n2 = 0;

           
        for (int j = len2 - 1; j >= 0; j--)
        {
          
            int n2 = num2[j] - '0';

           
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

           
            carry = sum / 10;

            
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

      
        i_n1++;
    }

   
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

   
    if (i == -1)
        return "0";

   
    string s = "";

    while (i >= 0)
        s +=to_string(result[i--]);

    return s;
}
struct node {
    int type;
    string value;
    struct node* parent;
    struct node* left;
    struct node* right;
    int xi;
    int pow;
};
struct node* newNode(int type, string value, node* parent) {

    struct node* node = new struct node();
    node->type = type;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->pow = 0;
    return(node);
}
node* op;
vector<node*> EiTrees;
string getExpression(node* current) {

    if (current->type == 1)
        return "(" + getExpression(current->left) + "+" + getExpression(current->right) + ")";
    else if (current->type == 2)
        return "(" + getExpression(current->left) + "*" + getExpression(current->right) + ")";
    else if (current->type == 3)
        return "(" + getExpression(current->left) + "#" + getExpression(current->right) + ")";
    else
        return current->value;
}
node* construct(int i, int l, int r, node* parent, bool left) {
    int cnt1 = 0;
    int cnt2 = 0;
    node* current = NULL;
    for (int a = l; a < r; a++) {

        if (Ei[i][a] == '(')
            cnt1++;

        else if (Ei[i][a] == ')')
            cnt2++;

        else if (Ei[i][a] == '+' && cnt1 - 1 == cnt2) {
            current = newNode(1, "+", parent);
           
           
          
            current->left = construct(i, l + 1, a, current, true);
            current->right = construct(i, a + 1, r - 1, current, false);
            if (current->left->type == 0 && current->right->type == 0) {
                current->type = 0;
                current->value = findSum(current->left->value, current->right->value);
                current->right->parent = NULL;
                current->left->parent = NULL;
                current->right = NULL;
                current->left = NULL;
            }
           
          
            
    
            
            
                   
                
            break;


        }
        else if (Ei[i][a] == '*' && cnt1 - 1 == cnt2) {
            current = newNode(2, "*", parent);
            
           

            current->left = construct(i, l + 1, a, current, true);

            current->right = construct(i, a + 1, r - 1, current, false);
            if (current->left->value == "0" || current->right->value == "0") {
                current= newNode(0, "0", parent);
            }
        else if (current->left->type == 0 && current->right->type == 0) {
                current->type = 0;
                current->value = multiply(current->left->value, current->right->value);
                current->right->parent = NULL;
                current->left->parent = NULL;
                current->right = NULL;
                current->left = NULL;
        }
            else {
                current->parent = newNode(1, "+", parent);
                current->parent->right = newNode(0, "0", current->parent);
                current->parent->left = current;
                current = current->parent;

            }
           
               
            
            break;


        }
        else if (Ei[i][a] == '#' && cnt1 - 1 == cnt2) {
            current = newNode(3, "#", parent);
            
            
            current->left = construct(i, l + 1, a, current, true);
            current->right = construct(i, a + 1, r - 1, current, false);
            
           
            

            
            



            break;

        }



    }
    if (current == NULL) {
        current = newNode(0, Ei[i].substr(l, r - (l)), parent);
    }


    return current;

}
int compareToTreesWithEqualPOW(node* T1, node* T2) {
    if (T1->type == 3 && T2->type == 3) {
        if (T1->xi == T2->xi)
            return 0;
        else if (T1->xi < T2->xi)
            return -1;
        else
            return 1;
    }
    else if (T1->type == 2 && T2->type == 2) {
        int val = compareToTreesWithEqualPOW(T1->left, T2->left);
        if (val != 0)
            return val;
        else {
            return compareToTreesWithEqualPOW(T1->right, T2->right);
        }
    }
    else if (T1 == NULL && T2 == NULL)
        return 0;

}
void Addition_skalar_AdditionsTree(string value, node* right) {
   
    if (right->type == 1) {
        if (right->left->type == 0) {
           
            right->left->value = findSum(value, right->left->value);

            return;



        }
        else {
            Addition_skalar_AdditionsTree(value, right->right);
        }
    }
    else if (right->type == 0) {
        right->value = findSum(value, right->value);

        return;
    }
    else {
        node* NewNode = newNode(1, "+", right->parent);
        NewNode->parent->right = NewNode;
        NewNode->left = right;
        right->parent = NewNode;
        NewNode->right = newNode(0,value,NewNode);
     
    }
           
        
    
}


node* Addition_Tree_Tree(node* T1, node* T2,bool left) {
    if ((T1->type == 3 && T2->type == 3)|| ((T1->type == 2 && T2->type == 2) &&(T1->left->type == 3 && T2->left->type == 3))) {
       val=  compareToTreesWithEqualPOW(T1, T2);
      if (val == 0) {
          stop = true;
          if (left) {
              node* NewNode = newNode(2, "*", T2->parent);
              T2->parent->left = NewNode;
              NewNode->left= newNode(0, "2", NewNode);
              NewNode->right = T2;
              T2->parent = NewNode;
              T2 = NewNode;
          }
          else {
              node* NewNode = newNode(2, "*", T2->parent);
              T2->parent->right = NewNode;
              NewNode->left = newNode(0, "2", NewNode);
              NewNode->right = T2;
              T2->parent = NewNode;
              T2 = NewNode;
          }
      }
    
     
      
    }
    else if (T1->type == 2 && T2->type == 3 || ((T1->type == 2 && T2->type == 2) && (T1->left->type == 0 && T2->left->type == 3))) {
         val = compareToTreesWithEqualPOW(T1->right, T2);
        if (val == 0) {
            stop = true;
            if (left) {
                node* NewNode = newNode(2, "*", T2->parent);
                T2->parent->left = NewNode;
                NewNode->left = newNode(0, findSum("1", T1->left->value), NewNode);
                NewNode->right = T2;
                T2->parent = NewNode;
                T2 = NewNode;
            }
            else {
                node* NewNode = newNode(2, "*", T2->parent);
                T2->parent->right = NewNode;
                NewNode->left = newNode(0, findSum("1", T1->left->value), NewNode);
                NewNode->right = T2;
                T2->parent = NewNode;
                T2 = NewNode;
            }
        }
        
    }
        else if (T1->type == 3 && T2->type == 2 || ((T1->type == 2 && T2->type == 2) && (T1->left->type == 3 && T2->left->type == 0))) {
             val = compareToTreesWithEqualPOW(T1, T2->right);
            if (val == 0) {
                stop = true;
                T2->left->value = findSum("1", T2->left->value);
            }
           

        }
        else if (((T1->type == 2 && T2->type == 2) && (T1->left->type == 0 && T2->left->type == 0))) {
         val = compareToTreesWithEqualPOW(T1->right, T2->right);
        if (val == 0) {
            stop = true;
            T2->left->value = findSum(T1->left->value, T2->left->value);
        }
       
       
    
    }
    return T2;
}
int getPow(node* Tree) {
    if (Tree->type == 3)
        return Tree->pow;
    else if(Tree->left->type==3)
        return  Tree->left->pow;
    else if(Tree->right->type == 3){
        return  Tree->right->pow;
    }
    else {
        return  Tree->right->left->pow;
    }
}

node* Addition_Tree_AdditionsTree(node* T1, node* T2,int T1Pow){
   
  
    if (T2->type == 1) {
        int T2Pow = getPow(T2->left);
       
            if (T2Pow == T1Pow) {
                T2->left=Addition_Tree_Tree(T1, T2->left, true);
                if (val==-1) {
                    node* NewNode = newNode(1, "+", T2->parent);
                    if (T2->parent != NULL)
                        T2->parent->right = NewNode;
                    NewNode->left = T1;
                    T1->parent = NewNode;
                    NewNode->right = T2;
                    T2->parent = NewNode;
                    T2 = NewNode;
                }
                else if(val==1)
                    T2->right = Addition_Tree_AdditionsTree(T1, T2->right, T1Pow);
            }
            else if (T2Pow > T1Pow)
               T2->right= Addition_Tree_AdditionsTree(T1, T2->right, T1Pow);
            else
            {
                node* NewNode = newNode(1, "+", T2->parent);
                if(T2->parent!=NULL)
                T2->parent->right = NewNode;
                NewNode->left = T1;
                T1->parent = NewNode;
                NewNode->right = T2;
                T2->parent = NewNode;
                T2 = NewNode;
            }
       
        

        }
    else if (T2->type == 0) {
        node* NewNode = newNode(1, "+", T2->parent);
        T2->parent->right = NewNode;
        NewNode->right = T2;
        T2->parent = NewNode;
        NewNode->left = T1;
        T1->parent = NewNode;
        T2 = NewNode;
      
    }
    else {
        int T2Pow = getPow(T2);
        if (T2Pow == T1Pow) {
            T2=Addition_Tree_Tree(T1, T2, false);
            if (val==-1) {
                node* NewNode = newNode(1, "+", T2->parent);
                T2->parent->right = NewNode;
                NewNode->left = T1;
                T1->parent = NewNode;
                NewNode->right = T2;
                T2->parent = NewNode;
                T2 = NewNode;
              
            }
            else if (val == 1) {
                node* NewNode = newNode(1, "+", T2->parent);
                T2->parent->right = NewNode;
                NewNode->left = T2;
                T2->parent = NewNode;
                NewNode->right = T1;
                T1->parent = NewNode;
                T2 = NewNode;
            }
        }
        else if (T2Pow > T1Pow) {
            node* NewNode = newNode(1, "+", T2->parent);
            T2->parent->right = NewNode;
            NewNode->left = T2;
            T2->parent = NewNode;
            NewNode->right = T1;
            T1->parent = NewNode;
            T2 = NewNode;
        }
          
        else {
            node* NewNode = newNode(1, "+", T2->parent);
            T2->parent->right = NewNode;
            NewNode->left = T1;
            T1->parent = NewNode;
            NewNode->right = T2;
            T2->parent = NewNode;
            T2 = NewNode;
           
        }
            
    }
    return T2;
    
}

node* Addition_AdditionsTrees_simplify(node* T1, node* T2) {
    if (T1->type == 1) {
        int T1Pow = getPow(T1->left);
        T2= Addition_Tree_AdditionsTree(T1->left, T2, T1Pow);
        T2=Addition_AdditionsTrees_simplify(T1->right, T2);
    }
    else if (T1->type == 0) {
        Addition_skalar_AdditionsTree(T1->value, T2);
    }
    else {
        int T1Pow = getPow(T1);
       T2= Addition_Tree_AdditionsTree(T1, T2, T1Pow);
    }
    return T2;
}




void Multiplikation_Addition_simplify_type0(string value, node* right,bool left) {
    if (right == NULL)
        return;
    else {
        if (right->type == 1) {
            Multiplikation_Addition_simplify_type0( value, right->left,true);
            Multiplikation_Addition_simplify_type0( value,right->right,false);
        }
        else if (right->type == 2) {
            if (right->left->type == 0) {
                right->left->value = multiply(value, right->left->value);
            }
            else if (right->left->type == 3) {
                right->parent = newNode(2, "*", right->parent);
                right->parent->parent->left = right->parent;
                right->parent->right = right;
                right->parent->left = newNode(0, value, right->parent);
            }
        }
            else if (right->type == 3) {
            if (left) {
                right->parent = newNode(2, "*", right->parent);
                right->parent->parent->left = right->parent;
                right->parent->right = right;
                right->parent->left = newNode(0, value, right->parent);
            }
            else {
                node* NewNode= newNode(2, "*", right->parent);
                NewNode->parent->right = NewNode;
                NewNode->left= newNode(0, value, NewNode);
                NewNode->right = right;
                right->parent = NewNode;
            }

            }
            else if (right->type == 0) {
            right->value= multiply(value, right->value);
        }
        
       
    }

}
node* copyTree(node* Tree, node* parent) {

    node* copy = newNode(Tree->type, Tree->value, parent);
    copy->xi = Tree->xi;
    copy->pow = Tree->pow;
    if (Tree->left != NULL)
        copy->left = copyTree(Tree->left, copy);
    if (Tree->right != NULL)
        copy->right = copyTree(Tree->right, copy);

    return copy;


}

node* Multiplikation_Addition_simplify_type3(node* current, node* right,bool left) {
    if (right == NULL)
        return right;
    else {
        if (right->type == 1) {
            right->left=Multiplikation_Addition_simplify_type3(copyTree(current,current->parent), right->left,true);
            right->right=Multiplikation_Addition_simplify_type3(current, right->right,false);
        }
        else if (right->type == 2) {
            if (right->left->type == 0) {
                right->right= Multiplikation_Addition_simplify_type3(current, right->right,false);
            }
            else if (right->left->type == 3) {
                if (right->left->xi >= current->xi) {
                    if (left) {
                        current->pow = 1 + right->left->pow;
                        node* NewNode = newNode(2, "*", right->parent);
                        NewNode->parent->left = NewNode;
                        NewNode->right = right;
                        right->parent = NewNode;
                        NewNode->left = current;
                        current->parent = NewNode;
                        right = NewNode;
                    }
                    else {
                        current->pow = 1 + right->left->pow;
                        node* NewNode = newNode(2, "*", right->parent);
                        NewNode->parent->right = NewNode;
                        NewNode->right = right;
                        right->parent = NewNode;
                        NewNode->left = current;
                        current->parent = NewNode;
                        right = NewNode;
                    }
                   
                    
                    
                }
                else if (right->right != NULL) {
                    right->left->pow++;
                    right->right= Multiplikation_Addition_simplify_type3(current, right->right,false);
                }
                
            }
        }
        else if (right->type == 3) {
            if (right->xi >= current->xi) {
                if (!left) {
                    current->pow = 1 + right->pow;
                    node* NewNode = newNode(2, "*", right->parent);
                    right->parent->right = NewNode;
                    NewNode->left = current;
                    current->parent = NewNode;
                    NewNode->right = right;
                    right->parent = NewNode;
                    right = NewNode;
                }
                else {
                    current->pow = 1 + right->pow;
                    node* NewNode = newNode(2, "*", right->parent);
                    right->parent->left = NewNode;
                    NewNode->left = current;
                    current->parent = NewNode;
                    NewNode->right = right;
                    right->parent = NewNode;
                    right = NewNode;
                }
            }
            else {
                if (!left) {
                    right->pow++;
                    node* NewNode = newNode(2, "*", right->parent);
                    NewNode->parent->right = NewNode;
                    NewNode->left = right;
                    right->parent = NewNode;
                    NewNode->right = current;
                    current->parent = NewNode;
                    right = NewNode;
                }
                else {
                    right->pow++;
                    node* NewNode = newNode(2, "*", right->parent);
                    NewNode->parent->left = NewNode;
                    NewNode->right = current;
                    current->parent = NewNode;
                    NewNode->left = right;
                    right->parent = NewNode;
                    right = NewNode;
                }
            }
           

        }
        else if (right->type == 0 && right->value != "0") {
            current->pow = 1;
            node* NewNode = newNode(2, "*", right->parent);
            NewNode->parent->right = NewNode;
            right->parent = NewNode;
            current->parent = NewNode;
            NewNode->left = right;
            NewNode->right = current;
            right = NewNode;

        }

       
    }
    return right;

}
node* Multiplikation_simplify_itmult(node* current, node* right) {
    if (current->left->type == 0)
       Multiplikation_Addition_simplify_type0(current->left->value, right,true);
    else if (current->left->type == 3) {
        right= Multiplikation_Addition_simplify_type3(current->left, right,true);
    }
  
    if (current->right->type == 2)
        right= Multiplikation_simplify_itmult(current->right, right);
    else {
        if (current->right->type == 0)
            Multiplikation_Addition_simplify_type0(current->right->value, right,true);
        else {
            right= Multiplikation_Addition_simplify_type3(current->right, right,true);
        }
    }




    return right;
}

node* Multiplikation_simplify_itadd(node* current, node* right) {
    node* copyright = copyTree(right, NULL);
    if(current->left->type==2)
        copyright= Multiplikation_simplify_itmult(current->left, copyright);
    else if(current->left->type == 3)
        copyright= Multiplikation_Addition_simplify_type3(current->left, copyright,true);
    

       node*  NewNode= copyright;
      
        if (current->right->type != 1&&current->right->value!="0") {
           copyright= copyTree(right, NULL);
           if (current->right->type == 2) {
               copyright= Multiplikation_simplify_itmult(current->right, copyright);
             
           }
           else if (current->right->type == 3) {
               copyright = Multiplikation_Addition_simplify_type3(current->right, copyright,true);
             
           }
           else
               Multiplikation_Addition_simplify_type0(current->right->value, copyright,true);

           copyright= Addition_AdditionsTrees_simplify(NewNode, copyright);
        }
        else if(current->right->value != "0"){
          
            copyright = Multiplikation_simplify_itadd(current->right, right);
            copyright = Addition_AdditionsTrees_simplify(NewNode, copyright);
        }
    
    return copyright;

}

node* simplify(node* current, bool left) {

    if (current->left != NULL)
         current->left = simplify(current->left, true);

    if (current->right != NULL)
        current->right = simplify(current->right, false);

    if (current->type == 1) {
        //Links Zahl
        if (current->left->type == 0) {
            //rechts Zahl
            if (current->right->type == 0) {
                current->type = 0;
                current->value = findSum(current->left->value, current->right->value);
                current->right->parent = NULL;
                current->left->parent = NULL;
                current->right = NULL;
                current->left = NULL;
            }
            //rechts AdditionsTree
            else if (current->right->type == 1) {
               
                if (current->left->value != "0")
                    Addition_skalar_AdditionsTree(current->left->value, current->right);
                if (current->parent != NULL) {
                    if (left) {
                        current->parent->left = current->right;
                        current->right->parent = current->parent;
                    }
                    else {
                        current->parent->right = current->right;
                        current->right->parent = current->parent;
                    }
                    current = current->right;
                }
                else {
                    return current->right;
                }
                }
            //rechts Xi
            else if (current->right->type == 3) {
                node* swap = current->left;
                current->left = current->right;
                current->right = swap;
            }

            
        }
        //Links und Rechts AdditionsTree
        else if (current->left->type == 1&& current->right->type==1) {
            op = current;
            current->right= Addition_AdditionsTrees_simplify(current->left, current->right);
           
            if (current->right->value != "0" && current->parent != NULL) {
                if (left) {
                    current->parent->left = current->right;
                    current->right->parent = current->parent;
                }
                else {
                    current->parent->right = current->right;
                    current->right->parent = current->parent;
                }
                current = current->right;
            }
            else return current->right;
        
     


        }
        //Links  AdditionsTree und Rechts Zahl
        else if (current->left->type == 1 && current->right->type == 0) {
            node* swap = current->left;
            current->left = current->right;
            current->right = swap;
            op = current;
            if(current->left->value!="0")
                Addition_skalar_AdditionsTree(current->left->value, current->right);
            if (current->parent != NULL) {
                if (left) {
                    current->parent->left = current->right;
                    current->right->parent = current->parent;
                }
                else {
                    current->parent->right = current->right;
                    current->right->parent = current->parent;
                }
                current = current->right;
            }
            else {
                return current->right;
            }
        
      }
        //Links  AdditionsTree und Rechts Xi
        else if (current->left->type == 1 && current->right->type == 3) {
            node* swap = current->left;
            current->left = current->right;
            current->right = swap;
            current->right=Addition_Tree_AdditionsTree(current->left, current->right,getPow(current->left));
            if (current->parent != NULL) {
                if (left) {
                    current->parent->left = current->right;
                    current->right->parent = current->parent;
                }
                else {
                    current->parent->right = current->right;
                    current->right->parent = current->parent;
                }
                current = current->right;
            }
            else {
                return current->right;
            }

        }
        //Links  Xi und Rechts AdditionsTree
        else if (current->left->type == 3 && current->right->type == 1) {
        current->right = Addition_Tree_AdditionsTree(current->left, current->right, getPow(current->left));
        if (current->parent != NULL) {
            if (left) {
                current->parent->left = current->right;
                current->right->parent = current->parent;
            }
            else {
                current->parent->right = current->right;
                current->right->parent = current->parent;
            }
            current = current->right;
        }
        else {
            return current->right;
        }

        }
        //Links und Rechts Xi
        else if (current->left->type == 3 && current->right->type == 3) {
            if (current->left->xi > current->right->xi) {
                node* swap = current->left;
                current->left = current->right;
                current->right = swap;
            }
            else if (current->left->xi == current->right->xi) {
                
                node* NewNode = newNode(1, "+", current->parent);
                if (NewNode->parent != NULL) {
                    if (left)
                        NewNode->parent->left = NewNode;
                    else 
                        NewNode->parent->right = NewNode;
                    
                }

                NewNode->right= newNode(0, "0", NewNode);
                node* secNewNode= newNode(2, "*", NewNode);
                NewNode->left = secNewNode;
                secNewNode->left = newNode(0, "2", secNewNode);
                secNewNode->right = current->right;
                current->right->parent = secNewNode;
                current = NewNode;
            }

        }
        

    }
    else if (current->type == 2) {
    //Links Zahl
        if (current->left->type == 0) {
            //Rechts Zahl
            if (current->right->type == 0) {
                current->type = 0;
                current->value = multiply(current->left->value, current->right->value);
                current->right->parent = NULL;
                current->left->parent = NULL;
                current->right = NULL;
                current->left = NULL;
            }
            //Rechts AdditionsTree
            else if (current->right->type == 1) {
                op = current;
                if (current->left->value != "1")
                Multiplikation_Addition_simplify_type0(current->left->value, current->right,false);
                if (left) {
                    current->parent->left = current->right;
                    current->right->parent = current->parent;
                }
                else {
                    current->parent->right = current->right;
                    current->right->parent = current->parent;
                }
                current = current->right;
            }
          
        }
        //Links und Rechts AdditionsTree
        else if (current->left->type == 1&&current->right->type==1) {
            op = current;
            current->right=Multiplikation_simplify_itadd(current->left, current->right);
          
            if (left) {
                current->parent->left = current->right;
                current->right->parent = current->parent;
            }
            else {
                current->parent->right = current->right;
                current->right->parent = current->parent;
            }
            current = current->right;
        }
        //Links AdditionsTree und Rechts Zahl
        else if (current->left->type == 1 && current->right->type == 0) {
            node* swap = current->left;
            current->left = current->right;
            current->right = swap;
            op = current;
            if (current->left->value != "1")
            Multiplikation_Addition_simplify_type0(current->left->value, current->right,false);
            if (left) {
                current->parent->left = current->right;
                current->right->parent = current->parent;
            }
            else {
                current->parent->right = current->right;
                current->right->parent = current->parent;
            }
            current = current->right;
        }
        //Links Xi und Rechts Zahl
        else if (current->left->type == 3 && current->right->type == 0) {
            node* swap = current->left;
            current->left = current->right;
            current->right = swap;
        }
        //Links Xi und Rechts AdditionsTree
        else if (current->left->type == 3 && current->right->type == 1) {
            op = current;
            current->right= Multiplikation_Addition_simplify_type3(current->left, current->right,false);
          
            if (left) {
                current->parent->left = current->right;
                current->right->parent = current->parent;
            }
            else {
                current->parent->right = current->right;
                current->right->parent = current->parent;
            }
            current = current->right;
        }
        //Links AdditionsTree und Rechts Xi
        else if (current->left->type == 1 && current->right->type == 3) {
            node* swap = current->left;
            current->left = current->right;
            current->right = swap;
            op = current;
            current->right= Multiplikation_Addition_simplify_type3(current->left, current->right,false);
           
            if (left) {
                current->parent->left = current->right;
                current->right->parent = current->parent;
            }
            else {
                current->parent->right = current->right;
                current->right->parent = current->parent;
            }
            current = current->right;
        }
        //Links und Rechts Xi
        else if (current->left->type == 3 && current->right->type == 3) {
            if (current->left->xi > current->right->xi) {
                node* swap = current->left;
                current->left = current->right;
                current->right = swap;
                
            }
            current->left->pow =2;
        }
        
        
       
    }
    else if (current->type == 3) {
        string expression = getExpression(current);
        int val = Xi[expression];
        if (val == 0) {
            Xi[expression] = cnt3;
            current->xi = cnt3;
            cnt3++;

        }
        else
            current->xi = val;

        current->pow =1;
    }



    return current;
}
string getExpression_Final(node* current) {

    if (current->type == 1) {
        if (current->right->value != "0")
            return "(" + getExpression_Final(current->left) + "+" + getExpression_Final(current->right) + ")";
        else return getExpression_Final(current->left);
    }
        
    else if (current->type == 2) {
        if(current->left->value!="1")
            return "(" + getExpression_Final(current->left) + "*" + getExpression_Final(current->right) + ")";
        else return getExpression_Final(current->right);

    }
       
    else if (current->type == 3)
        return "(" + getExpression_Final(current->left) + "#" + getExpression_Final(current->right) + ")";
    else
        return current->value;
}

int main() {
    int t;
    cin >> t;
   for (int tc = 1; tc <= t; tc++) {

        equivalenceclasses.clear();
        cnt = 1;
        cnt3 = 1;
        int n;
        cin >> n;
        ans = vector<int>(n);
        Ei = vector<string>(n);
        EiTrees = vector<node*>(n);
       
        for (int i = 0; i < n; i++) {
            cin >> Ei[i];
            EiTrees[i] = construct(i, 0, Ei[i].size(), NULL, true);
            EiTrees[i] = simplify(EiTrees[i], true);
            string Tupel = getExpression_Final(EiTrees[i]);
           //cout << endl << Tupel << endl;
            int val = equivalenceclasses[Tupel];
            if (val == 0) {
                equivalenceclasses[Tupel] = cnt;
                ans[i] = cnt;
                cnt++;
            }
            else
                ans[i] = val;
            

        }

       cout << "Case #" << tc << ": ";
        for (int i = 0; i < n; i++)
            cout << ans[i] << " ";

        cout << endl;



    }


    return 0;
}
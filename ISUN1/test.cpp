#include<bits/stdc++.h>
using namespace std;

struct node 
{ 
    int key;
    int cleft, idx;
    struct node *left, *right; 
}; 
   
// A utility function to create a new BST node 
struct node *newNode(int item) 
{ 
    struct node *temp =  (struct node *)malloc(sizeof(struct node)); 
    temp->key = item; 
    temp->cleft=0;
    temp->left = temp->right = NULL; 
    return temp; 
}
   
/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) {
    	
        node->left  = insert(node->left, key); 
        node->cleft++;
	}
    else
        node->right = insert(node->right, key);  
  
    /* return the (unchanged) node pointer */
    return node; 
} 

int index(struct node* node,int key){
    //assume the target is exist in the tree
//    cout<<node->key<<endl;
    if(node->key==key){
        if(node->left!=NULL && node->left->key==key) return index(node->left,key);
        else return node->cleft;
    }
    else if(node->key>key){
        return index(node->left,key);
    }
    else if(node->key<key){
        return node->cleft+1+index(node->right,key);
    }
}

int main() { 
    // Click HELP above to see examples of handling input/debug/output 
    // INPUT: scanf("%i", &n); 
    // DEBUG: printf("%d\n", n); 
    // OUTPUT: printf("%d\n", result); 
    
    //we can use AVL but im afraid i cannot complete by the time
    int n;
    node* parent=NULL;
    cin>>n;
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        parent=insert(parent,temp);
    }
    int ask;
    cin>>ask;
    cout<<index(parent,ask)<<endl;
    // Write the code to solve the problem below, 
    // format the "result" as specified in the problem statement 
    // and finally, write the result to stdout 
    // IMPORTANT: Remove all debug statements for final submission 
    return 0; 
} 

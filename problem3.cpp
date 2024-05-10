//Bobokulov Asilbek 230092 FCS1
//CS 111 Data Structures and Algorithms
#include<bits/stdc++.h>
using namespace std;
class Node {
public:
    int key;
    Node *left;
    Node *right;
    int height;
};
int height(Node *node){
    if(node==NULL) return 0;
    return node->height;
}
int getBalanceFactor(Node *node){
    if(node==NULL) return 0;
    return height(node->left)- height(node->right);
}
Node *newNode(int key){
    Node *node=new Node();
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->height=1;
    return node;
}
Node *rotateRight(Node *x){
    Node *y=x->left;
    Node *t=y->right;
    y->right=x;
    x->left=t;
    x->height=max(height(x->right), height(x->left))+1;
    y->height=max(height(y->right), height(y->left))+1;
    return y;
}
Node *rotateLeft(Node *y){
    Node *x=y->right;
    Node *t=x->left;
    x->left=y;
    y->right=t;
    y->height=max(height(y->left), height(y->right))+1;
    x->height=max(height(x->left), height(x->right))+1;
    return x;
}
Node *insertNode(Node *node, int key){
    if(node==NULL){
        return newNode(key);
    }
    if(key<node->key){
        node->left= insertNode(node->left,key);
    }else if(key>node->key){
        node->right= insertNode(node->right,key);
    }else{
        return node;
    }
    node->height=1+max(height(node->left), height(node->right));
    int balanceFactor= getBalanceFactor(node);
    if(balanceFactor>1){
        if(key<node->left->key){
            return rotateRight(node);
        }else if(key>node->left->key){
            node->left= rotateLeft(node->left);
        return rotateRight(node);
        }
    }
    if(balanceFactor<-1){
        if(key<node->right->key){
            node->right= rotateRight(node->right);
            return rotateLeft(node);
        }else if(key>node->right->key){
            return rotateLeft(node);
        }
    }
    return node;
}
Node *nodeWithMimumValue(Node *node) {
    Node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}
Node *deleteNode(Node *node, int key){
    if(node==NULL){
        return node;
    }
    if(key<node->key){
        node->left= deleteNode(node->left,key);
    }else if(key>node->key){
        node->right= deleteNode(node->right,key);
    }else{
        if(node->right==NULL||node->left==NULL){
        Node* temp=node->left?node->left:node->right;
        if(temp==NULL){
            temp=node;
            node=NULL;
        }else{
            *node=*temp;}
            free(temp);
        }else{
            Node *temp = nodeWithMimumValue(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right,
            temp->key);
        }
    }
    if (node==NULL){
        return node;
    }
    node->height=1+max(height(node->left), height(node->right));
    int balanceFactor= getBalanceFactor(node);
    if(balanceFactor>1){
        if(getBalanceFactor(node->left)>=0){
            return rotateRight(node);
        }else{
            node->left= rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if(balanceFactor<-1){
        if(getBalanceFactor(node->right)<=0){
        return rotateLeft(node);
    }else{
        node->right= rotateRight(node->right);
        return rotateLeft(node);
    }
    }
    return node;
}
vector<pair<double, double>> vec;
void printTree(Node *root) {
    if (root != nullptr) {
        vec.push_back({root->height, root->key});
        printTree(root->left);
        printTree(root->right);
    }
}
int maxHeight(Node *root) {
    int mx = 1;
    if (root != nullptr) {
        mx = max(root->height, mx);
        printTree(root->left);
        printTree(root->right);
    }
    return mx;
}
int main()
{
    Node *AVLTree;
    int n; cin >> n;

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        AVLTree = insertNode(AVLTree, x);
    }
    printTree(AVLTree);
    vector<double> ans(maxHeight(AVLTree) + 1);
    for(auto x:vec){
        ans[x.first] += x.second;
        //cout << x.first << ' ' << x.second << '\n';
    }
    for(int i = 0; i < ans.size(); i++){
        double cnt = 0;
        for(auto x:vec) if(x.first == i) cnt ++;
        if(cnt) ans[i] /= cnt;
    }
    reverse(ans.begin(), ans.end()); ans.pop_back();
    for(auto x:ans) cout << x << ' ';
}

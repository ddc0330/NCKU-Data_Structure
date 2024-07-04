#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    char color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node* initializeNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = 'R';
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void leftRotate(Node** root, Node* x){ //變更*root的值，使用Node** //變更x指向的值，使用Node*
    Node* y = x->right;
    //link x & y->left
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    //link root & y
    y->parent = x->parent;
    if(x->parent == NULL) { //x is root
        *root = y;
    }
    else if(x == x->parent->left) { //x is the left of root
        x->parent->left = y;
    }
    else{ //x is the right of root
        x->parent->right = y;
    }
    //link x & y
    y->left = x;
    x->parent = y;
}

void rightRotate(Node** root, Node* y){ 
    Node* x = y->left;
    //link y & x->rigt
    y->left = x->right;
    if(x->right != NULL){
        x->right->parent = y;
    }
    //link x & root
    x->parent = y->parent;
    if(y->parent == NULL){ // y is root
        *root = x;
    }
    else if(y == y->parent->left){ // y is the left of root
        y->parent->left = x;
    }
    else{ // y is the right of root
        y->parent->right = x;
    }
    //link x & y
    x->right = y;
    y->parent = x;
}

void insertFixup(Node** root, Node* newNode){
    //when newNode is root or its parent is B,we dont need to change 
    while(newNode->parent != NULL && newNode->parent->color == 'R'){ 
        if(newNode->parent == newNode->parent->parent->left){ //newNode is left
            Node* y = newNode->parent->parent->right; //uncle node
            if(y != NULL && y->color == 'R'){ //uncle node is RED
                newNode->parent->color = 'B';
                y->color = 'B';
                newNode->parent->parent->color = 'R';
                newNode = newNode->parent->parent; //newnode point to grandpa node and keep fixing
            }
            else{ //uncle node is black or NULL node(is black too)
                if(newNode == newNode->parent->right){ //newNode is right,
                    newNode = newNode->parent;
                    leftRotate(root, newNode);
                }
                //now newNode is left
                newNode->parent->color = 'B';
                newNode->parent->parent->color = 'R';
                rightRotate(root, newNode->parent->parent);
            }
        }
        else{ // newNode is right,contrary rotate way
            Node* y = newNode->parent->parent->left;
            if (y != NULL && y->color == 'R') {
                newNode->parent->color = 'B';
                y->color = 'B';
                newNode->parent->parent->color = 'R';
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rightRotate(root, newNode);
                }
                newNode->parent->color = 'B';
                newNode->parent->parent->color = 'R';
                leftRotate(root, newNode->parent->parent);
            }
        }
    }
    (*root)->color = 'B'; // Root must always be black
}

void insert(Node** root, int data){
    Node* newNode = initializeNode(data);
    Node* y = NULL;
    Node* x = *root;
    // point x to the insert position, y be the parent
    while (x != NULL) {
        y = x;
        if (newNode->data < x->data) {
            x = x->left;
        }
        else if (newNode->data > x->data) {
            x = x->right;
        }
        else {
            // 如果資料已存在，釋放新節點並立即返回
            free(newNode);
            return;
        }
    }
    newNode->parent = y;

    if(y == NULL){
        *root = newNode; // Tree is empty
    }
    else if(newNode->data < y->data) {
        y->left = newNode;
    }
    else {
        y->right = newNode;
    }
    insertFixup(root, newNode);
}

Node* search(Node* root, int data) {
    //point root to the data we want to find, or set root NULL
    while (root != NULL && root->data != data) {
        if (data < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root ;
}

void transplant(Node** root, Node* u, Node* v) { //u->parent remove link from u and link to v
    if (u->parent == NULL) {//u is root
        *root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

Node* minimum(Node* x) {
    Node* cur = x;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

Node* createNilNode() {
    Node *nilNode = (Node*)malloc(sizeof(Node));
    nilNode->color = 'B';
    nilNode->left = nilNode->right = nilNode->parent = NULL;
    return nilNode;
}

void deleteFixup(Node** root, Node* x , Node* xparent) {
    if(x!=NULL)
        xparent=x->parent;
    //遞補紅色不用做
    while (x != *root && (x == NULL || x->color == 'B')) {          //可能導致無窮迴圈
            Node *temp=createNilNode();
        if (x ==xparent->left) {             //x may be NULL
            Node *w =xparent->right;
            if (w != NULL && w->color == 'R') {
                // Case 1: Sibling is red
                w->color = 'B';
                xparent->color = 'R';
                leftRotate(root, xparent);
                w = xparent->right;
            }
            if(w==NULL){
                xparent->right=temp;
                temp->parent=xparent;
                w=temp;
            }
            if ((w->left == NULL || w->left->color == 'B') && (w->right == NULL || w->right->color == 'B')) {
                // Case 2: Both children of the sibling are black
                w->color = 'R';
                x = xparent;
            }
            else {
                if (w->right == NULL || w->right->color == 'B') {
                    // Case 3: The right child of the sibling is black
                    if (w->left != NULL) {
                        w->left->color = 'B';
                    }
                    w->color = 'R';
                    rightRotate(root, w);
                    w = xparent->right;
                }
                if(w==NULL){
                    xparent->right=temp;
                    temp->parent=xparent;
                    w=temp;
                }
                // Case 4: The right child of the sibling is red
                w->color = xparent->color;
                xparent->color = 'B';
                if (w->right != NULL) {
                    w->right->color = 'B';
                }
                leftRotate(root, xparent);
                x = *root; // Exit the loop
            }
        }
        else {
            // Symmetric to the "left" case
            Node *w = xparent->left;

            if (w != NULL && w->color == 'R') {
                w->color = 'B';
                xparent->color = 'R';
                rightRotate(root, xparent);
                w = xparent->left;
            }
            if(w==NULL){
                temp->parent=xparent;
                xparent->left=temp;
                w=temp;
            }

            if ((w->right == NULL || w->right->color == 'B') && (w->left == NULL || w->left->color == 'B')) {
                w->color = 'R';
                x = xparent;
            }
            else {
                if (w->left == NULL || w->left->color == 'B') {
                    if (w->right != NULL) {
                        w->right->color = 'B';
                    }
                    w->color = 'R';
                    leftRotate(root, w);
                    w = xparent->left;
                }
                if(w==NULL){
                    temp->parent=xparent;
                    xparent->left=temp;
                    w=temp;
                }
                w->color = xparent->color;
                xparent->color = 'B';
                if (w->left != NULL) {
                    w->left->color = 'B';
                }
                rightRotate(root, xparent);
                x = *root; // Exit the loop
            }
        }
    }
    if (x != NULL) {
        x->color = 'B'; // Ensure that the root is always black
    }
}

void deleteNode(Node**root ,Node* node) 
{
    Node* y = node; 
    Node* x = NULL; //y's child //which will replace y
    Node *xparent=NULL;
    char delete_color = node->color;
    if (node == NULL) {
        free(node);
        return;
    }
    if(node->left==NULL&&node->right==NULL){
        if(node->parent->left==node){
            node->parent->left=NULL;
            free(node);
        }
        else if(node->parent->right==node){
            node->parent->right=NULL;
            free(node);
        }
        return;
    }
    else if (node->left == NULL) {
        x = node->right;
        transplant(root ,node, node->right);
    }
    else if (node->right == NULL) {
        x = node->left;
        transplant(root ,node, node->left);
    }
    else {
        y = minimum(node->right);
        delete_color = y->color;
        x = y->right;
        xparent=y;
        if (y->parent == node) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            transplant(root, y, y->right);
            y->right = node->right;
            if (y->right != NULL) {
                y->right->parent = y;
            }
        }
        transplant(root, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }
    if (delete_color == 'B') {
        deleteFixup(root, x , xparent);
    }
    free(node);
}

void delete(Node **root, int x) {
    Node *nodeToDelete = search(*root, x);

    if (nodeToDelete != NULL) {
        deleteNode(root, nodeToDelete); 
    }
    else{
        free(nodeToDelete);
    }
}

int main(){
    Node* root = NULL;
    char a[20];int x;
    while(1){
        scanf("%s",a);
        if(strcmp(a,"insert")==0){
            scanf("%d",&x);
            insert(&root,x);
        }
        else if(strcmp(a,"search")==0){
            scanf("%d",&x);
            Node* tmp = search(root,x);
            if (tmp != NULL) {
                if (tmp->color == 'R') {
                    printf("red\n");
                }
                else if (tmp->color == 'B') {
                    printf("black\n");
                }
            }
            else {
                printf("Not found\n");
            }
        }
        else if(strcmp(a,"delete")==0){
            scanf("%d",&x);
            delete(&root,x);
        }
        else if(strcmp(a,"quit")==0){
            break;
        }
    }  
    return 0;
}
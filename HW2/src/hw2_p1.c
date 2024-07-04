#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Node {
    int key;
    int value;
    int degree; //child's num
    int marked; //lost children or not
    struct Node* parent;
    struct Node* child;
    struct Node* right;
    struct Node* left;
} Node;

typedef struct FHeap {
    Node* min;
    int numNodes;
} FHeap;

FHeap* createFheap(){
    FHeap* newHeap = (FHeap*)malloc(sizeof(FHeap));
    newHeap->min = NULL;
    newHeap->numNodes = 0;
    return newHeap;
}

Node* createNode(int key,int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->degree = 0;
    newNode->marked = 0;
    newNode->child = NULL;
    newNode->parent = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    return newNode;
}
void insert(FHeap* heap, int key, int value){
    Node* newNode = createNode(key, value);
    //if heap is empty
    if (heap->min == NULL) {
        heap->min = newNode;
    }
    else {
        //insert newnode to min's right
        newNode->right = heap->min->right;
        newNode->left = heap->min;
        heap->min->right->left = newNode;
        heap->min->right = newNode;
        // Update min if necessary
        if (newNode->key < heap->min->key) {
            heap->min = newNode;
        }
    }
    heap->numNodes++;
}

void link(Node* min, Node* other){
    // Remove other from the root list
    other->left->right = other->right;
    other->right->left = other->left;
    // Make other a child of min
    other->parent = min;
    other->left = other;
    other->right = other;
    min->degree++;
    if (min->child == NULL) {
        min->child = other;
    }
    else {
        other->right = min->child->right;
        other->left = min->child;
        min->child->right->left = other;
        min->child->right = other;
    }
    other->marked = 0;
}

void consolidate(FHeap* heap){
    //create degree list
    int maxDegree = 1000;
    Node* arr[maxDegree];
    for (int i = 0; i < maxDegree; i++) {
        arr[i] = NULL;
    }
    // Count the number of roots in the root list
    Node* current = heap->min;
    int numRoots = 0;
    do {
        numRoots++;
        current = current->right;
    } while (current != heap->min);
    // Traverse the root list and consolidate nodes with the same degree
    current = heap->min;
    for (int i = 0; i < numRoots; i++) {
        int degree = current->degree;
        Node* next = current->right;
        //check min
        if(current->key < heap->min->key)
            heap->min = current;
        //degree already exist
        while (arr[degree] != NULL) {
            Node* other = arr[degree];
            if (current->key > other->key) {
                link(other,current);
                heap->min = other;
            }
            else{
                link(current,other);
                heap->min = current;
            }
            arr[degree] = NULL;
            degree++;
        }

        arr[degree] = current;
        current = next;
    }
}

void extract(FHeap* heap){
    Node* minNode = heap->min;
    // min has child
    if(minNode->child != NULL){
        Node* child = minNode->child;
        do{
            Node* nextChild = child->right;
            //put child to min right side
            child->left = heap->min;
            child->right = heap->min->right;
            heap->min->right->left = child;
            heap->min->right = child;
            child->parent = NULL;
            child = nextChild;
        }while(child != minNode->child);
    }
    // Remove minNode from the root list
    minNode->left->right = minNode->right;
    minNode->right->left = minNode->left;
    //heap has only one node
    if (minNode == minNode->right) {
        heap->min = NULL;
    }
    else {
        //min point to the right node of min
        heap->min = minNode->right;
        consolidate(heap);
    }
    
}

void cut(FHeap* heap, Node* child, Node* parent) {
    // Remove child from parent
    // only one child
    if (child->right == child) {
        parent->child = NULL;
    }
    //multiple child
    else {
        child->right->left = child->left;
        child->left->right = child->right;
        //this child link to parent
        if (parent->child == child) {
            parent->child = child->right;
        }
    }
    parent->degree--;

    // Add child to root list
    child->left = heap->min;
    child->right = heap->min->right;
    heap->min->right->left = child;
    heap->min->right = child;
    child->parent = NULL;
    child->marked = 0;
}

void cascadingCut(FHeap* heap, Node* node) {
    Node* parent = node->parent;

    if (parent != NULL) {
        if (node->marked != 1) {
            node->marked = 1;
        }
        else {
            cut(heap, node, parent);
            cascadingCut(heap, parent);
        }
    }
}

Node* findNode(Node* start, int key, int value) {
    Node* current = start;
    Node* result = NULL;
    do {
        //min is result
        if (current->key == key && current->value == value) {
            result = current;
            break;
        }
        //min has child
        if (current->child != NULL) {
            result = findNode(current->child, key, value);
            if (result != NULL) {
                break;
            }
        }
        //find next root
        current = current->right;
    } while (current != start);

    return result;
}

void decrease(FHeap* heap, int key, int value , int y){
    Node* target = findNode(heap->min, key, value);
    target->key -= y;
    Node* parent = target->parent;
    if (parent != NULL && target->key < parent->key) {
        cut(heap, target, parent);
        cascadingCut(heap, parent);
    }
    if (target->key < heap->min->key) {
        heap->min = target;
    }
}

int main(){
    FHeap* heap = createFheap();
    char a[20];
    int x,y,val;
    while(1){
        scanf("%s",a);
        if(strcmp(a,"insert") == 0){
            scanf("%d %d",&x,&val);
            insert(heap, x, val);
        }
        else if(strcmp(a,"extract") == 0 && heap->min!=NULL){
            printf("(%d)%d\n",heap->min->key,heap->min->value);
            extract(heap);
        }
        else if(strcmp(a,"delete") == 0){
            scanf("%d %d",&x,&val);
            decrease(heap, x, val, 1000000);
            extract(heap);
        }
        else if(strcmp(a,"decrease") == 0){
            scanf("%d %d %d",&x,&val,&y);
            decrease(heap, x, val, y);
        }
        else if(strcmp(a,"quit") == 0){
            break;
        }
    }
}
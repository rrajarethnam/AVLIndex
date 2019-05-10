#include <stdio.h>

using namespace std;

template <typename K, typename T>
class AVLIndex{

    public:
    Index(){
        root = NULL;
    }
    void add(K key, T object){
        root = add(root, key, object);
    }

    bool remove(K key){
        return deleteKey(&root, key);     
    }

    bool get(K key, T* value){
        return get(root, key, value);
    }

    int max(int a, int b){
        return a > b ? a : b;
    }

    
    struct Node{
        K key;
        T value;
        Node *left;
        Node *right;
        Node *parent;
        int height;

        Node(K key, T value){
            this->key = key;
            this->value = value;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }
    };

    int height(Node* node){
        return node != NULL ? node->height : 0;
    }

    Node *root;

    void print(){
        printPreOrder(root);
        printf("\n");
    }

    void print(Node* node){
    
        if(node == NULL)
            return;
        
        if(node->left != NULL){
            print(node->left);
        }       
        printf("%d\n", node->key);
        if(node->right != NULL){
            print(node->right);
        }
        
    }

    void printPreOrder(Node* node){
    
        if(node == NULL)
            return;
        
        printf("%d[", node->key);
        if(node->left != NULL){
            printPreOrder(node->left);
        }       
        if(node->right != NULL){
            printPreOrder(node->right);
        }
        printf("]");
        
    }


    Node* add(Node* node, K key, T object){
        if(node == NULL){
            return new Node(key, object);
        }
        if(node->key == key) {
            //printf("Replacing current value\n");
            node->value = object;
            return node;
        }
        if(node->key > key){
            node->left = add(node->left, key, object);
            node->height = node->left->height+1;
            //printf("Adding to left\n");

            if(height(node->left) - height(node->right) > 1){
                node = rotateRight(node);
            }
            return node;
        }
        else{
            node->right = add(node->right, key, object);
            node->height = node->right->height+1;
            //printf("Adding to right\n");

            if(height(node->right) - height(node->left) > 1){
                node = rotateLeft(node);
            }
            return node;
        }
        
    }

    Node* rotateRight(Node* node){
        Node* newNode = node->left;
        node->left = newNode->right;
        newNode->right = node;
        node->height = max(height(node->left), height(node->right))+1;
        newNode->height = max(height(newNode->left), height(newNode->right))+1;
        return newNode;
    }

    Node* rotateLeft(Node* node){
        Node* newNode = node->right;
        node->right = newNode->left;
        newNode->left = node;
        node->height = max(height(node->left), height(node->right))+1;
        newNode->height = max(height(newNode->left), height(newNode->right))+1;
        return newNode;
    }


    bool get (Node* node, K key, T* value){
        
        if( node == NULL)
            return false;
        if(node->key == key){
            *value = node->value;
            return true;
        }
        else{
            if(node->key > key){
                return get(node->left, key, value);
            } else {
                return get(node->right, key, value);
            }
        }
    }

    Node* min(Node* node){
        if(node == NULL){
            return NULL;
        }
        while(node->left != NULL){
            node->left->parent = node;
            node = node->left;
        }
        return node; 
    }

    Node* deleteMin(Node* parent, Node* node){
        if(node == NULL)
            return NULL;
        if(node->left == NULL){
            if(parent->left == node)
                parent->left = NULL;
            else parent->right = NULL;
        }
        else node = deleteMin(node, node->left);
        node->parent = parent;
        return node;
    }

    bool deleteKey(Node **pnode, K key){
        Node *node = *pnode;
        bool deleted = false;
        if (node->key == key){
            if(node->left == NULL && node->right == NULL){
                *pnode = NULL;
            }
            else if(node->left == NULL){
                *pnode = node->right;
            }
            else if (node->right == NULL){
                *pnode = node->left;
            }
            else{
                Node* rnode = deleteMin(node, node->right);
                node->key = rnode->key;
                node->value = rnode->value;
                
                if(rnode->parent->right == NULL)
                    node->height = node->height-1;
                delete rnode;
            }
            deleted = true;
        }
        else{
            if (node->key > key){
                if (node->left != NULL)
                    deleted = deleteKey(&node->left, key);
            }
            else {
                if (node->right != NULL)
                    deleted = deleteKey(&node->right, key);
            }
        }
        if(deleted == true){
            if(height(node->left) - height(node->right) > 1){
                *pnode = rotateRight(node);
            }

            if(height(node->right) - height(node->left) > 1){
                *pnode = rotateLeft(node);
            }
        }
        return deleted;
    }
};

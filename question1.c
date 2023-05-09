#include <stdio.h>
#include <stdlib.h>

typedef enum TypeTag {ADD, SUB, MUL, DIV, FIB, LEAf} TypeTag;

typedef struct Node
{
    TypeTag type;
    long long num;
    struct Node* left;
    struct Node* right;

} Node;

Node* create_node(TypeTag type, long long num, Node* left, Node* right)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->num = num;
    node->left = left;
    node->right = right;
    return node;
}

Node* makeFunc(TypeTag type, Node* left, Node* right)
{
    return create_node(type, 0, left, right);
}


// bottom up approach for fibonacci
long long fibonacci(long long n)
{
    if (n == 0 || n == 1)
        return n;

    long long f0 = 0;
    long long f1 = 1;
    long long f2 = 1;
    for (int i = 2; i <= n; i++)
    {
        f2 = f0 + f1;
        f0 = f1;
        f1 = f2;
    }
    return f2;
}

void calc(Node *node){
    if(node == NULL){
        return;
    }else if(node->type == LEAf){
       return;
   }
   else{
       // check if right is Null and if it is null i need to get the left node number abs then get its fib
        calc(node->left);
        calc(node->right);
        int shouldGetFib = 0;
        if(node->right == NULL) {
            node->right = create_node(LEAf, 0, NULL, NULL);
            shouldGetFib = 1;
        }
        if(node->type == ADD){
            node->num = node->left->num + node->right->num;
        }
        else if(node->type == SUB){
            node->num =  node->right->num - node->left->num ;
        }
        else if(node->type == MUL){
            node->num = node->left->num * node->right->num;
        }
        else if(node->type == DIV){
            if(node->left->num == 0){
                printf("Error: Division by zero\n");
                exit(1);
            }
            node->num = node->right->num / node->left->num ;
        }
        node->type = LEAf;

        if(shouldGetFib==1) {
            if(node->left->num<0){
                node->num = fibonacci(-1*node->left->num-1);
            } else{
                node->num = fibonacci(node->left->num-1);
            }
        }
        free(node->left);
        free(node->right);
        node->left = NULL;
        node->right = NULL;

   }
}


int main(){
    Node *node1 = create_node(LEAf, 10, NULL, NULL);
    Node *node2 = create_node(LEAf, 6, NULL, NULL);
    Node *node3 = create_node(LEAf, 4, NULL, NULL);
    Node *node4 = create_node(LEAf, 5, NULL, NULL);

    Node *add = makeFunc(ADD, node1, node2);
    Node *mul = makeFunc(MUL, node3, node4);
    Node *sub = makeFunc(SUB,mul, add);
    Node *fib = makeFunc(SUB, sub, NULL);

    calc(add);
    printf("%lld\n", add->num);
    calc(mul);
    printf("%lld\n", mul->num);
    calc(sub);
    printf("%lld\n", sub->num);
    calc(fib);
    printf("%lld\n", fib->num);


}





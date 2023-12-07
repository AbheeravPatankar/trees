#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
struct node
{
    struct node* ptrToRightNode;
    int data;
    struct node* ptrToLeftChild;
};
struct node* temp2;
int top = 0;
void push(struct node* ptr, struct node* stack)
{

    stack[top] = *ptr;
    top++;
}
struct node pop(struct node* stack)
{
    struct node store;
    top--;
    store = stack[top];

    return store;
}
void inOrderTraversal(struct node* root)
{
    struct node stack[10];
    struct node store;
    struct node* temp;
    temp = root;
        while (temp != NULL)
        {           
            push(temp, stack);
            temp = temp->ptrToLeftChild;
        }
        push(temp, stack);
        printf("%d ", temp->data);
        store = pop(stack);
        temp = store.ptrToRightNode;

}
void check(struct node* temp, int inputData)
{

    if (temp != NULL)
    {
        if (inputData > temp->data)
        {
            temp2 = temp;
            check(temp = temp->ptrToRightNode, inputData);
            return;
        }
        else
        {
            temp2 = temp;
            check(temp = temp->ptrToLeftChild, inputData);
            return;
        }
    }
    else
        return;
}
struct node* insertNode(struct node* root)
{
    int data;

    static struct node* newNode;
    newNode = (struct node*)malloc(sizeof(struct node));
    newNode->ptrToLeftChild = NULL;
    newNode->ptrToRightNode = NULL;
    scanf("%d", &data);
    newNode->data = data;
    check(root, data);
    if (temp2 == NULL)
    {
        root = newNode;
        newNode->data = data;
        return root;
    }
    else if (data > temp2->data)
    {
        temp2->ptrToRightNode = newNode;
    }
    else
    {
        temp2->ptrToLeftChild = newNode;
    }
}

int main()
{
    static struct node* root = NULL;

    struct node* ptrToInsert;
    int data;

    root = insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    insertNode(root);
    inOrderTraversal(root);
}
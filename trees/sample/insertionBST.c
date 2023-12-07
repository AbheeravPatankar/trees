#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
struct node
{
    struct node* ptrToRightNode;
    int data;
    struct node* ptrToLeftChild;
};
struct node* root = NULL;
void insertNode()
{
    struct node* newNode;
    struct node* temp;
    struct node* temp2 = root;
    int flag;

    if (root == NULL) // enetring root node
    {
        newNode = (struct node*)malloc(sizeof(struct node));
        scanf("%d", &newNode->data);
        root = newNode;
        newNode->ptrToRightNode = NULL;
        newNode->ptrToLeftChild = NULL;
    }
    else
    {
        temp = root;
        newNode = (struct node*)malloc(sizeof(struct node));
        scanf("%d", &newNode->data);
        while (temp != NULL)
        {
            if (newNode->data > temp->data)
            {
                temp2 = temp;
                temp = temp->ptrToRightNode;
                flag = 0;
            }
            else if (newNode->data < temp->data)
            {
                temp2 = temp;
                temp = temp->ptrToLeftChild;
                flag = 1;
            }
            if (flag == 1)
            {
                temp2->ptrToLeftChild = newNode;
            }
            else
            {
                temp2->ptrToRightNode = newNode;
            }
        }
    }

}
void display()
{
    printf("%d\n", root->data);
    printf("%d", (root->ptrToRightNode)->data);
}
int main()
{
    

    insertNode();
    insertNode();
    display();

}
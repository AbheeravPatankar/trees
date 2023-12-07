#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>



struct node
{
    struct node* ptrToRightNode;
    int data;
    struct node* ptrToLeftChild;
};
struct node* temp2;
int flag = 0;
int count = 0;
void preOrderTraversal(struct node * root)
{
    if (root == NULL)return;

    printf("%d  ", root->data);
    preOrderTraversal(root->ptrToLeftChild);
    preOrderTraversal(root->ptrToRightNode);

}

void postOrderTraversal(struct node* root)
{
    if (root == NULL)return;

    
    postOrderTraversal(root->ptrToLeftChild);
    postOrderTraversal(root->ptrToRightNode);
    printf("%d  ", root->data);

}

void inOrderTraversal(struct node* root)
{
    if (root == NULL)return;


    inOrderTraversal(root->ptrToLeftChild);
    printf("%d  ", root->data);
    inOrderTraversal(root->ptrToRightNode);
    

}

void search(struct node* root,int element)
{
    

    if (root == NULL)return;


    search(root->ptrToLeftChild, element);
    
    if (root->data == element)
    {
        flag = 1;
    }
    search(root->ptrToRightNode, element);
    

}
void check(struct node* temp, int inputData)
{
    
    if (temp != NULL)
    {
        if (inputData > temp->data)
        {
            temp2 = temp;
            check(temp = temp->ptrToRightNode, inputData);
            return ;
        }
        else
        {
            temp2 = temp;
            check(temp = temp->ptrToLeftChild, inputData);
            return ;
        }

    }
    else
        return;
}
struct node* insertNode(struct node * root)
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

struct Node* findMax(struct node* t)
{
    while (t->ptrToRightNode != NULL)
    {
        t = t->ptrToRightNode;
    }

    return t;
}

struct node* delete(struct node* root,struct node* ptrToPrevNode, int val)
{
    struct node* temp;
    
    if (root == NULL) printf("value not present");

    else if (val < root->data)
        root->ptrToLeftChild = delete(root->ptrToLeftChild,root, val);

    else if (val > root->data)
        root->ptrToRightNode = delete(root->ptrToRightNode,root, val);

    else
    {
        if (root->ptrToRightNode != NULL && root->ptrToLeftChild != NULL)
        {
            int value;
            temp = findMax(root->ptrToLeftChild);
            value = temp->data;
            temp = delete(temp, root, temp->data);
            root->data = value;
            
        }
        else if (root->ptrToLeftChild != NULL && root->ptrToRightNode == NULL)
        {
            temp = root;
            if (ptrToPrevNode->data > root->data)
            {
                ptrToPrevNode->ptrToLeftChild = root->ptrToLeftChild;
                root = root->ptrToLeftChild;
                free(temp);
            }
            else
            {
                ptrToPrevNode->ptrToRightNode = root->ptrToLeftChild;
                root = root->ptrToLeftChild;
                free(temp);
            }
        }
        else if(root->ptrToRightNode != NULL && root->ptrToLeftChild == NULL)
        {
            
            temp = root;
            if (ptrToPrevNode->data > root->data)
            {
                ptrToPrevNode->ptrToLeftChild = root->ptrToRightNode;
                root = root->ptrToRightNode;
                free(temp);
            }
            else
            {
                ptrToPrevNode->ptrToRightNode = root->ptrToRightNode;
                root = root->ptrToRightNode;
                free(temp);
            }
        }
        else //deleting leaf node
        {
            if (ptrToPrevNode->data > root->data)
            {
                ptrToPrevNode->ptrToLeftChild = NULL;
                free(root);
                root = NULL;
            }
            else
            {
                ptrToPrevNode->ptrToRightNode = NULL;
                free(root);
                root = NULL;
            }
        }
    }
    return root;
}

int main()
{
    static struct node* root = NULL;
    struct node* ptrToInsert;
    int element;
    
    

    int expression;
    printf("Enter data in root node\n");
    root = insertNode(root);
    
    while (1)
    {
        printf("Enter ur expression\n1->insertion\n2->search\n3->in order traversal\n4->preorder traversal\n5->postorder traversal\n6->delete\n7->exit\n");
        
        scanf("%d", &expression);
        switch (expression)
        {
            case 1:
                insertNode(root);
                break;
            case 2:
                printf("enter the element to search\n");
                scanf("%d", &element);
                search(root, element);
                if (flag == 1)
                {
                    printf("element found \n");

                }
                else
                {
                    flag = 0;
                    printf("element not found\n");
                }
                break;
            case 3:
                inOrderTraversal(root);
                printf("\n");
                break;
            case 4:
                postOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                preOrderTraversal(root);
                printf("\n");
                break;
            case 6:
                printf("enter the element to delete\n");
                scanf("%d", &element);
                delete(root,NULL,element);
            default:
                break;

        }
    }
    
}
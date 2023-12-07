#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node* ptrToLeft;
    struct node* ptrToRight;
}SNODE;
int maxHeight = 0;
void height(SNODE* root, int count)
{
    SNODE* temp = root;
    
    if (temp->ptrToLeft == NULL && temp->ptrToRight == NULL)
    {
        if (count > maxHeight)
        {
            maxHeight = count;
        }
    }
    else if (temp->ptrToLeft == NULL)
    {
        count++;
        temp = temp->ptrToRight;
        height(temp, count);
    }
    else if (temp->ptrToRight == NULL)
    {
        count++;
        temp = temp->ptrToLeft;
        height(temp, count);
    }
    else
    {
        count++;
        height(temp->ptrToRight, count);
        height(temp->ptrToLeft, count);
    }
}

SNODE* mirror(SNODE* root)
{
    SNODE* temp = root;
    if (temp->ptrToLeft != NULL && temp->ptrToRight != NULL)
    {
        SNODE* temp2 = temp->ptrToLeft;
        temp->ptrToLeft = temp->ptrToRight;
        temp->ptrToRight = temp2;
        mirror(temp->ptrToLeft);
        mirror(temp->ptrToRight);
    }
    else if (temp->ptrToLeft != NULL)
    {
        temp->ptrToRight = temp->ptrToLeft;
        temp->ptrToLeft = NULL;
        mirror(temp->ptrToRight);
    }
    else if (temp->ptrToRight != NULL)
    {
        temp->ptrToLeft = temp->ptrToRight;
        temp->ptrToRight = NULL;
        mirror(temp->ptrToLeft);
    }
    else
    {
        return root;
    }
    return root;
}

SNODE* insert(SNODE* root)
{
    int caseVar = 0;
    SNODE* temp = root;
    SNODE* newNode;
    int data;
    while (caseVar != -1)
    {
        printf("Enter the operation you have to perform :");
        scanf("%d", &caseVar);
        switch (caseVar)
        {
        case 1: //go left
            if (temp->ptrToLeft != NULL)
            {
                temp = temp->ptrToLeft;
                printf("\nyou are at the node %d :\n", temp->data);
            }
            else
            {
                printf("\nThe left pointer is Null\n");
            }
            break;
        case 2: // go right
            if (temp->ptrToRight != NULL)
            {
                temp = temp->ptrToRight;
                printf("\nyou are at the node %d :\n", temp->data);
            }
            else
            {
                printf("\nThe right pointer is Null\n");
            }
            break;
        case 3: //insert a node to the right of the current node
            printf("\nEnter the data inside the node :");
            scanf("%d", &data);
            newNode = (SNODE*)malloc(sizeof(SNODE));
            newNode->data = data;
            newNode->ptrToLeft = NULL;
            newNode->ptrToRight = NULL;
            temp->ptrToRight = newNode;
 
            break;
        case 4: //Insert to the left of the current node
            printf("\nEnter the data inside the node :");
            scanf("%d", &data);
            newNode = (SNODE*)malloc(sizeof(SNODE));
            newNode->data = data;
            newNode->ptrToLeft = NULL;
            newNode->ptrToRight = NULL;
            temp->ptrToLeft = newNode;

            break;
        case 5://go back to the root;
            temp = root;
            printf("\nYou are back at the node %d\n", temp->data);
            printf("\n%d %d\n", temp->ptrToLeft->data, temp->ptrToRight->data);
            break;
        case 6:
            height(root, 0);
            printf("\nThe height of the tree is %d\n", maxHeight);
            break;
        case 7: //get mirror image
            root = mirror(root);
            break;
        default:
            printf("\nInvalid input !\n");
            break;

        }
    }
}

int main()
{
    printf("Enter the data in the root node");
    SNODE* root = (SNODE*)malloc(sizeof(SNODE));
    int data;
    int count = 0;
    scanf("%d", &data);
    root->data = data;
    root->ptrToLeft = NULL;
    root->ptrToRight = NULL;
    for (int i = 0; i < 10; i++)
    {
        root = insert(root);
    }

}

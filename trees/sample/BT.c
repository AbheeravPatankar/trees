#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//  ----------------------------------------------structures------------------------------------------------------------

struct childStatus // linked list
{
	int flag;
	int data;
	struct childStatus* ptrToNextNode;
};

struct node // tree
{
	struct node* ptrToLeftChild;
	int data;
	struct node* ptrToRightNode;
};

struct queue // queue
{
	struct node* data;
	struct queue* ptrToNextNode;
};

//  ----------------------------------------------global declaratoins------------------------------------------------------------

struct queue* rear;
struct queue* front;
static struct childStatus* headToLinkedList = NULL;
static struct childStatus* tailToLinkedList = NULL;

//  ----------------------------------------------queue functions--------------------------------------------------------

void enqu(struct node* ptr)
{

	static struct queue* temp;
	static struct queue* newNode = NULL;
	if (front == NULL)
	{
		rear = (struct queue*)malloc(sizeof(struct queue)); // creating queue head node
		rear->data = ptr;
		rear->ptrToNextNode = NULL;

		front = rear;
	}
	else
	{
		newNode = (struct queue*)malloc(sizeof(struct queue));
		newNode->data = ptr;
		newNode->ptrToNextNode = NULL;
		rear->ptrToNextNode = newNode;
		rear = newNode;
	}
}

void dequ(struct node* ptr)
{
	static struct queue* temp;
	temp = front;
	// printf("data in the dequed element is %d \n", (front->data)->data);
	front = front->ptrToNextNode;

	free(temp);
}

void freeQ()
{
	//struct queue* temp;
	//do
	//{
	//	temp = front;
	//	front = front->ptrToNextNode;
	//	free(temp);
	//} while (front != rear);
	front = NULL;
	rear = NULL;
}


// -----------------------------------------------tree functions--------------------------------------------------------

void isChildPresent(int flag, int data)
{

	struct childStatus* newNode = NULL;

	if (headToLinkedList == NULL)
	{
		headToLinkedList = (struct childStatus*)malloc(sizeof(struct childStatus));
		headToLinkedList->flag = flag;
		headToLinkedList->data = data;
		headToLinkedList->ptrToNextNode = NULL;
		tailToLinkedList = headToLinkedList;
	}
	else
	{
		newNode = (struct childStatus*)malloc(sizeof(struct childStatus));
		newNode->flag = flag;
		newNode->data = data;
		newNode->ptrToNextNode = NULL;
		tailToLinkedList->ptrToNextNode = newNode;
		tailToLinkedList = newNode;
	}
}

void lvlOrderTraverse(struct node* root)
{
	
	int flag;
	struct node* temp = root;
	enqu(root);
	while (front != NULL)
	{
		if (root->ptrToLeftChild != NULL)
		{
			temp = root->ptrToLeftChild;
			enqu(root->ptrToLeftChild);
			isChildPresent(1, temp->data);
		}
		else
		{
			isChildPresent(0, -1);
		}

		if (root->ptrToRightNode != NULL)
		{
			temp = root->ptrToRightNode;
			enqu(root->ptrToRightNode);
			isChildPresent(1, temp->data);
		}
		else
		{
			isChildPresent(0, -1);
		}
		dequ(root);
		
		if (front != NULL)
			root = front->data;
	}
	printf("displaying elements \n");
	freeQ();
	
}

void insert(struct node* root, int nodes)
{
	static struct queue* head = NULL;

	struct node* newNode;
	int data;
	if (nodes > 0)
	{

		printf("enter the data in rightChild for the node %d or Enter -1 to leave it NULL : ", root->data);
		scanf("%d", &data);
		if (data != -1)
		{
			newNode = (struct node*)malloc(sizeof(struct node));
			newNode->ptrToLeftChild = NULL;
			newNode->ptrToRightNode = NULL;
			newNode->data = data;
			root->ptrToRightNode = newNode;
			enqu(newNode);
			nodes--;
		}
		else
		{
			root->ptrToRightNode = NULL;
		}

		printf("enter the data in left Child for the node %d or Enter -1 to leave it NULL : ", root->data);
		scanf("%d", &data);
		if (data != -1 && nodes > 0)
		{
			newNode = (struct node*)malloc(sizeof(struct node));
			newNode->ptrToLeftChild = NULL;
			newNode->ptrToRightNode = NULL;
			newNode->data = data;
			root->ptrToLeftChild = newNode;
			enqu(newNode);
			nodes--;
		}
		else
		{
			root->ptrToLeftChild = NULL;
		}
		dequ(root);
		if(front != NULL)
			insert(front->data, nodes);
		
	}
	else
	{
		freeQ();
		return;
	}
}

void display(struct node* root)
{
	struct childStatus* temp = headToLinkedList;
	printf(" %d ", root->data);
	do
	{
		// printf("%d ", temp->flag);
		if (temp->flag == 1)
		{
			printf(" %d ", temp->data);
		}
		temp = temp->ptrToNextNode;
	} while (temp != tailToLinkedList);
}

int checkForMirror(struct node* left, struct node* right)
{
	enqu(left);
	enqu(right);
	while (front != NULL)
	{

		struct node* temp;
		if (left->data != right->data)
			return 0;

		if (left->ptrToLeftChild != NULL && right->ptrToRightNode != NULL)
		{
			if ((left->ptrToLeftChild)->data != (right->ptrToRightNode)->data)
				return 0;
			enqu(left->ptrToLeftChild);
			enqu(right->ptrToRightNode);
		}
		else if (left->ptrToLeftChild == NULL && right->ptrToRightNode == NULL)
		{
			// continue;
		}
		else
		{
			return 0;
		}

		if (left->ptrToRightNode != NULL && right->ptrToLeftChild != NULL)
		{
			if ((left->ptrToRightNode)->data != (right->ptrToLeftChild)->data)
				return 0;

			enqu(left->ptrToRightNode);
			enqu(right->ptrToLeftChild);
		}
		else if (left->ptrToRightNode == NULL && right->ptrToLeftChild == NULL)
		{
			// continue;
		}
		else
		{
			return 0;
		}

		dequ(left);
		dequ(right);
		if (front != NULL)
		{
			left = front->data;
			right = (front->ptrToNextNode)->data;
		}
	}
	freeQ();
	return 1;
}

int checkForBinarySearchTree(struct node* root)
{
	enqu(root);
	int flag = 0;
	while (front != NULL)
	{
		if (root->ptrToLeftChild == NULL && root->ptrToRightNode == NULL)
		{
			
		}
		else if (root->ptrToLeftChild == NULL && root->ptrToRightNode != NULL)
		{
			if (root->data < (root->ptrToRightNode)->data)
			{
				flag = 1;
			}
			else
			{
				return 0;
				freeQ();
			}
		}
		else if (root->ptrToRightNode == NULL && root->ptrToLeftChild != NULL)
		{
			if ((root->ptrToLeftChild)->data < root->data)
			{
				flag = 1;
			}
			else
			{
				return 0;
				freeQ();
			}
		}
		else
		{
			if ((root->ptrToLeftChild)->data < root->data && root->data < (root->ptrToRightNode)->data)
			{
				flag = 1;
			}
			else
			{
				return 0;
				freeQ();
			}
		}
		if (root->ptrToLeftChild != NULL)
		{

			enqu(root->ptrToLeftChild);

		}
		else
		{
			isChildPresent(0, -1);
		}

		if (root->ptrToRightNode != NULL)
		{

			enqu(root->ptrToRightNode);

		}
		else
		{
			isChildPresent(0, -1);
		}
		dequ(root);

		if (front != NULL)
			root = front->data;
		
	}
	
	return 1;
	freeQ();
}

void printAllLeafNodes(struct node* root)
{
	
	int flagL;
	int flagR;
	struct node* temp = root;
	enqu(root);
	while (front != NULL)
	{
		if (root->ptrToLeftChild != NULL)
		{

			enqu(root->ptrToLeftChild);

			flagL = 0;
		}
		else
		{
			flagL = 1;
		}

		if (root->ptrToRightNode != NULL)
		{

			enqu(root->ptrToRightNode);

			flagR = 0;
		}
		else
		{
			flagR = 1;
		}
		dequ(root);
		if (flagL == 1 && flagR == 1)
		{
			printf("%d ", root->data);
		}
		else
		{
			flagR = 0;
			flagL = 0;
		}
		if (front != NULL)
			root = front->data;
	}
	freeQ();

}

int compute_height(struct node* root)
{
	if (root == NULL) return 0;

	int left = compute_height(root->ptrToLeftChild);
	int right = compute_height(root->ptrToRightNode);

	int height = (left > right ? left : right);
	height++;
	return height;

}

// ----------------------------------------------------main function------------------------------------------------------

int main()
{
	static struct node* root = NULL;

	int nodes;
	int height;
	int isMirror;
	int isBST;
	int caseVariable;
	
	while (1)
	{
		printf("\nenter the operation you are willing to perform : \n");
		scanf("%d", &caseVariable);
		switch (caseVariable)
		{
		case 1:
			printf("\nEnter the number of nodes in the tree : ");
			scanf("%d", &nodes);
			root = (struct node*)malloc(sizeof(struct node)); // creating root node
			root->ptrToLeftChild = NULL;
			root->ptrToRightNode = NULL;
			printf("\nEnter the data in root node : ");
			scanf("%d", &root->data);

			enqu(root);
			insert(root, nodes);
			break;
		case 2:
			lvlOrderTraverse(root);
			display(root);
			break;
		case 3:
			isMirror = checkForMirror(root->ptrToLeftChild, root->ptrToRightNode);
			printf("\n is mirror ?? -> %d\n", isMirror);
			freeQ();
			break;
		case 4:
			printf("all the leaf nodes are : ");
			printAllLeafNodes(root); printf("\n");
			break;
		case 5:
			height = compute_height(root);
			printf("height of the tree is %d", height);
			break;
		case 6:
			isBST = checkForBinarySearchTree(root);
			printf("\n is BST ?? -> %d", isBST);
			break;
		default:
			break;
			
		}
	}
	

	
}
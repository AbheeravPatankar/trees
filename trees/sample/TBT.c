#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node* ptrToRightNode;
	struct node* ptrToLeftNode;
	int leftBit, rightBit;
	int data;
};
struct stack
{
	struct node* node;
	struct stack* ptrToNextNode;
};

struct stack* push(struct stack* head, struct stack* tail, struct stack* value)
{
	struct stack* temp;
	if (head == NULL)
	{
		head = (struct stack*)malloc(sizeof(struct stack));
		head->node = value;
		head->ptrToNextNode = NULL;
		tail = head;
		return tail;
	}
	else
	{
		temp = (struct stack*)malloc(sizeof(struct stack));
		temp->node = value;
		temp->ptrToNextNode = NULL;
		tail->ptrToNextNode = temp;
		tail = temp;
		return tail;
	}
}

void popAndPrint(struct stack* head, struct stack* tail)
{
	struct stack* temp = head;
	while (temp->ptrToNextNode != tail)
	{
		temp = temp->ptrToNextNode;
	}
	printf("%d ", (tail->node)->data);
	free(tail);
	tail = temp;
}

void inOrderTraversal(struct node* root, struct node* head)
{
	struct node* temp;
	temp = root;
	do
	{
		while (temp->leftBit == 1)
		{
			temp = temp->ptrToLeftNode;

		} 
		if(temp != head)
			printf("%d ", temp->data);

		if (temp->rightBit == 0)
		{
			while (temp->rightBit == 0)
			{
				temp = temp->ptrToRightNode;
				if (temp != head)
					printf("%d ", temp->data);
			}
			temp = temp->ptrToRightNode;
		}
		else
			temp = temp->ptrToRightNode;
	} while (temp != head);


}

//void preOrderTraversal(struct node* root, struct node* head)
//{
//	struct node* temp;
//
//
//	temp = root;
//	do
//	{
//		while (temp->leftBit == 1)
//		{
//			printf("%d ", temp->data);
//			temp = temp->ptrToLeftNode;
//		}
//		printf("%d ", temp->data);
//
//		temp = temp->ptrToRightNode;
//
//		while (temp->rightBit == 0)
//		{
//			temp = temp->ptrToRightNode;
//		}
//		temp = temp->ptrToRightNode;
//
//	} while (temp != head);
//
//}


//void postOrderTraversal(struct node* root, struct node* headToTree)
//{
//	struct node* temp;
//	struct stack* head = NULL;
//	struct stack* tail = NULL;
//	temp = root;
//	int leftRightFlag;
//	int count = 0;
//	do
//	{
//
//		while (temp->leftBit == 1 || temp->rightBit == 1)
//		{
//			tail = push(head, tail, temp);
//			if (count == 0)
//			{
//				head = tail;
//				count++;
//			}
//			if (temp->leftBit == 1)
//			{
//				temp = temp->ptrToLeftNode;
//				leftRightFlag = 0;
//			}
//			else
//			{
//				temp = temp->ptrToRightNode;
//				leftRightFlag = 1;
//			}
//
//		}
//		printf("%d ", temp->data);
//
//		if (leftRightFlag == 0) // left leaf node
//		{
//			temp = temp->ptrToRightNode;
//			if (temp->rightBit == 1)
//			{
//				temp = temp->ptrToRightNode;
//				leftRightFlag = 1;
//			}
//			else
//			{
//				while (temp->rightBit == 0)
//				{
//					popAndPrint(head, tail);
//					temp = temp->ptrToRightNode;
//				}
//				temp = temp->ptrToRightNode;
//				leftRightFlag = 1;
//			}
//		}
//		else
//		{
//			while (temp->rightBit == 0)
//			{
//				popAndPrint(head, tail);
//				temp = temp->ptrToRightNode;
//			}
//			temp = temp->ptrToRightNode;
//			leftRightFlag = 1;
//		}
//
//
//	} while (temp != headToTree);
//
//	popAndPrint(head, tail);
//}

struct node* findMax(struct node* t)
{
	while (t->rightBit != 0)
	{
		t = t->ptrToRightNode;
	}

	return t;
}

struct node* delete(struct node* root, struct node* ptrToPrevNode, int val)  //Incorrect operation
{
	struct node* temp;
	struct node* temp2;

	if (root == NULL) printf("value not present");

	else if (val < root->data)
		root->ptrToLeftNode = delete(root->ptrToLeftNode, root, val);

	else if (val > root->data)
		root->ptrToRightNode = delete(root->ptrToRightNode, root, val);

	else
	{
		if (root->leftBit != 0 && root->rightBit != 0)
		{
			int value;
			temp = findMax(root->ptrToLeftNode);
			value = temp->data;
			temp = delete(temp, root, temp->data);
			root->data = value;

		}
		else if (root->leftBit != NULL && root->rightBit == NULL)
		{
			temp = root;
			if (ptrToPrevNode->data > root->data)
			{
				ptrToPrevNode->ptrToLeftNode = root->ptrToLeftNode;
				root = root->ptrToLeftNode;				
				temp2 = root->ptrToLeftNode;
			}
			else
			{
				ptrToPrevNode->ptrToRightNode = root->ptrToLeftNode;
				root = root->ptrToLeftNode;
				temp2 = root->ptrToLeftNode;
			}
			
			while (root->rightBit != 0)
			{
				root = root->ptrToRightNode;
			}
			root->ptrToRightNode = temp->ptrToRightNode;
			root = temp2;
			free(temp);
		}
		else if (root->rightBit != NULL && root->leftBit == NULL)
		{

			temp = root;
			if (ptrToPrevNode->data > root->data)
			{
				ptrToPrevNode->ptrToLeftNode = root->ptrToRightNode;
				root = root->ptrToRightNode;
				temp2 = root->ptrToRightNode;
			}
			else
			{
				ptrToPrevNode->ptrToRightNode = root->ptrToRightNode;
				root = root->ptrToRightNode;
				temp2 = root->ptrToRightNode;
			}
			
			while (root->leftBit != 0)
			{
				root = root->ptrToLeftNode;
			}
			root->ptrToLeftNode = temp->ptrToLeftNode;
			root = temp2;
			free(temp);
			
		}
		else //deleting leaf node
		{
			if (ptrToPrevNode->data > root->data)
			{
				ptrToPrevNode->ptrToLeftNode = root->ptrToLeftNode;
				ptrToPrevNode->leftBit = 0;
				free(root);
				root = ptrToPrevNode->ptrToLeftNode;
			}
			else
			{
				ptrToPrevNode->ptrToRightNode = root->ptrToRightNode;
				ptrToPrevNode->rightBit = 0;
				free(root);
				root = ptrToPrevNode->ptrToRightNode;
			}
		}
	}
	return root;
}

struct node* insert(struct node* head)
{
	struct node* newNode;
	static struct node* root;
	newNode = (struct node*)malloc(sizeof(struct node));
	struct node* temp;
	int flag;
	printf("enter data in node \n");
	scanf("%d", &(newNode->data));
	if (head->ptrToLeftNode == head)  // inserting the root node
	{
		root = newNode;
		root->leftBit = 0;
		root->rightBit = 0;
		root->ptrToLeftNode = head;
		root->ptrToRightNode = head;
		head->ptrToLeftNode = root;

	}
	else
	{
		temp = root;
		while (1)
		{

			if (newNode->data > temp->data && temp->rightBit != 0)
			{
				temp = temp->ptrToRightNode;
			}
			else if (newNode->data < temp->data && temp->leftBit != 0)
			{
				temp = temp->ptrToLeftNode;
			}
			else
			{
				if (temp->data > newNode->data)
				{
					newNode->ptrToLeftNode = temp->ptrToLeftNode;
					newNode->ptrToRightNode = temp;
					newNode->leftBit = 0;
					newNode->rightBit = 0;
					temp->leftBit = 1;
					temp->ptrToLeftNode = newNode;
					break;
				}
				else
				{
					newNode->ptrToLeftNode = temp;
					newNode->ptrToRightNode = temp->ptrToRightNode;
					newNode->leftBit = 0;
					newNode->rightBit = 0;
					temp->rightBit = 1;
					temp->ptrToRightNode = newNode;
					break;
				}

			}
		}

	}

	return root;
}
int main()
{
	struct node* head;
	struct node* temp;
	struct node* root;
	int caseVariable;
	int value;
	head = (struct node*)malloc(sizeof(struct node));
	temp = head;
	head->ptrToRightNode = temp;
	head->ptrToLeftNode = temp;
	head->leftBit = 1;
	head->rightBit = 1;
	printf("Insterting the root node");
	root = insert(head);

	while (1)
	{
		printf("Enter the operation to perform \n1->insert\n2->delete\n3->inOrderTraversal\n");
		scanf("%d", &caseVariable);
		switch (caseVariable)
		{
		case 1:
			root = insert(head);
			break;
		case 2:
			printf("Insert element to delete \n");
			scanf("%d", &value);
			delete(root,NULL, value);
			break;
		case 3:
			inOrderTraversal(root, head);
			break;
		default:
			break;
		}
	}
	
	

}
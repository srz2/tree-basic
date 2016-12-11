#include <iostream>
#include <stdio.h>
using namespace std;

#ifndef ALLOW_DUPLICATES
#define ALLOW_DUPLICATES	true
#endif

class Node
{
public:
    int data;
    Node * parent;
    Node * left;
    Node * right;
public:

    Node()
    {
        data = -1;
        parent = NULL;
        left = NULL;
        right = NULL;
    }

    Node(Node * p, int data)
    {
    	this->data = data;
		parent = p;
		left = NULL;
		right = NULL;
    }

    void add(int value)
    {
        if(value <= 0)
            throw "Add: Data value must be greater than zero!\n";

        //Determine to put data in this node or either the left or right sub trees
        if(this->data <= 0)								//If no value assigned, assign one
        {
            this->data = value;
        }
        else
        {
            if(this->data > value)						//If value is less then data, create/add value to left
            {
            	if(this->left == NULL)
            	{
            		this->left = new Node(this, value);
            	}
            	else
            	{
            		this->left->add(value);
            	}
            }
            else if(this->data < value)					//If value is greater than data, create/add value
            {
            	if(this->right == NULL)
            	{
            		this->right = new Node(this, value);
            	}
            	else
            	{
            		this->right->add(value);
            	}
            }
            else if(this->data == value)				//Value is equal to data, make it part of the left child or add on to it
            {
            	cout << "Duplicate value " << value << " found: " << (ALLOW_DUPLICATES ? "ADDING" : "IGNORING") << endl;
#if ALLOW_DUPLICATES
            	if(this->left == NULL)
				{
					this->left = new Node(this, value);
				}
				else
				{
					Node * oldLeft = this->left;
					this->left = new Node(this, value);

					oldLeft->parent = this->left;
					this->left->left = oldLeft;
				}
#endif
            }
            else
            {
                cout << "Add: Unhandled item" << endl;
            }
        }
    }

    Node * remove(int value)
    {
        if(value <= 0)
            throw "Data value must be greater than zero!\n";

        Node * removedNode = NULL;
        if(this->data == value)
        {
        	if(this->left == NULL && this->right == NULL)		//Is a leaf
        	{
        		removedNode = this;
        		if(this->parent->left == removedNode)
        		{
        			this->parent->left = NULL;
        		}
        		else
        		{
        			this->parent->right = NULL;
        		}

        	}
        	else if(this->left != NULL)							//Has left child
        	{
        		removedNode = this;
        		if(this->parent->left == removedNode)
				{
    				this->parent->left = this->left;
				}
				else
				{
    				this->parent->right = this->left;
				}
        	}
        	else if(this->right != NULL)						//Has right child
        	{
        		removedNode = this;
        		if(this->parent->left == removedNode)
				{
    				this->parent->left = this->right;
				}
				else
				{
    				this->parent->right = this->right;
				}
        	}
        	else
        	{
        		cout << "Should never see me" << endl;
        	}
        }
        else if(value < this->data)
        {
        	if(this->left != NULL)
        	{
        		removedNode = this->left->remove(value);
        	}
        }
        else if(value > this->data)
        {
        	if(this->right != NULL)
        	{
        		removedNode = this->right->remove(value);
        	}
        }
        else
        {
            cout << "Remove: Unhandled item" << endl;
        }

        return removedNode;
    }
};

void preorder(Node * root)
{
	if(root == NULL)
	{
		return;
	}

	printf("%d\n", root->data);
	preorder(root->left);
	preorder(root->right);
}

void inorder(Node * root)
{
	if(root == NULL)
	{
		return;
	}

	inorder(root->left);
	printf("%d\n", root->data);
	inorder(root->right);
}

void postorder(Node * root)
{
	if(root == NULL)
	{
		return;
	}

	postorder(root->left);
	postorder(root->right);
	printf("%d\n", root->data);
}

int main()
{
    try
    {
        Node * root = new Node(NULL, 5);
        root->add(8);
        root->add(7);
        root->add(3);
        root->add(4);
        root->add(23);
        root->add(54);
        root->add(67);
        root->add(12);
        root->add(65);
        root->add(19);
        root->add(1);
        root->add(2);

// Duplicate value
//        root->add(3);

        preorder(root);

        cout << "Done!" << endl;
    }
    catch(const char * e)
    {
        printf("[ERR]: %s", e);
    }
}

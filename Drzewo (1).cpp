#include<iostream>
#include <string>
#include <sstream>

// BST

using namespace std;

struct Element{
	int key;
	int value;
};

struct Node{
	Element elem;
	Node* left;
	Node* right;
	Node* parent;
};

// Binary search tree
struct BST{
    Node* root;
};

void init(BST & tree){
    tree.root = NULL;
}

bool insertElem(BST & tree, Element elem){
    Node* newnode = new Node;

    newnode->elem = elem;
    newnode->left = NULL;
    newnode->right = NULL;

    if (tree.root == NULL)
    {
        newnode->parent = NULL;
        tree.root = newnode;
        return true;
    }
    else
    {
        Node* current;
        Node* parent = tree.root;

        if (tree.root->elem.key > elem.key)
            current = tree.root->left;
        else if (tree.root->elem.key < elem.key)
            current = tree.root->right;
        else
            return false;

        while (current != NULL)
        {
            parent = current;

            if (current->elem.key > elem.key)
                current = current->left;
            else if (current->elem.key < elem.key)
                current = current->right;
            else
                return false;
        }

        newnode->parent = parent;
        if (parent->elem.key > elem.key)
            parent->left = newnode;
        else
            parent->right = newnode;
    }

	return true;
}

void showInorder(Node* curr)
{
    if (curr != NULL)
    {
        showInorder(curr->left);
        cout << curr->elem.key << "(" << curr->elem.value << "),";
        showInorder(curr->right);
    }
}

void showInorder(BST & tree){
    showInorder(tree.root);
    cout << endl;
}

void showPreorder(Node* curr)
{
    if (curr != NULL)
    {
        cout << curr->elem.key << "(" << curr->elem.value << "),";
        showPreorder(curr->left);
        showPreorder(curr->right);
    }
}

void showPreorder(BST & tree){
    showPreorder(tree.root);
    cout << endl;
}

void showPostorder(Node* curr)
{
    if (curr != NULL)
    {
        showPostorder(curr->left);
        showPostorder(curr->right);
        cout << curr->elem.key << "(" << curr->elem.value << "),";
    }
}

void showPostorder(BST & tree){
    showPostorder(tree.root);
    cout << endl;
}

Node *findNode(Node *node,int key){
	if (node != NULL)
    {
        if (node->elem.key == key)
            return node;

        if (node->elem.key > key)
            return findNode(node->left, key);
        else
            return findNode(node->right, key);
    }
    return NULL;
}



bool findKey(BST & tree,int key, Element &elem){

    Node* result = findNode(tree.root, key);

    if (result == NULL) return false;

    elem = result->elem;

	return true;
}

Node *minimalNode(Node *node){
	if (node == NULL) return node;

	while (node->left != NULL)
        node = node->left;
    return node;
}

bool removeKey(BST & tree, int key, Element &elem){
    Node* todel = findNode(tree.root, key);

    if (todel == NULL) return false;

    elem = todel->elem;

    if (todel->left == NULL)
    {
        if (todel->parent == NULL)
        {
            tree.root = todel->right;
            if (tree.root != NULL)
                tree.root->parent = NULL;
        }
        else if (todel->parent->left == todel)
        {
            todel->parent->left = todel->right;
            if (todel->right != NULL)
                todel->right->parent = todel->parent;
        }
        else
        {
            todel->parent->right = todel->right;
            if (todel->right != NULL)
                todel->right->parent = todel->parent;
        }
    }
    else if (todel->right == NULL)
    {
        if (todel->parent == NULL)
        {
            tree.root = todel->left;
            tree.root->parent = NULL;
        }
        else if (todel->parent->left == todel)
        {
            todel->parent->left = todel->left;
            if (todel->left != NULL)
                todel->left->parent = todel->parent;
        }
        else
        {
            todel->parent->right = todel->left;
            if (todel->left != NULL)
                todel->left->parent = todel->parent;
        }
    }
    else
    {
        Node* todel2 = todel->right;

        while (todel2->left != NULL)
            todel2 = todel2->left;

        todel->elem = todel2->elem;

        if (todel2->parent->left == todel2)
        {
            todel2->parent->left = todel2->right;
            if (todel2->right != NULL)
                todel2->right->parent = todel2->parent;
        }
        else
        {
            todel2->parent->right = todel2->right;
            if (todel2->right != NULL)
                todel2->right->parent = todel2->parent;
        }

        todel = todel2;
    }

    delete todel;

    return true;
}

void clear(Node *node){
    if (node != NULL)
    {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void clear(BST & tree){
    clear(tree.root);
    tree.root = NULL;
}

int numberOfNodes(Node* curr)
{
    if (curr == NULL) return 0;
    return numberOfNodes(curr->left) + numberOfNodes(curr->right) + 1;
}

int numberOfNodes(BST & tree){
	return numberOfNodes(tree.root);
}

int height(Node* curr)
{
    if (curr == NULL) return -1;
    int l = height(curr->left);
    int r = numberOfNodes(curr->right);

    if (l > r) return l +1;
    return r + 1;
}

int height(BST & tree){
    int h = height(tree.root);

    if (h == -1) return 0;
    return h;
}

int functionA(BST & tree){
	return -1;
}

int functionB(BST & tree, int key){
	return -1;
}

bool functionC(BST & tree, int key, Element &elem){
	return false;
}


void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	BST *tree;
	int currentT=0;
	int value;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"SI"))
		{
			showInorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SP"))
		{
			showPreorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SQ"))
		{
			showPostorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clear(tree[currentT]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(tree[currentT]);
			continue;
		}

		if(isCommand(command,"NN"))
		{
			cout << numberOfNodes(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"HE"))
		{
			cout << height(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"FA"))
		{
			cout << functionA(tree[currentT]) << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;


		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			showBool(insertElem(tree[currentT],elem));
			continue;
		}

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			Element elem;
			bool ret=removeKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentT=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			tree=new BST[value];
			continue;
		}

		if(isCommand(command,"FB"))
		{
			cout << functionB(tree[currentT],value) << endl;
			continue;
		}

		if(isCommand(command,"FC"))
		{
			Element elem;
			bool ret=functionC(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}

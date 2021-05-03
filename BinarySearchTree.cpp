//This program is a binary search tree that allows for
//insertion (through the console or a file), search, removal, and display.
//Author: Kevin Lei
//Date: 4/29/2021


#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>

using namespace std;

//Struct for the Binary Search Tree nodes
struct Node {
  int data;
  Node* left;
  Node* right;
};

//Function prototypes
void DISPLAY(Node* root, int depth);
void INSERT(Node* & root, int newData);
Node* SEARCH(Node* root, int data);
Node* REMOVE(Node* & root, int data);
int findMin(Node* root);


//Main function
int main() {

  //Creating the root
  Node* root = NULL;

  cout << "Welcome to Binary Search Tree" << endl;
  char input[10];

  //While loop will continue as long as user doesn't input QUIT
  while (strcmp(input, "QUIT") != 0) {
    cout << "Type INSERT, REMOVE, SEARCH, DISPLAY, or QUIT" << endl;

    cin >> input;
    
    if (strcmp(input, "INSERT") == 0) { //User inputed INSERT
      char data[500];
      char method[10];
      cout << "Type CONSOLE or FILE" << endl;

      cin >> method;

      if (strcmp(method, "CONSOLE") == 0) { //Insert through the console
	cout << "Type the numbers to be added to the binary search tree" << endl;
	cin.get();
	cin.get(data, 500);
	cin.get();

	char* ptr;
	ptr = strtok(data, " ");
	while (ptr != NULL) {
	  int newData = atoi(ptr);
	  INSERT(root, newData);
	  ptr = strtok(NULL, " ");
	}
      } else if (strcmp(method, "FILE") == 0) { //Insert through a file
	char fileName[50];
	cout << "Type the name of the file" << endl;
	cin >> fileName;

	ifstream file;
	srand(time(0));
	file.open(fileName);
	if (file == NULL) {
	  cout << fileName << " could not be accessed" << endl;
	} else {
	  while (file >> data) {
	    int newData = atoi(data);
	    INSERT(root, newData);
	  }
	}
      } else {
	cout << "Invalid input" << endl;
      }
    } else if (strcmp(input, "REMOVE") == 0) { //User inputed REMOVE
      cout << "Type what you would like to remove" << endl;
      int data;
      cin >> data;

      if (SEARCH(root, data) == NULL) { //First checking whether or not the data is in the tree
	cout << data << " was not found" << endl;
      } else {
	root = REMOVE(root, data);
      }
    } else if (strcmp(input, "SEARCH") == 0) { //User inputed SEARCH
      cout << "Type what you would like to search for" << endl;
      int data;
      cin >> data;

      if (SEARCH(root, data) != NULL) {
	cout << data << " was found" << endl;
      } else {
	cout << data << " was not found" << endl;
      }
    } else if (strcmp(input, "DISPLAY") == 0) { //User inputed DISPLAY
      DISPLAY(root, 0);
    } else if (strcmp(input, "QUIT") != 0) { //User inputed invalid input
      cout << "Invalid input" << endl;
    }
  }

  cout << "Goodbye" << endl;
  return 0;
}

//Function displays the tree nicely
void DISPLAY(Node* root, int depth) {
  if (root != NULL) {
    //depth += 10;
    DISPLAY(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
      cout << "   ";
    }
    cout << root->data << "\n";
    DISPLAY(root->left, depth + 1);
  }
  return;
}

//Function inserts an integer into the Binary Search Tree
void INSERT(Node* & root, int newData) {
  if (root == NULL) {
    root = new Node;
    root->data = newData;
    root->left = NULL;
    root->right = NULL;
  } else if (root->data > newData) {
    INSERT(root->left, newData);
  } else  {
    INSERT(root->right, newData);
  }
}

//Function searches the binary search tree for a specific integer
//and returns the pointer if it is found or NULL if it is not found
Node* SEARCH(Node* root, int data) {
  Node* current = root;
  while (current != NULL) {
    if (data < current->data) {
      current = current->left;
    } else if (data > current->data) {
      current = current->right;
    } else {
      return current;
    }
  }
  return NULL;
}

//Function recursively removes a specific integer from the tree
Node* REMOVE(Node* & root, int data) {
  if (root == NULL) {
    return root;
  }
  if (data < root->data) {
    root->left = REMOVE(root->left, data);
  } else if (data > root->data) {
    root->right = REMOVE(root->right, data);
  } else {
    if (root->left == NULL) {
      Node* temp  = root->right;
      delete(root);
      return temp;
    } else if (root->right == NULL) {
      Node* temp = root->left;
      delete(root);
      return temp;
    } else {
      int nextLargest = findMin(root->right);
      root->data = nextLargest;
      root->right = REMOVE(root->right, nextLargest);
    }
  }
  return root;
  /*if (SEARCH(root, data) == NULL) {
    cout << data << " was not found" << endl;
    return;
  }

  Node* target = SEARCH(root, data);
  if (target->left == NULL && target->right == NULL) {
    delete(target);
  } else if (target->left == NULL) {
    target = target->right;
  } else if (target->right == NULL) {
    target = target->left;
  } else {
    Node* nextLargest = target->right;
    while (nextLargest->left != NULL) {
      nextLargest = nextLargest->left;
    }
    if (nextLargest->left == NULL && nextLarget->right == NULL) {
      Node* temp
    }
  }*/

  /*if (SEARCH(root, data) != NULL && root != NULL) {
    if (root->data == data) {


    } else {
      REMOVE(root->right, data);
      REMOVE(root->left, data);
    }
  }*/
}

//Function finds the minimum integer in a tree or subtree
//Used in the REMOVE function to find the next largest integer
int findMin(Node* root) {
  if (root->left == NULL) {
    return root->data;
  } else {
    return findMin(root->left);
  }
}


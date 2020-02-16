#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include"util.h"
using namespace std;

struct Node *root, *worldRoot;
int screenMode = MODE_VIEW;

vector<pointKey> pointKeys;
void drawEdge(Node *curr, int x=65, int y=-1, int range=40){
	if(y == 3) return;
	
	y++;
	
	int currX = x;
	int currY = y * 3;
	int nextY = (y + 1) * 3;
	
	pointKeys.push_back(pointKey(currX, currY, curr->key));
	curr->setCoor(currX, currY);
	
	range -= 12;
	
	if(curr->left){
		int nextX = x - range;
		drawEdge(curr->left, nextX, y, range);
		if(y < 3) dda(currX, currY, nextX, nextY);
	}
	
	if(curr->right){
		int nextX = x + range;
		drawEdge(curr->right, nextX, y, range);
		if(y < 3) dda(currX, currY, nextX, nextY);
	}
}

void message(){
	gotoxy(30,55);
	cout << "You can navigate using arrow key";
	buang();
}

void view(Node *curr){
	system("cls");
	if(!root){
		gotoxy(0, 55);
		cout << "No Data (Press space to go to menu)";
	}
	else{
		setColor(COLOR_EDGE);
		pointKeys.clear();
		worldRoot = curr;
		drawEdge(curr);
		setColor(COLOR_NODE);
		for(int i=0 ; i<pointKeys.size() ; i++){
			pointKey pk = pointKeys[i];
			gotoxy(pk.y, pk.x);
			cout << pk.key;	
		}
	}
	
	buang();
}

void insertNode(Node *&curr, int key, Node *parent=0){	
	if(!curr){
		curr = new Node(key, parent);
		view(getParent(curr, 3));
		return;
	}
	
	curr->print(COLOR_MOVE);
	buang();
	wait();
	curr->print(COLOR_NODE);
	buang();
	
	if(curr->key == key){
		curr->print(COLOR_SAME);
		buang();
		wait();
		curr->print(COLOR_NODE);
		buang();
		return;
	}
	else if(key > curr->key){
		view(getParent(curr, 2));
		insertNode(curr->right, key, curr);
	}
	else if(key < curr->key){
		view(getParent(curr, 2));
		insertNode(curr->left, key, curr);
	}
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	int balance = getBalance(curr);
	if(balance > 1 && key < curr->left->key){
		curr->print(COLOR_ROTATE);
		curr->left->print(COLOR_ROTATE);
		curr->left->left->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateR(curr);

		view(getParent(curr, 1));
	}
	else if(balance < -1 && key > curr->right->key){
		curr->print(COLOR_ROTATE);
		curr->right->print(COLOR_ROTATE);
		curr->right->right->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateL(curr);
		
		view(getParent(curr, 1));
	}
	else if(balance > 1 && key > curr->left->key){
		curr->print(COLOR_ROTATE);
		curr->left->print(COLOR_ROTATE);
		curr->left->right->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateL(curr->left);
		rotateR(curr);
		
		view(getParent(curr, 1));
	}
	else if(balance < -1 && key < curr->right->key){
		curr->print(COLOR_ROTATE);
		curr->right->print(COLOR_ROTATE);
		curr->right->left->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateR(curr->right);
		rotateL(curr);
		
		view(getParent(curr, 1));
	}
}

void deleteNode(Node *&curr, int key){
	if(!curr) return;
	
	curr->print(COLOR_MOVE);
	buang();
	wait();
	curr->print(COLOR_NODE);
	buang();
	
	if(key > curr->key){
		view(getParent(curr, 2));
		deleteNode(curr->right, key);
	}
	else if(key < curr->key){
		view(getParent(curr, 2));
		deleteNode(curr->left, key);
	}
	else{
		curr->print(COLOR_SAME);
		buang();
		wait();
		curr->print(COLOR_NODE);
		buang();
		
		if(curr->left){
			Node *predecessor = getPredecessor(curr);
			curr->key = predecessor->key;
			
			predecessor->print(COLOR_FIND_CHILD);
			curr->print(COLOR_FIND_CHILD);
			buang();
			wait();
			curr->print(COLOR_NODE);
			buang();
			
			deleteNode(curr->left, curr->key);
		}
		else if(curr->right){
			Node *successor = getSuccessor(curr);
			curr->key = successor->key;
			
			successor->print(COLOR_FIND_CHILD);
			curr->print(COLOR_FIND_CHILD);
			buang();
			wait();
			curr->print(COLOR_NODE);
			buang();
			
			deleteNode(curr->right, curr->key);
		}
		else{
			Node *parent = getParent(curr, 3);
			delete curr;
			curr = NULL;
			view(parent);
		}
	}
	
	if(!curr) return;
		
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	int balance = getBalance(curr);
	
	if(balance > 1 && getBalance(curr->left) >= 0){
		curr->print(COLOR_ROTATE);
		curr->left->print(COLOR_ROTATE);
		curr->left->left->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateR(curr);
	
		view(getParent(curr, 1));
	}
	else if(balance < -1 && getBalance(curr->right) <= 0){
		curr->print(COLOR_ROTATE);
		curr->right->print(COLOR_ROTATE);
		curr->right->right->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateL(curr);
		
		view(getParent(curr, 1));
	}
	else if(balance > 1 && getBalance(curr->left) < 0){
		curr->print(COLOR_ROTATE);
		curr->left->print(COLOR_ROTATE);
		curr->left->right->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateL(curr->left);
		rotateR(curr);
		
		view(getParent(curr, 1));
	}
	else if(balance < -1 && getBalance(curr->right) > 0){
		curr->print(COLOR_ROTATE);
		curr->right->print(COLOR_ROTATE);
		curr->right->left->print(COLOR_ROTATE);
		buang();
		wait();
		
		rotateR(curr->right);
		rotateL(curr);
		
		view(getParent(curr, 1));
	}
}

int main(){	
	system("mode 131,40");
	start();
	
	vector<int> nums;
	Node *curr = 0;
	bool first = true;
	
	while(true){
		char move = getch();
		
		if(first){
			first = false;
			screenMode = MODE_VIEW;
			move = -1;
		}
		
		if(move == SPACE)
		{
			system("cls");
			cout << "1. Insert" << endl 
				<< "2. Delete" << endl 
				<< "3. View" << endl  
				<< "4. Exit" << endl;

			int inp;
			while(true){
				inp = inputNumeric("Input : ");
				if(inp >=1 && inp <= 4) break;
			}
			screenMode = inp - 1;
			
			if(inp == 4){
				emengan();
				buang();
				popAll(root);
				getchar();
				return 0;
			}
		}
		
		if(screenMode == MODE_INSERT)
		{
			system("cls");
			nums.clear();
			screenMode = MODE_VIEW;
			
			int n = inputNumeric("Input number of nodes : ");
			for(int i=0 ; i<n ; i++){
				int inp = inputNumeric("Input node value : ");
				nums.push_back(inp);
			}
			
			for(int i=0 ; i<n ; i++){
				view(root);
				insertNode(root, nums[i]);
				wait();
			}
			
			curr = worldRoot;
			message();
		}
		else if(screenMode == MODE_DELETE)
		{
			system("cls");
			screenMode = MODE_VIEW;
			int inp = inputNumeric("Input node value : ");
			view(root);
			deleteNode(root, inp);
			message();
		}
		else if(screenMode == MODE_VIEW)
		{
			if(!curr){
				view(root);
				continue;
			}
			
			if(move == ARROW_UP){
				if(curr->parent){
					curr = curr->parent;
					view(curr);
				}
			}
			else if(move == ARROW_RIGHT){
				if(curr->right){
					curr = curr->right;
					view(curr);	
				}
			}
			else if(move == ARROW_LEFT){
				if(curr->left){
					curr = curr->left;
					view(curr);	
				}
			}
			else{
				view(worldRoot);
			}
			
			message();
		}
	}
}

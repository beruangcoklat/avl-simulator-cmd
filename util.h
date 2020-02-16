#pragma once
#include<iostream>
#include<string>
#include<math.h>
#include<windows.h>
using namespace std;

const int COLOR_NODE = 7;
const int COLOR_EDGE = 0;
const int COLOR_MOVE = 2;
const int COLOR_ROTATE = 4;
const int COLOR_SAME = 4;
const int COLOR_SWAP = 4;
const int COLOR_FIND_CHILD = 4;

const int ARROW_UP = 72;
const int ARROW_RIGHT = 77;
const int ARROW_LEFT = 75;
const int SPACE = 32;
const int ENTER = 13;

const int MODE_INSERT = 0;
const int MODE_DELETE = 1;
const int MODE_VIEW = 2;

const int SLEEP_TIME = 1000;

void gotoxy(int y, int x){
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void buang(){
	gotoxy(35, 0);
}

void wait(){
	Sleep(SLEEP_TIME);
//	getchar();
}

void dda(int x0, int y0, int x1, int y1){
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int step = dx > dy ? dx : dy;
	
	double ix = (double)dx / step;
	double iy = (double)dy / step;
	
	for(int i=1 ; i<=step ; i++){
		double nx = (double)x0 ;
		double ny = (double)y0 ;
		
		if(x1 > x0) nx += (i * ix);
		else if(x1 < x0) nx -= (i * ix);
		if(y1 > y0) ny += (i * iy);
		else if(y1 < y0) ny -= (i * iy);
		
		gotoxy((int)ny, (int)nx);
		cout << (char) 219;
	}
}

void setColor(int color){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | FOREGROUND_INTENSITY);
}

struct pointKey{
	int x, y, key;
	pointKey(int x, int y, int key){
		this->x = x;
		this->y = y;
		this->key = key;
	}
};

struct Node{
	int key, height;
	Node *right, *left, *parent;
	int x, y;
	
	Node(int key, Node *parent){
		this->key = key;
		this->parent = parent;
		height = 1;
		right = left = NULL;
	}
	
	void setCoor(int x, int y){
		this->x = x;
		this->y = y;
	}
	
	void print(int color){
		gotoxy(y, x);
		setColor(color);
		cout << key;
	}
};

int getMax(int a, int b){
	return a > b ? a : b;
}

int getHeight(Node *x){
	return x ? x->height : 0;
}

int getBalance(Node *x){
	return x ? getHeight(x->left) - getHeight(x->right) : 0;
}

Node *getPredecessor(Node *curr){
	curr = curr->left;
	while(curr->right) curr = curr->right;
	return curr;
}

Node *getSuccessor(Node *curr){
	curr = curr->right;
	while(curr->left) curr = curr->left;
	return curr;
}

Node *getParent(Node *curr, int count){
	Node *ret = curr;
	for(int i=0 ; i<count ; i++){
		if(ret->parent) ret = ret->parent;
		else break;
	}
	return ret;
}

void rotateL(Node *&curr){
	Node *right = curr->right;
	Node *rightLeft = right->left;
	
	right->parent = curr->parent;
	curr->parent = right;
	if(rightLeft) rightLeft->parent = curr;
	
	right->left = curr;
	curr->right = rightLeft;
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	right->height = getMax(getHeight(right->left), getHeight(right->right)) + 1;
	
	curr = right;
}

void rotateR(Node *&curr){
	Node *left = curr->left;
	Node *leftRight = left->right;
	
	left->parent = curr->parent;
	curr->parent = left;
	if(leftRight) leftRight->parent = curr;
	
	left->right = curr;
	curr->left = leftRight;
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
	left->height = getMax(getHeight(left->left), getHeight(left->right)) + 1;
	
	curr = left;
}

void emengan(){
	system("cls");
	for(int i=0 ; i<10 ; i++) cout << endl;
	cout << "               _     _                   _____                               _______ _                           _                " << endl;
	cout << "     /\\       | |   (_)                 / ____|                             |__   __| |                         | |               " << endl;
	cout << "    /  \\   ___| |__  _  _____   _____  | (___  _   _  ___ ___ ___  ___ ___     | |  | |__  _ __ ___  _   _  __ _| |__             " << endl;
	cout << "   / /\\ \\ / __| '_ \\| |/ _ \\ \\ / / _ \\  \\___ \\| | | |/ __/ __/ _ \\/ __/ __|    | |  | '_ \\| '__/ _ \\| | | |/ _` | '_ \\            " << endl;
	cout << "  / ____ \\ (__| | | | |  __/\\ V /  __/  ____) | |_| | (_| (_|  __/\\__ \\__ \\    | |  | | | | | | (_) | |_| | (_| | | | |           " << endl;
	cout << " /_/____\\_\\___|_| |_|_|\\___|_\\_/_\\___| |_____/ \\__,_|\\___\\___\\___||___/___/  _ |_|__|_|_|_|_|  \\___/ \\__,_|\\__, |_| |_|      _    " << endl;
	cout << " |  ____|  (_) | | |       |  ____|/ _|/ _|         | |                     | | |__   __|                   __/ |           | |   " << endl;
	cout << " | |__ __ _ _| |_| |__     | |__  | |_| |_ ___  _ __| |_      __ _ _ __   __| |    | | ___  __ _ _ __ _____|___/ _____  _ __| | __" << endl;
	cout << " |  __/ _` | | __| '_ \\    |  __| |  _|  _/ _ \\| '__| __|    / _` | '_ \\ / _` |    | |/ _ \\/ _` | '_ ` _ \\ \\ /\\ / / _ \\| '__| |/ /" << endl;
	cout << " | | | (_| | | |_| | | |_  | |____| | | || (_) | |  | |_ _  | (_| | | | | (_| |    | |  __/ (_| | | | | | \\ V  V / (_) | |  |   < " << endl;
	cout << " |_|  \\__,_|_|\\__|_| |_( ) |______|_| |_| \\___/|_|   \\__( )  \\__,_|_| |_|\\__,_|    |_|\\___|\\__,_|_| |_| |_|\\_/\\_/ \\___/|_|  |_|\\_\\" << endl;
}

void popAll(Node *x){
	if(!x) return;
	popAll(x->left);
	popAll(x->right);
	delete x;
	x = 0;
}

int convertStringToNumeric(string str){
	int ret = 0;
	int mult = 1;
	for(int i=str.length()-1 ; i >= 0 ; i--){
		ret += ((str[i]) - '0') * mult;
		mult *= 10;
	}
	return ret;
}

int inputNumeric(string print){
	string inp;
	while(true){
		cout << print;
		getline(cin, inp);
		
		bool valid = true;
		int len = inp.length();
		for(int i=0 ; i<len ; i++){
			if(!isdigit(inp[i])){
				valid = false;
				break;
			}
		}
		
		if(valid && len > 0){
			return convertStringToNumeric(inp);
		}
	}
}

void start(){
	for(int i=0 ; i<10 ; i++) cout << endl;
	
	cout << "    ___ _    ____       _____ _                 __      __  _           " << endl;
	cout << "   /   | |  / / /      / ___/(_)___ ___  __  __/ /___ _/ /_(_)___  ____ " << endl;
	cout << "  / /| | | / / /       \\__ \\/ / __ `__ \\/ / / / / __ `/ __/ / __ \\/ __ \\" << endl;
	cout << " / ___ | |/ / /___    ___/ / / / / / / / /_/ / / /_/ / /_/ / /_/ / / / /" << endl;
	cout << "/_/  |_|___/_____/   /____/_/_/ /_/ /_/\\__,_/_/\\__,_/\\__/_/\\____/_/ /_/ " << endl << endl;
	
	cout << "Press any key to start!";
	buang();                                                                       
}

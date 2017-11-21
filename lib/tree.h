#include <nan.h>
#include <vector>

using namespace Nan;
using namespace v8;
using namespace std;

/*
The tree struct it's n-ary, not it's binary because we've can make up to 9 moves for every node
The node will not have a separated files because i am bored
The maximum it's defined because i have so little time to finnish this.
*/

const int MAXNODES = 9;

struct Node {
	//Basically, the node has only the childs and data
	// Get the isolated instance for the data
private:
	Isolate* isolate = v8::Isolate::GetCurrent();

public:
	int data[3][3] = { { 0 } };

	Node *childs[MAXNODES] = { NULL };

	Node(); //For init
	Node(int init[3][3]); //Root node (?)

	void MakeMoves(int next);
	Local<Object> GetObject();
	Local<Array> GetData();
	bool IsWinner();
	void Destroy(); // Recursively destroy nodes
};


struct Tree { 
private:
	Isolate* isolate = v8::Isolate::GetCurrent();
	Node *root;

public:
	Tree();
	Tree(int data[3][3]);
	void Insert(Local<Array> data);
	Local<Object> GetObject();
	void MakeMoves(int next);
	void Clean();
};
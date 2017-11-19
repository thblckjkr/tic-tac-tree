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

	Local<Array> _data = Array::New(isolate);
	Node* childs[MAXNODES] = { NULL };
public:

	Node(); //For init
	Node(Local<Array> data); //Root node (?)

	Local<Object> GetChildren(int depth);
	Local<Array> GetData();
	void Insert(Local<Array> node);
};


struct Tree { 
private:
	Isolate* isolate = v8::Isolate::GetCurrent();

	Node *root;
public:
	Tree();
	Tree(Local<Array> data);
	void Insert(Local<Array> data);
	Local<Object> GetObject();
};
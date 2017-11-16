#include <nan.h>
#include <vector>

using namespace Nan;
using namespace v8;
using namespace std;

/*
The tree struct it's n-ary, not it's binary because we've can make up to 9 moves for every node

The node will not have a separated files because i am bored
*/

struct Node {
	//Basically, the node has only the childs and data

	// Get the isolated instance for the data
private:
	Isolate* isolate = v8::Isolate::GetCurrent();
	Local<Array> _data = Array::New(isolate);

	vector<Node>* childs;
public:
	Node(); //For init
	Node(Local<Array> data); //Root node (?)
	Node(vector<Node> children, Local<Array> data); //Any node

	vector<Node>* GetChildren();
	void SetChildren(vector<Node> cihldren);
	void SetData(Local<Array> data);
	Local<Array> GetData();
};


struct Tree { 
private:
	Node *root;

public:
	Tree();
	Tree(Local<Array> data);
	void SetRoot(Local<Array> data);
	Local<Array> GetData();
};
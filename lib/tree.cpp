#include <node.h>
#include "tree.h"

Node::Node(){
}

Node::Node(Local<Array> data){
	_data = Local<Array>::Cast(data);
}

Local<Object> Node::GetObject(){
	//v8::HandleScope handle_scope;
	Handle<Object> node = Object::New(isolate);

	node->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "node") );

	node->Set( String::NewFromUtf8(isolate, "data"), this->_data );
	if( childs[0] == NULL ){
		return node;
	}

	Handle<Array> children = Array::New(isolate, MAXNODES);
	for(int i = 0; i < MAXNODES -1; i++){
		if( childs[i] != NULL ){
			children->Set(i, childs[i]->GetObject());
		}
	}

	node->Set( String::NewFromUtf8(isolate, "children"), children );
	
	return node;
}

void Node::MakeMoves(int next){
	Isolate* isolate = v8::Isolate::GetCurrent();
	Local<Array> row = Array::New(isolate);
	Node *tempNode;

	Local<Array> gamepad = Array::New(isolate);
	Local<Array> tempRow = Array::New(isolate);

	int counter = 0;
	int nextMove = ( next == 1 ) ? 2 : 1;

	for(int i = 0; i < 3; i++){
		// Get row by row
		row = Local<Array>::Cast(this->_data->Get(i));
		
		for(int j = 0; j < 3; j++){
			if( (int)row->Get(j)->Int32Value() == 0 ){
				gamepad = this->_data; // Create handler
				tempRow = Local<Array>::Cast(gamepad->Get(i));

				tempRow->Set(j, Integer::New(isolate, next));
				gamepad->Set( j, tempRow );

				tempNode = new Node(gamepad);

				tempNode->MakeMoves(nextMove);

				this->childs[counter] = tempNode;

				counter++;
			}
		}
	}
}

Local<Array> Node::GetData(){
	return this->_data;
}

Tree::Tree(Local<Array> data){
	Node *temp;
	temp = new Node(data);
	root = temp;
}

Local<Object> Tree::GetObject(){
	//v8::HandleScope handle_scope;
	Local<Object> tree = Object::New(isolate);
	tree->Set( String::NewFromUtf8(isolate, "tree"), root->GetObject());
	return tree;
}

void Tree::MakeMoves(int next){
	root->MakeMoves(next);
}
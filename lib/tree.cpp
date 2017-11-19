#include <node.h>
#include "tree.h"

Node::Node(){
}

Node::Node(Local<Array> data){
	_data = Local<Array>::Cast(data);
}

Local<Array> Node::GetData(){
	return this->_data;
}

Local<Object> Node::GetObject(){
	Local<Object> node = Object::New(isolate);

	node->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "node") );

	node->Set( String::NewFromUtf8(isolate, "data"), this->_data );

	Local<Array> children = Array::New(isolate, MAXNODES);
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
				gamepad = Local<Array>::Cast(this->_data); // Create Locale
				
				tempRow = Local<Array>::Cast(gamepad->Get(i));

				tempRow->Set( j, Integer::New(isolate, next));
				gamepad->Set( i, tempRow );

				tempNode = new Node(gamepad);

				tempNode->MakeMoves(nextMove);

				this->childs[counter] = tempNode;

				counter++;
			}
		}
	}
}

Tree::Tree(Local<Array> data){
	root = new Node(data);
}

Local<Object> Tree::GetObject(){
	Local<Object> tree = Object::New(isolate);
	tree->Set( String::NewFromUtf8(isolate, "tree"), root->GetObject());
	return tree;
}

void Tree::MakeMoves(int next){
	root->MakeMoves(next);
}
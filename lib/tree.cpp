#include <node.h>
#include "tree.h"

Node::Node(){
}

Node::Node(Local<Array> gamepad){
	// Local<Array> data = Array::New(isolate);
	data = gamepad;
}

Local<Array> Node::GetData(){
	return data;
}

Local<Object> Node::GetObject(){
	Local<Object> node = Object::New(isolate);

	node->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "node") );

	node->Set( String::NewFromUtf8(isolate, "data"), data );

	Local<Array> children = Array::New(isolate);
	for(int i = 0; i < MAXNODES - 1; i++){
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
	Local<Array> gamepad = Array::New(isolate);
	Local<Array> tempRow = Array::New(isolate);

	int counter = 0;
	int nextMove = ( next == 1 ) ? 2 : 1;

	for(int i = 0; i < 3; i++){
		// Get row by row
		row = Local<Array>::Cast(data->Get(i));
		
		for(int j = 0; j < 3; j++){
			if( (int)row->Get(j)->Int32Value() != 0 ){
				continue;
			}

			// Create a temporal array, modify it and add to data
			gamepad = Local<Array>::Cast(data);
			tempRow = Local<Array>::Cast(gamepad->Get(i));

			tempRow->Set( j, Integer::New(isolate, next));
			gamepad->Set( i, tempRow );

			this->childs[counter] = new Node();
			this->childs[counter]->data = gamepad;
			this->childs[counter]->MakeMoves(nextMove);

			counter = counter + 1;
		}
	}
}

Tree::Tree(Local<Array> gamepad){
	root = new Node();
	root->data = gamepad;
}

Local<Object> Tree::GetObject(){
	Local<Object> tree = Object::New(isolate);
	tree->Set( String::NewFromUtf8(isolate, "tree"), root->GetObject());
	return tree;
}

void Tree::MakeMoves(int next){
	root->MakeMoves(next);
}
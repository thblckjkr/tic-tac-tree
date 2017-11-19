#include <node.h>
#include "tree.h"

Node::Node(){

}

Node::Node(Local<Array> data){
	_data = Local<Array>::Cast(data);
}

Local<Object> Node::GetChildren(int depth){
	//v8::HandleScope handle_scope;
	Handle<Object> node = Object::New(isolate);

	node->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "anything") );

	node->Set( String::NewFromUtf8(isolate, "data"), this->_data );
	  
	Handle<Array> children = Array::New(isolate, MAXNODES);
	for(int i = 0; i < MAXNODES -1; i++){
		if( childs[i] == NULL ){
			node->Set( String::NewFromUtf8(isolate, "children"), children );
			return node;
		}
		children->Set(i, childs[i]->GetChildren(depth));
	}
	return node;
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

	tree->Set( String::NewFromUtf8(isolate, "name"),String::NewFromUtf8(isolate, "original"));

	tree->Set( String::NewFromUtf8(isolate, "data"), root->GetData() );

	tree->Set( String::NewFromUtf8(isolate, "children"), root->GetChildren(0) );

	return tree;
}
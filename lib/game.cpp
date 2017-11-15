#include <nan.h>

using namespace Nan;
using namespace v8;
using namespace std;

//This it's already a class, so no needs to make a Game class
/*
class node {
  int[3][3] _data;
public:
  node* parent;
  node(int[3][3] data){
    _data = data;
    parent = NULL;
  }
}

class tree {
  public:
    tree();
    ~tree();
    void insert(int key);

  private:
    node *root;
    void insert(int key, node *leaf);

}

tree::tree(){
  root = NULL;
}*/

void getTree(const v8::FunctionCallbackInfo<v8::Value>&args) {
  Isolate* isolate = args.GetIsolate();
  
  //v8::HandleScope handle_scope;
  Handle<Object> tree = Object::New(isolate);

  
  // Create the array
  Local<Array> gamepad = Local<Array>::Cast(args[0]);
  // unsigned int rows = gamepad.Length();
  
  tree->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "root") );
  tree->Set( String::NewFromUtf8(isolate, "data"), gamepad );
  //tree->Set( String::New("children"), Array::New(gamepad) );

  
  // Send back the gamepad
  args.GetReturnValue().Set(tree);
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "test", getTree);
  /* Callback initializations
  exports->Set(Nan::New("NameFunction").ToLocalChecked(),
  Nan::New<v8::FunctionTemplate>(NameFunction)->GetFunction());*/
}

NODE_MODULE(addon, Initialize)
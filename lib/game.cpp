#include <nan.h>

using namespace Nan;
using namespace v8;
using namespace std;

Local<Array> makeMove(Isolate* isolate, Local<Array> gamepad );
void getTree(const v8::FunctionCallbackInfo<v8::Value>&args);

void getTree(const v8::FunctionCallbackInfo<v8::Value>&args) {
  Isolate* isolate = args.GetIsolate();
  
  //v8::HandleScope handle_scope;
  Handle<Object> tree = Object::New(isolate);

  Handle<Object> child = Object::New(isolate);

  
  // Create the array
  Local<Array> gamepad = Local<Array>::Cast(args[0]);
  // unsigned int rows = gamepad.Length();
  
  tree->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "root") );
  tree->Set( String::NewFromUtf8(isolate, "data"), gamepad );

  child->Set( String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, "X on up-left") );
  child->Set( String::NewFromUtf8(isolate, "data"), makeMove(isolate, gamepad) );

  tree->Set( String::NewFromUtf8(isolate, "children"), child );

  
  // Send back the gamepad
  args.GetReturnValue().Set(tree);
}

Local<Array> makeMove(Isolate* isolate, Local<Array> gamepad ){

  Local<Array> row = Array::New(isolate);
  row->Set(0, gamepad->Get(0));

  if( (int)row->Get(0)->Int32Value() == 0 ){
    row->Set(0, Integer::New(isolate, 1));
  }
  gamepad->Set( 0, row );
  return gamepad;
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "test", getTree);
  /* Callback initializations
  exports->Set(Nan::New("NameFunction").ToLocalChecked(),
  Nan::New<v8::FunctionTemplate>(NameFunction)->GetFunction());*/
}

NODE_MODULE(addon, Initialize)
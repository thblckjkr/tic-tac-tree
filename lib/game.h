#include <nan.h>

using namespace Nan;
using namespace v8;
using namespace std;

Local<Array> makeMove(Isolate* isolate, Local<Array> gamepad );
void getTree(const v8::FunctionCallbackInfo<v8::Value>&args);
void Initialize(v8::Local<v8::Object> exports);
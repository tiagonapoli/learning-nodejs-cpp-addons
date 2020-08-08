#include <node.h>
#include <iostream>
using namespace v8;

void Add(const FunctionCallbackInfo<Value> &args) {
	if (args.Length() < 2 || !args[0]->IsNumber() || !args[1]->IsNumber()) {
		return;
	}

	Isolate *isolate = args.GetIsolate();
	double value = args[0]->NumberValue(isolate->GetCurrentContext()).ToChecked() + args[1]->NumberValue(isolate->GetCurrentContext()).ToChecked();
	Local<Number> ret = Number::New(isolate, value);
	args.GetReturnValue().Set(ret);
}

void CallbackCall(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	Local<Function> cb = Local<Function>::Cast(args[0]);
	cb->Call(isolate->GetCurrentContext(), Null(isolate), 0, nullptr);
	return;
}

void CallbackCallWithParams(const FunctionCallbackInfo<Value> &args) {
	Isolate *isolate = args.GetIsolate();
	Local<Function> cb = Local<Function>::Cast(args[0]);

    Local<Value> cbArgs[1] = { args[1] };
	cb->Call(isolate->GetCurrentContext(), Null(isolate), 1, cbArgs);
	return;
}

void Init(Local<Object> exports) {
	NODE_SET_METHOD(exports, "add", Add);
	NODE_SET_METHOD(exports, "callCb", CallbackCall);
    NODE_SET_METHOD(exports, "callCbWithArgs", CallbackCallWithParams);
}

NODE_MODULE(parameters_addon, Init)
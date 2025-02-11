#pragma once
#include "archives/archive.hpp"
#include "nlohmann/json.hpp"
#include <stack>

struct StackContext {
	enum class Context {
		Array,
		Object
	};

	Context context;
	int unnamedIndex;
	nlohmann::ordered_json document;
	const char* name;

	StackContext(Context context) : context(context), unnamedIndex(0) { }

	std::string GetNextName() {
		if (name != nullptr) {
			const char* temp = name;
			name = nullptr; 
			return temp;
		}

		return "unnamedVariable_" + std::to_string(unnamedIndex++);
	}
};

class JSONOutputArchive : public OutputArchive<JSONOutputArchive> {
public:
	JSONOutputArchive(std::ostream& stream) : 
		OutputArchive<JSONOutputArchive>(this),
		_stream(stream) 
	{ 
		_contextStack.push(StackContext::Context::Object);
	};

	~JSONOutputArchive() {
		_stream << TopStack().document.dump(4);
	}

	template<typename T>
	void ProcessImpl(T&& data) {
		int something = 0;
		something++;
		//TopStack().document[TopStack().GetNextName()] = data;
	}

	void SetNextName(const char* name) {
		TopStack().name = name;
	}

	void StartArray() {
		_contextStack.push(StackContext::Context::Array);
	}

	void EndArray() {
		StackContext context = _contextStack.top().document;
		_contextStack.pop();
		TopStack().document["Random Name 2"] = context.document;
	}

private:
	StackContext& TopStack() {
		return _contextStack.top();
	}

private:
	std::ostream& _stream;
	std::stack<StackContext> _contextStack;
};


template<typename T>
void Prologue(JSONOutputArchive& a, ArrayRef<T>&& ar) {
	std::cout << "Prologueing Array" << std::endl;
	a.StartArray();
}

template<typename T>
void Prologue(JSONOutputArchive& a, NVP<T>&& nvp) {
	std::cout << "Prologueing NVP" << std::endl;
	a.SetNextName(nvp.name);
}
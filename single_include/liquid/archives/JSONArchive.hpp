#pragma once
#include <liquid/archives/archive.hpp>
#include <nlohmann/json.hpp>
#include <stack> 

namespace Liquid {
	/// <summary>
	/// Context of the indentation stack.
	/// </summary>
	struct StackContext {
		enum class Context {
			Array,
			Object
		};

		Context context;
		int unnamedIndex;
		nlohmann::ordered_json document;
		const char* name;

		StackContext(Context context) : context(context), unnamedIndex(0), name(nullptr) { }

		/// <summary>
		/// Fetches and increases the current unnamed index value.
		/// </summary>
		/// <returns>The current unnamed index value.</returns>
		int GetNextUnnamedIndex() { return unnamedIndex++; }

		/// <summary>
		/// Returns the currently set name, or a substitue based on an unnamed index value.
		/// </summary>
		/// <returns>The currently set name, or a substitue based on an unnamed index value.</returns>
		std::string GetNextName() {
			if (name != nullptr) {
				const char* temp = name;
				name = nullptr;
				return temp;
			}

			return "_" + std::to_string(GetNextUnnamedIndex());
		}

		/// <summary>
		/// Retrieves the next variable in the current object, based on the next name in the context.
		/// </summary>
		/// <returns>The next variable in the current object</returns>
		nlohmann::ordered_json& GetNextVariable() { return document[GetNextName()]; }

		/// <summary>
		/// Retrieves the next index in the current array.
		/// </summary>
		/// <returns>The next index in the current array</returns>
		nlohmann::ordered_json& GetNextArrayIndex() { return document[GetNextUnnamedIndex()]; }
	};

	/// <summary>
	/// Archive that outputs serialized data into JSON formatted files.
	/// </summary>
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
		void SaveData(T&& data) {
			if (TopStack().context == StackContext::Context::Array)
				TopStack().document.push_back(data);
			else
				TopStack().GetNextVariable() = data;
		}

		/// <summary>
		/// Sets next name in the context list.
		/// </summary>
		/// <param name="name">Next name entry</param>
		void SetNextName(const char* name) { TopStack().name = name; }

		/// <summary>
		/// Starts an indent with the corresponding context.
		/// </summary>
		/// <param name="ctx">Context for the indent.</param>
		void StartIndent(StackContext::Context ctx) { _contextStack.push(ctx); }

		/// <summary>
		/// End the current indent.
		/// </summary>
		void EndIndent() {
			StackContext context = TopStack();
			_contextStack.pop();
			SaveData(context.document);
		}


	private:
		StackContext& TopStack() {
			return _contextStack.top();
		}

	private:
		std::ostream& _stream;
		std::stack<StackContext> _contextStack;
	};

#ifdef DISABLE


	/// <summary>
	/// Archive that inputs JSON formatted files into serialized data.
	/// </summary>
	class JSONInputArchive : public OutputArchive<JSONInputArchive> {
	public:
		JSONInputArchive(std::istream& stream) :
			OutputArchive<JSONInputArchive>(this)
		{
			_contextStack.push(StackContext::Context::Object);
			_contextStack.top().document = nlohmann::json::parse(stream);
		};

		template<typename T>
		void LoadData(T&& data) {
			if (TopStack().context == StackContext::Context::Array)
				data = TopStack().GetNextArrayIndex();
			else
				data = TopStack().GetNextVariable();
		}

		/// <summary>
		/// Sets next name in the context list.
		/// </summary>
		/// <param name="name">Next name entry</param>
		void SetNextName(const char* name) {
			TopStack().name = name;
		}

		/// <summary>
		/// Opens an indent with the corresponding context.
		/// </summary>
		/// <param name="ctx">Context for the indent.</param>
		void OpenIndent(StackContext::Context ctx) {
			StackContext context = TopStack();
			_contextStack.push(ctx);
			if (context.context == StackContext::Context::Array) 
				TopStack().document = context.document[TopStack().unnamedIndex++];
			else
				TopStack().document = context.GetNextVariable();
		}

		/// <summary>
		/// Closes the current indent.
		/// </summary>
		void CloseIndent() {
			_contextStack.pop();
		}

	private:
		StackContext& TopStack() {
			return _contextStack.top();
		}

	private:
		std::stack<StackContext> _contextStack;
	};
#endif // DISABLE

	template<typename T>
	std::enable_if_t<std::is_arithmetic_v<T>>
	save(JSONOutputArchive& archive, T& t) {
		archive.SaveData(t);
	}

	template<typename T>
	std::enable_if_t<std::is_array_v<T>>
	serialize(JSONOutputArchive& ar, T& t) {
		for(auto const& i : t)
			ar(i);
	}

#pragma region OutputArchive
	template<typename T>
	std::enable_if_t<std::is_array_v<T>>
	prologue(JSONOutputArchive& a, T&) {
		a.StartIndent(StackContext::Context::Array);
	}

	template<typename T>
	std::enable_if_t<std::is_array_v<T>>
	epilogue(JSONOutputArchive& a, T& ar) {
		a.EndIndent();
	}
#pragma endregion

}
#pragma once

#include <cassert>
#include <functional>

template<typename T>
struct CachedVar {
	CachedVar() : _callback(nullptr) {}
	CachedVar(std::function<T()> callback) : _callback(callback) {}
	constexpr bool isCached() {
		return _set;
	}

	void clear() {
		_set = false;
	}

	void set(const T& val) {
		_var = val;
		_set = true;
	}

	T& get() {
		if(!_set && _callback) {
			_var = _callback();
			_set = true;
		}
		assert(_set);
		return _var;
	}

private:
	std::function<T()> _callback;
	T _var;
	bool _set;
};

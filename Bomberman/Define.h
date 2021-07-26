#pragma once
template <typename T>
inline void Safe_Release(T& _Obj)
{
	if (_Obj)
	{
		delete _Obj;
		_Obj = NULL;
	}
}

#define SAFE_RELEASE(obj) Safe_Release(obj)

#pragma once

template <class T>
class CSingleton
{
private:
	static T* inst;

public:
	CSingleton() {}
	virtual ~CSingleton() {}

	static T* GetInstance()
	{
		if (!inst)
		{
			inst = new T;
		}
		return inst;
	}

	static void DestroyInstance()
	{
		if (inst)
		{
			delete inst;
		}
		inst = nullptr;
	}
};

template <class T>
T* CSingleton<T>::inst = nullptr;
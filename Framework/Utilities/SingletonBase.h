#pragma once

template <typename transMatrix>
class SingletonBase
{
public:
	static void Create()
	{
		if (instance == nullptr)
			instance = new transMatrix();
	}

	static void Delete()
	{
		delete instance;
		instance = nullptr;
	}

	static transMatrix* Get()
	{
		return instance;
	}

protected:
	static transMatrix* instance;
};

template<typename transMatrix> 
transMatrix* SingletonBase<transMatrix>::instance = nullptr;
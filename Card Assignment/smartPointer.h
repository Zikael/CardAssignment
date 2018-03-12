#ifndef _SMARTPOINTER_H
#define _SMARTPOINTER_H

template<typename T > class smartPointer
{
private:
	T* mptr = nullptr;
public:
	smartPointer(T* ptr)
	{
		mptr = ptr;
	}
	~smartPointer()
	{
		delete mptr;
	}

	T& operator* ()
	{
		return *mptr; 
	};

	T* operator->() const
	{
		return mptr;
	};
};

#endif
#pragma once
#include <iostream>
using namespace std;

template <class ElemType> class MyStack
{
public:
	const static  int MAXSIZE = 100;
	ElemType data[MAXSIZE];
	int top;

public:
	void init();			// 初始化栈
	bool empty();			// 判断栈是否为空
	ElemType gettop();	    // 读取栈顶元素(不出栈)
	void push(ElemType x);	// 进栈
	ElemType pop();			// 出栈
};


template<class T> void MyStack<T>::init()
{
	this->top = 0;
}

template<class T> bool MyStack<T>::empty()
{
	return this->top == 0 ? true : false;
}

template<class T> T MyStack<T>::gettop()
{
	if (empty())
	{
		cout << "栈为空！\n";
		exit(1);
	}
	return this->data[this->top - 1];
}

template<class T> void MyStack<T>::push(T x)
{
	if (this->top == MAXSIZE)
	{
		cout << "栈已满！\n";
		exit(1);
	}
	this->data[this->top] = x;
	this->top++;
}

template<class T> T MyStack<T>::pop()
{
	if (this->empty())
	{
		cout << "栈为空! \n";
		exit(1);
	}

	T e = this->data[this->top - 1];
	this->top--;
	return e;
}

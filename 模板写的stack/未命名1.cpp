#include <iostream>
#include<cstdlib>

using namespace std;

template<class T> class Stack
{
public:
	Stack(int = 100);
	~Stack()
	{delete [] value;};
	T push(T);
	bool empty();
	T pop();
	T Size();
	T top();
	
private:
	int size;
	T *value;
	int status;
};

template< class T > Stack<T>::Stack(int x):
	size(x),
	status(-1),
	value(new T[size])
{}  //empty

template< class T >bool Stack<T>::empty() 
{
	if(status == -1) return 1;
	else return 0;
}

template< class T > T Stack<T>::push(T x)
{
	status+=1;
	value[status]=x; 
} 

template< class T > T Stack<T>::pop()
{
	if(!Stack<T>::empty())
	{
		status--;
	}
}

template< class T > T Stack<T>::Size()
{
	return status+1;
}

template< class T > T Stack<T>::top()
{
	return value[status];
}

void test()
{
	Stack <int> stack1;
	stack1.push(1);
	stack1.push(9);
	stack1.push(1);
	stack1.pop();
	cout<<stack1.top();
}

int main()
{
	test();
	return 0;
}

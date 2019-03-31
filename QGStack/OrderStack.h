#pragma once

template <typename T>
class OrderStack
{
public:
	OrderStack();
	//带参构造：初始化栈大小
	OrderStack(int initmaxSize);
	~OrderStack();

	//清空
	void clear(void);
	//是否空
	bool isEmply();
	//获得栈顶元素引用,空栈返回false，getter不变
	bool getTop(T& getter);
	//出栈，空栈返回false
	bool pop();
	//出栈，空栈返回false，getter不变
	bool pop(T& getter);
	//入栈
	void push(T data);
	//栈元素数量
	int size();
	//栈大小
	int maxsize();
	//重设栈大小，若元素数量大于重设大小，取消重设返回false
	bool remaxSize(int resize);

private: 
	int stackTop;			//栈顶
	int maxSize;			//最大数量
	int stackSize;			//当前元素数量
	T* stackData;			//数据
};

template<typename T>
inline OrderStack<T>::OrderStack()
{
	stackTop = -1;
	maxSize = 40;
	stackSize = 0;
	stackData = new T[maxSize];
}

template<typename T>
inline OrderStack<T>::OrderStack(int initmaxSize)
{
	stackTop = -1;
	maxSize = initmaxSize;
	stackSize = 0;
	stackData = new T[maxSize];
}

template<typename T>
inline OrderStack<T>::~OrderStack()
{
	delete stackData;
}

template<typename T>
inline void OrderStack<T>::clear(void)
{
	stackSize = 0;
	stackTop = -1;
}

template<typename T>
inline bool OrderStack<T>::isEmply()
{
	if (stackSize)
		return true;
	return false;
}

template<typename T>
inline bool OrderStack<T>::getTop(T & getter)
{
	if (!stackSize)
		return false;
	getter = stackData[stackTop];
	return true;
}

template<typename T>
inline bool OrderStack<T>::pop()
{
	if (!stackSize)
		return false;
	stackSize--;
	stackTop--;
	return true;
	
}

template<typename T>
inline bool OrderStack<T>::pop(T & getter)
{
	if (!stackSize)
		return false;
	getter = stackData[stackTop];
	stackSize--;
	stackTop--;
	return true;
}

template<typename T>
inline void OrderStack<T>::push(T data)
{
	if (stackSize == maxSize)
	{
		remaxSize(maxSize * 2);
		push(data);
	}
	else
	{
		stackTop++;
		stackSize++;
		stackData[stackTop] = data;
	}
}

template<typename T>
inline int OrderStack<T>::size()
{
	return stackSize;
}

template<typename T>
inline int OrderStack<T>::maxsize()
{
	return maxSize;
}

template<typename T>
inline bool OrderStack<T>::remaxSize(int resize)
{
	if (resize < stackSize)
		return false;
	maxSize = resize;
	T* newdata = new T[maxSize];//新建数组
	for (int i = 0; i < stackSize; i++)//复制数据
		newdata[i] = stackData[i];
	delete stackData;//释放旧数组
	stackData = newdata;
	return true;
}

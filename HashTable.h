#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <iostream>
using namespace std;

enum State
{
	EMPTY,	//空状态
	DELETE,	//删除状态
	EXIST,	//存在状态
};

template <class T>
class HashTable
{
public:
	HashTable(const T& capacity = 10)
		:_capacity(capacity)
		,_size(0)
		,_tables(new T[_capacity])
		,_states(new State[_capacity])
	{
		for(size_t i = 0; i<_capacity; i++)		//将表的每一个位置的状态置空
		{
			_states[i] = EMPTY;		
		}
	}
	HashTable(const HashTable<T>& ht)
		:_capacity(ht._capacity)
		,_size(ht._size)
		,_tables(new T[_capacity])
		,_states(new State[_capacity])
	{
		for(size_t i = 0; i<_capacity; ++i)
		{
			_tables[i] = ht._tables[i];
			_states[i] = ht._states[i];
		}
	}
	HashTable<T>& operator=(HashTable<T> ht)
	{
		if(this != &ht)
		{
			swap(_capacity, ht._capacity);
			swap(_size, ht._size);
			swap(_tables, ht._tables);
			swap(_states, ht._states);
		}
		return *this;
	}
	~HashTable()
	{
		if(_tables != NULL)
		{
			delete[] _tables;
			_tables = NULL;
		}
		if(_states != NULL)
		{
			delete[] _states;
			_states = NULL;
		}
		_size = 0;
	}
public:
	bool Insert(const T& key)
	{
		if(_capacity == _size)
		{
			cout<<"HashTable is full."<<endl;
			return false;
		}
		size_t index = _HashFun(key);	//找key的位置
		while(EXIST == _states[index])	//线性探测
		{
			if(key == _tables[index])
			{
				return false;
			}
			++index;
			if(index == _capacity)//当到达末尾时，跳到表开始处，继续找非存在位置插入元素
			{
				index = 0;
			}
		}
		_tables[index] = key;	//将key存入表中
		_states[index] = EXIST;	//状态置为存在
		++_size;				//将_size加一
		return true;		
	}
	bool Find(const T& key)
	{
		size_t index = _HashFun(key);	//找key的位置
		size_t start = index;			//查找开始处
		while(EMPTY == _states[index])
		{
			if(key == _tables[index])
			{
				if(DELETE == states[index])
				{
					return false;
				}
				else
				{
					return true;
				}
			}
			++index;
			if(index == _capacity)	//当index等于容量时，从表头开始继续查找
			{
				index = 0;
			}
			if(index == start)	//如果查找到第二次走到开始位置，表示没找到
			{
				return false;
			}
		}
		return false;
	}
	bool Remove(const T& key)
	{
		if(0 == _size)
		{
			cout<<"HashTable is empty."<<endl;
			return false;
		}
		size_t index = _HashFun(key);
		size_t start = index;
		while(_states[index] == EMPTY)
		{
			if(_tables[index] == key)
			{
				if(_states[index] == DELETE)
				{
					return false;
				}
				else
				{
					_states[index] = DELETE;
					--_size;
					return true;
				}
			}
			++index;
			if(index == _capacity)
			{
				index = 0;
			}
			if(index = start)
			{
				return false;
			}
		}
		return false;
	}
	void Print()
	{
		for(size_t i = 0; i<_capacity; ++i)
		{
			printf("[%d, %d]-->",_states[i], _tables[i]);
		}
		cout<<"Nvl."<<endl;
		
	}
protected:
	size_t _HashFun(const T& key)
	{
		return key%_capacity;
	}
	
private:
	size_t _capacity;	//哈希表容量
	size_t _size;		//哈希表元素个数
	T* _tables;			//哈希表
	State* _states;		//哈希表的状态表
};

#endif

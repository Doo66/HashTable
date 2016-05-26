#include "HashTable.h"

void Test()
{
	HashTable<int> ht;
	ht.Insert(89);
	ht.Insert(18);
	ht.Insert(49);
	ht.Insert(58);
	ht.Insert(9);
	//ht.Insert(19);
	ht.Print();

}

int main()
{
	Test();
	return 0;
}


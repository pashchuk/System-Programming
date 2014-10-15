#include <iostream>
#include <string>
#include "Table.h"


using namespace std;
using namespace tables;

void Insert(table*);
void Print(table*);
void Update(table*);
void Delete(table*);

void main(string args[])
{
	table table;
	table.size = 0;
	table.rows = new row[100];
	string cmd;
	while (1)
	{
		cin >> cmd;
		if (cmd == "ins")
		{
			Insert(&table);
			continue;
		}
		if (cmd == "print")
		{
			Print(&table);
			continue;
		}
		if (cmd =="del")
		{
			Delete(&table);
			continue;
		}
		if (cmd == "upd")
		{
			Update(&table);
			continue;
		}
		if (cmd == "sort")
		{
			Sort(&table);
			continue;
		}
		if (cmd == "exit")
			break;
		cout << "incorrect command \n";
	}
	for (int i = 0; i < table.size; i++)
	{
		delete[] table.rows[i].key.mainKey;
	}

	
}

void Insert(table* table)
{
	cout << "input element in format:('first key'_'second key_'value')\n";
	row *newRow = new row();
	cin >> newRow->key.mainKey >> newRow->key.secondKey >> newRow->data;
	newRow->isDelete = false;
	Insert(table, newRow);
	cout << "new element inserted\n";
}
void Print(table *table)
{
	printf("%-12s %-12s %-12s %-12s \n", "Primary key", "Second key", "Float value", "Deleted");
	for (int i = 0; i < table->size; i++)
	{
		printf("%-12s %-12c %-12.3f %-10s \n", table->rows[i].key.mainKey, (char)table->rows[i].key.secondKey, table->rows[i].data, table->rows[i].isDelete ? "true" : "false");
	}
}
void Update(table *table)
{
	cout << "input key of element in format:('first key'_'second key)\n";
	key key;
	cin >> key.mainKey >> key.secondKey;
	cout << "input new value:\n";
	row *newRow = new row();
	cin >> newRow->data;
	newRow->key = key;
	newRow->isDelete = 0;
	bool res = 0;
	try
	{
		res = Update(table, key, newRow);
	}
	catch (exception ex)
	{
		cout << "Element update failed\n";
	}
	cout << (res ? "Element update succesfull\n" : "Element update failed\n");
}
void Delete(table *table)
{
	cout << "input key of element in format:('first key'_'second key)\n";
	key key;
	cin >> key.mainKey >> key.secondKey;
	bool res;
	try
	{
		res = Delete(table, key);
	}
	catch (exception ex)
	{
		cout << "element delete failed\n";
		return;
	}
	cout << (res ? "Element delete succesfull\n" : "Element delete failed\n");
}

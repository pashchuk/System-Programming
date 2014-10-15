#include "Table.h"
#include "cstring"
#include <iostream>

bool tables::key::operator==(const key& key)
{
	if (!strcmp(mainKey, key.mainKey))
		return secondKey == key.secondKey;
	return 0;
}
bool tables::key::operator!=(const key& key)
{
	if (!strcmp(mainKey, key.mainKey))
		return secondKey != key.secondKey;
	return 1;
}
bool tables::key::operator<(const tables::key& key)
{
	if (!strcmp(mainKey, key.mainKey))
		return secondKey < key.secondKey;
	return strcmp(mainKey, key.mainKey) < 0;
}
bool tables::key::operator>(const tables::key& key)
{
	if (!strcmp(mainKey, key.mainKey))
		return secondKey > key.secondKey;
	return strcmp(mainKey, key.mainKey) > 0;
}
bool tables::key::operator<=(const tables::key& key)
{
	if (!strcmp(mainKey, key.mainKey))
		return secondKey <= key.secondKey;
	return strcmp(mainKey, key.mainKey) < 0;
}
bool tables::key::operator>=(const tables::key& key)
{
	if (!strcmp(mainKey, key.mainKey))
		return secondKey >= key.secondKey;
	return strcmp(mainKey, key.mainKey) > 0;
}
tables::key::key()
{
	mainKey = new char[10];
	secondKey = 0;
}
tables::row& tables::row::operator=(const tables::row& newRow)
{
	char * temp = new char[10];
	strcpy(temp, newRow.key.mainKey);
	key.mainKey = temp;
	key.secondKey = newRow.key.secondKey;
	data = newRow.data;
	isDelete = false;
	return *this;
}

tables::row* tables::DirectSearch(tables::table *table, tables::DirectKey address)
{
	return &table->rows[address];
}

tables::row* tables::LinearSearch(tables::table *table, tables::key key)
{
	int counter = 0;
	while (table->rows[counter].key.mainKey != nullptr)
	{
		if (table->rows[counter++].key == key)
			return &table->rows[counter - 1];
	}
	return nullptr;
}

tables::row* BinnarySearchRecursive(tables::table *table, tables::key key, int startLength, int endLength)
{
	if (endLength < startLength)
		return nullptr;
	int mid = (startLength + endLength) >> 1;
	if (table->rows[mid].key == key)
		return &table->rows[mid];
	if (key <= table->rows[mid].key)
		return BinnarySearchRecursive(table, key, startLength, mid);
	else
		return BinnarySearchRecursive(table, key, mid + 1, endLength);
	return nullptr;
}

tables::row* tables::BinnarySearch(tables::table *table, tables::key key)
{
	return BinnarySearchRecursive(table, key, 0, table->size - 1);
}

void tables::Sort(tables::table *table)
{
	for (int i = 0; i < table->size; i++)
		for (int j = 0; j < table->size - i - 1; j++)
			if (table->rows[j].key > table->rows[j + 1].key)
				{
					tables::row tempRecord = table->rows[j];
					table->rows[j] = table->rows[j + 1];
					table->rows[j + 1] = tempRecord;
				}
}

bool tables::Insert(tables::table *table, tables::row *newRow)
{
	*(table->rows + table->size) = *newRow;
	table->size++;
	return true;
}
bool tables::Delete(tables::table *table, tables::key key)
{
	tables::row *finded = tables::BinnarySearch(table, key);
	if (finded != nullptr)
		if (!finded->isDelete)
		{
			finded->isDelete = true;
			return true;
		}
	return false;
}
bool tables::Update(tables::table * table, tables::key key, tables::row *newRow)
{
	tables::row *finded = tables::BinnarySearch(table, key);
	if (finded != nullptr)
		if (!finded->isDelete)
		{
			*finded = *newRow;
			return true;
		}
	return false;
}

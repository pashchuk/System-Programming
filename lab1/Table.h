
namespace tables{
	typedef unsigned long DirectKey;

	struct key
	{
		char *mainKey;
		unsigned char secondKey;
	public:
		key();
		bool operator==(const key& key);
		bool operator!=(const key& key);
		bool operator<(const key& key);
		bool operator>(const key& key);
		bool operator<=(const key& key);
		bool operator>=(const key& key);
	};

	struct row
	{
		key key;
		float data;
		bool isDelete;
	public:
		row& operator=(const row& row);
	};
	struct table
	{
		row *rows;
		int size;
	};

	row* DirectSearch(table*, DirectKey);
	row* LinearSearch(table*, key);
	row* BinnarySearch(table*, key);
	bool Insert(table*, row*);
	bool Delete(table*, key);
	bool Update(table*, key, row*);
	void Sort(table*);
}
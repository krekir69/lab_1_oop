#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
class CStr {
private:
	char* string;
	char* generate(int length)
	{
		if (length > 0  && length <= 20)
		{
			char* s = new char[length + 1];
			for (int i = 0; i < length;i++)
			{
				s[i] = 'a' + rand() % 26;
			}
			s[length] = '\0';
			return s;
		}
		else
			return 0;
	}
public:
	CStr& operator+=(CStr& obj);
	CStr() {
		int len = 1 + rand() % 20;
		string = generate(len);
	}
	CStr(const char* str) {
		string = new char[strlen(str) + 1];
		strcpy_s(string, strlen(str) + 1, str);
	}
	CStr(int length) {
		string = generate(length);
	}
	CStr(const CStr& obj) {
		string = new char[strlen(obj.string) + 1];
		strcpy_s(string, strlen(obj.string) + 1, obj.string);
	}
	~CStr() {
		delete[] string;
	}
	CStr& operator=(CStr& obj)
	{
		if (this != &obj) {
			delete[] string;
			int len = strlen(obj.string);
			string = new char[len + 1];
			strcpy_s(string, len + 1, obj.string);
		}
		return *this;
	}
	CStr& operator=(const char* str)
	{
		delete[] string;
		if (str == nullptr) {
			string = new char[1];
			string[0] = '\0';
		}
		else {
			int len = strlen(str);
			string = new char[len + 1];
			strcpy_s(string, len + 1, str);
		}
		return *this;
	}
	CStr operator+(const CStr& obj) const
	{
		int len1 = strlen(this->string);
		int len2 = strlen(obj.string);
		int newlen = len1 + len2;
		char* buff = new char[newlen + 1];
		strcpy_s(buff, newlen + 1, this->string);
		strcat_s(buff, newlen + 1, obj.string);
		CStr res(buff);
		delete[] buff;
		return res;
	}
	
	bool operator>(CStr& obj) const;
	char& operator[](int index)
	{
		return string[index];
	}
	int get_length() const
	{
		return strlen(string);
	}
	friend ostream& operator<<(ostream& stream, CStr& obj);
	friend istream& operator>>(istream& stream, CStr& obj);	
};
ostream& operator<<(ostream& stream, CStr& obj)
{
	stream << obj.string;
	return stream;
}
bool CStr::operator>(CStr& obj) const
{
	return (strcmp(this->string, obj.string) > 0);
}
istream& operator>>(istream& stream, CStr& obj)
{

	const int BUF = 1024;
	char buffer[BUF];
	stream >> buffer;
	delete[] obj.string;
	int len = strlen(buffer);
	obj.string = new char[len + 1];
	strcpy_s(obj.string, len + 1, buffer);
	return stream;
}
CStr& CStr::operator+=(CStr& obj)
{
	int len1 = strlen(this->string);
	int len2 = strlen(obj.string);
	char* buff = new char[len1 + len2 + 1];
	strcpy_s(buff, len1 + len2 + 1, this->string);
	strcat_s(buff, len1 + len2 + 1, obj.string);
	delete[] string;
	string = buff;
	return *this;
}
class CStrArray {
	CStr** arr;
	int capacity, size;
public:
	CStrArray(int cap) {
		capacity = cap;
		size = 0;
		arr = new CStr *[capacity];
		for (int i = 0;i < capacity; ++i) 
			arr[i] = nullptr;
		
	}
	CStrArray& operator +=(CStr* obj) {
		if (size < capacity) {
			arr[size++] = obj;
		}
		else {
			cout << "Массив переполнен" << endl;
		}
		return *this;
	}
	~CStrArray() {
		delete[] arr;
	}
	CStr* operator[](int index) {
		if (index >= 0 && index < size) {
			return arr[index];
		}
		return nullptr;
	}
	void sort_by_content() {
		for (int i = 0; i < size - 1;++i) {
			for (int j = 0; j < size - 1 - i; ++j) {
				if (arr[j] != nullptr && arr[j + 1] != nullptr) {
					
					if (*arr[j] > *arr[j + 1]) {
						swap(arr[j], arr[j + 1]);
					}
				}
			}
		}
	}
	void sort_by_length()
	{
		for (int i = 0; i < size - 1; ++i)
		{
			for (int j = 0; j < size - 1 - i; ++j)
			{
				if (arr[j] != nullptr && arr[j + 1] != nullptr)
				{
					if (arr[j]->get_length() > arr[j + 1]->get_length())
					{
						swap(arr[j], arr[j + 1]);
					}
				}
			}
		}
	}
	bool check_sort() {
		for (int i = 1; i < size; ++i) {
			if (*arr[i - 1] > *arr[i])
				return false;
		}
		return true;
	}
	friend ostream& operator<<(ostream& stream, CStrArray& obj);
};
ostream& operator<<(ostream& stream, CStrArray& obj) {
	for (int i = 0; i < obj.size; ++i)
		stream << *obj.arr[i] << " ";
	return stream;
}
int main() {
	setlocale(LC_ALL, "RUS");
	srand(time(0));
	CStr a;
	CStr b("orange");
	CStr c(10);
	CStr d("kiwi");
	CStr e("pear");
	cout << "Строка a :"<< a << endl;
	cout << "Строка b :" << b << endl;
	cout << "Строка c :" << c << endl;
	cout << "Строка d :" << d << endl;
	cout << "Строка e :" << e << endl;
	CStr f = a + b;   
	cout << "a + b = " << f << endl;
	a += c;          
	cout << "a += c -> " << a << endl;
	cout << "b > c ? " << (b > c ? "true" : "false") << endl;
	cout << "b[1] = " << b[1] << endl;
	cout << "len(c) = " << c.get_length() << endl;
	cout << "Создаем массив строк:\n";
	CStrArray arr(5);

	arr += &a;
	arr += &b;
	arr += &c;
	arr += &d;
	arr += &e;

	cout << "Исходный массив:\n" << arr << endl;
	arr.sort_by_content();
	cout << "\nОтсортировано по содержимому:\n" << arr << endl;
	cout << "Проверка упорядоченности: " << (arr.check_sort() ? "OK" : "NOT SORTED") << endl;
	arr.sort_by_length();
	cout << "\nОтсортировано по длине:\n" << arr << endl;

	return 0;	
}
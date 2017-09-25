#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
//#include <windows.h>
#include <algorithm>
#include "advert.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ios_base;
unsigned int count = {0};
unsigned int ads = {0};

Advert::Advert()
{
	name_ad = "\0";
	price = {0.0};
	photo = {0};
}

Advert::Advert(unsigned int c)
{
	ifstream fin;
	fin.open("avito.html");
	string temp;
	string * str;
	str = new string[count];
	for (unsigned int i = {0}; i < count && !fin.eof(); ++i)
	{
		getline(fin, temp);
		str[i] = temp;
	}
	unsigned int line[ads]; // Строки, над которыми содержатся названия объявлений
	unsigned int i = {0};
	for (unsigned int j = {0}; j < ads; ++j)
    {
		while (!find_ad(str[i++],about))
			line[j]++;
		line[j+1] = line[j] + 1;
	}
	fin.clear();
	fin.seekg(0, ios_base::beg);
	unsigned int line1[ads]; // Строки, после которых содержатся цены объявлений
	unsigned int k = {0};
	for (unsigned int j = {0}; j < ads; ++j)
    {
		while (k < count - 2 && !find_ad(str[k++],about))
		{
				line1[j]++;
		}
			line1[j+1] = line1[j] + 1;
	}

	string t_price;
	if (find_ad(str[line1[c] + 1],rub))
	{
		string prc;
		t_price = str[line1[c] + 1];  
		unsigned int pos = str[line1[c] + 1].find(rub,0) - 1;
		t_price.erase(pos,t_price.length() + 1);
		t_price.erase (0,27); 
		unsigned int j = {0};
		for (unsigned int i = {0}; i < t_price.length(); ++i)
		{
			if (t_price[i] != ' ')
				prc[j++] = t_price[i];
		}
		price = strtod(prc.c_str(), nullptr); 
	}
	else
		price = {0.0};

	if (find_ad(str[line[c]],about))
	{
		name_ad = str[line[c] - 2];
	}
	name_ad.erase (0,27);
	if (name_ad == " </span><span>&lt;/<span class=\"end-tag\">a</span>&gt;</span><span>") 
	{
		name_ad = str[line[c] - 3];
		name_ad.erase (0,27);
	}
	else if (name_ad.find("<span class=\"entity\"><span>&amp;</span>quot;</span>", 0) != -1)
	{
		string temp1 = "<span class=\"entity\"><span>&amp;</span>quot;</span>";
		string temp2 = "<span class=\"entity\"><span>&amp;</span>quot;</span>";
		unsigned int pos1 = name_ad.find(temp1, 0);
		name_ad.erase(pos1,temp1.length());
		unsigned int pos2 = name_ad.find(temp2, 0);
		name_ad.erase(pos2,temp1.length());
	}

	string t_photo;
	if (find_ad(str[line[c]-15],ad))
	{
		unsigned int pos1 = str[line[c]-15].find("</span>raquo;</span>",0);
		t_photo = str[line[c]-15];
		t_photo.erase(0,pos1 + 22);
		t_photo = t_photo[0];
		if (t_photo != "с")
		{
			photo = atoi(t_photo.c_str());
		}
		else 
			photo = {1};
	}
	else
		photo = {1};

	fin.close();
	delete [] str;
}

Advert::~Advert()
{
}

unsigned int get_count_of_ads()
{
	ifstream fin;
	fin.open("avito.html");
	string temp;
	string * str;

	if (!fin.is_open())
	{
		cout << "[-] Could't open file!";
		exit(EXIT_FAILURE);
	}
	while (!fin.eof())
	{
		unsigned int i = {0};
		while (getline(fin, temp))
		{
			count++;			
		}
	}
	fin.clear();
	fin.seekg(0, ios_base::beg);
	str = new string[count];
	for (unsigned int i = {0}; i < count && !fin.eof(); ++i)
	{
		getline(fin, temp);
		str[i] = temp;
		if (find_ad(str[i],about))
			ads++;
	}
	fin.close();
	delete [] str;
	return ads;
}

bool find_ad(string str, const string ad)
{
	if (str.find(ad,0) == -1)
		return false;
	else 
		return true;
}

void Advert::print(unsigned int i)
{
	cout << "Объявление " << i+1 << ": " << name_ad << endl << "Цена: " << price << " руб." << endl << "Количество фотографий: " << photo << endl << endl;
}

bool operator<(const Advert &v1, const Advert &v2)
{
	return v1.price < v2.price;
}

bool sort_photo(const Advert &v1, const Advert &v2)
{
	return v1.photo < v2.photo;
}

void sort_ad(unsigned int choice, vector<Advert> v)
{
	if (choice == 1)
	{
		for (unsigned int i = {0}; i < ads; ++i)
		{
			v[i].print(i);
		}
	}
	else if (choice == 2)
	{
		std::sort(v.begin(), v.end());
		for (unsigned int i = {0}; i < ads; ++i)
		{
			v[i].print(i);
		}
	}
	else if (choice == 3)
	{
		std::sort(v.begin(), v.end(), sort_photo);
		for (unsigned int i = {0}; i < ads; ++i)
		{
			v[i].print(i);
		}
	}
	else if (choice == 4)
	{
		double g_price = {0.0};
		cout << endl << "Введите максимальную цену: ";
		cin >> g_price;
		std::sort(v.begin(), v.end());
		for (unsigned int i = {0}; i < ads; ++i)
		{
			if (v[i].get_price() < g_price)
			{
				v[i].print(i);
			}
		}
	}
	else if (choice == 5)
	{
		double m_price = {0.0};
		cout << endl << "Введите минимальную цену: ";
		cin >> m_price;
		std::sort(v.begin(), v.end());
		for (unsigned int i = {0}; i < ads; ++i)
		{
			if (v[i].get_price() > m_price)
			{
				v[i].print(i);
			}
		}
	}
	else if (choice == 6)
	{
		string str1;
		cout << endl << "Введите фразу для поиска: ";
		cin.get();
		cin.sync();
		//SetConsoleCP(1251);
		getline(cin,str1);
		//SetConsoleCP(65001);
		cout << endl << "Результаты поиска для " << str1 << ":" << endl;
		unsigned int k = {0};
		for (unsigned int i = {0}; i < ads; ++i)
		{
			string str2 = v[i].get_name();
			if (str2.find(str1,0) != -1)
			{
				v[i].print(i);
				cout << endl;
				k++;
			}
		}
		if (k == 0) 
			cout << endl << "Ничего не нашлось:(" << endl << endl;
	}
	else if (choice == 7)
	{
		char ch[54];
		char c = 'A';
		for (unsigned int i = {0}; i < 27; ++i)
		{
			ch[i] = c++;
		}
		c = 'a';
		for (unsigned int i = {26}; i < 53; ++i)
		{
			ch[i] = c++;
		}
		for (unsigned int i = {0}; i < ads; ++i)
		{
			string str = v[i].get_name();
			for (unsigned int j = {0}; j < 53; ++j)
			{
				if (str.find(ch[j],0) != -1)
				{
					v[i].print(i);
					break;
				}
			}
		}
	}
}
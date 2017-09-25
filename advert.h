#ifndef ADVERT_H_
#define ADVERT_H_
#include <string>
#include <vector>
using std::string;
using std::vector;
const string ad = "<span class=\"attribute-name\">title</span>=\"<a class=\"attribute-value\">Объявление <span class=\"entity\"><span>&amp;</span>laquo;</span>"; 
const string about = "</span><span>&lt;/<span class=\"end-tag\">h3</span>&gt;</span><span> </span><span>&lt;<span class=\"start-tag\">div</span> <span class=\"attribute-name\">class</span>=\"<a class=\"attribute-value\">about</a>\"&gt;</span><span>";
const string rub = "руб.";
//const string ph = "фотографий)"; 
class Advert
{
private:
	string name_ad;
	double price;
	unsigned int photo;
public:
	Advert();
	Advert(unsigned int);
	~Advert();
	double get_price() { return price; }
	string get_name() { return name_ad; }
	unsigned int get_photo() { return photo; }
	void print(unsigned int i);
	friend bool operator<(const Advert &v1, const Advert &v2);
	friend bool sort_photo(const Advert &v1, const Advert &v2);
};
unsigned int get_count_of_ads();
bool find_ad(string, const string);
void sort_ad(unsigned int choice, vector<Advert> v);
#endif
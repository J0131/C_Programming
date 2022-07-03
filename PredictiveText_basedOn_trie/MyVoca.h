#ifndef MY_VOCA_H
#define MY_VOCA_H
#include <iostream>
#include <string>
#include <list>
using namespace std;
enum Word_Type { NOUN, VERB, ADJ, ADV, PREPOS }; // noun, verb, adjective, adverbs, preposition
typedef list<string> List_Str;
typedef list<string>::iterator Lst_Str_Itr;
class MyVoca
{
	friend ostream& operator<<(ostream& fout, MyVoca& mv) // MyVoca 출력연산자
	{
		const string wd_ty[] = { "n", "v", "adj", "adv", "prepos" };
		list<string>::iterator itr;
		fout << mv.keyWord << "(" << wd_ty[mv.type] << "): \n";
		fout << " - thesaurus(";
		for (itr = mv.thesaurus.begin(); itr != mv.thesaurus.end(); ++itr)
		{
			fout << *itr << ", ";
		}
		fout << ")" << endl;
		fout << " - example usage(";
		for (itr = mv.usages.begin(); itr != mv.usages.end(); ++itr)
		{
			fout << *itr << " ";
		}
		fout << ")";
		return fout;
	}
public:
	MyVoca(string kw, Word_Type wt, List_Str thes, List_Str ex_usg) // 생성자
		:keyWord(kw), type(wt), thesaurus(thes), usages(ex_usg) {}
	MyVoca() {} // 기본생성자
	string getKeyWord() { return keyWord; } // key를 반환
	void operator=(const MyVoca& right) // 대입연산자
	{
		keyWord = right.keyWord;
		type = right.type;
		thesaurus = right.thesaurus;
		usages = right.usages;
	}
private:
	string keyWord; // key
	Word_Type type; // 타입
	List_Str thesaurus; // 유의어
	List_Str usages; //
};
#endif



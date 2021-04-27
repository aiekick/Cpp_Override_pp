#include <iostream>
#include <ostream>

class Num
{
public:
	int m_Value = 0;

public:
	Num(int v){m_Value = v;}
	Num& operator++ () // pre inc
	{
		++m_Value;
		printf("++i : %i\n", m_Value);
		return *this;
	}
	Num& operator-- () // pre dec
	{
		--m_Value;
		printf("--i : %i\n", m_Value);
		return *this;
	}
	Num operator++ (int) // post inc
	{
		Num tmp = *this;
		++m_Value;
		printf("i++ : %i\n", m_Value);
		return tmp;
	}
	Num operator-- (int) // post dec
	{
		Num tmp = *this;
		--m_Value;
		printf("i-- : %i\n", m_Value);
		return tmp;
	}
};
Num operator* (Num a, Num b)
{
	printf("%i * %i : %i\n", a.m_Value, b.m_Value, a.m_Value * b.m_Value);
	return Num(a.m_Value * b.m_Value);
}
Num operator+ (Num a, Num b)
{
	printf("%i + %i : %i\n", a.m_Value, b.m_Value, a.m_Value + b.m_Value);
	return Num(a.m_Value + b.m_Value);
}
std::ostream& operator<< (std::ostream& stm, Num v) {stm << v.m_Value; return stm;}

int main ()
{
	// https://stackoverflow.com/questions/949433/why-are-these-constructs-using-pre-and-post-increment-undefined-behavior#30914692
	
	{
		int i = 5;
		i = i++ + ((++i) * (i--));
		// ordre :
		// i-- => 5
		// ++i => 6
		// 5*6 => 30
		// i++ => 6
		// 30 + 6 => 36
		// 36 +1 - 1 => 36
		// msvc : retour 42 !?
		// mingw32 : retour 47 !?
		// clang : retour 54 !?
		std::cout << "int i(5), i = i++ + ++i * i-- => " << i << std::endl;
	}

	{
		Num i = 5;
		i = i++ + ((++i) * (i--));
		// ordre :
		// i-- => 5
		// ++i => 6
		// 5*6 => 30
		// i++ => 6
		// 30 + 6 => 36
		// 36 +1 - 1 => 36
		// msvc : retour 30 !?
		// mingw32 : retour 30 !?
		// clang : retour 54 !?
		std::cout << "Num i(5), i = i++ + ++i * i-- => " << i << std::endl;
	}

	// clang sur win10 donne ca : "via cmake"
	// int i(5), i = i++ + ++i * i-- => 54
	// i++ : 6
	// ++i : 7
	// i-- : 6
	// 7 * 7 : 49
	// 5 + 49 : 54
	// Num i(5), i = i++ + ++i * i-- => 54
	
	// Mingw32 sur win10 donne ca : "via cmake"
	// int i(5), i = i++ + ++i * i-- => 47
	// i-- : 4
	// ++i : 5
	// 5 * 5 : 25
	// i++ : 6
	// 5 + 25 : 30
	// Num i(5), i = i++ + ++i * i-- => 30
	
	// MSVC sur win10 donne ca : "via cmake"
	// int i(5), i = i++ + ++i * i-- => 42
	// i-- : 4
	// ++i : 5
	// 5 * 5 : 25
	// i++ : 6
	// 5 + 25 : 30
	// Num i(5), i = i++ + ++i * i-- => 30
	
	// g++ sur linux donne ca : "g++ main.cpp -o main -v"
	// int i(5), i = i++ + ++i * i-- => 47
	// i-- : 4
	// ++i : 5
	// 5 * 5 : 25
	// i++ : 6
	// 5 + 25 : 30
	// Num i(5), i = i++ + ++i * i-- => 30
	
	// clang sur linux donne ca : "clang++ -std=c++11 -pedantic -Wall main.cpp -o main -v"
	// int i(5), i = i++ + ++i * i-- => 54
	// i++ : 6
	// ++i : 7
	// i-- : 6
	// 7 * 7 : 49
	// 5 + 49 : 54
	// Num i(5), i = i++ + ++i * i-- => 54
	
	// conlusion : mieux vaut eviter les ++ ou -- en post dans des expression composés
	
	return 0;
}

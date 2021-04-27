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
	{
		int i = 5;
		i = i++ + ((++i) * (i--));
		std::cout << "int i(5), i = i++ + ++i * i-- => " << i << std::endl;
	}

	{
		std::cout << "Num i(5), i = i++ + ++i * i-- => " << std::endl;
		Num i = 5;
		i = i++ + ((++i) * (i--));
		std::cout << "result => " << i << std::endl;
	}

	return 0;
}

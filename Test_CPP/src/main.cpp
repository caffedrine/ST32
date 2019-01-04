#include <Derivative.h>
#include <cstdio>


class Test
{
public:
	int x, y;
	
	Test(int a, int b) : x(a), y(b)
	{
	
	}
	
	int Sum()
	{
		return x + y;
	}
};

Test t(12, 34);

int main()
{
	int x = t.x;
	int y = t.y;
	int sum = t.Sum();
	
	if(x+y < 1 && sum < 1)
		return 1;
	
	while(true)
	{
	}
}
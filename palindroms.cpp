#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

bool ispal(int *a, int lpal)
{
	for (int i = 0; i < lpal/2; i++)
	{
		if (a[i] != a[lpal-i-1])
		{
			return false;
		}
	}	
	return true;
}

bool tryoddpal(int *a, int cent, int width, int l)
{
	if (width > cent || width > l-cent-1) return false;
	//Checker
	return ispal(a+cent-width, 1+2*width);	
}

bool tryevenpal(int *a, int cent, int width, int l)
{
	if (width > cent || width > l-cent-1) return false;
	//Checker
	return ispal(a+cent-width, 2*width+2);
}

bool hasOddSubPal(int *a, int rad, int l)
{
	int maxMove = l-2*rad-1;
	for (int move = 0; move <= maxMove; move++)
	{
		if (tryoddpal(a,move+rad, rad, l))
		{
			return true;
		}
	}
	return false;
}

/*
int longestoddpal(int *a, int cent, int l) //Finding possible "Radius"
{
	int max = 0;
	for (int i = 0; tryoddpal(a, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}
*/ 

int longestoddpal(int *a, int l) //Finding possible "Radius" using Dichotomy
{
	int max = (l-1)/2;
	int min = 0;
	int cur = (min+max+1)/2;
	while (min!=max)
	{
		if (hasOddSubPal(a,cur,l))
		{
			min = cur;
			cur = (min+max+1)/2;
		}
		else
		{
			max = cur;
			cur = (min+max)/2;
		}
		if(cur == 0)
		{
			return 0;
		}
	}
	return cur;
}

/*
int longestevenpal(int *a, int cent, int l) //Finding possible "Radius"
{
	int max = std::min(cent, l-cent-1);
	int min = 0;
	int cur = -1;
	while (min!=max && cur != max && cur != min)
	{
		cur = int(std::round((min+max)/2.0));
		if (tryevenpal(a,cent,cur,l))
		{
			min = cur;
		}
		else
		{
			max = cur;
		}
		cur = int(std::round((min+max)/2.0));
		std::cout << "cur/min/max(even)" <<  cur << " " << min << " " << max << " in " << cent << "\n";
	}
	return cur;
}
*/
/*
int findevenpal(int *a, int l) //Finding center
{
	int max = 0;
	int pl = 0;
	for (int i = 0; i < l-1; i++)
	{
		int lp = 2*longestevenpal(a,i,l)+2;
		if (max < lp)
		{
			max = lp;
			pl = i;
		}
	}
	return max;
}

int findoddpal(int *a, int l) //Finding center
{
	int max = 0;
	int pl = 0;
	for (int i = 0; i < l-1; i++)
	{
		int lp = 2*longestoddpal(a, i, l)+1;
		if (max < lp)
		{
			max = lp;
			pl = i;
		}
	}
	return max;
}

int findpal(int *a, int l) //Finding maximum
{
	return std::max(findevenpal(a, l),findoddpal(a,l));
}
*/




bool isdoublepal(int *a, int *b, int lpal) 
{
	for (int i = 0; i < lpal/2; i++)
	{
		if (a[i]+b[i] != a[lpal-i-1]+b[lpal-i-1])
		{
			return false;
		}
	}	
	return true;
}

bool tryodddoublepal(int *a, int *b, int cent, int width, int l)
{
	if (width > cent || width > l-cent-1) return false;
	//Checker
	return isdoublepal(a+cent-width, b+cent-width, 1+2*width);
}

bool tryevendoublepal(int *a, int *b, int cent, int width, int l)
{
	if (width > cent || width > l-cent-1) return false;
	//Checker
	return isdoublepal(a+cent-width, b+cent-width, 2*width+2);
}

int longestodddoublepal(int *a, int *b, int cent, int l) //Finding possible "Radius"
{
	int max = 0;
	for (int i = 0; tryodddoublepal(a, b, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}

int longestEvendoublepal(int *a, int *b, int cent, int l) //Finding possible "Radius"
{
	int max = 0;
	for (int i = 0; tryevendoublepal(a, b, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}

int findodddoublepal(int *a, int *b, int l) //Finding center
{
	int max = 0;
	int pl = 0;
	for (int i = 0; i < l-1; i++)
	{
		int lp = 2*longestodddoublepal(a, b, i, l)+1;
		if (max < lp)
		{
			max = lp;
			pl = i;
		}
	}
	return max;
}
int findEvendoublepal(int *a, int *b, int l) //Finding center
{
	int max = 0;
	int pl = 0;
	for (int i = 0; i < l-1; i++)
	{
		int lp = 2*longestEvendoublepal(a, b, i, l)+2;
		if (max < lp)
		{
			max = lp;
			pl = i;
		}
	}
	return max;
}

int findDoublepal(int *a, int *b, int l) //Finding maximum
{
	return std::max(findEvendoublepal(a,b,l),findodddoublepal(a,b,l));
}

int carmovement(int *a, int *b, int l, int carInter)
{
	int max = 0;
	for (int carPos = 0; carPos < carInter; carPos++)
	{
		max = std::max(max, findDoublepal(a+carPos, b, l));
	}
	return max;
}
int calcCarInterLength(int n, int m)
{
	return abs(n-m);
}

int main()
{
	std::ifstream inp("inputpal.txt");
	int n = 0;
	int m = 0;
	std::cin >> n >> m;
	int a[n] = {};
	int b[m] = {};
	for (int i = 0; i < n; i++)
	{
		std::cin >> a[i];
	}
	for (int i = 0; i < m; i++)
	{
		std::cin >> b[i];
	}
	/*
	if (n > m)
	{
		std::cout << carmovement(a,b,m,calcCarInterLength(n,m)) << "\n";
	}
	else
	{
		std::cout << carmovement(b,a,n,calcCarInterLength(m,n)) << "\n";
	}
	*/
	std::cout << longestoddpal(a,n)*2+1;
	return 0;
}

//???????????????????????? ?????????????????????????????? ???????????????????????? ????????????

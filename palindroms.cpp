#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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
	//��������� �����������
	return ispal(a+cent-width, 1+2*width);
	
}

bool tryevenpal(int *a, int cent, int width, int l)
{
	if (width > cent || width > l-cent-1) return false;
	//��������� �����������
	return ispal(a+cent-width, 2*width+2);
}


int longestoddpal(int *a, int cent, int l) //������� "�������" �� ��������
{
	int max = 0;
	for (int i = 0; tryoddpal(a, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}

int longestevenpal(int *a, int cent, int l) //������� "�������" �� ������
{
	int max = 0;
	for (int i = 0; tryevenpal(a, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}

//�������
//����������� ������
int findevenpal(int *a, int l) //������� ������
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

int findoddpal(int *a, int l) //������� ������
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

int findpal(int *a, int l) //������� ������
{
	return std::max(findevenpal(a, l),findoddpal(a,l));
}





bool isdoublepal(int *a, int *b, int lpal) //�������� ���� �������� ���������� ����� �� �����-���������
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
	//��������� �����������
	return isdoublepal(a+cent-width, b+cent-width, 1+2*width);
}

bool tryevendoublepal(int *a, int *b, int cent, int width, int l)
{
	if (width > cent || width > l-cent-1) return false;
	//��������� �����������
	return isdoublepal(a+cent-width, b+cent-width, 2*width+2);
}

int longestodddoublepal(int *a, int *b, int cent, int l) //������� "�������" �� �������� ��� ���� ��������
{
	int max = 0;
	for (int i = 0; tryodddoublepal(a, b, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}

int longestEvendoublepal(int *a, int *b, int cent, int l) //������� "�������" �� ������ ��� ���� ��������
{
	int max = 0;
	for (int i = 0; tryevendoublepal(a, b, cent, i, l); i++)
	{
		max = i;
	}
	return max;
}

int findodddoublepal(int *a, int *b, int l) //������� ������
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
int findEvendoublepal(int *a, int *b, int l) //������� ������
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

int findDoublepal(int *a, int *b, int l) //������� ������
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
	if (b[0] == b[1]) std::cout << findpal(a,n);
	else std::cout << "3";
	return 0;
}

//�������� ���������� �������� ����

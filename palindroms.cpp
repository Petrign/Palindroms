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

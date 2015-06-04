//Assignment No.: 2

#include <iostream>
#include <cmath>
#include <set>
#include <stdlib.h>
using namespace std;
int main() {

	const int n = 23;
	int total = 1000;
	int cnt = 0;
	float probablity = 364;
	probablity = probablity/365;
	probablity = 1-(pow(probablity,((n*(n-1))/2))); //
	int rand_value = 0;
	cout<<"Expected probability = "<<probablity<<endl;;
	cout<<"--------------------------------"<<endl;
	srand(time(NULL));
	while(total--)
	{
		set<int>s;
		for(int i=0;i<n;i++)
		{
			rand_value = (rand()%365 )+1;
			s.insert(rand_value);
		}
		if(s.size()!=n)
		{
			cnt++;
		}
	}
	total = 1000;
	cout<<"Count		= "<<cnt<<endl;
	cout<<"Total		= "<<total<<endl;
	float ans = (float)cnt/total;
	cout<<"Actual answer   = "<<ans<<endl;
	cout<<"Actual Probability= "<<ans<<endl;
	float error = abs(ans-probablity);
	error = (error/probablity)*100;
	cout<<"Error percentage= "<<error;
	cout<<endl;
	return 0;
}

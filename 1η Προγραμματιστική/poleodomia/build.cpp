#include <iostream>
//#include <stdio.h>
#include <algorithm>
//#include <stdlib.h>  
using namespace std;


struct building{
	long long value;
	int index;
};

bool comp(const building &lhs, const building &rhs) { return lhs.value < rhs.value; }

long long cost(int l, int r, building *array){
	if(r==l) return array[l].value;
	building *max; 
	max = max_element(array+l,array+r+1,comp);
	long long total;
	if(max->index==l) total = cost(max->index+1,r,array)+max->value;
	else if(max->index==r) total = cost(l,max->index-1,array)+max->value;
	else total = min(cost(l,max->index-1,array)+(r-max->index+1)*max->value,cost(max->index+1,r,array)+(max->index-l+1)*max->value);
return total;
}



int main(){
	int N;
	cin >>N;
	building *H;
	H = new building[N];
	for(int i=0; i<N; i++){
		cin >>H[i].value;
		H[i].index=i;
	}
	long long result;
	result = cost(0,N-1,H);
	cout<<result<<endl;
}

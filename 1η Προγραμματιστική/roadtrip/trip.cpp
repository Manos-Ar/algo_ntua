#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

struct Car {
	Car(){};
	Car(int mon, int cap){
		capacity = cap;
		money = mon;
	}
	int capacity, money;
};

struct komvoi{
	int old_d, new_d;
};
bool sortByDistance(const komvoi &lhs, const komvoi &rhs) { return lhs.old_d < rhs.old_d; }

bool sortByCapacity(const Car &lhs, const Car &rhs) { return lhs.capacity < rhs.capacity; }

bool comp(const Car &lhs, const Car &rhs) { return lhs.money < rhs.money; }

//bool min(const Car &lhs, const Car &rhs) { return lhs.money < rhs.money; }

int N,K,D,T,Ts,Cs,Tf,Cf;

double turbo (int distance,int cap){//ποσα στεπ με σπορ
	if(distance*Cs>cap) return -1;
	else if(distance*Cf<=cap) return (double) distance;
	else{
		double spor;
		spor = (double) (cap-(distance*Cs))/(Cf-Cs);
		return spor;
	}
}

double time(int dis,int cap){//χρονος απο σταθμο σε σταθμο
	double time,spor;
	spor=turbo(dis,cap);
	if(spor==-1) return -1;
	time = (double) Tf*spor + (dis-spor)*Ts;
	return time;
}

double total_time (komvoi *dis, int cap){ //συνολικος χρονος για ενα αμαξι
	double total=0;
	double time1;
	for(int i=0; i<K+1; i++){
		time1 = time(dis[i].new_d, cap);
		if(time1==-1) return -1;
		total += time1;
	}
	return total;
}

int car(int l, int r,Car *cars, komvoi *dis){
	int mid,cap;
	double time;
	mid = l+(r-l)/2;
	cap = cars[mid].capacity;
	time = total_time(dis,cap);
	if(r==l){
		if(time==-1 || time>T) return -1;
		else if(time<=T) return mid;
	}
	else if(time==-1 || time>T) mid = car(mid+1,r,cars,dis);
	else if(time<=T) mid = car(l,mid,cars,dis);
	return mid;
}

int main(){
std::ios::sync_with_stdio(false);
cin >> N >> K >> D >> T;

Car* cars = new Car[N];
komvoi *distance = new komvoi[K+1];
int tmp1, tmp2;
for(int i=0; i<N; i++){
	cin >> tmp1>> tmp2;
	cars[i] = Car(tmp1,tmp2);
}

for(int i=0; i<K; i++){
	cin >> tmp1;
	distance[i].old_d=tmp1;
}
cin >>Ts>>Cs>>Tf>>Cf;
sort(distance,distance+K,sortByDistance);
sort(cars, cars+N, sortByCapacity);
distance[K].old_d = D;
distance[0].new_d=distance[0].old_d;
for(int i=1; i<K+1; i++)
	distance[i].new_d = abs(distance[i].old_d-distance[i-1].old_d);

int index;

if(N==1){
	double time = total_time(distance,cars[0].capacity);
	if(time==-1) cout<<"-1"<<endl;
	else cout<<cars[0].money<<endl;
	}
else{
	index = car(0,N-1,cars,distance);
	if(index==-1) cout<<"-1"<<endl;
	else{
		Car *result;
		result = min_element(cars+index,cars+N,comp);
		cout<<result->money<<endl;
	}
  }
}

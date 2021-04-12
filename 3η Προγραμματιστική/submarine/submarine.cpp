#include <stdlib.h>
#include <iostream>
#include <stdbool.h>

using namespace std;

int array[180][180][101];
int N, M, K, X;
struct Pilot{
	Pilot(){
		is = false;
	}
	void set(int e){
		is = true;
		e_x = e/M;
		e_y = e%M;
	}
	bool is;
	int e_x, e_y;
};

int main(){
	std::ios::sync_with_stdio(false);
	
	int s, e, s_x, s_y, e_x, e_y, sum=0;
	cin >> N>> M>> K>> X;
	Pilot *pilot = new Pilot[N*M];
	
	for(int i=0; i<K; i++){
		cin >> s >> e;
		s_x = s/M;
		s_y = s%M;
		pilot[s_x*M + s_y].set(e);
	}

	for(int k=0; k<K+1; k++){
		if(k==0) array[0][0][0] = 1;
		else array[0][0][k] = 0;
	}
	
	for(int x=0; x<X+1; x++){
		for(int n=0; n<N; n++){
			for(int m=0; m<M; m++){
				if(n==0 && m==0) continue;
				if(pilot[n*M + m].is==true && x==0){
					array[n][m][0]=0;
				}
				else if(pilot[n*M + m].is==true && x!=0){
					e_x = pilot[n*M + m].e_x;
					e_y = pilot[n*M + m].e_y;
					array[n][m][x] = array[e_x][e_y][x-1];
				}
				else if(pilot[n*M + m].is == false){
					if(n == 0) array[n][m][x] = (array[n][m-1][x])%1000000103;
					else if (m == 0) array[n][m][x] = (array[n-1][m][x])%1000000103;
					else array[n][m][x] = (array[n-1][m][x] + array[n][m-1][x])%1000000103;
				}
			}
		}
	}
	
	for(int x=0; x<= X; x++)
		sum = (sum+array[N-1][M-1][x])%1000000103;
	cout<<sum<<endl;
}

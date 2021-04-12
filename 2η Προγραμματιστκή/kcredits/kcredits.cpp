#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <stdbool.h>

using namespace std;
int N;

void Increasing (int *ar, int *ls){
  if(N==0) return;
  int *inc1 = new int[N], end, index;
  end=0;
  inc1[0] = ar[0];
  ls[0] = 1;
  for(int i=1; i<N; i++){
    if(inc1[0] > ar[i]){
      inc1[0] = ar[i];
    }
    else if(inc1[end] < ar[i]){
      end++;
      inc1[end] = ar[i];
    }
    else{
      index = lower_bound(inc1, inc1+end+1, ar[i]) - inc1;
      inc1[index] = ar[i];
    }
    ls[i] = end+1;
  }
  free(inc1);
  return;
}

bool comp(const int &lhs, const int &rhs) { return lhs > rhs; }

void Decreasing (int *ar, int *ls){
  if(N==0) return;
  int *dec1 = new int[N], end, index;
  end=0;
  dec1[0] = ar[N-1];
  ls[N-1] = 1;
  for(int i=N-2; i>=0; i--){
    if(dec1[0] < ar[i]){
      dec1[0] = ar[i];
    }
    else if(dec1[end] > ar[i]){
      end++;
      dec1[end] = ar[i];
    }
    else{
      index = lower_bound(dec1, dec1+end+1, ar[i], comp)-dec1;
      dec1[index] = ar[i];
    }
    ls[i] = end+1;
  }
  free(dec1);
  return;
}

int main(){
std::ios::sync_with_stdio(false);
  int K;
  cin >> N>> K;
  int social[N];
  for(int i=0; i<N; i++){
    cin >>social[i];
  }
  int lis[2][N], maxv;
	Increasing(social, lis[0]);
	if(K==1){
    Decreasing(social, lis[1]);
    
    maxv=lis[0][N-1];
    for(int i=0; i<=N-2; i++){
      maxv = max(maxv, lis[0][i]+lis[1][i+1]);
    }
    cout<<maxv<<endl;
	}
  else{
    int row_k, row_k_1;
    lis[1][0]=1;
    row_k_1 = 0;
    row_k = 1;
    for(int k=1; k<=K; k++){
      if(k%2==0){
        row_k_1 = 1;
        row_k = 0;
      }
      else{
      	row_k_1 = 0;
      	row_k = 1;
      }
      for(int i=1; i<N; i++){
        maxv=0;
        for(int j=0; j<i; j++){
          if(social[i]>social[j]) maxv = max(maxv,lis[row_k][j]);
          else maxv = max(maxv,lis[row_k_1][j]);
        }
       lis[row_k][i]=maxv+1;
       }
     }
    maxv=0;
    for(int i=0; i<N; i++){
      maxv = max(maxv, lis[row_k][i]);
    }
    cout<<maxv<<endl;
  }
}



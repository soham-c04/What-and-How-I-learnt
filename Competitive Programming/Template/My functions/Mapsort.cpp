#include<bits/stdc++.h>
using namespace std;
void merge(int ky[],int val[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int L[n1], R[n2],kyL[n1],kyR[n2];
  for (i = 0; i < n1; i++){  
    L[i] = val[l + i];
    kyL[i] = ky[l + i];
}
  for (j = 0; j < n2; j++){
    R[j] = val[m + 1 + j];
    kyR[j] = ky[m + 1 + j];
}
  i = 0; 
  j = 0;
  k = l; 
while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      val[k] = L[i];
      ky[k]=kyL[i];
      i++;
    }
    else {
      val[k] = R[j];
      ky[k]=kyR[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    val[k] = L[i];
    ky[k]=kyL[i];
    i++; k++;
  }
  while (j < n2) {
    val[k] = R[j];
    ky[k]=kyR[j];
    j++; k++;
  }
}
void mapsort(int ky[],int val[], int l, int r)
{
  if (l < r) {
    int m = l + (r - l) / 2;
    mapsort(ky, val, l, m);
    mapsort(ky, val, m + 1, r);
    merge(ky, val, l, m, r);
  }
}
void printarray(int A[], int size)
{
  int i;
  for (i = 0; i < size; i++)
	cout << A[i] << " ";
  cout << "\n";
}

int main(){
	int k[6];
	for(int i=0;i<6;i++){
		k[i]=i+1;
	}
	int a[6]={5,4,3,2,7,1};
	mapsort(k,a,0,5);
	printarray(k,6);
	printarray(a,6);
	return 0;
}

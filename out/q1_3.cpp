#include <bits/stdc++.h>
using namespace std;


int main(){
	int n=10;
	int arr1[n]={1,2,3,4,5,6,7,8,9,10};
	int arr2[n] ={11,12,13,14,15,16,17,18,19,20};

	for(int i=0;i<n;i++){
		printf("%d, ",arr1[i]);
	}
	printf("\n");
	for(int i=0;i<n;i++){
		printf("%d, ",arr2[i]);
	}
	printf("\n");
	for(int i=0;i<n;i++){
		printf("%d, ",arr1[i]+arr2[i]);
	}
	return 0;

}


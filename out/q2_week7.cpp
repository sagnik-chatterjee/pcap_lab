#include <bits/stdc++.h>

using namespace std;


int main(){
	int n =10;
	int *arr= (int*) malloc(n*sizeof(int));
	for(int i=0;i<n;i++){
		arr[i] = rand()%50;
	}
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	//sorteing
	printf("\n"); 
	sort(arr,arr+n);
	for(int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	return 0;
}

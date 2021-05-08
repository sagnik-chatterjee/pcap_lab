#include <bits/stdc++.h>

using namespace std;


int main(){
	int n =10;
	int a[n]= {13,10,4,7,1,4,8,0,5,6};
	for(int i=0;i<n;i++){
		printf("%d, ",a[i]);
	}
	sort(a,a+n);
	printf("\n");
	for(int i=0;i<n;i++){
		printf("%d, ",a[i]);
	}
	return 0;
	
}

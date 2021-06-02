#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<cstdio>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

__global__ void findWordCount(char* str, char* word, int* count, int strl, int wordl)
{
	//Every thread skips the previous words and check for only its words
	int id = threadIdx.x;
	int c = 0;
	int i = 0;
	for (i = 0; i < strl; i++)
	{
		if (str[i] == ' ')
			c++;
		if (c == id)
		{
			break;
		}
	}
	char* w = (char*)malloc(sizeof(char) * 10);
	int j = 0;
	if (i != 0)
		i = i + 1;
	for (;i < strl;i++)
	{
		if (str[i] == ' ')
			break;
		w[j++] = str[i];
	}
	w[j] = '\0';
	printf("Thread ID-%d Checking Word-%s\n", id, w);
	int flag = 0;
	for (i = 0;i < j;i++)
		if (word[i] != w[i])
		{
			flag = 1;
			break;
		}
	if (flag == 0)
		atomicAdd(count, 1);

}

int main()
{
	char* str = (char*)malloc(sizeof(char) * 100);
	char* word = (char*)malloc(sizeof(char) * 10);
	str = "Hello my name is hvr i study in manipal in manipal hello";
	word = "manipal";
	int* wordCount = (int*)malloc(sizeof(int));
	*wordCount = 0;
	printf("Given String: %s\nGiven Word: %s\n", str, word);
	// Count the number of words in the string
	int count = 1; //For the last word
	for (int i = 0;i < strlen(str);i++)
	{
		if (str[i] == ' ')
			count++;
	}
	char* d_str, * d_word;
	int* d_wordCount;
	cudaMalloc((void**)&d_str, sizeof(char) * 100);
	cudaMalloc((void**)&d_word, sizeof(char) * 10);
	cudaMalloc((void**)&d_wordCount, sizeof(int));
	cudaMemcpy(d_str, str, sizeof(char) * 100, cudaMemcpyHostToDevice);
	cudaMemcpy(d_word, word, sizeof(char) * 10, cudaMemcpyHostToDevice);
	cudaMemcpy(d_wordCount, wordCount, sizeof(int), cudaMemcpyHostToDevice);
	dim3 gridDim(1, 1, 1);
	dim3 blockDim(count, 1, 1);
	findWordCount << < 1, count >> > (d_str, d_word, d_wordCount, strlen(str), strlen(word));
	cudaMemcpy(wordCount, d_wordCount, sizeof(int), cudaMemcpyDeviceToHost);
	printf("Total Occurences: %d\n", *wordCount);
	cudaFree(d_word);
	cudaFree(d_wordCount);
	cudaFree(d_str);
	return 0;
}
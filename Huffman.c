#include <string.h>

#include "Huffman.h"

void CreateHuffmanTree(HuffmanNode *huffmantree , int kinds , int num)
{
	int i;
	int s1 , s2;
	for (i = kinds; i < num; ++i)
	{

		Select(huffmantree , i , &s1 , &s2);

		huffmantree[s1].parent = huffmantree[s2].parent = i;
		huffmantree[i].leftchild = s1;
		huffmantree[i].rightchild = s2;
		huffmantree[i].count = huffmantree[s1].count + huffmantree[s2].count;
	}
}

void HuffmanCode(HuffmanNode *huffmantree , int kinds)
{
	int i;
	int cur , next , index;
	char codetemp[256];

	for (i = 0; i < 256; ++i)
	{
		codetemp[i] = '\0';
	}

	for (i = 0; i < kinds; ++i)
	{
		index = 254;
		for (cur = i , next = huffmantree[i].parent; next != 0; cur = next , next = huffmantree[next].parent)
		{
			if (huffmantree[next].leftchild == cur)
			{
				codetemp[--index] = '0';
			}
			else
			{
				codetemp[--index] = '1';
			}
		}
		strcpy(huffmantree[i].code , &codetemp[index]);
	}
}

void Select(HuffmanNode *huffmantree , int n , int *s1 , int *s2)
{
	int i;
	int min = huffmantree[0].count;
	for (i = 0; i < n; ++i)
	{
		if (min < huffmantree[i].count)
		{
			min = huffmantree[i].count;
		}
	}
	++min;
	for (i = 0; i < n; ++i)
	{
		if (0 == huffmantree[i].parent && huffmantree[i].count < min)
		{
			min = huffmantree[i].count;
			*s1 = i;
		}
	}
	huffmantree[*s1].parent = 1;

	min = huffmantree[0].count;
	for (i = 0; i < n; ++i)
	{
		if (min < huffmantree[i].count)
		{
			min = huffmantree[i].count;
		}
	}
	++min;
	for (i = 0; i < n; ++i)
	{
		if (0 == huffmantree[i].parent && huffmantree[i].count < min)
		{
			min = huffmantree[i].count;
			*s2 = i;
		}
	}
}

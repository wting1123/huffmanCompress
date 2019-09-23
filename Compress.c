#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Compress.h"

int Compress(char *filename , char *extractfilename)
{
	int i , j;
	int kinds = 0;
	int filelength = 0;
	unsigned char c;

	FILE *fp , *efp;

	Node node[256] , temp;

	int num;

	HuffmanNode *huffmantree;

	char codebuf[256];
	int codelength;

	//初始化字符编码域,统计结点
	///////////////////////////////////
	for (i = 0; i < 256; ++i)
	{
		codebuf[i] = '\0';
	}
	for (i = 0; i < 256; ++i)
	{
		node[i].ch = (unsigned char)i;
		node[i].count = 0;
	}
	///////////////////////////////////


    //统计文件长度,字符频率
    ///////////////////////////////////
 	fp = fopen (filename , "rb");
	if (fp == NULL)
	{
   		return -1;
	}
	fread(&c , sizeof(unsigned char) , 1 , fp);
	while (!feof(fp))
	{
		++node[c].count;
		++filelength;
		fread(&c , sizeof(unsigned char) , 1 , fp);
	}
	fclose(fp);
	///////////////////////////////////


	//统计字符种类
	///////////////////////////////////
	for (i = 0; i < 255; ++i)
	{
		for (j = i + 1; j < 256; ++j)
		{
			if (node[i].count < node[j].count)
			{
				temp = node[i];
				node[i] = node[j];
				node[j] = temp;
			}
		}
	}
	for (i = 0; i < 256; ++i)
	{
		if (node[i].count)
		{
			++kinds;
		}
	}
	///////////////////////////////////

    if (1 == kinds)
    {
    	//特殊情况(文件只含一种字符)
    	///////////////////////////////////
    	efp = fopen(extractfilename , "wb");
		fwrite (&kinds , sizeof(int) , 1 , efp);
		fwrite (&node[0].ch , sizeof(unsigned char) , 1 , efp);
		fwrite (&node[0].count , sizeof(int) , 1 , efp);
		fclose (efp);
		///////////////////////////////////
    }
    else
    {
    	//初始化顺序存储的哈夫曼结点
    	///////////////////////////////////
    	num = 2 * kinds - 1;
        huffmantree = (HuffmanNode*)malloc(num * sizeof(HuffmanNode));
        for (i = 0; i < kinds; ++i)
        {
        	huffmantree[i].ch = node[i].ch;
        	huffmantree[i].count = node[i].count;
        	huffmantree[i].parent = 0;
        	huffmantree[i].leftchild = huffmantree[i].rightchild = -1;
        }
        for ( ;i < num; ++i)
		{
			huffmantree[i].parent = 0;
			huffmantree[i].leftchild = huffmantree[i].rightchild = -1;
		}
		///////////////////////////////////


		//创建哈夫曼树
		///////////////////////////////////
		CreateHuffmanTree(huffmantree , kinds , num);
		///////////////////////////////////


		//生成哈夫曼编码
		///////////////////////////////////
		HuffmanCode(huffmantree , kinds);
		///////////////////////////////////


		//将字符种类,字符,频率,文件长度依次写入压缩文件前部分
		///////////////////////////////////
		efp = fopen (extractfilename , "wb");
		fwrite (&kinds , sizeof(int) , 1 , efp);
		for (i = 0; i < kinds; ++i)
		{
			fwrite (&huffmantree[i].ch , sizeof(unsigned char) , 1 , efp);
			fwrite (&huffmantree[i].count , sizeof(int) , 1 , efp);
		}
		fwrite (&filelength , sizeof(int) , 1 , efp);
		///////////////////////////////////


		//将字符编码写入压缩文件
		///////////////////////////////////
		fp = fopen (filename , "rb");
		fread (&c , sizeof(unsigned char) , 1 , fp);
		while (!feof(fp))
		{
			for (i = 0; i < kinds; ++i)
			{
				if (c == huffmantree[i].ch)
				{
					strcat(codebuf , huffmantree[i].code);
				}
			}

			while (strlen(codebuf) >= 8)
			{
				c = '\0';
				for (i = 0; i < 8; ++i)
				{
					c <<= 1;
					if ('1' == codebuf[i])
					{
						c |= 1;
					}
				}
				fwrite (&c , sizeof(unsigned char) , 1 , efp);
				strcpy(codebuf , codebuf + 8);
			}
			fread(&c , sizeof(unsigned char) , 1 , fp);
		}

		codelength = strlen(codebuf);
		if (codelength > 0)
		{
			c = '\0';
			for (i = 0; i < codelength; ++i)
			{
				c <<= 1;
				if ('1' == codebuf[i])
				{
					c |= 1;
				}
			}
			c <<= 8 - codelength;
			fwrite (&c , sizeof(unsigned char) , 1 , efp);
		}
		///////////////////////////////////

		fclose (fp);
		fclose (efp);
    }

	free (huffmantree);
}




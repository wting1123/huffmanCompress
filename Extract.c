#include <stdio.h>
#include <stdlib.h>

#include "Extract.h"

int Extract(char *extractfilename , char *filename)
{
    int i;
	int filelength;
	int writenlength = 0;
	int kinds;
	int num;
	HuffmanNode *huffmantree;

	FILE *fp , *efp;

	unsigned char c;
	int root;

	//从压缩文件中获取文件字符种类
	///////////////////////////////////
	efp = fopen (extractfilename, "rb");
	if (efp == NULL)
	{
		return -1;
	}
	fread (&kinds , sizeof(int) , 1 , efp);
	///////////////////////////////////

	if (1 == kinds)
	{
		//特殊情况
		///////////////////////////////////
		fread (&c , sizeof(unsigned char) , 1 , efp);
		fread (&filelength , sizeof(int) , 1 , efp);//此时权就是文件长度
		fp = fopen (filename , "wb");
		while (--filelength)
		{
			fwrite (&c , sizeof(unsigned char) , 1 , fp);
		}
		fclose (efp);
		fclose (fp);
		///////////////////////////////////
	}
	else
	{
		//将压缩文件字符,频率存入哈夫曼结点
		///////////////////////////////////
		num = 2 * kinds - 1;
		huffmantree = (HuffmanNode*)malloc(num * sizeof(HuffmanNode));
		for (i = 0; i < kinds; ++i)
		{
			fread (&huffmantree[i].ch , sizeof(unsigned char) , 1 , efp);
			fread (&huffmantree[i].count , sizeof(int) , 1 , efp);
			huffmantree[i].parent = 0;
			huffmantree[i].leftchild = huffmantree[i].rightchild = -1;
		}
		for( ; i < num; ++i)
		{
			huffmantree[i].parent = 0;
			huffmantree[i].leftchild = huffmantree[i].rightchild = -1;
		}
		///////////////////////////////////


		//还原哈夫曼树
		///////////////////////////////////
		CreateHuffmanTree(huffmantree , kinds , num);
		///////////////////////////////////

		fread (&filelength , sizeof(int) , 1 , efp);

		fp = fopen (filename , "wb");
		root = num - 1;
		while(1)
		{
			fread (&c , sizeof(unsigned char) , 1 , efp);

			for(i = 0; i < 8; ++i)
			{
				if(c & 128)
				{
					root = huffmantree[root].rightchild;
				}
				else
				{
					root = huffmantree[root].leftchild;
				}

				if(root < kinds)
				{
					fwrite (&huffmantree[root].ch , sizeof(unsigned char) , 1 , fp);
					++writenlength;
					if (writenlength == filelength)
					{
						 break;
					}
					root = num - 1;
				}
				c <<= 1;
			}
			if (writenlength == filelength)
			{
				 break;
			}
		}

		fclose(efp);
		fclose(fp);

		free(huffmantree);
	}
}

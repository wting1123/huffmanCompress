#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "Compress.h"
#include "Extract.h"

int main() 
{
	int flag;
	char c;
	char filename[100] , extractfilename[100];
	clock_t t1 , t2; 
	
	while (1)
	{
   		printf ("\t _______________________________________________\n");
   		printf ("\t|                                               |\n");   
   		printf ("\t| C-压缩文件                                    |\n");   
   		printf ("\t| E-解压缩                                      |\n");   
   		printf ("\t| Q-退出                                        |\n");
   		printf ("\t|_______________________________________________|\n");
   		printf ("\n");
	   	do
	   	{
	    	printf ("\n\t请选择功能:"); 
	    	scanf (" %c", &c);
	    	c = toupper(c);
	    	putchar('\n');
	    	if ('C' != c && 'E' != c && 'Q' != c)
	    	{ 
	     		printf ("\t选项错误,请重新输入!\n");
	    	}
	   	}
		while ('C' != c && 'E' != c && 'Q' != c); 
		
		if ('C' == c)
		{
			printf ("\t请您输入需要压缩的文件:");
			fflush(stdin);
 	 	    gets (filename);
	 	    putchar('\n');
			 
			printf ("\t请您输入压缩后的文件:");
			fflush(stdin);
	   	    gets (extractfilename);
	   	    putchar('\n');
	   	    
			t1 = clock();
			printf ("\t正在帮您压缩...");
			flag = Compress(filename , extractfilename);
			t2 = clock();
			putchar('\n');
			
		   	if (-1 == flag)
		   	{
		   		printf ("\t文件打开失败!\n"); 
	   			exit(1); 
		   	}
		   	else
		   	{
		   		printf("\n\t压缩操作完成!\n\n");
		   	}
			
			printf("\t压缩耗费时间: %g秒\n" , (t2 - t1) / 1000.0);
		}
	   	else if ('E' == c)
		{ 
			printf ("\t请您输入需要解压的文件:");
			fflush(stdin);
	   		gets (extractfilename);
	   		putchar('\n');
	   	    
	   	    printf ("\t请您输入解压缩后的文件:");
			fflush(stdin);
	 	    gets (filename);
	 	    putchar('\n');
			
			t1 = clock();
			printf ("\t正在帮您解压缩...");
			flag = Extract(extractfilename , filename);
			t2 = clock();
			putchar('\n');
			
		   	if (-1 == flag)
		   	{
		   		printf ("\t文件打开失败!\n"); 
	   			exit(1); 
		   	}
		   	else
		   	{
		   		printf("\n\t解压缩操作完成!\n\n");
		   	}
			
			printf("\t解压缩耗费时间: %g秒\n" , (t2 - t1) / 1000.0);
		}
	   	else 
	   	{
	    	printf ("\t再见!\n"); 
	    	exit(0);
	   	}  
	}
	return 0;
}

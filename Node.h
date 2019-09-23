#ifndef _NODE_H_
#define _NODE_H_

typedef struct _NODE_
{
	unsigned char ch;   //×Ö·û 
	int count;          //È¨ 
}Node;

typedef struct _HUFFMANNODE_
{
	unsigned char ch;   //×Ö·û 
	int count;          //È¨ 
	char code[256];     //¹ş·òÂü±àÂë 
    int parent , leftchild , rightchild;
}HuffmanNode;

#endif

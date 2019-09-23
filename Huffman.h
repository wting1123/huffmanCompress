#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "Node.h"

void CreateHuffmanTree(HuffmanNode *huffmantree , int kinds , int num);

void HuffmanCode(HuffmanNode *huffmantree , int kinds);

void Select(HuffmanNode *huffmantree , int n , int *s1 , int *s2);

#endif

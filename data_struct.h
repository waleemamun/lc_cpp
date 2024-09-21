/*
 * data_struct.h
 *
 *  Created on: May 29, 2017
 *      Author: wmamun
 */

#ifndef DATA_STRUCT_H_
#define DATA_STRUCT_H_
#include <stdio.h>


typedef struct List_{
	uint32_t data;
	struct List_ *next;
} List;

typedef struct Tree_ {
	uint32_t data;
	struct Tree_ *left;
	struct Tree_ *right;
} Tree;

typedef struct Stack_ {
	int data;
	int min;
} Stack;

typedef struct Graph_ {
	int node;
	struct Graph_ *adj_list;
} Graph;
void init_graph(int num_nodes,int num_edges);
void print_graph_adj_list(int num_nodes);
void insert_at_head(List **head,uint32_t data) ;
void print_list(List **head);

List* find_entry(List **head,uint32_t data) ;

void insert_into_sorted_list(List **head, uint32_t data);

int
delete_from_list_unsorted(List **head, uint32_t data);

List* kth_to_last (List **head ,int k);
void
partition_list (List **head, int val);
int
list_palindrome(List **head);

Tree*
create_bstree (int arr[],int p, int q);

void
in_order_traversal (Tree *node);

void
pre_order_traversal (Tree *node);

void
post_order_traversal (Tree *node);
void compressed_v2(char *str);

int is_unique (char *str);
int is_permutation(char *str1, char *str2);
int is_palindrom_bit(char *str);
int one_edit (char *str1, char *str2);
void compressed(char *str) ;
void rotate90 (int a[][4],int size) ;
void
max_diff(int arr[], int size);
int lengthOfLongestSubstring(char* s);
int tree_height(Tree *node) ;
int lengthOfLongestSubstring(char* s);

#endif /* DATA_STRUCT_H_ */

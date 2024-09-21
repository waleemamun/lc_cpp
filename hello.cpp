/*
 * hello.c
 *
 *  Created on: Mar 29, 2017
 *      Author: wmamun
 */
#include <stdio.h>
#include <stdint.h>
#include "data_struct.h"
#include <string.h>
#include <stdlib.h>
#define MAX_ENTRY 10

int unsort_arr[MAX_ENTRY]  = {10,5,9,2,4,6,7,1,3,8};
int un_heap_arr[MAX_ENTRY+1] = {-1,16,4,10,14,7,9,3,2,8,1};
List *head_ptr;
Tree *root_ptr;
int freq_count[11]; // for 0...11
int lin_unsort_arr[MAX_ENTRY+1]  = {-1,9,5,9,7,4,6,3,1,3,3};
int lin_sort_arr[MAX_ENTRY+1] = {-1};

#define swap(a,b)  \
	(a) = (a)^(b)  \
    (b) = (a)^(b)  \
    (a) = (a)^(b)
/*
 * order of N sort and only applicable if the Max number is known
 * requires an Array of size N so for example if the Max 100000000
 * we would need an array of size 100000000
 * */
void count_sort (int arr[],int size){

	int i    = 0;
    // init the freq array
	for (i = 0;i < 11; i++) {
		freq_count[i] = 0;
	}
	// count frequency
	for (i = 1;i < size; i++) {
		freq_count[arr[i]]++;
	}
	// cumalate freq so that we know for each value i where it
	// needs to be inserted in the sorted array
	for (i = 1; i < 11; i++) {
		freq_count[i] = freq_count[i-1] + freq_count[i];
	}
	// insert the item in proper position in sorted array using the position from
	// freq_count array. We start from array size and decrement cause we want to keep the
	// order of the element in the array meaning same value array will appear in same order
	// this property of maintaining the order in this sorting is also called stable sort
	for (i = size-1; i >= 1; i--) {
		lin_sort_arr[freq_count[arr[i]]] = arr[i];
		freq_count[arr[i]]--;
	}

}


void print_arr (int arr[],int size) {
	int i=0;
	for (i = 0; i < size; i++) {
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void bub_sort (int arr[],int size) {
	int i   = 0;
	int j   = 0;
	int tmp = 0;
    // move the smallest element to a[i] position
	// at each iteration of the outer loop
	for (i = 0; i < size; i++) {
		for (j = i+1; j < size ;j++) {
			if (arr[i] >= arr[j] ) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}

}

void insert_sort (int arr[],int size) {
	int i   = 0;
	int j   = 0;
	int tmp = 0;
	// we start from 1 so that the initial boundary is (0,1)
	// and everything will be sorted between them, so for each ith postion
	// 0 to i-1 pos are sorted and we insert the ith element in right position and get
	// 0 to i sorted elems
	for (i = 1; i < size; i++) {
		tmp = arr[i];
		for (j = i; j >= 0; j--){
			// the array at each iteration is sorted between the position 0 and j-1 this statement
			// is the most important aspect of this algo and target is to fit 'tmp' in the correct position in (0,j)
			// we move every element which is greater than tmp to the right and find the position
			// to insert tmp at correct position.In each iteration j denotes the postion to enter tmp or the value in arr[j-1].
			if ( j && (tmp <= arr[j-1])) {
				arr[j] = arr[j-1];
			} else{
				break;
			}
		}
		arr[j] = tmp;
	}
}
// merge sort implements a divide and conquer algo its divides up the array
//in small sub arrays (size of 2) up to when no more division can happen and then start merging those divided subarrays
// but during merge each element of the array is compared and stored in a sorted order in the merged array
// Here p ,q and r are indices in the array, specially r is the last index in the array
void merge_arr (int arr[], int p,int q,int r) {

	int left[MAX_ENTRY];
	int right[MAX_ENTRY];
	int i         = 0;
	int j         = 0;
	int k         = 0;
	int len_left  = 0;
	int len_right = 0;

#define INFINITY 10000
	for (i = 0; i<MAX_ENTRY; i++) {
		left[i] = right[i] = INFINITY;
	}

	for (i = p, j = 0 ; i <= q; i++) {
		left[j++] = arr[i];
	}
	len_left = j;

	for (i = q+1, j = 0; i<=r; i++ ) {
		right[j++] = arr[i];
	}
	len_right = j;

	j = k = 0;
	// we are filling up the merged array pos p to r in a sorted order
	for (i = p; i <= r; i++) {
		if (left[j] <= right[k] && j < len_left) {
			arr[i] = left[j++];
		} else {
			if (k < len_right)
				arr[i] = right[k++];
		}
	}
}
// Here p  is the starting index and r is the end index not size
void merge_sort (int arr[],int p,int r) {
	int q = 0;
	if ( p < r) {
		q = (p+r)/2;
		printf ("%u %u : %u %u\n",p,q,q+1,r);
		// divide the array in to two halves arr[p...r] and arr[q+1...r]
		merge_sort(arr,p,q);
		merge_sort(arr,q+1,r);
		// merge the dived sorted array to bigger arr[p...q] sorted array
		merge_arr(arr,p,q,r);
	}

}

#define left_child(i)   ((i) << 1)
#define right_child(i)  (((i) << 1) + 1)
#define parent(i) ((i) >> 1)
// assunption is a heap property exist in the array but only A[i]
// position violates the heap so we have to push A[i] down to its
// proper position
void max_heapify (int arr[],int i) {

	uint32_t largest = i; // init largest to i so that at recursion break i == largest condition is met
	uint32_t left    = left_child(i);
	uint32_t right   = right_child(i);
	uint32_t temp    = 0;

	if (left < MAX_ENTRY && arr[i] < arr[left]) {
		largest = left_child(i);
	}
	if (right < MAX_ENTRY && arr[largest] < arr[right]) {
		largest = right_child(i);
	}
	if (i != largest) {
		temp = arr[largest];
		arr[largest] = arr [i];
		arr[i] = temp;
		max_heapify(arr, largest);
	}
}
// in the sub array A(n/2+1 ....n) are all leaves of the tree so each is a 1 -element heap.
// The function build_max_heap will work on the remaining node and calls max_heapify
// to build the heap
void build_max_heap(int arr[],int size) {

	int i = 0;
	for (i = size/2; i >= 1 ; i--) {
		max_heapify(arr,i);
	}
}
void heap_sort(int arr[], int size) {

	int i   = size;
	int tmp = 0;

	build_max_heap(arr,size);
	for (i = size; i>=2 ; i--) { // we use i>=2 cause when i == 2 the heapsize is 2 and A[1..2] will besorte from the call of heapify
		tmp = arr[1];
		arr[1] = arr[i];
		arr[i] = tmp;
		max_heapify(arr,1);
	}
}
int partition (int arr[],int p,int r) {

	int x = arr[r];
	int j = p;
	int i = p-1;
	int tmp;
    // we move all element <= x to the left side and
	// all elem > x to the right
	// Note: we have to loop from p to r-1,
	// r-1 is the element before r and we have to loop to r-1
	// so the loop breaking condition is "j <= r-1"

	for (j = p;j <= r-1;j++) {
		if(arr[j] <= x) {
			i++;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	// now all element <=x is on left and >=x is on right
	// finally move x to its right position and return the position to qsort
	i++;
	tmp = arr[i];
	arr[i] = arr[r];
	arr[r] = tmp;
	return i;


}
void q_sort (int arr[],int p,int r) {
    // get q value from partition after partition all value <= q will be on left of q
	// and all val > q will be on right of q, so q is actually in the desired position
	// in the sorted array
	int q = 0;
	// if p >= r we have the minimal array which is sorted by default
	// this could be use as the recursion termination condition
	if (p < r) {
		q = partition(arr,p,r);
		// now we recursively sort the subarr[p ,q-1] and arr[q+1,r]
		// note a[q] is in right position
		q_sort(arr,p,q-1);
		q_sort(arr,q+1,r);
	}
}

int main (){

	//printf("Before \n");
	//print_arr(unsort_arr, MAX_ENTRY);
	//bub_sort(unsort_arr, MAX_ENTRY);

	//insert_sort(unsort_arr, MAX_ENTRY);
	//printf("After Insert Sort\n");
	//merge_sort(unsort_arr, 0,9);
	//build_max_heap(un_heap_arr , MAX_ENTRY);
	//printf("After build heap\n");
	//print_arr(un_heap_arr, MAX_ENTRY+1);
#define LIST_TEST 1
#define QSORT_TEST 2
#define CSORT_TEST 3
#define CREATE_BST_TEST 4
#define CREATE_ARR_TEST 5
#define CREATE_GRPH_TEST 6
	uint32_t data,opt;

	opt = CREATE_ARR_TEST;
	switch (opt) {

	case LIST_TEST:
	{
		printf("List test\n");

	    for (int i = 1 ; i<=2; i++){
			//insert_at_head(&head_ptr,data);
	    	scanf("%u",&data);
			insert_at_head(&head_ptr,data);
		}
		print_list(&head_ptr);
		/*printf ("Search ?\n");
		data = 5;
		//scanf("%u",&data);
		elem = find_entry(&head_ptr, data);

		if (elem)
			printf("Found %u\n",elem->data);
		delete_from_list_unsorted(&head_ptr, data);
		print_list(&head_ptr);
		printf("Exiting test code\n");*/

        if (list_palindrome(&head_ptr)) {
        	printf("Yes\n");
        } else {
        	printf("NO\n");
        }

		break;
	}
	case QSORT_TEST:
	{
		printf("QSort test\n");
		printf("Before \n");
		print_arr(unsort_arr, MAX_ENTRY);
		q_sort(unsort_arr,0,MAX_ENTRY-1);
		printf("After \n");
		print_arr(unsort_arr, MAX_ENTRY);
		break;
	}
	case CSORT_TEST:
	{
		printf("CSort test\n");
		printf("Before \n");
		print_arr(lin_unsort_arr, MAX_ENTRY+1);
		count_sort(lin_unsort_arr,11);
		printf("After \n");
		print_arr(lin_sort_arr, MAX_ENTRY+1);
		break;
	}
	case CREATE_BST_TEST:
	{
		printf("Create BST test\n");
		q_sort(unsort_arr,0,MAX_ENTRY-1);
		printf("Sorted Array \n");
		print_arr(unsort_arr, MAX_ENTRY);

		root_ptr = create_bstree(unsort_arr,0,MAX_ENTRY-1);
		if (root_ptr) {
			printf("root %u\n",root_ptr->data);
			printf("InOrder : ");
			in_order_traversal(root_ptr);
			printf("\n");

			printf("PreOrder : ");
			pre_order_traversal(root_ptr);
			printf("\n");

			printf("PostOrder : ");
			post_order_traversal(root_ptr);
			printf("\n");
		}
		int h = tree_height(root_ptr);
		printf("Tree height %d\n",h);
		break;
	}
	case CREATE_ARR_TEST:
	{
		printf(" here\n");
		char str[100];
		strcpy(str,"bbbbb");
        int len = lengthOfLongestSubstring(str);
        printf(" len = %d \n",len);

		break;

	}
	case CREATE_GRPH_TEST:
	{
		int num_nodes = 5;
		int num_edges = 5;

		init_graph(num_nodes,num_edges);
		print_graph_adj_list(num_nodes);
		break;
	}

	}
	return 0;
}

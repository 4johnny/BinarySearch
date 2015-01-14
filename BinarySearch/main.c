//
//  main.c
//  BinarySearch
//
//  Created by Johnny on 2015-01-13.
//  Copyright (c) 2015 Empath Solutions. All rights reserved.
//

#include <stdio.h>

typedef struct Range {
	int index;
	int count;
} Range;

void initRange(Range *range);

int indexOfTargetInSortedList(int sortedList[], int target, int min, int max);
void rangeOfTargetInSortedList(Range *range, int sortedList[], int target, int min, int max);


int main(int argc, const char * argv[]) {
	
	int target = 13;

	int sortedList[] = {0, 1, 2, 3, 5, 7, 13, 21, 34, 55};
	int index = indexOfTargetInSortedList(sortedList, target, 0, sizeof(sortedList)/sizeof(int) - 1);
	printf("Index: %d\n", index);
	
	target = 21;
	int sortedListWithDuplicates[] = {0, 1, 2, 3, 5, 7, 13, 21, 21, 21, 34, 55};
	Range range; initRange(&range);
	rangeOfTargetInSortedList(&range, sortedListWithDuplicates, target, 0, sizeof(sortedListWithDuplicates)/sizeof(int) - 1);
	printf("Range: {index: %d, count: %d}\n", range.index, range.count);
	
	return 0;
}


void initRange(Range *range) {
	range->index = -1;
	range->count = 0;
}

int indexOfTargetInSortedList(int sortedList[], int target, int min, int max) {
	
	if (max < min) return -1;
	
	int midpoint = (min + max) / 2;  // Average, rounded down
	
	if (target > sortedList[midpoint])
		return indexOfTargetInSortedList(sortedList, target, midpoint + 1, max);
	
	if (target < sortedList[midpoint])
		return indexOfTargetInSortedList(sortedList, target, min, midpoint - 1);
	
	return midpoint;
}

void rangeOfTargetInSortedList(Range *range, int sortedList[], int target, int min, int max) {
	
	if (max < min) return;
	
	int midpoint = (min + max) / 2;  // Average, rounded down
	
	if (target == sortedList[midpoint]) {
		range->index = midpoint;
		range->count++;
	}
	
	// Traverse right
	Range rightRange; initRange(&rightRange);
	rangeOfTargetInSortedList(&rightRange, sortedList, target, midpoint + 1, max);

	// Traverse left
	Range leftRange; initRange(&leftRange);
	rangeOfTargetInSortedList(&leftRange, sortedList, target, min, midpoint - 1);

	// Least non-negative index wins
	if (rightRange.index >= 0 && (range->index < 0 || rightRange.index < range->index)) range->index = rightRange.index;
	if (leftRange.index >= 0 && (range->index < 0 || leftRange.index < range->index)) range->index = leftRange.index;

	// Accumulate counts
	range->count += rightRange.count + leftRange.count;
}

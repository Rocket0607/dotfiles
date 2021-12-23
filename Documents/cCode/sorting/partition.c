#include <stdio.h>

static inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void dump_list(int *l, int len) {
    for (int i = 0; i < len; i++)
        printf(" %3d", l[i]);
    putchar('\n');
}

static int partition(int *L, int left, int right) {
    int pivot = left;
    int p_val = L[pivot];

    printf("left: %i, right: %i \n", left, right);
    dump_list(L, 19);
    while (left < right) {
        while (L[left] <= p_val)
            left++;
        while (L[right] > p_val)
            right--;
        if (left < right)
            swap(&L[left], &L[right]);
        printf("left: %i, right: %i \n", left, right);
        dump_list(L, 19);
    }
    swap(&L[pivot], &L[right]);
    return right;
}

int main() {
    int arr[19] = {5, 4, 2, 1, 6, 3, 6, 8, 3, 26, 15, 23, 8, 7, 13, 17, 19, 21, 22};
    partition(arr, 0, 18);
    dump_list(arr, 19);
    return 0;
}

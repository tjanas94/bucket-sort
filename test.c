#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sort.h"

#define array_length(array) (sizeof(array) / sizeof((array)[0]))
#define arrays_equal(array, expected) (memcmp((array), (expected), sizeof(array)) == 0)

void test_insertion_sort()
{
    double array[] = {0.5, 0.4, 0.6, 0.1, 0.1};
    double expected[] = {0.1, 0.1, 0.4, 0.5, 0.6};

    sort(array, array_length(array));
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_bucket_sort()
{
    double array[] = {0.5, 0.4, 0.6, 0.1, 0.1, 0.5, 0.3, 0.2, 0.7, 0.4};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.5, 0.6, 0.7};

    sort(array, array_length(array));
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_big_sort()
{
    double array[] = {0.5, 0.4, 0.6, 0.1, 0.1, 50.5, 0.3, 0.2, 0.7, 0.4};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};

    sort(array, array_length(array));
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_reverse_sort()
{
    double array[] = {50.5, 0.7, 0.6, 0.5, 0.4, 0.4, 0.3, 0.2, 0.1, 0.1};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};

    sort(array, array_length(array));
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_sorted_sort()
{
    double array[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};

    sort(array, array_length(array));
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_same_sort()
{
    double array[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    double expected[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    sort(array, array_length(array));
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

int main(void)
{
    test_insertion_sort();
    test_bucket_sort();
    test_big_sort();
    test_reverse_sort();
    test_sorted_sort();
    test_same_sort();

    return 0;
}

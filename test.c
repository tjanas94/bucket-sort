#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sort.h"

double number_comparator(void *first, void *second)
{
    return *(double *)first - *(double *)second;
}

double number_scoring(void *element)
{
    return *(double *)element;
}

double string_comparator(void *first, void *second)
{
    return strcmp(*(char **)first, *(char **)second);
}

double string_scoring(void *element)
{
    return **((char **)element) - '0';
}

int string_arrays_equal(char **array, char **expected, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        if (strcmp(array[i], expected[i]) != 0)
        {
            return 0;
        }
    }

    return 1;
}

void test_insertion_sort()
{
    double array[] = {0.5, 0.4, 0.6, 0.1, 0.1};
    double expected[] = {0.1, 0.1, 0.4, 0.5, 0.6};

    sort(array, array_length(array), sizeof(double), number_comparator, number_scoring);
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_bucket_sort()
{
    double array[] = {0.5, 0.4, 0.6, 0.1, 0.1, 0.5, 0.3, 0.2, 0.7, 0.4};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.5, 0.6, 0.7};

    sort(array, array_length(array), sizeof(double), number_comparator, number_scoring);
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_big_sort()
{
    double array[] = {0.5, 0.4, 0.6, 0.1, 0.1, 50.5, 0.3, 0.2, 0.7, 0.4};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};

    sort(array, array_length(array), sizeof(double), number_comparator, number_scoring);
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_reverse_sort()
{
    double array[] = {50.5, 0.7, 0.6, 0.5, 0.4, 0.4, 0.3, 0.2, 0.1, 0.1};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};

    sort(array, array_length(array), sizeof(double), number_comparator, number_scoring);
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_sorted_sort()
{
    double array[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};
    double expected[] = {0.1, 0.1, 0.2, 0.3, 0.4, 0.4, 0.5, 0.6, 0.7, 50.5};

    sort(array, array_length(array), sizeof(double), number_comparator, number_scoring);
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_same_sort()
{
    double array[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    double expected[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    sort(array, array_length(array), sizeof(double), number_comparator, number_scoring);
    assert(arrays_equal(array, expected));
    printf("%s passed\n", __func__);
}

void test_insertion_strings()
{
    char *array[] = {"abcd", "5", "test", "abcd", "5", "test", "abcd", "5", "test"};
    char *expected[] = {"5", "5", "5", "abcd", "abcd", "abcd", "test", "test", "test"};

    sort(array, array_length(array), sizeof(double), string_comparator, string_scoring);
    assert(string_arrays_equal(array, expected, array_length(array)));
    printf("%s passed\n", __func__);
}

void test_bucket_strings()
{
    char *array[] = {"abcd", "5", "test", "abcd", "5", "test", "abcd", "5", "test", "abcd", "5", "test"};
    char *expected[] = {"5", "5", "5", "5", "abcd", "abcd", "abcd", "abcd", "test", "test", "test", "test"};

    sort(array, array_length(array), sizeof(double), string_comparator, string_scoring);
    assert(string_arrays_equal(array, expected, array_length(array)));
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
    test_insertion_strings();
    test_bucket_strings();

    return 0;
}

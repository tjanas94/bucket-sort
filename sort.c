#include <assert.h>
#include <string.h>
#include <math.h>
#include "sort.h"

#define has_bigger_items_before(array, index) ((index) > 0 && ((array)[(index)-1]) > ((array)[(index)]))
#define append_to_bucket(bucket, element) ((bucket)->data[(bucket)->length++] = (element))

void sort(double *array, size_t size)
{
    if (size > MINIMAL_BUCKET_SORT_SIZE)
    {
        bucket_sort(array, size);
    }
    else
    {
        insertion_sort(array, size);
    }
}

void bucket_sort(double *array, size_t size)
{
    bucket_sort_state *state = initialize_bucket_sort(array, size);
    assign_to_buckets(state);
    sort_and_join_buckets(state);
    free(state);
}

void insertion_sort(double *array, size_t size)
{
    for (size_t i = 1; i < size; ++i)
    {
        for (size_t j = i; has_bigger_items_before(array, j); --j)
        {
            double temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }
    }
}

bucket_sort_state *initialize_bucket_sort(double *array, size_t size)
{
    size_t number_of_buckets = sqrt(size);
    bucket_sort_state *state = malloc(sizeof(bucket_sort_state) + number_of_buckets * (sizeof(bucket) + size * sizeof(double)));
    assert(state);

    state->number_of_elements = size;
    state->number_of_buckets = number_of_buckets;
    state->elements = array;
    initialize_buckets(state);

    state->min_element = min(array, size);
    state->max_element = max(array, size);

    return state;
}

void assign_to_buckets(bucket_sort_state *state)
{
    for (size_t i = 0; i < state->number_of_elements; ++i)
    {
        double element = state->elements[i];
        size_t selected_bucket_index = select_bucket(state, element);
        append_to_bucket(state->buckets + selected_bucket_index, element);
    }
}

void sort_and_join_buckets(bucket_sort_state *state)
{
    size_t sorted_length = 0;

    for (size_t i = 0; i < state->number_of_buckets; ++i)
    {
        bucket *bucket = state->buckets + i;
        if (bucket->length > 0)
        {
            insertion_sort(bucket->data, bucket->length);
            memcpy(state->elements + sorted_length, bucket->data, bucket->length * sizeof(double));
            sorted_length += bucket->length;
        }
    }
}

void initialize_buckets(bucket_sort_state *state)
{
    bucket *buckets = (bucket *)(state + 1);
    double *buckets_data = (double *)(buckets + state->number_of_buckets);

    for (size_t i = 0; i < state->number_of_buckets; ++i)
    {
        buckets[i].length = 0;
        buckets[i].data = buckets_data + i * state->number_of_elements;
    }

    state->buckets = buckets;
}

size_t select_bucket(bucket_sort_state *state, double element)
{
    if (state->max_element <= state->min_element)
    {
        return 0;
    }

    size_t result = (element - state->min_element) * state->number_of_buckets / (state->max_element - state->min_element);

    if (result >= state->number_of_buckets)
    {
        result = state->number_of_buckets - 1;
    }

    return result;
}

double min(double *array, size_t size)
{
    assert(size);
    double result = array[0];

    for (size_t i = 1; i < size; ++i)
    {
        if (array[i] < result)
        {
            result = array[i];
        }
    }

    return result;
}

double max(double *array, size_t size)
{
    assert(size);
    double result = array[0];

    for (size_t i = 1; i < size; ++i)
    {
        if (array[i] > result)
        {
            result = array[i];
        }
    }

    return result;
}

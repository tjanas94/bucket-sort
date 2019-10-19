#include <assert.h>
#include <string.h>
#include <math.h>
#include "sort.h"

void sort(void *array, size_t length, size_t element_size, comparator_t compare, scoring_t score)
{
    if (length < MINIMAL_BUCKET_SORT_SIZE)
    {
        insertion_sort(array, length, element_size, compare);
    }
    else
    {
        bucket_sort(array, length, element_size, compare, score);
    }
}

void insertion_sort(void *array, size_t length, size_t element_size, comparator_t compare)
{
    for (size_t i = 1; i < length; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            void *previous = element_at(array, j - 1, element_size);
            void *current = element_at(array, j, element_size);

            if (compare(previous, current) <= 0)
            {
                break;
            }

            swap(previous, current, element_size);
        }
    }
}

void swap(void *first, void *second, size_t element_size)
{
    void *tmp = malloc(element_size);
    assert(tmp);

    memcpy(tmp, first, element_size);
    memcpy(first, second, element_size);
    memcpy(second, tmp, element_size);

    free(tmp);
}

void bucket_sort(void *array, size_t length, size_t element_size, comparator_t compare, scoring_t score)
{
    struct bucket_sort_t *bucket_sort = initialize_bucket_sort(array, length, element_size, compare, score);
    assign_to_buckets(bucket_sort);
    sort_and_join_buckets(bucket_sort);
    free(bucket_sort);
}

struct bucket_sort_t *initialize_bucket_sort(void *array, size_t length, size_t element_size, comparator_t compare, scoring_t score)
{
    size_t number_of_buckets = sqrt(length);
    struct bucket_sort_t *bucket_sort = malloc(sizeof(struct bucket_sort_t) + number_of_buckets * (sizeof(struct array_t) + length * element_size) + length * sizeof(double));
    assert(bucket_sort);

    bucket_sort->compare = compare;
    bucket_sort->score = score;
    bucket_sort->array_to_sort = (struct array_t){length, element_size, array};
    bucket_sort->grouped_array = (struct array_t){number_of_buckets, sizeof(struct array_t), NULL};
    initialize_buckets(bucket_sort);
    calculate_scores(bucket_sort);

    return bucket_sort;
}

void initialize_buckets(struct bucket_sort_t *bucket_sort)
{
    struct array_t *buckets = (struct array_t *)(bucket_sort + 1);
    uint8_t *buckets_data = (uint8_t *)(buckets + bucket_sort->grouped_array.length);

    for (size_t i = 0; i < bucket_sort->grouped_array.length; ++i)
    {
        buckets[i].length = 0;
        buckets[i].size = bucket_sort->array_to_sort.size;
        buckets[i].data = buckets_data + i * bucket_sort->array_to_sort.size;
    }

    bucket_sort->grouped_array.data = (uint8_t *)buckets;
    bucket_sort->scores = (double *)(buckets_data + bucket_sort->grouped_array.length * bucket_sort->array_to_sort.size);
}

void assign_to_buckets(struct bucket_sort_t *bucket_sort)
{
    for (size_t i = 0; i < bucket_sort->array_to_sort.length; ++i)
    {
        void *element = element_at(bucket_sort->array_to_sort.data, i, bucket_sort->array_to_sort.size);
        size_t selected_bucket_index = select_bucket(bucket_sort, bucket_sort->scores[i]);
        append_to_selected_bucket(bucket_sort->grouped_array, selected_bucket_index, element);
    }
}

void calculate_scores(struct bucket_sort_t *bucket_sort)
{
    for (size_t i = 0; i < bucket_sort->array_to_sort.length; ++i)
    {
        void *element = element_at(bucket_sort->array_to_sort.data, i, bucket_sort->array_to_sort.size);
        bucket_sort->scores[i] = bucket_sort->score(element);
    }

    bucket_sort->max_score = max(bucket_sort->scores, bucket_sort->array_to_sort.length);
    bucket_sort->min_score = max(bucket_sort->scores, bucket_sort->array_to_sort.length);
}

size_t select_bucket(struct bucket_sort_t *bucket_sort, double score)
{
    if (bucket_sort->max_score <= bucket_sort->min_score)
    {
        return 0;
    }

    size_t result = (score - bucket_sort->min_score) * bucket_sort->grouped_array.length / (bucket_sort->max_score - bucket_sort->min_score);

    if (result >= bucket_sort->grouped_array.length)
    {
        result = bucket_sort->grouped_array.length - 1;
    }

    return result;
}

void append_to_selected_bucket(struct array_t array, size_t index, void *element)
{
    struct array_t *selected_array = element_at(array.data, index, array.size);
    memcpy(element_at(selected_array->data, selected_array->length, selected_array->size), element, selected_array->size);
    ++selected_array->length;
}

void sort_and_join_buckets(struct bucket_sort_t *bucket_sort)
{
    size_t sorted_length = 0;

    for (size_t i = 0; i < bucket_sort->grouped_array.length; ++i)
    {
        struct array_t *selected_array = element_at(bucket_sort->grouped_array.data, i, bucket_sort->grouped_array.size);
        if (selected_array->length > 0)
        {
            insertion_sort(selected_array->data, selected_array->length, selected_array->size, bucket_sort->compare);
            memcpy(bucket_sort->array_to_sort.data + sorted_length, selected_array->data, selected_array->length * selected_array->size);
            sorted_length += selected_array->length * selected_array->size;
        }
    }
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

#ifndef _SORT_H_INCLUDED
#define _SORT_H_INCLUDED

#include <stdlib.h>

#define MINIMAL_BUCKET_SORT_SIZE 5

typedef struct bucket
{
    size_t length;
    double *data;
} bucket;

typedef struct bucket_sort_state
{
    size_t number_of_elements;
    size_t number_of_buckets;
    double *elements;
    bucket *buckets;
    double min_element;
    double max_element;
} bucket_sort_state;

void sort(double *, size_t);

void bucket_sort(double *, size_t);

void insertion_sort(double *, size_t);

bucket_sort_state *initialize_bucket_sort(double *, size_t);

void assign_to_buckets(bucket_sort_state *);

void sort_and_join_buckets(bucket_sort_state *);

void initialize_buckets(bucket_sort_state *);

size_t select_bucket(bucket_sort_state *, double);

double min(double *, size_t);

double max(double *, size_t);

#endif

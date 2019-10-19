#ifndef _SORT_H_INCLUDED
#define _SORT_H_INCLUDED

#include <stdlib.h>
#include <stdint.h>

#define MINIMAL_BUCKET_SORT_SIZE 10
#define array_length(array) (sizeof(array) / sizeof((array)[0]))
#define arrays_equal(array, expected) (memcmp((array), (expected), sizeof(array)) == 0)
#define element_at(array, index, size) ((void *)((uint8_t *)(array) + (index) * (size)))

typedef double (*comparator_t)(void *, void *);

typedef double (*scoring_t)(void *);

struct array_t
{
    size_t length;
    size_t size;
    uint8_t *data;
};

struct bucket_sort_t
{
    struct array_t array_to_sort;
    struct array_t grouped_array;
    double *scores;
    double min_score;
    double max_score;
    comparator_t compare;
    scoring_t score;
};

void sort(void *, size_t, size_t, comparator_t, scoring_t);

void insertion_sort(void *, size_t, size_t, comparator_t);

void swap(void *, void *, size_t);

void bucket_sort(void *, size_t, size_t, comparator_t, scoring_t);

struct bucket_sort_t *initialize_bucket_sort(void *, size_t, size_t, comparator_t, scoring_t);

void initialize_buckets(struct bucket_sort_t *);

void assign_to_buckets(struct bucket_sort_t *);

void calculate_scores(struct bucket_sort_t *);

void append_to_selected_bucket(struct array_t, size_t, void *);

size_t select_bucket(struct bucket_sort_t *, double);

void sort_and_join_buckets(struct bucket_sort_t *);

double min(double *, size_t);

double max(double *, size_t);

#endif

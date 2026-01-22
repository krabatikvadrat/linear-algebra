#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

typedef struct
{
    size_t dim;
    double* elements;
} Vector_t;

typedef struct 
{
    bool success;
    double val;
} error_int;

typedef struct   
{
    bool success;
    Vector_t *vec;
} error_vec;

Vector_t *create_vector(size_t dim, const double* elements) 
{
    Vector_t *vector = malloc(sizeof(Vector_t));
    if (!vector) return NULL;

    vector->dim = dim;
    vector->elements = calloc(dim, sizeof(double));
    for (size_t i = 0; i < dim; i++)
    {
        vector->elements[i] = elements[i];
    }
    
    return vector;
}

size_t get_dimension(Vector_t *vec) {
    return vec->dim;
}

double* get_elements(Vector_t *vec) {
    return vec->elements;
}

void destroy_vector(Vector_t *vec) 
{
    if (!vec) return;
    free(vec->elements);
    free(vec);
}

void print_vector(Vector_t *vec) 
{
    printf("Dimension: %zu\n", vec->dim);
    for (size_t i = 0; i < vec->dim; i++)
    {
        printf("Elem[%zu]: %f\n", i, vec->elements[i]);
    }
    
}

error_int scalar_product(Vector_t *vec1, Vector_t *vec2) 
{
    error_int ret;
    double sum = 0;
    if(vec1->dim != vec2->dim) 
    {
        printf("The dimensions of the supplied vectors does not match");
        ret.success = false;
        ret.val = 0;
        return ret;
     
    }
    for (size_t i = 0; i < vec1->dim; i++)
    {
        sum += vec1->elements[i] * vec2->elements[i];
    }
    
    ret.success = true;
        ret.val = sum;
        return ret;
}

error_vec add_vector(Vector_t *vec1, Vector_t *vec2) 
{
    error_vec ret;

    if(vec1->dim != vec2->dim) 
    {
        printf("The dimensions of the supplied vectors does not match");
        ret.success = false;
        ret.vec = NULL;
        return ret;
    }
    double *elems = calloc(vec1->dim, sizeof(double));
    
    
    for (size_t i = 0; i < vec1->dim; i++)
    {
        elems[i] = vec1->elements[i] + vec2->elements[i];
    }
    Vector_t *vec = create_vector(vec1->dim, elems);
    free(elems);
    ret.success = true;
    ret.vec = vec;
    return ret;
}

error_vec sub_vector(Vector_t *vec1, Vector_t *vec2) 
{
    error_vec ret;

    if(vec1->dim != vec2->dim) 
    {
        printf("The dimensions of the supplied vectors does not match");
        ret.success = false;
        ret.vec = NULL;
        return ret;
    }
    double *elems = calloc(vec1->dim, sizeof(double));
    
    
    for (size_t i = 0; i < vec1->dim; i++)
    {
        elems[i] = vec1->elements[i] - vec2->elements[i];
    }
    Vector_t *vec = create_vector(vec1->dim, elems);
    free(elems);
    ret.success = true;
    ret.vec = vec;
    return ret;
}

double vector_length(Vector_t *vec) 
{
    double sum = 0;

    for (size_t i = 0; i < vec->dim; i++)
    {
        sum += pow(vec->elements[i], 2);
    }
    return sqrt(sum);
}

double vector_angle(Vector_t *vec1, Vector_t *vec2) 
{
    double len1 = vector_length(vec1);
    double len2 = vector_length(vec2);
    double dot = scalar_product(vec1, vec2).val;

    return acos(dot / (len1 * len2));
}

int main() {
    double elems[] = {1,2,3};
    Vector_t *vec1 = create_vector(3, elems);
    Vector_t *vec2 = create_vector(3, elems);
    print_vector(vec1);
    printf("Dot product: %f\n", scalar_product(vec1, vec2).val);
    
    Vector_t *add_vec = add_vector(vec1,vec2).vec;
    print_vector(add_vec);

    Vector_t *sub_vec = sub_vector(vec1,vec2).vec;
    print_vector(sub_vec);

    printf("Length: %f\n", vector_length(vec1));
    printf("Length: %f\n", vector_length(vec2));
    printf("Length: %f\n", vector_length(add_vec));
    printf("Length: %f\n", vector_length(sub_vec));
    printf("Angle: %f\n", vector_angle(vec1, add_vec));
    destroy_vector(add_vec);
    destroy_vector(sub_vec);
    destroy_vector(vec1);
    destroy_vector(vec2);
    return 0;
}
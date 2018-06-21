#include "stdint.h"
#include "uint28_t.h"

typedef struct mnist_object 
{
	uint28_t image[28];
	uint8_t label;
} mnist_object_t;

typedef struct cluster 
{
	mnist_object_t* mnist_objects;
	uint32_t num_of_objects;
} cluster_t;

typedef struct reference_cluster 
{
	cluster_t* cluster;
	uint8_t label;
} reference_cluster_t;

void init_clusters(void);

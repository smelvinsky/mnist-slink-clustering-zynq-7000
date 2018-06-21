#ifndef SLINK_CLUSTERING_MNIST_CLUSTERS_H
#define SLINK_CLUSTERING_MNIST_CLUSTERS_H

#include "stdint.h"
#include "uint28_t.h"

#define NUM_OF_REFERENCE_CLUSTERS 		(uint8_t)10
#define MNIST_IMAGE_ROW_NUM				28
#define MNIST_IMAGE_COL_NUM				28

typedef struct mnist_object 
{
	uint28_t image[MNIST_IMAGE_ROW_NUM];
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

#endif /* SLINK_CLUSTERING_MNIST_CLUSTERS_H */

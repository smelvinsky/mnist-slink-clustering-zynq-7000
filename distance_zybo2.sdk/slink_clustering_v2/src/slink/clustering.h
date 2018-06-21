#ifndef SRC_SLINK_CLUSTERING_H_
#define SRC_SLINK_CLUSTERING_H_

#include "../mnist_clusters.h"

typedef enum ClusteringMode
{
	HW_MODE,
	SW_MODE
} ClusteringMode_t;

uint32_t get_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2, ClusteringMode_t mode);
uint8_t get_matching_ref_cluster_index(const mnist_object_t *mnist_object, uint32_t *shortest_distance, ClusteringMode_t mode);
#endif /* SRC_SLINK_CLUSTERING_H_ */

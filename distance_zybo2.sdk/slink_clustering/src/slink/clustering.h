#ifndef SRC_SLINK_CLUSTERING_H_
#define SRC_SLINK_CLUSTERING_H_

#include "../mnist_clusters.h"

uint32_t get_sw_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2);
uint32_t get_hw_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2);

#endif /* SRC_SLINK_CLUSTERING_H_ */

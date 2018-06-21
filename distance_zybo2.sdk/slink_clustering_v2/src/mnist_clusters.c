#include "uint28_t.h"
#include "mnist_clusters.h"

#include "./mnist_clusters/mnist_clusters_0.h"
#include "./mnist_clusters/mnist_clusters_1.h"
#include "./mnist_clusters/mnist_clusters_2.h"
#include "./mnist_clusters/mnist_clusters_3.h"
#include "./mnist_clusters/mnist_clusters_4.h"
#include "./mnist_clusters/mnist_clusters_5.h"
#include "./mnist_clusters/mnist_clusters_6.h"
#include "./mnist_clusters/mnist_clusters_7.h"
#include "./mnist_clusters/mnist_clusters_8.h"
#include "./mnist_clusters/mnist_clusters_9.h"

// array storing 10 reference clusters
reference_cluster_t reference_clusters[10];

// External reference clusters
extern cluster_t cluster_0;
extern cluster_t cluster_1;
extern cluster_t cluster_2;
extern cluster_t cluster_3;
extern cluster_t cluster_4;
extern cluster_t cluster_5;
extern cluster_t cluster_6;
extern cluster_t cluster_7;
extern cluster_t cluster_8;
extern cluster_t cluster_9;

// 10 reference clusters initialization:
void init_clusters()
{
	reference_clusters[0].cluster = &cluster_0;
	reference_clusters[0].label = 0;
	init_cluster_0();

	reference_clusters[1].cluster = &cluster_1;
	reference_clusters[1].label = 1;
	init_cluster_1();

	reference_clusters[2].cluster = &cluster_2;
	reference_clusters[2].label = 2;
	init_cluster_2();

	reference_clusters[3].cluster = &cluster_3;
	reference_clusters[3].label = 3;
	init_cluster_3();

	reference_clusters[4].cluster = &cluster_4;
	reference_clusters[4].label = 4;
	init_cluster_4();

	reference_clusters[5].cluster = &cluster_5;
	reference_clusters[5].label = 5;
	init_cluster_5();

	reference_clusters[6].cluster = &cluster_6;
	reference_clusters[6].label = 6;
	init_cluster_6();

	reference_clusters[7].cluster = &cluster_7;
	reference_clusters[7].label = 7;
	init_cluster_7();

	reference_clusters[8].cluster = &cluster_8;
	reference_clusters[8].label = 8;
	init_cluster_8();

	reference_clusters[9].cluster = &cluster_9;
	reference_clusters[9].label = 9;
	init_cluster_9();
}


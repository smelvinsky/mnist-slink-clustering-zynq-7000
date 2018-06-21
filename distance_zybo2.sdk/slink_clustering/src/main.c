#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "mnist_clusters.h"
#include "timer.h"


#define NUM_OF_REFERENCE_CLUSTERS 10

extern reference_cluster_t reference_clusters[NUM_OF_REFERENCE_CLUSTERS]; // in mnist_clusters.c


static void print_startup_info()
{
	const char *startup_info =
			"\n\r\e[1m*************** Hardware Accelerated SLINK Clustering Example **************\e[0m\n\n\r"
			"\t\e[3mauthors:\e[0m\t\e[4mSmela D., Rybicka M.\e[0m\n\r"
			"\t\e[3mtarget dev:\e[0m\tXilinx Zynq-7000 SoC (xc7z010clg400-1)\n\r"
			"\t\e[3menv:\e[0m\t\tVivado v2018.1 (Linux 64-bit)\n\r"
			"\t\e[3mrev:\e[0m\t\t0.01\n\r"
			"\t\e[3mdate:\e[0m\t\tJune 2018\n\r"
			"\n\r\e[1m****************************************************************************\e[0m\n\n\r";

	printf(startup_info);
}


static void print_ref_clusters_init_info()
{
	uint32_t num_of_mnist_objects = 0;
	for (int i = 0; i < NUM_OF_REFERENCE_CLUSTERS; i++)
	{
		num_of_mnist_objects += reference_clusters[i].cluster->num_of_objects;
	}

	printf("MNIST database successfully loaded (%lu images - %lu bytes)\n\r", num_of_mnist_objects, num_of_mnist_objects * sizeof(mnist_object_t));
}


int main()
{
	double time_elapsed_ms = 0;

    init_platform();
    print_startup_info();

    printf("Initializing reference MNIST clusters ...\n\r");
    timer_start();
    init_clusters();
    time_elapsed_ms = timer_stop();
    printf("Reference clusters initialization finished (took %.2f ms)\n\r", time_elapsed_ms);
    print_ref_clusters_init_info();

    cleanup_platform();
    return 0;
}

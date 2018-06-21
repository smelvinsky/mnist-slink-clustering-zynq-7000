#include <stdio.h>
#include "uint28_t.h"
#include "platform.h"
#include "xil_printf.h"
#include "mnist_clusters.h"
#include "timer.h"
#include "slink/clustering.h"


extern reference_cluster_t reference_clusters[NUM_OF_REFERENCE_CLUSTERS]; // in mnist_clusters.c


static void print_startup_info(void)
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


static void print_ref_clusters_init_info(void)
{
	uint32_t num_of_mnist_objects = 0;
	for (int i = 0; i < NUM_OF_REFERENCE_CLUSTERS; i++)
	{
		num_of_mnist_objects += reference_clusters[i].cluster->num_of_objects;
	}

	printf("MNIST database successfully loaded (%lu images - %lu bytes)\n\n\r", num_of_mnist_objects, num_of_mnist_objects * sizeof(mnist_object_t));
}


static void print_timing_info(void)
{
	double time_elapsed_ms = 0;

	timer_start();
	uint32_t distance = get_dist_between_mnist_obj(&(reference_clusters[0].cluster[0].mnist_objects[0])
	  											 , &(reference_clusters[0].cluster[0].mnist_objects[1])
												 , SW_MODE );
	time_elapsed_ms = timer_stop();
	printf("Measured distance by software function: %lu (took %.2f ms)\n\r", distance, time_elapsed_ms);

    timer_start();
    distance = get_dist_between_mnist_obj(&(reference_clusters[0].cluster[0].mnist_objects[0])
    									, &(reference_clusters[0].cluster[0].mnist_objects[1])
										, HW_MODE );
	time_elapsed_ms = timer_stop();
	printf("Measured distance by hardware accelerator: %lu (took %.2f ms)\n\n\r", distance, time_elapsed_ms);
}


static void print_mnist_image(const mnist_object_t *mnist_object)
{
	printf("Image:\n");
	    for (int column = 0; column < 28; column++)
	    {
	        for (int row = 0; row < 28; row++)
	        {
	            if ((mnist_object->image[column] & (1UL << (unsigned) row)) == 0)
	            {
	                printf(".");
	            }
	            else
	            {
	                printf("X");
	            }
	        }
	        printf("\n");
	    }
}


static void init_ref_clusters(void)
{
	double time_elapsed_ms = 0;

    printf("Initializing reference MNIST clusters ...\n\r");
    timer_start();
    init_clusters();
    time_elapsed_ms = timer_stop();
    printf("Reference clusters initialization finished (took %.2f ms)\n\r", time_elapsed_ms);
    print_ref_clusters_init_info();
    print_timing_info();
}


static void clustering_demo(mnist_object_t *mnist_object)
{
	uint8_t matching_ref_cluster_index;
	uint32_t shortest_distance;
	double time_elapsed_ms = 0;

	printf("Recognizing MNIST image...\n\r");
	print_mnist_image(mnist_object);

	timer_start();
	matching_ref_cluster_index = get_matching_ref_cluster_index(mnist_object, &shortest_distance, SW_MODE);
	time_elapsed_ms = timer_stop();
	printf("Digit value predicted by software function: %u with similarity coefficient of %.2f %% (took %.2f ms)\n\r"
			, reference_clusters[matching_ref_cluster_index].label
			, 100.0 * (((MNIST_IMAGE_COL_NUM * MNIST_IMAGE_ROW_NUM) - (float) shortest_distance) / (MNIST_IMAGE_COL_NUM * MNIST_IMAGE_ROW_NUM))
			, time_elapsed_ms);

	timer_start();
	matching_ref_cluster_index = get_matching_ref_cluster_index(mnist_object, &shortest_distance, HW_MODE);
	time_elapsed_ms = timer_stop();

	printf("Digit value predicted by hardware accelerator: %u with similarity coefficient of %.2f %% (took %.2f ms)\n\n\r"
			, reference_clusters[matching_ref_cluster_index].label
			, 100.0 * (((MNIST_IMAGE_COL_NUM * MNIST_IMAGE_ROW_NUM) - (float) shortest_distance) / (MNIST_IMAGE_COL_NUM * MNIST_IMAGE_ROW_NUM))
			, time_elapsed_ms);
}


int main()
{
	/* ************************************************ PLATFORM INIT ************************************************ */
    init_platform();
    print_startup_info();
    /* *************************************************************************************************************** */

    /* ************************************************ CLUSTERS INIT ************************************************ */
    init_ref_clusters();
    /* *************************************************************************************************************** */

    /* *********************************************** CLUSTERING DEMO *********************************************** */
    mnist_object_t mnist_object_demo;
    memset(&mnist_object_demo, 0, sizeof(mnist_object_demo));

    UINT28_SET(mnist_object_demo.image[0], (uint32_t) 0x00000000);
    UINT28_SET(mnist_object_demo.image[1], (uint32_t) 0x00000000);
    UINT28_SET(mnist_object_demo.image[2], (uint32_t) 0x00F00000);
    UINT28_SET(mnist_object_demo.image[3], (uint32_t) 0x00000F00);
    UINT28_SET(mnist_object_demo.image[4], (uint32_t) 0x0A000000);
    UINT28_SET(mnist_object_demo.image[5], (uint32_t) 0x00FC0000);
    UINT28_SET(mnist_object_demo.image[6], (uint32_t) 0x007FF000);
    UINT28_SET(mnist_object_demo.image[7], (uint32_t) 0x007FF800);
    UINT28_SET(mnist_object_demo.image[8], (uint32_t) 0x003FF800);
    UINT28_SET(mnist_object_demo.image[9], (uint32_t) 0x003EFC00);
    UINT28_SET(mnist_object_demo.image[10], (uint32_t) 0x001F3C00);
    UINT28_SET(mnist_object_demo.image[11], (uint32_t) 0x000FFC00);
    UINT28_SET(mnist_object_demo.image[12], (uint32_t) 0x0007FC00);
    UINT28_SET(mnist_object_demo.image[13], (uint32_t) 0x0003F800);
	UINT28_SET(mnist_object_demo.image[14], (uint32_t) 0x0007FC00);
	UINT28_SET(mnist_object_demo.image[15], (uint32_t) 0x0001F800);
	UINT28_SET(mnist_object_demo.image[16], (uint32_t) 0x0003F800);
	UINT28_SET(mnist_object_demo.image[17], (uint32_t) 0x0007FC00);
	UINT28_SET(mnist_object_demo.image[18], (uint32_t) 0x00079E00);
	UINT28_SET(mnist_object_demo.image[19], (uint32_t) 0x00071E00);
	UINT28_SET(mnist_object_demo.image[20], (uint32_t) 0x00070F80);
	UINT28_SET(mnist_object_demo.image[21], (uint32_t) 0x003F0FC0);
	UINT28_SET(mnist_object_demo.image[22], (uint32_t) 0x00170F00);
	UINT28_SET(mnist_object_demo.image[23], (uint32_t) 0x0003FF00);
	UINT28_SET(mnist_object_demo.image[24], (uint32_t) 0x0001FE00);
	UINT28_SET(mnist_object_demo.image[25], (uint32_t) 0x0000F000);
	UINT28_SET(mnist_object_demo.image[26], (uint32_t) 0x00000000);
	UINT28_SET(mnist_object_demo.image[27], (uint32_t) 0x00000000);

    clustering_demo(&(reference_clusters[3].cluster->mnist_objects[10]));
    clustering_demo(&mnist_object_demo);
    /* *************************************************************************************************************** */

    cleanup_platform();
    return 0;
}

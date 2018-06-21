#include <stdio.h>
#include "xil_io.h"
#include "xparameters.h"
#include "distance_zybo2_ip.h"
#include "../mnist_clusters.h"
#include "clustering.h"


/* distance hw accelerator registers' offset def */
#define DISTANCE_IP_BASE_ADDR			XPAR_DISTANCE_ZYBO2_IP_0_S00_AXI_BASEADDR
#define DISTANCE_IP_OFFSET_STEP			4

#define DISTANCE_IP_REG_CTRL			DISTANCE_ZYBO2_IP_S00_AXI_SLV_REG0_OFFSET
#define DISTANCE_IP_REG_IMG_1_FIRST		DISTANCE_ZYBO2_IP_S00_AXI_SLV_REG1_OFFSET
#define DISTANCE_IP_REG_IMG_2_FIRST		DISTANCE_ZYBO2_IP_S00_AXI_SLV_REG29_OFFSET
#define DISTANCE_IP_REG_STATUS			DISTANCE_ZYBO2_IP_S00_AXI_SLV_REG57_OFFSET
#define DISTANCE_IP_REG_RESULT			DISTANCE_ZYBO2_IP_S00_AXI_SLV_REG58_OFFSET

extern reference_cluster_t reference_clusters[NUM_OF_REFERENCE_CLUSTERS]; // in mnist_clusters.c


static uint32_t get_sw_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2)
{
	uint32_t distance = 0;

	for (int column = 0; column < MNIST_IMAGE_ROW_NUM; column++)
	{
		for (int row = 0; row < MNIST_IMAGE_ROW_NUM; row++)
		{
			if ((mnist_object_1->image[column] ^ mnist_object_2->image[column]) & (1UL << (row)))
			{
				distance++;
			}
		}
	}

	return distance;
}


static uint32_t get_hw_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2)
{
	uint32_t distance = 0;

	for (int row = 0; row < MNIST_IMAGE_ROW_NUM; row++)
	{
		DISTANCE_ZYBO2_IP_mWriteReg(DISTANCE_IP_BASE_ADDR, DISTANCE_IP_REG_IMG_1_FIRST + (row * DISTANCE_IP_OFFSET_STEP), mnist_object_1->image[row]);
		DISTANCE_ZYBO2_IP_mWriteReg(DISTANCE_IP_BASE_ADDR, DISTANCE_IP_REG_IMG_2_FIRST + (row * DISTANCE_IP_OFFSET_STEP), mnist_object_2->image[row]);
	}

	DISTANCE_ZYBO2_IP_mWriteReg(DISTANCE_IP_BASE_ADDR, DISTANCE_IP_REG_CTRL, 0x00000001);
	DISTANCE_ZYBO2_IP_mWriteReg(DISTANCE_IP_BASE_ADDR, DISTANCE_IP_REG_CTRL, 0x00000000);

	while(!(DISTANCE_ZYBO2_IP_mReadReg(DISTANCE_IP_BASE_ADDR, DISTANCE_IP_REG_STATUS) & 0x00000001));

	distance = DISTANCE_ZYBO2_IP_mReadReg(DISTANCE_IP_BASE_ADDR, DISTANCE_IP_REG_RESULT);
	return distance;
}


uint32_t get_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2, ClusteringMode_t mode)
{
	if (mode == HW_MODE)
	{
		return get_hw_dist_between_mnist_obj(mnist_object_1, mnist_object_2);
	}
	else
	{
		return get_sw_dist_between_mnist_obj(mnist_object_1, mnist_object_2);
	}
}


uint32_t get_dist_between_mnist_obj_and_cluster(const mnist_object_t *mnist_object, cluster_t *cluster, ClusteringMode_t mode)
{
	uint32_t min_distance = UINT32_MAX;
	uint32_t distance_tmp;

	for (int mnist_obj_index = 0; mnist_obj_index < cluster->num_of_objects; mnist_obj_index++)
	{
		distance_tmp = get_dist_between_mnist_obj(mnist_object, &(cluster->mnist_objects[mnist_obj_index]), mode);
		if (distance_tmp < min_distance)
		{
			min_distance = distance_tmp;
		}
	}

	return min_distance;
}


uint8_t get_matching_ref_cluster_index(const mnist_object_t *mnist_object, uint32_t *shortest_distance, ClusteringMode_t mode)
{
	uint8_t matching_ref_cluster_index;
	uint32_t min_distance = UINT32_MAX;
	uint32_t distance_tmp;

	for (int ref_cluster_index = 0; ref_cluster_index < NUM_OF_REFERENCE_CLUSTERS; ref_cluster_index++)
	{
		distance_tmp = get_dist_between_mnist_obj_and_cluster(mnist_object, reference_clusters[ref_cluster_index].cluster, mode);
		if (distance_tmp < min_distance)
		{
			min_distance = distance_tmp;
			matching_ref_cluster_index = ref_cluster_index;
		}
	}

	*shortest_distance = min_distance;
	return matching_ref_cluster_index;
}

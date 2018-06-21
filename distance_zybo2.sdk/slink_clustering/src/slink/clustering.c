#include "clustering.h"

uint32_t get_sw_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2)
{
	uint32_t distance = 0;

	for (int column = 0; column < 28; column++)
	{
		for (int row = 0; row < 28; row++)
		{
			if ((mnist_object_1->image[column] ^ mnist_object_2->image[column]) & (1UL << (row)))
			{
				distance++;
			}
		}
	}

	return distance;
}

uint32_t get_hw_dist_between_mnist_obj(const mnist_object_t *mnist_object_1, const mnist_object_t *mnist_object_2)
{
	uint32_t distance = 0;
	//TODO: HARDWARE ACCELERATED DISTANCE MEASUREMENT
	return distance;
}

#include "../volumeElimination/volumeElimination.h"
#include <vil/vil_image_view.h>

#ifndef _HIERSUPERVOXEL_H_
#define _HIERSUPERVOXEL_H_

template<class T>
class hierSuperVoxel
{
public:
	hierSuperVoxel(vil_image_view<T> &im, int voxelsize);//max size of each supervoxel
	int getLabel(int i, int j, int k);
private:
	int _width;
	int _height;
	int _layers;
	volumeElimination::vector3i _label;
	double hierSuperVoxel<T>::cost(double v1, double v2);
};

#include "hierSuperVoxel.cpp"

#endif
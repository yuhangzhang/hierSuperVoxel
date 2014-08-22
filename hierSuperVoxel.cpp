#include "hierSuperVoxel.h"

#ifndef _HIERSUPERVOXEL_CPP_
#define _HIERSUPERVOXEL_CPP_


template<class T>
double hierSuperVoxel<T>::cost(double v1, double v2)
{
	double tempf=-fabs(v1-v2);
	tempf = exp(tempf/0.02)+0.01;
	
	return tempf;
}


template<class T>
hierSuperVoxel<T>::hierSuperVoxel(vil_image_view<T>& im, int voxelsize)
{
	_width=im.ni();
	_height=im.nj();
	_layers=im.nplanes();

	if( _width>voxelsize || _height>voxelsize || _layers>voxelsize )
	{
		width = _width/3;
		height = _height/3;
		layers = _layers/3;
	}

	vil_image_view<T>& im_small(width,height,layers);

	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			for(int k=0;k<layers;k++)
			{
				T tempT=0;

				for(int ii=i*3;ii<i*3+3;ii++)
				{
					for(int jj=j*3;jj<j*3+3;jj++)
					{
						for(int kk=k*3;kk<k*3+3;kk++)
						{
							tempT += im(ii,jj,kk);
						}
					}
				}

				im_small(i,j,k) = tempT/9.0;
			}
		}
	}

	hierSuperVoxel<T> hsv(im_small,voxelsize);

	_label.resize(_width);

	for(int i=0;i<_width;i++)
	{
		_label[i].resize(_height);

		int ii = (i/3>width)?width-1:i/3;

		for(int j=0;j<_height;j++)
		{
			_label[i][j].resize(_layers);

			int jj = (j/3>height)?height-1:j/3;

			for(int k=0;k<_layers)
			{
				int kk = (k/3>layers)?layers-1:k/3
				_label[i][j][k] = hsv.getLabel(ii,jj,kk);
			}
		}
	}

}


template<class T>
int hierSuperVoxel<T>::getLabel(int i, int j, int k)
{
	return _label[i][j][k];
}
#endif
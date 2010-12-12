#include <stdio.h>

static byte*** bmp_array()
{

	Bitmap bmp = Bitmap->FromFile("image.bmp");
	//КАК?! Как это делается в чистосях?

	int height = bmp.Height;
	int width = bmp.Width;
	byte*** bmpArray = malloc(height * sizeof(byte**));
	for(int i = 0; i < height; ++i)
	{
		bmpArray[i] = malloc(width * sizeof(byte*));
		for(int j = 0; j < width; ++j)
		{
			bmpArray[i][j] = malloc(3 * sizeof(byte));
		}
	}


	for (int i = height - 1; i >= 0; i--)
	{

		for(j = 0; j < width; ++j)
		{
			//bmpArray[i][j] = GetPixel(bmp->Canvas->Handle, i, j);
			//сработает ли?!
		}
	}




	return bmpArray;
}

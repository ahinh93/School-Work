#include "Image.h"

Image::Image()
{
	pixels = NULL;
	width = 0;
	height = 0;
}

Image::Image(int w, int h)
{
	width = w;
	height = h;
	pixels = new float**[height];	
	int i, j, k;
	for (i = 0; i < height; i++)
	{
		pixels[i] = new float*[width];
		for (j = 0; j < width; j++)
		{
			pixels[i][j] = new float[3];
			for (k = 0; k < 3; k++)
			{
				pixels[i][j][k] = 0;
			}
		}
	}
}

Image::Image(Image I)
{
	int i, j, k;
	width = I.getWidth();
	height = I.getHeight();
	
	pixels = new float**[height];
	for (i = 0; i<height; i++)
	{
		pixels[i] = new float*[width];
		for (j = 0; j < width; j++)
		{
			pixels[i][j] = new float[3];
			for (k = 0; k<3; k++)
			{
				pixels[i][j][k] = I.pixels[i][j][k];
			}
		}
	}
}

int Image::getWidth()
{
	return width;
}
	
int Image::getHeight()
{
	return height;
}

bool Image::fromPPMFile(string filename)
{
	string line;
	ifstream f (filename, ios::in);
	if (f.is_open())
	{
		if (getline(f, line))
		{
			if (line.compare("P3") != 0)
			{
				f.close();
				return false;
			}
		}
		if (getline(f, line))
		{
			char currentLine[] = line.c_str();
			char *p = strtok(currentLine, " ");
			while (p != NULL)
			{
				cout << p << endl;
				p = strtok(NULL, " ");
			}
		
		}
	
		f.close();
	}	
	
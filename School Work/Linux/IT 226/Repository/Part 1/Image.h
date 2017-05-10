#ifndef IMAGE_H
#define IMAGE_H
using namespace std;

class Image 
{
	private:
		float***pixels;
		int width;
		int height;
		
	public:
		//constructors
		Image();
		Image(int w, int h);
		Image(Image i);
		
		//methods
		int getWidth()const;
		int getHeight()const;
		bool fromPPMFile(const string filename);
		bool toPPMFile(const string filename);
		bool flipVertical();
		void thresholdForDisplay();
		Image getEdges()const;

};	
#endif

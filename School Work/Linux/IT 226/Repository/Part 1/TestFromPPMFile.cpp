#include <iostream>
#include "Image.h"
using namespace std;


int main()
{

//call fromPPMFile then feed it earthmap.ppm
//then put it into default image
//then call cout's

/* Test other constructors
Image defaultImage;
cout << "Default's width: " << defaultImage.getWidth() << " Default's height: " << defaultImage.getHeight<<endl();

cout << "Creating new Image object, expecting height = 5, width = 10"<<endl;
Image definedImage(10, 5);
cout << "Defined image's width: " << definedImage.getWidth() << " Defined image's height: " << definedImage.getHeight<<endl();
*/

Image image;
image.fromPPMFile("earthmap.ppm");

cout << "success" <<endl;


}

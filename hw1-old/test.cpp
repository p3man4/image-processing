#include <Magick++.h>
#include <iostream>

using namespace std;
using namespace Magick;

#define ZOOM_OUT 0.5
int main(int argc, char**argv)
{

	InitializeMagick(*argv);

	Image master("/home/jun/Downloads/rebecca-ferguson-tom-cruise.jpg");
//	master.display();

	Image second = master;
	int size_x = 256, size_y=256;
	second.zoom(Geometry(size_x*ZOOM_OUT,size_y*ZOOM_OUT));
	//second.resize("256x256");
	second.display();
//	Image third = master;
//	third.resize("800x600");
//	second.write("rebeca640x480.jpg");
//	thrid.write("rebeca800x600.jpg");

        second.modifyImage();
        Pixels my_pixcel_cache(second);
        PixelPacket* pixels;
        int start_x=10, start_y=20,size_x=200,size_y=100;
        pixels=my_piexel_cache.get(start_x,start_y,size_x,size_y);
        *pixels= Color("black");
        *(pixels+200)=Color("green");
        my_pixel_cache.sync();
        second.display();

	return 0;
}

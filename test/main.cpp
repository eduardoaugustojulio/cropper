#include <iostream>

#include "cropper.h"

int get_image(const int argc, const char **argv)
{
	if(argc < 2){
		std::cout << "usage: " << argv[0] << " {image} " << std::endl;
		return EXIT_FAILURE;
	}

	Cropper cropper(argv[1]);
}

int get_video(const int argc, const char **argv)
{
	cv::addWeighted()

	int error_code = 0;
	cv::VideoCapture cap(0);

	if(!cap.isOpened())
		return -1;

	cv::Mat frame;
	for(;;){

		cap >> frame;
		Cropper c(frame);
	}

}

int main(const int argc, const char **argv)
{
	get_image(argc, argv);
	//get_video(argc, argv);
}

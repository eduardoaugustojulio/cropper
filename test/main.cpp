#include <iostream>

#include "cropper.h"

int get_image(const int argc, const char **argv)
{
	if(argc < 2){
		std::cout << "usage: " << argv[0] << " {image 1} or {image 2}  " << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << std::to_string(argc) << std::endl;

	if(argc == 2)
		Cropper cropper(argv[1]);
	else if(argc == 3)
		Cropper cropper(argv[1], argv[2]);

	return EXIT_SUCCESS;

}

int get_video(const int argc, const char **argv)
{
	if(argc < 2){
		std::cout << "usage: " << argv[0] << " {camera url}" << std::endl;
		return EXIT_FAILURE;
	}

	cv::VideoCapture cap(argv[1]);

	if(!cap.isOpened())
		return -1;

	cv::Mat frame;
	if(cap.read(frame))
		Cropper c(frame);

	return EXIT_SUCCESS;
}

int main(const int argc, const char **argv)
{
	//get_image(argc, argv);
	get_video(argc, argv);
	return EXIT_SUCCESS;
}

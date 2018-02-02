#ifndef CROPPER_H
#define CROPPER_H

#include    <iostream>
#include    <vector>
#include    <chrono>
#include    <tuple>
#include    <algorithm>
#include	<fstream>
#include	<unistd.h>
#include	<string>
#include	<sys/stat.h>

#include	<opencv2/opencv.hpp>
#include	<opencv2/core.hpp>
#include	<opencv2/imgproc.hpp>
#include	<opencv2/features2d.hpp>


class Cropper{
public:
    Cropper(std::string input = "", std::string output = "");
	Cropper(cv::Mat &img);
	void run(cv::Mat img);
    ~Cropper();

private:
    const std::vector<std::string> winNames = { "Crop Image" , "Cropped" };
	const std::string  fileName = {"positions.xml"};
	const int maxPositions = 2;

    std::pair<cv::Mat, cv::Mat> image;
    std::pair<cv::Point, cv::Point> points = std::make_pair(cv::Point(0, 0), cv::Point(0, 0));
    cv::Rect rectangle = cv::Rect(0,0,0,0);
    cv::Mat rectFromImage;

    bool clicked = false;

    static void onMouse(int event, int x, int y, int f, void *userdata);
    void onMouse(int event, int x, int y);

	void checkBoundary();
    void showImage();
	void message();

	void clearPositionsFile(){
		if(fileExists(this->fileName)){
			std::ofstream ofs;
			ofs.open(this->fileName, std::ofstream::out | std::ofstream::trunc);
			ofs.close();
		}
	}

	inline bool fileExists (const std::string& name) {
	  struct stat buffer;
	  return (stat (name.c_str(), &buffer) == 0);
	}
};

#endif // CROPPER_H

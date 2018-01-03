#ifndef CROPPER_H
#define CROPPER_H

#include    <iostream>
#include    <vector>
#include    <chrono>
#include    <tuple>
#include    <algorithm>

#include	<opencv2/opencv.hpp>
#include	<opencv2/core.hpp>
#include	<opencv2/imgproc.hpp>
#include	<opencv2/features2d.hpp>


class Cropper{
public:
    Cropper(std::string input = "", std::string output = "");
    ~Cropper();

private:
    const std::vector<std::string> winNames = { "Crop Image" , "Cropped" };

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
};

#endif // CROPPER_H

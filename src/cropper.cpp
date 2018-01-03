#include    <iostream>
#include    <vector>
#include    <chrono>
#include    <tuple>
#include    <algorithm>

#include	<opencv2/opencv.hpp>
#include	<opencv2/core.hpp>
#include	<opencv2/imgproc.hpp>
#include	<opencv2/features2d.hpp>

#include    "cropper.h"

Cropper::Cropper(std::string input, std::string output)
{
    cv::setUseOptimized(true);
    cv::setNumThreads(4);

    if(input.empty() || cv::imread(input, cv::IMREAD_GRAYSCALE).empty()){
        std::cout << "Passed empty file or dosent exist" << std::endl;
        exit(-1);
    }

    this->message();

    this->image.first = cv::imread(input, cv::IMREAD_GRAYSCALE);
    cv::namedWindow(this->winNames.at(0), cv::WINDOW_FULLSCREEN);
    cv::setMouseCallback(this->winNames.at(0).c_str(), this->onMouse, this);

    if(!this->image.first.empty())
        cv::imshow(this->winNames.at(0), this->image.first);

    while(true){
        auto key = cv::waitKey();
        if(key == 27) break;

        if(key == 's' && this->rectFromImage.data){
            cv::imwrite((output.empty() ? "imagedefault.jpeg" : output) , this->rectFromImage);
            std::cout << "  Saved "<< (output.empty() ? "imagedefault.jpeg" : output) << std::endl;
        }
        if(key == 'm' && rectFromImage.data)
            cv::imshow(this->winNames.at(1), this->rectFromImage);

        if(key == '6') this->rectangle.x++;
        if(key == '4') this->rectangle.x--;
        if(key == '8') this->rectangle.y--;
        if(key == '2') this->rectangle.y++;

        if(key == 'w') { this->rectangle.y--; this->rectangle.height++;}
        if(key == 'd') this->rectangle.width++;
        if(key == 'x') this->rectangle.height++;
        if(key == 'a') { this->rectangle.x--; this->rectangle.width++;}

        if(key == 't') { this->rectangle.y++; this->rectangle.height--;}
        if(key == 'h') this->rectangle.width--;
        if(key == 'b') this->rectangle.height--;
        if(key == 'f') { this->rectangle.x++; this->rectangle.width--;}

        if(key ==27) break;
        if(key =='r') {
            this->rectangle.x=0;
            this->rectangle.y=0;
            this->rectangle.width=0;
            this->rectangle.height=0;
        }
        showImage();
    }
}

Cropper::~Cropper()
{

}

void Cropper::onMouse(int event, int x, int y, int f, void *userdata)
{
    Cropper* cropper = reinterpret_cast<Cropper*>(userdata);
    if(cropper)
        cropper->onMouse(event, x , y);
}

void Cropper::onMouse(int event, int x, int y)
{
    switch (event) {
    case CV_EVENT_MOUSEMOVE:

        if(this->clicked){
            this->points.second.x = x;
            this->points.second.y = y;
        }

        break;
    case CV_EVENT_LBUTTONUP:

        this->points.second.x = x;
        this->points.second.y = y;
        this->clicked = false;

        break;
    case  CV_EVENT_LBUTTONDOWN  :

        this->clicked = true;

        this->points.first.x = x;
        this->points.first.y = y;

        this->points.second.x = x;
        this->points.second.y = y;

        break;

    default:
        break;
    }

    if(this->clicked){
        if(this->points.first.x > this->points.second.x){
            this->rectangle.x = this->points.second.x;
            this->rectangle.width = (this->points.first.x - this->points.second.x);
        } else {
            this->rectangle.x = this->points.first.x;
            this->rectangle.width = (this->points.second.x - this->points.first.x);
        }

        if(this->points.first.y > this->points.first.y){
            this->rectangle.y = this->points.first.y;
            this->rectangle.height = (this->points.first.y - this->points.second.y);
        } else {
            this->rectangle.y = this->points.first.y;
            this->rectangle.height = (this->points.second.y - this->points.first.y);
        }
    }

    this->showImage();

}

void Cropper::checkBoundary()
{
    if(this->rectangle.width > (this->image.second.cols - this->rectangle.x))
        this->rectangle.width = (this->image.second.cols - this->rectangle.x);

    if(this->rectangle.height > (this->image.second.rows - this->rectangle.y))
        this->rectangle.height = (this->image.second.rows - this->rectangle.y);

    if(this->rectangle.x < 0)
        this->rectangle.width = 0;

    if(this->rectangle.y < 0)
        this->rectangle.height = 0;
}

void Cropper::showImage()
{
    this->image.second = this->image.first.clone();
    checkBoundary();

    if(this->rectangle.width > 0 && this->rectangle.height > 0){
        this->rectFromImage = this->image.first(cv::Rect(this->rectangle));
    }

    cv::rectangle(this->image.second, rectangle, cv::Scalar(0,255,0), 4, 8, 0 );
    cv::imshow(this->winNames.at(0), this->image.second);
}

void Cropper::message()
{
    std::cout << "Click and drag for Selection" << std::endl << std::endl;
    std::cout << "------> Press 'm' to to show" << std::endl;
    std::cout << "------> Press 's' to save" <<std::endl << std::endl;

    std::cout << "------> Press '8' to move up" << std::endl;
    std::cout << "------> Press '2' to move down" << std::endl;
    std::cout << "------> Press '6' to move right" << std::endl;
    std::cout << "------> Press '4' to move left" << std::endl << std::endl;

    std::cout << "------> Press 'w' increas top" << std::endl;
    std::cout << "------> Press 'x' increas bottom" << std::endl;
    std::cout << "------> Press 'd' increas right" << std::endl;
    std::cout << "------> Press 'a' increas left" << std::endl << std::endl;

    std::cout << "------> Press 't' decrease top" << std::endl;
    std::cout << "------> Press 'b' decrease bottom" << std::endl;
    std::cout << "------> Press 'h' decrease right" << std::endl;
    std::cout << "------> Press 'f' decrease left" << std::endl << std::endl;

    std::cout << "------> Press 'r' to reset" << std::endl;
    std::cout << "------> Press 'Esc' to quit" << std::endl << std::endl;
}

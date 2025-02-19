#include <opencv2/opencv.hpp>

int main() {
    // Load an image from file
    cv::Mat image = cv::imread("image.png");

    // Check if the image is loaded properly
    if (image.empty()) {
        std::cout << "Could not open or find the image!" << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Display the original image
    cv::imshow("Original Image", image);

    // Display the grayscale image
    cv::imshow("Grayscale Image", grayImage);

    // Wait for any key press to close the windows
    cv::waitKey(0);

    return 0;
}

/*
g++ -o media  media.cpp `pkg-config --cflags --libs opencv4`
*/
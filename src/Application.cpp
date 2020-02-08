#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

// TODO Declare class ColorMatrix

class ColorMatrix {
public:
	ColorMatrix();
	~ColorMatrix();
};

void parse(ColorMatrix& colorMtx, std::fstream& file) {
	// TODO parsing
}

void compute(std::string filePath) {
	std::fstream fileToParse(filePath, std::fstream::in);
	//TODO parsing & compution
	fileToParse.close();
}

int main(int argc, char** argv) {
	std::string filePath = "C:\\Users\\User\\Desktop\\Nature.";
	cv::Mat image = cv::imread(filePath + "jpeg");

	std::fstream imageDataFile(filePath + "pdt", std::fstream::out);

	for (int x = 0; x < image.rows; x++) {
		for (int y = 0; y < image.cols; y++) {
			cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(y, x));
			imageDataFile << color << std::endl;
		}
	}

	imageDataFile.close();

	cv::String windowName = "Nature.jpeg"; //Name of the window
	cv::namedWindow(windowName); // Create a window
	cv::imshow(windowName, image); // Show our image inside the created window.
	cv::waitKey(0); // Wait for any keystroke in the window
	cv::destroyWindow(windowName); //destroy the created window

#ifdef COMPUTE
	compute(filePath + "pdt");
#endif

	return 0;
}
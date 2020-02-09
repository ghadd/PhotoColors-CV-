#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

enum {
	blue, green, red
};

#define SCALER 10

bool isNotBackground(uchar b, uchar g, uchar r) {
	return true;
}

int main(int argc, char** argv) {
	std::string customPath;
	while (1) {
		std::cin >> customPath;
		if (customPath == "quit()") break;
		std::string filePath = "C:\\Users\\User\\Desktop\\" + customPath;
		cv::Mat image = cv::imread(filePath);

		if (image.empty()) {
			std::cout << "No such file in current directory" << std::endl;
			continue;
		}

		cv::String imageWindowName = customPath; //Name of the window
		cv::namedWindow(imageWindowName); // Create a window
		cv::imshow(imageWindowName, image); // Show our image inside the created window.

		std::fstream imageDataFile(filePath + ".pdt", std::fstream::out);

		std::vector<unsigned long long> sumsOfColorValues(3, 0);
		imageDataFile << image.rows << "x" << image.cols << std::endl;
		unsigned long long totalValuedPixelsCount = image.rows * image.cols;
		//for (int y = 0; y < image.rows; y++) {
		//	for (int x = 0; x < image.cols; x++) {
		//		cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));
		//		uchar blues = color[0];
		//		uchar greens = color[1];
		//		uchar reds = color[2];

		//		if ((uint)blues >= 50 || (uint)greens >= 50 || (uint)reds >= 50) {
		//			//50 to add track some intensity
		//			sumsOfColorValues[blue] += (uint)blues;
		//			sumsOfColorValues[green] += (uint)greens;
		//			sumsOfColorValues[red] += (uint)reds;
		//		}
		//		else {
		//			totalValuedPixelsCount--;
		//		}
		//		imageDataFile << (uint)reds << " " << (uint)greens << " " << (uint)blues << std::endl;
		//	}
		//}

		// Let's try randomizing x and y for total of pixels over 10
		std::srand(time(NULL));
		unsigned long long totalCheckedPixelsCount = totalValuedPixelsCount / SCALER;
		for (int i = 0; i < totalValuedPixelsCount / SCALER; i++) {
			int x = std::rand() % image.cols;
			int y = std::rand() % image.rows;
			cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));

			uchar blues = color[0];
			uchar greens = color[1];
			uchar reds = color[2];

			if ((uint)blues >= 10 || (uint)greens >= 10 || (uint)reds >= 10 && isNotBackground(blues, greens, reds)) {
				sumsOfColorValues[blue] += (uint)blues;
				sumsOfColorValues[green] += (uint)greens;
				sumsOfColorValues[red] += (uint)reds;
			}
			else {
				totalCheckedPixelsCount--;
			}
		}

		size_t avgBlue = sumsOfColorValues[blue] / totalCheckedPixelsCount;
		size_t avgGreen = sumsOfColorValues[green] / totalCheckedPixelsCount;
		size_t avgRed = sumsOfColorValues[red] / totalCheckedPixelsCount;
		cv::Scalar mainColor(avgBlue, avgGreen, avgRed);
		imageDataFile << avgBlue << " " << avgGreen << " " << avgRed << std::endl;

		imageDataFile.close();

		cv::Mat mainColorImage(image.rows, image.cols, CV_8UC3, mainColor);

		cv::String mainColorWindowName = customPath + " / mainColor"; //Name of the window
		cv::namedWindow(mainColorWindowName); // Create a window
		cv::imshow(mainColorWindowName, mainColorImage); // Show our image inside the created window.

		cv::waitKey(0); // Wait for any keystroke in the window
		cv::destroyWindow(mainColorWindowName); //destroy the created window
		cv::destroyWindow(imageWindowName);
	}
	return 0;
}
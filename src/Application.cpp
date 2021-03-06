#include <opencv2/opencv.hpp> // working with images
#include <iostream> // console input&output
#include <vector> // std::vector
#include <ctime> // time()
#include <cmath> // sqrt, pow
#include <map> // std::map;
#include <utility> // std::pair;
#include <numeric>

enum {
	blue, green, red
};

#define SCALER 50

bool inRange(cv::Vec3b stable, cv::Vec3b floating) {
	double dist = sqrt(pow((uint)stable[blue] - (uint)floating[blue], 2) + \
		pow((uint)stable[green] - (uint)floating[green], 2) + \
		pow((uint)stable[red] - (uint)floating[red], 2));
	return dist <= 128;
}

std::pair < bool, int > vecContainsInRange(std::vector<cv::Vec3b> iterable, cv::Vec3b obj) {
	//cannot get any clue how can i use std::find_if()
	for (int i = 0; i < iterable.size(); i++) {
		if (inRange(iterable[i], obj)) {
			return std::make_pair(true, i);
		}
	}
	return std::make_pair(false, -1);
}

int main(int argc, char** argv) {
	std::string customPath;
	while (1) {
		std::cin >> customPath;
		if (customPath == "quit()") break;
		std::string filePath = "C:\\Users\\User\\Desktop\\TestsCV\\" + customPath;
		cv::Mat image = cv::imread(filePath);

		if (image.empty()) {
			std::cout << "No such file in current directory" << std::endl;
			continue;
		}

		unsigned long long totalValuedPixelsCount = (image.rows) * (image.cols);

		std::srand(time(NULL));
		//some problems with std::map tho
		std::vector<cv::Vec3b> popularColors;
		std::vector<uint> popularColorsEncounters;
		std::vector<std::pair<int, int> > coordinates;
		for (int i = 0; i < totalValuedPixelsCount / SCALER; i++) {
			int x = std::rand() % image.cols;
			int y = std::rand() % image.rows;
			cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x, y));
			if (vecContainsInRange(popularColors, color).first) {
				popularColorsEncounters[vecContainsInRange(popularColors, color).second]++;
			}
			else {
				popularColors.push_back(color);
				popularColorsEncounters.push_back(1);
				coordinates.push_back(std::make_pair(x, y));
			}
		}

		long long sumOfEncounters = std::accumulate(popularColorsEncounters.begin(), popularColorsEncounters.end(), 0);

		for (int i = 0; i < popularColors.size(); i++) {
			if (popularColorsEncounters[i] >= totalValuedPixelsCount / (10 * SCALER)) {
				std::cout << popularColors[i] << " " << popularColorsEncounters[i] << std::endl;
				int _radius = (MAX(image.rows, image.cols) / 4) * popularColorsEncounters[i] / sumOfEncounters;
				cv::circle(image, cv::Point(coordinates[i].first, coordinates[i].second), \
					_radius, cv::Scalar((uint)popularColors[i][0], \
					(uint)popularColors[i][1], (uint)popularColors[i][2]), -1);
				cv::circle(image, cv::Point(coordinates[i].first, coordinates[i].second), \
					_radius, cv::Scalar(0, 0, 0), 3);
			}
		}

		cv::String imageWindowName = customPath; //Name of the window
		cv::namedWindow(imageWindowName); // Create a window
		cv::imshow(imageWindowName, image); // Show our image inside the created window.

		cv::waitKey(0); // Wait for any keystroke in the window
		cv::destroyWindow(imageWindowName);
	}

	return 0;
}
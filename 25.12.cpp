//c/c++ standard libraries
#include <cstdlib>
#include <iostream>
#include <string>

//opencv includes
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>

//namespaces, no more std:: or cv::
using namespace std;
using namespace cv;

bool play = true;
int slider = 0, slider_max = 0, current = 0;
const String filename = "D:/Programs/Ffmpeg/video/2cars.mov";

void on_trackbar(int, void*) {
	current = getTrackbarPos("Frame", "Video Player");
};

int main(int argc, char* argv[]) {

	{
		/*
		if (argc != 2) {
		cout << "\nTo run program enter e.g 'VPlayer video.ext'\nEnter -help for more info\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
		}

		if (argv[1] == "-help") {
		cout << "Help is on the way, call 999\n";
		system("PAUSE");
		exit(EXIT_SUCCESS);
		}
		VideoCapture cap(argv[1]);

		if (!cap.isOpened()) {
		cout << "Error Opening file.\n";
		system("PAUSE");
		exit(EXIT_FAILURE);
		}
		*/
		VideoCapture cap(filename);
		slider_max = cap.get(CV_CAP_PROP_FRAME_COUNT);

		namedWindow("Video Player", WINDOW_NORMAL);
		createTrackbar("Frame", "Video Player", &slider, slider_max, on_trackbar);

		Mat frame;
			while (current <= slider_max) {
				if (current == slider_max)
					play = false;
				if (play) {
					cap.set(CAP_PROP_POS_FRAMES, current - 1);
					cap >> frame;
					imshow("Video Player", frame);
					current += 1;
				}
				char key = waitKey(33);				
				if (key == 32)
					play = !play;
				if (key == 44)
					if (current >= 5) {
						current -= 5;
						cap.set(CAP_PROP_POS_FRAMES, current - 1);
						cap >> frame;
						imshow("Video Player", frame);
					}
					else
						current = 0;
				if (key == 46)
					if ((current + 5) < slider_max) {
						current += 5;
						cap.set(CAP_PROP_POS_FRAMES, current - 1);
						cap >> frame;
						imshow("Video Player", frame);
					}
					else
						current = slider_max;
				setTrackbarPos("Frame", "Video Player", current);
				
			}
	}
	destroyAllWindows();
	system("PAUSE");
	return 0;
}

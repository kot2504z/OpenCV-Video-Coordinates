//c/c++ standard libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <math.h>

//opencv includes
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>

//namespaces, no more std:: or cv::
using namespace std;
using namespace cv;

String filename = "D:/Programs/Ffmpeg/video/2cars.mov";
VideoCapture cap(filename);

CvRect rect;
CvPoint point;
bool play = true, drag = false;
int slider = 0, slider_max = 0, current = 0, total = 0;

void on_trackbar(int, void*) {
	current = getTrackbarPos("Frame", "Video Player");
};

void mouse_click(int event, int x, int y, int flags, void* param) {

	if (event == CV_EVENT_LBUTTONDOWN && !drag) {
		point = cvPoint(x, y);
		drag = !drag;
		cout << x <<" "<< y << endl;
	}

	if (event == CV_EVENT_LBUTTONUP && drag) {
		rect = CvRect(x, y, x-point.x, y-point.y);
		cout << x - point.x <<" "<< y - point.y << endl;
		drag = !drag;
	}	
}

int main(int argc, char* argv[]) {
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
	Mat frame;
	slider_max = cap.get(CV_CAP_PROP_FRAME_COUNT);

	namedWindow("Video Player", WINDOW_NORMAL);
	createTrackbar("Frame", "Video Player", &slider, slider_max, on_trackbar);
	cvSetMouseCallback("Video Player", mouse_click, 0);

	while (total <= slider_max) {
		if (current != total) {
			current = getTrackbarPos("Frame", "Video Player");
			cap.set(CAP_PROP_POS_FRAMES, current);
			total = current;
		}

		char key = waitKey(33);				
		if (key == 32)
			play = !play;		

		if (!play) {				
			total = cap.get(CV_CAP_PROP_POS_FRAMES);
			if (key == 44)
				if (current >= 1) 
					current -= 1;
			if (key == 46)
				if ((current + 1) < slider_max)
					current += 1;
			if (current != cap.get(CV_CAP_PROP_POS_FRAMES)) {
				cap.set(CAP_PROP_POS_FRAMES, current - 1);
				cap >> frame;
				imshow("Video Player", frame);
			}
		}
		if (play) {
			if (total < slider_max) {
				current += 1;
				total += 1;
				cap >> frame;
				imshow("Video Player", frame);
			}
			else
				play = false;
		}			
		setTrackbarPos("Frame", "Video Player", current);
		if (key == 'q')
			break;
	}
	destroyAllWindows();
	system("PAUSE");
	return 0;
}

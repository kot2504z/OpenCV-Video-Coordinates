//c/c++ standard libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <windows.h>

//opencv includes
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>

//namespaces, no more std:: or cv::
using namespace std;
using namespace cv;

//String filename = "D:/Programs/Ffmpeg/video/2cars.mov";
//VideoCapture cap(filename);
Mat frame, draw, rec;

Point pt1, pt2;
bool play = true, drag = false;
int slider = 0, slider_max = 0, current = 0, total = 0;

void on_trackbar(int, void*) {
	current = getTrackbarPos("Frame", "Video Player");
};

void mouse_event(int event, int x, int y, int flags, void* param) {

	if (event == CV_EVENT_LBUTTONDOWN && !drag) {
		pt1 = Point(x, y);
		drag = !drag;
	}

	if (event == CV_EVENT_MOUSEMOVE && drag) {
		draw = frame.clone();
		rectangle (draw, pt1, Point(x,y), CV_RGB(0, 0, 0), 2, 8, 0);
		imshow("Video Player", draw);
	}

	if (event == CV_EVENT_LBUTTONUP && drag) {
		pt2 = Point(x, y);
		if (pt1 != pt2) {
			rectangle(draw, pt1, pt2, CV_RGB(0, 0, 0), 2, 8, 0);
			imshow("Video Player", draw);
		}
		drag = !drag;
	}
	if (event == CV_EVENT_RBUTTONDOWN) {
		draw(Rect(pt1, pt2)).copyTo(rec);
		namedWindow("rec", WINDOW_AUTOSIZE);
		imshow("rec", rec);
	}
	if (event == CV_EVENT_RBUTTONUP) {		
		imshow("Video Player", frame);
		drag = false;
	}
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "\nTo run program enter e.g 'VPlayer video.ext'\nEnter -help for more info and instructions\n";
		exit(EXIT_FAILURE);
	}

	if (argv[1] == "-help") {
		cout << "Video Editor" << endl;
		cout << "to rewind: ',' - 1 frame left, '.' - 1 frame right" << endl;
		cout << "spacebar - play/pause, 'q' - close all windows" << endl;
		cout << "left mouse button + drag - select area" << endl;
		cout << "right mouse button - copy area to new window" << endl;
		exit(EXIT_SUCCESS);
	}
	VideoCapture cap(argv[1]);
	
	if (!cap.isOpened()) {
		cout << "Error Opening file.\n";
		exit(EXIT_FAILURE);
	}
	slider_max = cap.get(CV_CAP_PROP_FRAME_COUNT);

	namedWindow("Video Player", WINDOW_NORMAL);
	createTrackbar("Frame", "Video Player", &slider, slider_max, on_trackbar);
	setMouseCallback("Video Player", mouse_event, 0);
	
	HWND handle = (HWND)cvGetWindowHandle("Video Player");
	while ((total <= slider_max) && IsWindowVisible(handle)) {
		if (current != total) {
			current = getTrackbarPos("Frame", "Video Player");
			cap.set(CAP_PROP_POS_FRAMES, current);
			total = current;
		}

		char key = waitKey(33);				
		if (key == 32) {
			drag = false;
			play = !play;
		}

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
	return 0;
}

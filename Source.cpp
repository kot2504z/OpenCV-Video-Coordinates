//Add here something for OpenCV project
//or not

#include <cstdlib>
#include <iostream>

//Here are OpenCV's includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv; //namespace for opencv

int main(int, char**) {

	// will add a file explorer later, or not.
	char filename[] = "D:/Programs/Ffmpeg/video/2cars.mov";
	VideoCapture cap(filename);
	
	if (!cap.isOpened()) {
		system("PAUSE");
		exit(EXIT_FAILURE);	
	}
	Mat window;
	namedWindow("Video Player", 1);

	for (;;) {
		Mat frame;
		cap >> frame;
		cvtColor(frame, window, CV_BGR2GRAY);
		
		//possible yuv line, will check that later.
		//cvtColor(frame, window, CV_YUV2BGR_YUY2);
		imshow("Video Player", window);

		//always end with exception, will check that later.
		//however, it works. Pathetic video player for now.
		if (waitKey(30) >= 0) 
			break;
	}
	return 0;
}
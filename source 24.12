//c/c++ standard libraries
#include <cstdlib>
#include <iostream>

//opencv includes
#include <opencv2/opencv.hpp>

//namespaces
using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

	//meh, example of read from console video player.
	//its constant player cuz of dev.
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
	char filename[] = "D:/Programs/Ffmpeg/video/2cars.mov";
	Mat frame;
	VideoCapture cap(filename);
	int frames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	namedWindow("Video Player", WINDOW_AUTOSIZE);

	for (int i = 0; i < frames; i++) {
		cap >> frame;
		imshow("Video Player", frame);
		waitKey(33);		
	}
	return 0;
}

#include <custom.h>

using namespace vid;

Video::Video(int s, int, int) {
	s = 0;
	VideoCapture cap(filename);
	slider = s;
	frames = cap.get(CV_CAP_PROP_FRAME_COUNT);
	slider_max = frames;
}

Video::~Video() {
	destroyAllWindows();
}

void Video::create() {
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

		namedWindow("Video Player", WINDOW_NORMAL);
		createTrackbar("Frame", "Video Player", &slider, slider_max, on_trackbar);

		Mat frame;
		for (int i = 0; i < frames; i++) {

			cap >> frame;
			imshow("Video Player", frame);
			waitKey();
		}
	}
}
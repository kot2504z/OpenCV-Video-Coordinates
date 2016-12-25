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

namespace vid {
	class Video {
		int slider, slider_max, frames;
		const String filename = "D:/Programs/Ffmpeg/video/2cars.mov";

	public:
		Video(int = 0, int = 0, int = 0);
		~Video();
		
		void create();
		friend void on_trackbar(int, void*);
	};
}
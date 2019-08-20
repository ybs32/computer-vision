#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	// Open default web camera
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}

	// Declare variables
	Mat frameSrc, frame; // Matrix class for handling image
	vector<vector<Point>> contours; // Multiple contours, contour is a collection of coordinates

	while (cap.read(frameSrc)) {

		// Smoothing (Aperture size is 3)
		medianBlur(frameSrc, frame, 3);

		// Grayscale
		cvtColor(frame, frame, CV_BGR2GRAY);

		/*
		 * Binarization using Otsu's method
		 * THRESH_BINARY: If the threshold is exceeded, the maximum value is set, otherwise it is 0.
		 */
		threshold(frame, frame, 0, 255, THRESH_BINARY | THRESH_OTSU);

		/*
		 * Morphological operations (Opening)
		 * The fourth argument Mat() is structure element (kernel) that the default size is 3x3.
		 * The fifth argument Point(-1, -1), the center of the kernel is used as the anchor.
		 * The sixth argument is the number of reductions and expansions.
		 */
		morphologyEx(frame, frame, MORPH_OPEN, Mat(), Point(-1, -1), 1);

		/*
		 * Detect contours
		 * CV_RETR_LIST: Extract all contours present in the image.
		 * CV_CHAIN_APPROX_NONE: Get all coordinates that make up the contour,
		 * adjacent 2 points exist within 8 neighborhoods.
		 */
		findContours(frame, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		imshow("frame", frameSrc);

		if (waitKey(30) >= 0) break;
	}

	return 0;
}

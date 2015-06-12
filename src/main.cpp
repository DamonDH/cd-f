#include "stdafx.h"
#include "speaker.h"
#include "vision.h"
#include "fingertipdetect.h"
#include "imgtrainer.h"

int main(int argc, char** argv) {
	cout
			<< "< Creating detector, descriptor extractor and descriptor matcher ..."
			<< endl;
	Ptr<ORB> detector = ORB::create();
	Ptr<DescriptorMatcher> descriptorMatcher = getMatcher();
	cout << ">" << endl;
	if (detector.empty() || descriptorMatcher.empty()) {
		cout
				<< "Can not create detector or descriptor exstractor or descriptor matcher of given types"
				<< endl;
	}
	cout << "< Reading the images..." << endl;
	vector<string> billMapping;

	int success = loadRecognitionSet("us", descriptorMatcher, billMapping);
	vector<string>::iterator it = billMapping.begin();
	cout<<"billMapping.size() = "<<billMapping.size()<<endl;

	if (success == 0) {
		cout << "Failed training images, exiting....." << endl;
		return -1;
	}
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "fail to open the cam ..";
		return -1;
	}
	int winTimes(0);
	cv::Mat qureyFrame, mgray_small;
	while (cap.read(qureyFrame)) {
		double t_all = (double) getTickCount();
		//clock_t start = clock();

		float scale_img = (float) (600.f / qureyFrame.rows);
		float scale_font = (float) (2 - scale_img) / 1.4f;

		cv::resize(qureyFrame, mgray_small, Size(320, 240));
		Mat drawImg;
		vector<int> debug_matches(billMapping.size(), 0);
		RecognitionResult result = recognize(mgray_small, true, &drawImg,
				detector, descriptorMatcher, billMapping, true, debug_matches);
		if (result.haswinner == true) {
			if (winTimes > 1) {
				winTimes = 0;
				//AutoSpeak(result.winner);
				cout << "result = " << result.winner << endl;
			}
			winTimes++;
		}
		//namedWindow("Result", WINDOW_NORMAL);
		t_all = ((double) getTickCount() - t_all) * 1000 / getTickFrequency();
		char buff[100];
		sprintf(buff, "%2.1f Fps. @ 320x240", (float) (1000 / t_all));
		string fps_info = buff;
		putText(drawImg, fps_info, Point(10, drawImg.rows - 10),
				FONT_HERSHEY_DUPLEX, scale_font, Scalar(255, 0, 0));
		imshow("coin", drawImg);
		if (waitKey(2) == 27) {
			cout << "Enter ESC to stop it" << endl;
			break;
		}
	}

	return 0;
}

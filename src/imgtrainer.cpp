#include "imgtrainer.h"

int loadRecognitionSet(string name, Ptr<DescriptorMatcher> descriptorMatcher,
		vector<string>& billMapping) {
	//out << "C:\\Users\HD\\Documents\\Visual Studio 2010\\Projects\\darwinwallet\\res\\raw" << name << ".yaml";

	//Ptr<ORB> detector = getTrainerDetector();
	//Ptr<FeatureDetector> detector2 = getQueryDetector();

	//system("dir C:\\Users\\HD\\Documents\\Visual Studio 2010\\Projects\\drawwinwallettest\\drawwinwallettest\\test  /B > C:\\Users\\HD\\Documents\\Visual Studio 2010\\Projects\\drawwinwallettest\\drawwinwallettest\\test.txt");
	ifstream fReadFName("./imagelist.txt");
	string oneline;
	vector<Mat> desc_set;
	Mat desc;
	vector<KeyPoint> kpts;
	Ptr<ORB> orb = ORB::create();

	while (getline(fReadFName, oneline)) {
		billMapping.push_back(oneline);
		string imgpath = "./template/" + oneline;
		//imgpath.erase(imgpath.end() - 1);
		//cout<<imgpath<<endl;
		Mat img = imread(imgpath);
		if (img.empty()) {
			cout << "Can not read tempalte images.." << endl;
			return 0;
		}

		orb->detectAndCompute(img, noArray(), kpts, desc);
		desc_set.push_back(desc);
		//billMapping.push_back(type);
	}

	//billMapping.push_back(type);

	descriptorMatcher->add(desc_set);
	descriptorMatcher->train();

	//FileStorage fileobj = FileStorage("/tmp/outty", FileStorage::WRITE);
	//descriptorMatcher->write(fileobj);

	return 1;
}

double fps(clock_t clock1, clock_t clock2) {
	double diffticks = clock2 - clock1;
	double fps = CLOCKS_PER_SEC / diffticks;
	return fps;
}

void imshowMany(const std::string& _winName, const vector<Mat>& _imgs) {
	int nImg = (int) _imgs.size();
	Mat dispImg;
	int size;
	int x, y;

	// w - Maximum number of images in a row
	// h - Maximum number of images in a column
	int w, h;
	// scale - How much we have to resize the image
	float scale;
	int max;

	if (nImg <= 0) {
		printf("Number of arguments too small....\n");
		return;
	} else if (nImg > 12) {
		printf("Number of arguments too large....\n");
		return;
	}

	else if (nImg == 1) {
		w = h = 1;
		size = 300;
	} else if (nImg == 2) {
		w = 2;
		h = 1;
		size = 300;
	} else if (nImg == 3 || nImg == 4) {
		w = 2;
		h = 2;
		size = 300;
	} else if (nImg == 5 || nImg == 6) {
		w = 3;
		h = 2;
		size = 200;
	} else if (nImg == 7 || nImg == 8) {
		w = 4;
		h = 2;
		size = 200;
	} else {
		w = 4;
		h = 3;
		size = 150;
	}

	dispImg.create(Size(100 + size * w, 60 + size * h), CV_8UC3);
	//Mat dispImg(100 + size*w, 60 + size*h, CV_8UC3);

	for (int i = 0, m = 20, n = 20; i < nImg; i++, m += (20 + size)) {
		x = _imgs[i].cols;
		y = _imgs[i].rows;

		max = (x > y) ? x : y;
		scale = (float) ((float) max / size);

		if (i % w == 0 && m != 20) {
			m = 20;
			n += 20 + size;
		}

		Mat imgROI = dispImg(Rect(m, n, (int) (x / scale), (int) (y / scale)));
		resize(_imgs[i], imgROI, Size((int) (x / scale), (int) (y / scale)));
	}

	namedWindow(_winName);
	imshow(_winName, dispImg);
}


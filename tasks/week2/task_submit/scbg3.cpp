#include <opencv2/opencv.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
using namespace cv;
using namespace std;
Mat toView(Mat ori)
{
	Mat res;
	resize(ori, res, Size(800, 800 * ori.rows / ori.cols));
	return res;
}
void imshowv(const char* name, Mat img)
{
	imshow(name, toView(img));
}
double gs(int x, double miu, double sigma)
{
	return 1.0 / sqrt(2 * M_PI) * exp(-(x - miu) * (x - miu) / sigma / sigma);
}

float rate = 0.1;
int main(int argc, char* argv[])
{
	VideoCapture cap(argv[1]);
	Mat frame, gray;
	Mat tmp, mius, sigmas, omigas;
	auto start = chrono::steady_clock::now();
	while (1)
	{
		cap >> frame;
		if (frame.empty()) break;
		resize(frame, frame, Size(frame.cols / 6, frame.rows / 6));
		cvtColor(frame, gray, CV_BGR2GRAY);
		if (mius.empty())
		{
			sigmas.create(gray.size(), CV_32FC3);
			omigas.create(gray.size(), CV_32FC3);
			mius.create(gray.size(), CV_32FC3);
			mius = Scalar(43.5, 127.5, 213);
			sigmas = Scalar(127.5, 127.5, 127.5);
			omigas = Scalar(1.0 / 3, 1.0 / 3, 1.0 / 3);
			gray.convertTo(gray, CV_32F);
		}
		else
		{
			auto itg = gray.begin<uchar>();
			auto it = mius.begin<Vec3f>();
			auto ita = sigmas.begin<Vec3f>();
			auto ito = omigas.begin<Vec3f>();
			auto ited = gray.end<uchar>();
			for (;itg != ited; itg++, it++, ita++, ito++) // for each pixel
			{
				int bst = -1; double bstp = -1e8, p;
				for (int i = 0; i < 3; i++) //select best model
				{
					if (abs(*itg - (*it)[i]) > 2.5 * (*ita)[i]) continue;
					else
					{
						p = gs(*itg, (*it)[i], (*ita)[i]);
						if (p  > bstp)
						{
							bst = i;
							bstp = p;
						}
					}
				}
				if (bst == -1) //no matched model
				{
					int wrs = -1; float wrso = -1e5;
					for (int i = 0; i < 3; i++)
					{
						if ((*ito)[i] < wrso)
						{
							wrs = i; wrso = (*ito)[i];
						}
					}
					//WARN!!!here is simplifed
					(*it)[wrs] = (*itg);
					(*ita)[wrs] = 128.0;
					//WARN!!!
				}
				else //matched, update omiga, miu, and sigma
				{
					float ws = 0;
					for (int i = 0; i < 3; i++)
					{
						(*ito)[i] = (i == bst ? (1 - rate) : rate) * (*ito)[i];
						ws += (*ito)[i];
					}
					*ito /= ws;
					float rou = (float)(rate * bstp);
					(*it)[bst] = (1 - rou) * (*it)[bst] + rou * (*itg);
					(*ita)[bst] = (1 - rou) * (*ita)[bst] + rou * (*itg - (*it)[bst]) * (*itg - (*it)[bst]);
				}
			}

		}
		//imshowv("Gray", gray);
		//if (waitKey(33) != 255) break;
	}
    auto it = mius.begin<Vec3f>();
    auto ita = sigmas.begin<Vec3f>();
    auto ito = omigas.begin<Vec3f>();
	auto ited = mius.end<Vec3f>();
	Mat res(gray.size(), gray.type());
	auto itr = res.begin<uchar>();
	for (; it != ited; it++, ita++, ito++, itr++)
	{
		int bst = -1; float bstv = -1e8, v;
		for (int i = 0; i < 3; i++)
		{
			v = (*ito)[i] / (*ita)[i];
			if (v > bstv)
			{
				bst = i; bstv = v;
			}
		}
		*itr = (uchar)(*it)[bst];
	}
	auto ed = chrono::steady_clock::now();
	vector<Mat> channels;
	split(mius, channels);
	Mat miu = channels[0];
	miu.convertTo(miu, CV_8U);
	imshowv("Miu", miu);
	cout << "Time Consume: " << chrono::duration_cast<chrono::milliseconds>(ed - start).count() / 1000.0 << "s" << endl;
	//cout << res << endl;
	imshowv("Result", res);
	//cout << mius << endl << sigmas << endl << omigas << endl;
	waitKey(0);
	return 0;
}

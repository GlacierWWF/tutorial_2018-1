#include "perspective.hpp"
#include <numeric>
struct PPTRestore::Ximpl
{
	enum imageStyle { normal, leanToRight, leanToLeft };
	int cannyThreshold;
	Mat srcImage, dstImage;
	Mat midImage, edgeDetect;
	Mat afterEnhance;
	vector<Point> resultPointsByEdge;
	vector<Point> resultPointsByContours;
	vector<Vec4i> lines;

	vector<Point> axisSort(const vector<Vec4i>& lines);
	vector<Point> pointsFilter(const vector<Point>& candidates);
	vector<Point> findCrossPoint(const vector<Vec4i>& lines);	

	vector<Point> axisSort(const vector<vector<Point>>& contours);
	vector<Point> findCrossPoint(const vector<vector<Point>>& contours);

	void doEdgeDetect();
	void doFindcontours();
	void doAffineTransform(Mat& image_pspct);

};

// PPTRestore::PPTRestore() : ator=(PPTRestore other)
// {pImpl(new Ximpl()){}
 PPTRestore::PPTRestore() : pImpl(new Ximpl()){}
// PPTRestore& PPTRestore::oper
// 	std::swap(other.pImpl, this->pImpl);
// 	return *this;
// }
 PPTRestore::~PPTRestore()
 {
 	delete pImpl;
 	pImpl = nullptr;
 }


vector<Point> PPTRestore::Ximpl::pointsFilter(const vector<Point>& candidate)
{
	vector<Point> candidates(candidate);
	vector<Point> filter(candidate);
	for (auto i = candidates.begin(); i != candidates.end();)
	for (auto j = filter.begin(); j != filter.end(); ++j)
	{
		if (abs((*i).x - (*j).x) < 5 && abs((*i).y - (*j).y) < 5 && abs((*i).x - (*j).x) > 0 && abs((*i).y - (*j).y) > 0)
			i = filter.erase(i);
		else
			++i;
	}
	return filter;
}
vector<Point> PPTRestore::Ximpl::axisSort(const vector<Vec4i>& lines)
{
	vector<Point> points(lines.size() * 2);
	for (size_t i = 0; i < lines.size(); ++i)
	{
		points[i * 2].x = lines[i][0];
		points[i * 2].y = lines[i][1];
		points[i * 2 + 1].x = lines[i][2];
		points[i * 2 + 1].y = lines[i][3];
	}
	points = this->pointsFilter(points);

	sort(points.begin(), points.end(), CmpDistanceToZero());
	return points;
}
void PPTRestore::Ximpl::doEdgeDetect()
{
	this->cannyThreshold = 80;
	float factor = 2.5;
	const int maxLinesNum = 10;
	Canny(this->srcImage, this->midImage, this->cannyThreshold, this->cannyThreshold * factor);
	threshold(this->midImage, this->midImage, 128, 255, THRESH_BINARY);
	cvtColor(this->midImage, this->edgeDetect, CV_GRAY2RGB);
	HoughLinesP(this->midImage, this->lines, 1, CV_PI / 180, 50, 100, 100);

	while (this->lines.size() >= 30)
	{
		this->cannyThreshold += 2;
		Canny(this->srcImage, this->midImage, this->cannyThreshold, this->cannyThreshold * factor);
		threshold(this->midImage, this->midImage, 128, 255, THRESH_BINARY);
		cvtColor(this->midImage, this->edgeDetect, CV_GRAY2RGB);
		HoughLinesP(this->midImage, this->lines, 1, CV_PI / 180, 50, 100, 100);
	}
	//cout << "cannyThreshold1:" << this->cannyThreshold << endl;

	Canny(this->srcImage, this->midImage, this->cannyThreshold, this->cannyThreshold * factor);
	threshold(this->midImage, this->midImage, 128, 255, THRESH_BINARY);
	cvtColor(this->midImage, this->edgeDetect, CV_GRAY2RGB);
	HoughLinesP(this->midImage, this->lines, 1, CV_PI / 180, 50, 100, 100);

	const int imageRow = this->midImage.rows;
	const int imageCol = this->midImage.cols;


	lines.erase(remove_if(lines.begin(), lines.end(), IsCloseToEdge()), lines.end());

	for (size_t i = 0; i < this->lines.size(); i++)
	{
		Vec4i l = this->lines[i];
		line(this->edgeDetect, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, CV_AA);
	}


	this->findCrossPoint(this->lines);
	
}
vector<Point> PPTRestore::Ximpl::findCrossPoint(const vector<Vec4i>& lines)
{
	int rightTopFlag = 0;
	int leftDownFlag = 0;
	int diagLength = 0;
	vector<Point> temp = this->axisSort(lines);
	Point leftTop, rightDown;
	vector<Point> rightTop(temp.size());
	vector<Point> leftDown(temp.size());

	leftTop.x = temp[0].x;
	leftTop.y = temp[0].y;
	rightDown.x = temp[temp.size() - 1].x;
	rightDown.y = temp[temp.size() - 1].y;
	for (auto & i : temp)
	if (i.x > leftTop.x && i.y < rightDown.y)
		rightTop.push_back(i);
	for (auto & i : temp)
	if (i.y > leftTop.y && i.x < rightDown.x)
		leftDown.push_back(i);

	diagLength = (leftTop.x - rightDown.x) * (leftTop.x - rightDown.x) + (leftTop.y - rightDown.y) * (leftTop.y - rightDown.y);
	rightTop.erase(remove(rightTop.begin(), rightTop.end(), Point(0, 0)), rightTop.end());
	leftDown.erase(remove(leftDown.begin(), leftDown.end(), Point(0, 0)), leftDown.end());
	for (auto i = rightTop.begin(); i != rightTop.end();)
	{
		if (((*i).x - leftTop.x) * ((*i).x - leftTop.x) + ((*i).y - leftTop.y) * ((*i).y - leftTop.y) < diagLength / 8)
			i = rightTop.erase(i);
		else
			++i;
	}



	int maxDistance = (rightTop[0].x - leftDown[0].x) * (rightTop[0].x - leftDown[0].x) + (rightTop[0].y - leftDown[0].y) * (rightTop[0].y - leftDown[0].y);

	for (size_t i = 0; i < rightTop.size(); ++i)
	for (size_t j = 0; j < leftDown.size(); ++j)
	if ((rightTop[i].x - leftDown[j].x) * (rightTop[i].x - leftDown[j].x) + (rightTop[i].y - leftDown[j].y) * (rightTop[i].y - leftDown[j].y) > maxDistance)
	{
		maxDistance = (rightTop[i].x - leftDown[j].x) * (rightTop[i].x - leftDown[j].x) + (rightTop[i].y - leftDown[j].y) * (rightTop[i].y - leftDown[j].y);
		rightTopFlag = i;
		leftDownFlag = j;
	}

	/*cout << rightTop[rightTopFlag].x << " " << rightTop[rightTopFlag].y << endl;
	cout << leftDown[leftDownFlag].x << " " << leftDown[leftDownFlag].y << endl;*/

	/*for (auto i : rightTop)
	cout << i.x << " " << i.y << endl;*/

	/*for (auto i : leftdown)
	cout << i.x << " " << i.y << endl;*/

	this->resultPointsByEdge.push_back(leftTop);
	this->resultPointsByEdge.push_back(rightTop[rightTopFlag]);
	this->resultPointsByEdge.push_back(leftDown[leftDownFlag]);
	this->resultPointsByEdge.push_back(rightDown);
	return this->resultPointsByEdge;
}



void PPTRestore::Ximpl::doAffineTransform(Mat& image_pspct)
{
	this->doEdgeDetect();
	Point2f _srcTriangle[4];
	Point2f _dstTriangle[4];
	vector<Point2f>srcTriangle(_srcTriangle, _srcTriangle + 4);
	vector<Point2f>dstTriangle(_dstTriangle, _dstTriangle + 4);

	const int leftTopX = (this->resultPointsByEdge[0].x + this->resultPointsByEdge[0].x) / 2;
	const int leftTopY = (this->resultPointsByEdge[0].y + this->resultPointsByEdge[0].y) / 2;
	const int rightTopX = (this->resultPointsByEdge[1].x + this->resultPointsByEdge[1].x) / 2;
	const int rightTopY = (this->resultPointsByEdge[1].y + this->resultPointsByEdge[1].y) / 2;
	const int leftDownX = (this->resultPointsByEdge[2].x + this->resultPointsByEdge[2].x) / 2;
	const int leftDownY = (this->resultPointsByEdge[2].y + this->resultPointsByEdge[2].y) / 2;
	const int rightDownX = (this->resultPointsByEdge[3].x + this->resultPointsByEdge[3].x) / 2;
	const int rightDownY = (this->resultPointsByEdge[3].y + this->resultPointsByEdge[3].y) / 2;

	//cout << leftTopX << " " << leftTopY << endl;
	//cout << rightTopX << " " << rightTopY << endl;
	//cout << leftDownX << " " << leftDownY << endl;
	//cout << rightDownX << " " << rightDownY << endl;


	int newWidth = 0;
	int newHeight = 0;

	newWidth = sqrt((leftTopX - rightTopX) * (leftTopX - rightTopX) + (leftTopY - rightTopY) * (leftTopY - rightTopY));
	newHeight = sqrt((leftTopX - leftDownX) * (leftTopX - leftDownX) + (leftTopY - leftDownY) * (leftTopY - leftDownY));

	this->dstImage = Mat::zeros(newHeight, newWidth, this->srcImage.type());

	srcTriangle[0] = Point2f(leftTopX, leftTopY);
	srcTriangle[1] = Point2f(rightTopX, rightTopY);
	srcTriangle[2] = Point2f(leftDownX, leftDownY);
	srcTriangle[3] = Point2f(rightDownX, rightDownY);

	dstTriangle[0] = Point2f(0, 0);
	dstTriangle[1] = Point2f(newWidth, 0);
	dstTriangle[2] = Point2f(0, newHeight);
	dstTriangle[3] = Point2f(newWidth, newHeight);


	Mat m1 = Mat(srcTriangle);
	Mat m2 = Mat(dstTriangle);
	Mat status;
	Mat h = findHomography(m1, m2, status, 0, 3);
	perspectiveTransform(srcTriangle, dstTriangle, h);
	warpPerspective(this->srcImage, this->dstImage, h, this->dstImage.size());
	imshow("Perspective Transformed", this->dstImage);
    image_pspct = this->dstImage.clone();
}

void PPTRestore::imageRestoreAndEnhance(Mat& full_image, Mat& image_pspct)
{
	pImpl->srcImage = full_image.clone();
	this->pImpl->doAffineTransform(image_pspct);
}
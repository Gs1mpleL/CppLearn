#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

bool recursive_bezier(const std::vector<cv::Point2f> &control_points, std::vector<cv::Point2f> &points1, std::vector<cv::Point2f> &points2, float t, cv::Mat &window){
    int size;
    size = points1.size();

    if(size == 1){
        window.at<cv::Vec3b>(points1[0].y, points1[0].x)[1] = 255;//设置该点的绿通道为255
        points2 = control_points;
        points1.clear();//结束计算后记得初始化容器
        return true;
    }
    for(int i = 0; i < size - 1; i++)
        points2.push_back((1 - t) * points1[i] + t * points1[i + 1]);
    points1.clear();
    return false;
}


void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window)
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    int size = control_points.size();
    std::vector<cv::Point2f> points1 = control_points, points2;
    bool flag = true, bflag;
    for (double t = 0.0; t <= 1.0; t += 0.001)
    {
        bflag = false;
        while(!bflag){
            if(flag)
                bflag = recursive_bezier(control_points, points1, points2, t, window);
            else
                bflag = recursive_bezier(control_points, points2, points1, t, window);
            flag = !flag;
        }
    }
}


int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 4) 
        {
            naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}

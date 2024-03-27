#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
int main(){
	cout<<"Hello word"<<endl;
	// 读取图片
    cv::Mat image = cv::imread("../example.jpg");
	
	// 检查图像是否成功读取
    if(image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return 1;
    }

    // 打印图像尺寸
    std::cout << "Image size: " << image.cols << "x" << image.rows << std::endl;

    return 0;
}

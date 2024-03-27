#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace std;

int main() {
    // 创建 ONNX Runtime 环境
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "MyExampleEnv");

    // 创建会话选项
    Ort::SessionOptions session_options;

    // 加载模型
    const std::string model_path = "../resnet18.onnx"; // 修改为你的模型路径
    Ort::Session session(env, model_path.c_str(), session_options);

    std::cout << "Model loaded successfully." << std::endl;
    
    // 获取模型元数据
    Ort::AllocatorWithDefaultOptions allocator;
    Ort::Session& session_ref = session;


    // 打印输入输出节点数量
    size_t num_input_nodes = session_ref.GetInputCount();
    size_t num_output_nodes = session_ref.GetOutputCount();
    std::cout << "Number of input nodes: " << num_input_nodes << std::endl;
    std::cout << "Number of output nodes: " << num_output_nodes << std::endl;

    // 打印输入节点名字
    std::shared_ptr<char> inputName = std::move(session.GetInputNameAllocated(0, allocator));
    std::vector<char*> inputNodeNames;
    inputNodeNames.push_back(inputName.get());
    std::cout << "输入节点名称:" << inputName << "\n";

    // 打印输入节点形状
    Ort::TypeInfo inputTypeInfo = session.GetInputTypeInfo(0);
    auto input_tensor_info = inputTypeInfo.GetTensorTypeAndShapeInfo();
    ONNXTensorElementDataType inputNodeDataType = input_tensor_info.GetElementType();
    std::vector<int64_t> inputTensorShape = input_tensor_info.GetShape();
    std::cout << "输入节点shape:";
    for (int i = 0; i<inputTensorShape.size(); i++)
    {
        std::cout << inputTensorShape[i]<<" ";
    }
    std::cout << "\n";

    //打印输出节点名字
    std::shared_ptr<char> outputName = std::move(session.GetOutputNameAllocated(0, allocator));
    std::vector<char*> outputNodeNames;
    outputNodeNames.push_back(outputName.get());
    std::cout << "输出节点名称:" << outputName << "\n";
 
    // 打印输出节点形状
    Ort::TypeInfo type_info_output0(nullptr);
    type_info_output0 = session.GetOutputTypeInfo(0);  //output0
    auto tensor_info_output0 = type_info_output0.GetTensorTypeAndShapeInfo();
    ONNXTensorElementDataType outputNodeDataType = tensor_info_output0.GetElementType();
    std::vector<int64_t> outputTensorShape = tensor_info_output0.GetShape();
    std::cout << "输出节点shape:";
    for (int i = 0; i<outputTensorShape.size(); i++)
    {
        std::cout << outputTensorShape[i]<<" ";
    }
    std::cout << "\n";

    // 读取图片
    cv::Mat image = cv::imread("../car1.jpeg");
	// 检查图像是否成功读取
    if(image.empty()) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return 1;
    }
    else{
        std::cerr << "Success to load image." << std::endl;
    };
    // 打印图像尺寸
    std::cout << "Image size: " << image.cols << "x" << image.rows << std::endl;
    // 对图像resize并重新打印形状
    cv::Mat imgBGRresize;
    cv::resize(image, imgBGRresize, cv::Size(224, 224), cv::InterpolationFlags::INTER_CUBIC);
    std::cout << "imgBGRresize size: " << imgBGRresize.cols << "x" << imgBGRresize.rows << std::endl;
    // BGR 2 RGB
    cv::Mat imgRGBresize = imgBGRresize;
    cvtColor(imgBGRresize, imgRGBresize, cv::COLOR_BGR2RGB);
    // 转Float的Tensor(对应ToTensor)
    cv::Mat model_input;
    imgRGBresize.convertTo(model_input, CV_32F, 1.0 / 255);  // 8位图像转float32浮点，归一化
    //分离通道进行HWC->CHW和标准化（对应Norm和permute）
    cv::Mat channels[3]; 
	cv::split(model_input, channels);
	std::vector<float> inputTensorValues; //用vector来保存这个输入Tensor
	float mean[] = { 0.485f, 0.456f, 0.406f };
	float std_val[] = { 0.229f, 0.224f, 0.225f };
	for (int i = 0; i < model_input.channels(); i++)	//标准化ImageNet
	{
		channels[i] -= mean[i];  // mean均值
		channels[i] /= std_val[i];   // std方差
	}
	for (int i = 0; i < model_input.channels(); i++)  //HWC->CHW
	{
		std::vector<float> data = std::vector<float>(channels[i].reshape(1, model_input.cols * model_input.rows));
		inputTensorValues.insert(inputTensorValues.end(), data.begin(), data.end());
	}
    // 创建内存信息
    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeDefault);
	// 把输入数据从vector中弄到inputTensors中，并添加输入张量到向量
    vector<Ort::Value> inputTensors;
	inputTensors.push_back(Ort::Value::CreateTensor<float>(memoryInfo, inputTensorValues.data(), inputTensorValues.size(), inputTensorShape.data(), inputTensorShape.size()));

    // 模型推理
    const char* in_names[] = { "input.1"};  
    const char* const* input_names = in_names;
    const char* out_names[] = { "191"};
    const char* const* output_names = out_names;
    
    std::vector<Ort::Value> outputTensor = session.Run(Ort::RunOptions{nullptr}, input_names, inputTensors.data(), 1, output_names, 1);   // 开始推理
    // Run(run_options, input_names, input_values, input_count, output_names, output_values.data(), output_count);
    std::cout << "outputTensor size:" << outputTensor.size() << std::endl;
    
    // 读取label.txt
    // 读取文件
    std::ifstream file("../label.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    // 读取文件中的内容并保存到 C++ 向量中
    std::vector<std::string> labelVector;
    std::string line;
    while (std::getline(file, line)) {
        labelVector.push_back(line);
    }

    // 输出结果
    if (!outputTensor.empty()) {  
        const Ort::Value& outputValue = outputTensor[0]; // 注意索引是从 0 开始的  
        // 检查 outputValue 是否包含张量  
        if (outputValue.IsTensor()) {  
            // 获取张量的元数据  
            const Ort::TensorTypeAndShapeInfo& info = outputValue.GetTensorTypeAndShapeInfo();  
            std::cout << "Tensor Type: " << info.GetElementType() << std::endl;  
            std::cout << "Shape: ";  
            std::vector<int64_t> shape = info.GetShape();  
            for (size_t i = 0; i < shape.size(); ++i) {  
                std::cout << shape[i] << " ";  
            }
            std::cout << std::endl;  

            //打印结果
            // 获取指向张量数据的const指针  
            const float* floatData = outputValue.GetTensorData<float>();  
            if (floatData != nullptr) {  
                // 计算张量中的元素总数  
                size_t elementCount = 1;  
                for (const auto& dim : shape) {  
                    elementCount *= dim;  
                }
                // 打印张量中的所有数据  
                std::cout << "Tensor Data:" << std::endl; 
                float max_conf = floatData[0];
                int class_index = 0;
                for (size_t i = 0; i < elementCount; ++i) {  
                    std::cout << floatData[i] << " ";
                    if (floatData[i] > max_conf){
                        max_conf = floatData[i];
                        class_index = i;
                    }
                    if ((i + 1) % 100 == 0) { // 每行打印10个元素  
                        std::cout << std::endl;  
                    }  
                } 
                std::cout << std::endl; // 打印完所有数据后换行
                std::cout << "result: cls_idx=" << class_index << ", confidence=" << max_conf << ", classes:"<< labelVector[class_index] << endl; 
            }
            //完成打印
        }
    }    
    return 0;
}
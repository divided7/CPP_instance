#include <onnxruntime_cxx_api.h>
#include <iostream>

int main() {
    // 创建 ONNX Runtime 环境
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "MyExampleEnv");

    // 创建会话选项
    Ort::SessionOptions session_options;

    // 加载模型
    const std::string model_path = "../mnist.onnx"; // 修改为你的模型路径
    Ort::Session session(env, model_path.c_str(), session_options);

    // 打印模型信息
    std::cout << "Model loaded successfully." << std::endl;
    
    return 0;
}

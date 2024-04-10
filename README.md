# CPP_instance

## OpenCV
首先安装opencv，在linux环境：
```bash
sudo apt update
sudo apt install libopencv-dev
sudo apt install build-essential
```
通过以上代码实现opencv的安装（在本地ubuntu上测试了opencv4.5.4, 4.5.5没问题, 在服务器上测试4.5.3有问题，不确定是环境还是版本问题）、基本C++编译器（例如gcc）的安装。


```bash
cd Opencv
mkdir build && cd build
cmake .. && make
```
此时在build文件夹内生成可执行文件hello,通过`./hello`运行

```bash
./hello
```
此时会打印图片的形状：
```bash
kiko@kiko-u:~/Desktop/hello/build$ ./hello
>>> Hello word
>>> Image size: 1366x96
```

## OnnxRuntime Load model
```bash
cd load_onnx
mkdir build && cd build
cmake .. && make
```
此时在build文件夹内生成可执行文件onnxruntime_example,通过`./onnxruntime_example`运行
```bash
./onnxruntime_example
```

此时会输出结果：
```bash
kiko@kiko-u:~/Desktop/load_onnx/build$ ./onnxruntime_example 
>>> Model loaded successfully.
```

## OnnxRuntime ImageNet预训练的Resnet18.onnx模型推理
```bash
cd infer_onnx
mkdir build && cd build
cmake .. && make
```

此时在build文件夹内生成可执行文件onnxruntime_example,通过`./onnxruntime_example`运行
```bash
./onnxruntime_example
```

此时会输出结果：
```bash
>>> Model loaded successfully.
>>> Number of input nodes: 1
>>> Number of output nodes: 1
>>> 输入节点名称:input.1
>>> 输入节点shape:1 3 224 224 
>>> 输出节点名称:191
>>> 输出节点shape:1 1000 
>>> ...
>>> ...
>>> result: cls_idx=817, confidence=12.453, classes:sports car
```
该模型暂未使用softmax对类别进行logit操作所以给出的置信度不是真正意义的置信度，但用于分类已够用。

## YOLOv8 Onnxruntime
```bash
cd YOLOv8-ONNXRuntime-CPP
mkdir build && cd build
cmake .. && make
```
这里如果只是报warning可以忽略；此时生成可执行文件：`Yolov8OnnxRuntimeCPPInference`

注：此代码相较于原yolov8项目修改了cmakelists，并将main.cpp中的模式由分类改为了检测；编译完成后在build文件夹内会有image文件夹，将图片放入image文件夹下，再执行代码：
```bash
./Yolov8OnnxRuntimeCPPInference
```
在有GUI界面的ubuntu下会直接弹出检测结果的图片窗口。其实这里给出的图片框并不准确，查阅issues应该是库不兼容的问题，可能需要检查一下box相关的代码或者更换库版本尝试，不过本项目主要以跑通各种模型为准，后续再修复该bug。

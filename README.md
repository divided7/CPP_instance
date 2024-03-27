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

## OnnxRuntime
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

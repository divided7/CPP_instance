# CPP_instance

首先安装opencv，在linux环境：
```bash
sudo apt update
sudo apt install libopencv-dev
sudo apt install build-essential
```
通过以上代码实现opencv的安装、基本C++编译器（例如gcc）的安装。


```bash
cd hello
rm -rf build
mkdir build
cd build
cmake .. && make
```
此时在build文件夹内生成可执行文件hello，复制一张样图sample.jpg到build（或者说复制到hello可执行文件）路径下

```bash
./hello
```
此时会打印图片的形状

## Platform: Ubuntu16.04
## Install OpenVINO: [OpenVINO开发必备知识点——环境搭建](https://www.toutiao.com/i6813281706506715651/)
## InsightFace OpenVINO Model:

- 链接:https://pan.baidu.com/s/1mtsMXN8889nBRaNRo9VlKQ  密码:h77z
- 解压并保存至model目录下

## FaceDetector OpenVINO Model:

- 下载如下模型，并保存至model目录下

```
wget https://download.01.org/opencv/2020/openvinotoolkit/2020.1/open_model_zoo/models_bin/1/face-detection-retail-0005/FP32/face-detection-retail-0005.xml
wget https://download.01.org/opencv/2020/openvinotoolkit/2020.1/open_model_zoo/models_bin/1/face-detection-retail-0005/FP32/face-detection-retail-0005.bin
```

## Usage:

```
source /opt/intel/openvino/setupvars.sh
cd face-openvino
mkdir build
cd build
cmake ..
make
cd ..
# 人脸特征提取demo
./bin/feature_extract model/model-0000.xml CPU image/test.jpg 
# 人脸检测demo
./bin/face_detect model/face-detection-retail-0005.xml CPU image/test.jpg
```

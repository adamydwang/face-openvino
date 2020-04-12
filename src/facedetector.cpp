#include <facedetector.hpp>

FaceDetector::FaceDetector(const std::string& model, const std::string& dev, int width, int height, float threshold)
  : BaseFace(model, dev, width, height), m_threshold(threshold) {
}

FaceDetector::~FaceDetector() {}

int FaceDetector::init() {
  return BaseFace::init();
}


int FaceDetector::process(cv::Mat& image, std::vector<cv::Rect>& faces) {
  int width = image.cols;
  int height = image.rows;
  BaseFace::preprocess(image);
  std::vector<float> raws;
  if (BaseFace::process(image, raws) < 0) {
    return -1;
  }
  //output shape: [1,1,N,7]
  //[image_id, predicted_label, confidence, x_min, y_min, x_max, y_max]
  //refer to https://docs.openvinotoolkit.org/2019_R2/_intel_models_face_detection_retail_0005_description_face_detection_retail_0005.html
  if (raws.size() % 7) {
    return -2;
  }
  for (int i = 0; i < raws.size(); i += 7) {
    if (raws[i+2] < m_threshold) {
      continue;
    }
    int x = raws[i+3] * width;
    int y = raws[i+4] * height;
    int w = (raws[i+5] - raws[i+3]) * width;
    int h = (raws[i+6] - raws[i+4]) * height;
    faces.emplace_back(x, y, w, h);
  }
  return 0;
}


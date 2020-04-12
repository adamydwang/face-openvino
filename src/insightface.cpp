#include <insightface.hpp>

InsightFace::InsightFace(const std::string& model, const std::string& dev, int width, int height) 
  : BaseFace(model, dev, width, height) {
}

InsightFace::~InsightFace() {}

int InsightFace::init() {
  return BaseFace::init();
}


int InsightFace::process(cv::Mat& image, std::vector<float>& feature) {
  BaseFace::preprocess(image);
  return BaseFace::process(image, feature);
}


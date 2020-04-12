#ifndef __FACEDETECTOR_HPP__
#define __FACEDETECTOR_HPP__

#include <baseface.hpp>

class FaceDetector : public BaseFace {
public:
  FaceDetector(const std::string& model, const std::string& dev, int width=300, int height=300, float threhold=0.8);
  ~FaceDetector();
  int init();
  int process(cv::Mat& image, std::vector<cv::Rect>& faces);

private:
  float m_threshold;
};

#endif

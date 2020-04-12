#ifndef __INSIGHTFACE_HPP__
#define __INSIGHTFACE_HPP__

#include <baseface.hpp>

class InsightFace : public BaseFace {
public:
  InsightFace(const std::string& model, const std::string& dev, int width=112, int height=112);
  ~InsightFace();
  int init();
  int process(cv::Mat& image, std::vector<float>& feature);
};

#endif

#ifndef __BASEFACE_HPP__
#define __BASEFACE_HPP__

#include <inference_engine.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <iostream>

class BaseFace {
public:
  BaseFace(const std::string& model, const std::string& dev, int width=112, int height=112);
  ~BaseFace();
  int init();
  int process(cv::Mat& image, std::vector<float>& res);
  void preprocess(cv::Mat& image);

  InferenceEngine::InferRequest m_ireq;
  std::string                   m_model;
  std::string                   m_device;
  std::string                   m_input_name;
  std::string                   m_output_name;
  int                           m_width;
  int                           m_height;
};

#endif

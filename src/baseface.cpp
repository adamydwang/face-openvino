#include <baseface.hpp>

BaseFace::BaseFace(const std::string& model, const std::string& dev, int width, int height) {
  m_model   = model;
  m_device  = dev;
  m_width   = width;
  m_height  = height;
}

BaseFace::~BaseFace() {}

int BaseFace::init() {
  try {
    InferenceEngine::Core ie;
    InferenceEngine::CNNNetwork network = ie.ReadNetwork(m_model);
    network.setBatchSize(1);
    InferenceEngine::InputsDataMap input_info(network.getInputsInfo());
    if (input_info.size() != 1) {
      std::cerr << "BaseFace model only accept one input" << std::endl;
      return -3;
    }
    //input image parameters init
    auto input = *input_info.begin();
    m_input_name = input.first;
    std::cout << "Input: " << m_input_name << std::endl;
    input.second->setPrecision(InferenceEngine::Precision::U8);
    input.second->setLayout(InferenceEngine::Layout::NCHW);
    //load model to device
    InferenceEngine::ExecutableNetwork executable_network = ie.LoadNetwork(network, m_device);
    //create inference request
    m_ireq = executable_network.CreateInferRequest();
    //output feature init
    InferenceEngine::OutputsDataMap output_info(network.getOutputsInfo());
    if (output_info.size() != 1) {
      std::cerr << "BaseFace model should only has one output" << std::endl;
      return -4;
    }
    m_output_name = output_info.begin()->first;
    output_info.begin()->second->setPrecision(InferenceEngine::Precision::FP32);
    std::cout << "Output: " << m_output_name << std::endl;
  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return -1;
  } catch (...) {
    std::cerr << "Unknown exception happend..." << std::endl;
    return -2;
  }
  std::cout << "BaseFace Initialize successfully!" << std::endl;
  return 0;
}


int BaseFace::process(cv::Mat& image, std::vector<float>& res) {
  m_ireq.Infer();
  InferenceEngine::Blob::Ptr output_blob = m_ireq.GetBlob(m_output_name);
  const int dims = output_blob->size();
  res.resize(dims);
  memcpy(res.data(), output_blob->buffer(), dims * sizeof(float));
  return 0;
}

void BaseFace::preprocess(cv::Mat& image) {
  cv::Mat resized;  
  cv::resize(image, resized, cv::Size(m_width, m_height));
  InferenceEngine::Blob::Ptr blob = m_ireq.GetBlob(m_input_name);
  unsigned char* ptr = (unsigned char*)blob->buffer();
  for (int c = 0; c < 3; ++c) {
    for (int y = 0; y < m_height; ++y) {
      for (int x = 0; x < m_width; ++x) {
        *(ptr++) = resized.at<cv::Vec3b>(y, x)[c];
      }
    }
  }
}

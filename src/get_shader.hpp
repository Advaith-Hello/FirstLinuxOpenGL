#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>



std::string get_shader(const std::string& filename)
{
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening shader: "
      << filename << std::endl;
  }

  std::ostringstream ss;
  ss << file.rdbuf();

  return ss.str();
}


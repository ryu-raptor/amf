#include "ResourceFiler.hpp"
#include <iostream>

int main(int argc, char const* argv[])
{
  if (argc != 2) {
    return -1;
  }

  otoge2019::ResourceFiler rf((std::string(argv[1])));
  std::cout << rf.get("root", "ResourceDirectory") << std::endl;

  return 0;
}

#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace otoge2019 {
  class ResourceFiler {
    private:
      std::shared_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> dictionary;
      std::string lockedCategory;

      void processFile(std::string resourcefilepath);

    public:
      ResourceFiler(std::string resourcefilepath);
      void append(std::string resourcefilepath);
      std::string get(std::string category, std::string key);
      void lockCategory(std::string);
      void unlockCategory();
      std::string get(std::string key);
  };
}

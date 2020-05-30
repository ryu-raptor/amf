#include "ResourceFiler.hpp"
#include <iostream>
#include <regex>
#include <ios>
#include <fstream>

namespace otoge2019 {
  void ResourceFiler::processFile(std::string resourcefilepath)
  {
    std::ifstream stream(resourcefilepath);
    if (stream.fail()) {
      throw std::ios_base::failure("ResourceFiler: リソースファイルの読み込みに失敗しました");
    }
    // 行で読み込む
    std::string line;
    std::string currentCategory;
    std::regex category_pattern(R"(\[(.+)\])");
    std::regex entry_pattern(R"((\w+) : (.+))");
    std::regex variable_pattern(R"(\$\{(\w+) : (.+)\})");

    while (std::getline(stream, line)) {
      std::smatch matches;
      // 正規表現マッチ
      // \[.+\]
      // カテゴリ作成
      if (std::regex_match(line, matches, category_pattern)) {
        auto categoryName = (matches.begin() + 1)->str();
        currentCategory = categoryName;
        std::cout << currentCategory << std::endl;
      }
      // .+ : .+
      else if (std::regex_match(line, matches, entry_pattern)) {
        // マッチしているので2つのサブマッチは必ずある
        auto key = (matches.begin() + 1)->str();
        auto value = (matches.begin() + 2)->str();
        // 変数置換
        std::smatch vmatches;
        //std::cout << std::regex_search(value, vmatches, variable_pattern, std::regex_constants::format_first_only) << std::endl;

        while (std::regex_search(value, vmatches, variable_pattern, std::regex_constants::format_first_only)) {
          std::cout << "vmatched" << std::endl;
          // category, keyを取り出す
          auto vcategory = (vmatches.begin() + 1)->str();
          auto vkey = (vmatches.begin() + 2)->str();
          // 値を取得
          auto replee = get(vcategory, vkey);
          // 置き換え
          value = std::regex_replace(value, variable_pattern, replee, std::regex_constants::format_first_only);
        }

        std::cout << key << ", " << value << std::endl;
        (*dictionary)[currentCategory][key] = value;
      }
    }
  }

  ResourceFiler::ResourceFiler(std::string resourcefilepath) {
    // 辞書を作成
    dictionary.reset(new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>());

    processFile(resourcefilepath);

    lockedCategory = "";
  }

  void ResourceFiler::append(std::string resourcefilepath)
  {
    processFile(resourcefilepath);
  }

  std::string ResourceFiler::get(std::string category, std::string key)
  {
    try {
      return dictionary->at(category).at(key);
    } catch (...) {
      throw std::out_of_range("(" + category + "," + key + ") : Not found.");
    }
  }

  void ResourceFiler::lockCategory(std::string category)
  {
    lockedCategory = category;
  }

  void ResourceFiler::unlockCategory()
  {
    lockedCategory = "";
  }

  std::string ResourceFiler::get(std::string key)
  {
    if (lockedCategory == "") {
      throw "lockCategoryを使ってからにしてください";
    }
    return dictionary->at(lockedCategory).at(key);
  }
} // namespace otoge2019

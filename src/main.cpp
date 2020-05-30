#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include <cmath>

int main()
{
  sf::Music music;
  if (!music.openFromFile("orchestral.ogg")) {
    return -1;
  }

  // tempo = beats per second
  // beat : x/y拍子のx
  float rhythm = 4;
  float tempo = 120;
  float starttime;
  float stagecounter;
  float sectiontempo = tempo / rhythm;
  float speed = 1 / (sectiontempo * 60);

  music.play();

  while (music.getStatus() == sf::Music::Playing) {
    auto offset = music.getPlayingOffset();
    auto musiccounter = offset.asSeconds();
    stagecounter = musiccounter - starttime;
    // 小節番号
    auto sectionno = (int)(std::floor(stagecounter / speed));
    std::cout << "\r小節番号: " << sectionno << std::flush;
  }

  return 0;
}


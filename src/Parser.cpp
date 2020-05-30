#include <iostream>
#include <vector>
#include <fstream>

namespace Otoge2019
{
  namespace Chart
  {
    class Parser
    {
    private:
    public:
      struct Node
      {
      };

      struct CommandNode : Node
      {
        std::string command;
        std::vector<std::string> arguments;
      };

      struct BlockNode : Node
      {
        std::vector<NoteStreamNode> part;
      };

      struct NoteStreamNode : Node
      {
        std::string noteStream;
        
        void append(NoteStreamNode appendee);
      };

      Node parseLine()
      {}
    };
  }
}


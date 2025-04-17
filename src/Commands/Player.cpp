
#include "MKTG.hpp"

namespace MKTG::Command
{

// static std::array<std::string, 2> parseArgs(std::string args)
// {
//     std::vector<std::string> vec;
//     size_t pos = 0;

//     while ((pos = args.find_first_of(' ')) != std::string::npos) {
//         vec.push_back(args.substr(0, pos));
//     }

//     ;
//     array[0] = line.substr(0, pos);
//     if (pos != std::string::npos) {
//         while (pos < line.size() && line[pos] == ' ') {
//             pos++;
//         }
//         array[1] = line.substr(pos);
//     }

//     return array;
// }

Result Player::run(MKTG::Generator &gen, std::string args)
{
    std::cout << "not implemented yet :(" << std::endl;
    return Result::CONTINUE;
}

std::string Player::getCommand() const
{
    return COMMAND_PLAYER;
}

} // namespace MKTG::Command


#include "App.hpp"
#include <QApplication>

namespace GNCApp
{

static void execExcel(std::string path)
{
    Logic::loadExcelFile(path);
    Logic::createWinnerSoloImage();
}

static void execUrl(std::string url)
{
    Logic::loadWebFile(url);
    Logic::createWinnerDuoImage();
}

static void execOutput(std::string path)
{
    Data::Winner::getInstance()->setOutputDir(path);
}

static int parseArgs(int ac, char **av)
{
    argparse::ArgumentParser args(GNCAPP_NAME, GNCAPP_VERSION, argparse::default_arguments::all, false);

    args.add_argument("-o", "--output")
        .help("Set the given output as the directory to where the content will be generated")
        .nargs(1)
        .action(&execOutput);
    auto &group = args.add_mutually_exclusive_group();
    group.add_argument("-e", "--excel")
         .help("Load excel path and create the solo Top 8 image")
         .nargs(1)
         .action(&execExcel);
    group.add_argument("-u", "--url")
         .help("Load and download content given by the url and create the duo Top 8 image")
         .nargs(1)
         .action(&execUrl);

    try {
        args.parse_args(ac, av);
    } catch (const std::exception& err) {
        Error() << err.what() << GGL::end;
        std::cerr << args << GGL::end;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

}

int main(int ac, char **av)
{
    QApplication app(ac, av);
    GNCApp::Data::loadData();
    int ret = GNCApp::parseArgs(ac, av);
    GNCApp::Data::unloadData();
    return ret;
}

#include "../Headers/FileManager.h"

std::string readWholeFile(const char *const path) {
    std::ifstream stream(path);
    std::string text(std::istreambuf_iterator<char>(stream), {});
    stream.close();
    return text;
}
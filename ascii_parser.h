//
// Created by Данил on 24.06.2023.
//

#ifndef ASCIIVIDEOPLAYER_ASCII_PARSER_H
#define ASCIIVIDEOPLAYER_ASCII_PARSER_H

#include <string>
#include <utility>
#include <vector>
#include <QString>

extern "C"
{
    #include <libavformat/avformat.h>
}

class AsciiParser {
public:
    struct AsciiFrame {
        int h, w;
        QString str;
        AsciiFrame(int h, int w);
    };

    std::string file_name;
    std::vector<AVPacket*> frames = {nullptr};
    int shrink = 5;
    int duration = 0;
    int fps = 1;

    void start();

    explicit AsciiParser(std::string file_name);

    AsciiFrame get_frame(int i);

private:
    AVCodecContext *codec_context;

    const std::string alphabet = " .,:;ox%#@";

    int open_file(AVFormatContext** format_context, const char *file_name);

    void start_parsing(const std::string &file_name);
};

#endif //ASCIIVIDEOPLAYER_ASCII_PARSER_H

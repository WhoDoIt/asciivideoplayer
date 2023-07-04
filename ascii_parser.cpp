//
// Created by Данил on 24.06.2023.
//

#include "ascii_parser.h"
#include <string>
#include <utility>
#include <vector>
extern "C"
{
#include <libavformat/avformat.h>
}


AsciiParser::AsciiFrame::AsciiFrame(int h, int w) : h(h), w(w) {
    str.resize(h * (w + 1));
}

AsciiParser::AsciiParser(std::string file_name) : file_name(file_name) {
}

int AsciiParser::open_file(AVFormatContext** format_context, const char *file_name) {
    *format_context = avformat_alloc_context();
    if (!*format_context) {
        av_log(nullptr, AV_LOG_ERROR, "Couldn't allocate memory for the input");
        return EXIT_FAILURE;
    }
    avformat_open_input(format_context, file_name, nullptr, nullptr);
    avformat_find_stream_info(*format_context,  nullptr);
    return EXIT_SUCCESS;
}

void AsciiParser::start_parsing(const std::string &file_name) {
    AVFormatContext *format_context = nullptr;
    open_file(&format_context, file_name.c_str());

    for (int i = 0; i < format_context->nb_streams; i += 1) {
        AVCodecParameters *codec_parameters = format_context->streams[i]->codecpar;
        if (codec_parameters->codec_type != AVMEDIA_TYPE_VIDEO) {
            continue;
        }
        fps = av_q2d(format_context->streams[i]->avg_frame_rate);

        AVCodec *codec = avcodec_find_decoder(codec_parameters->codec_id);
        codec_context = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codec_context, codec_parameters);
        avcodec_open2(codec_context, codec, nullptr);

        AVPacket* packet = av_packet_alloc();

        while (av_read_frame(format_context, packet) >= 0) {
            if (packet->stream_index != format_context->streams[i]->index)
                continue;
            frames.push_back(packet);
            duration += 1;
            packet = av_packet_alloc();
        }

        return;
    }
}

AsciiParser::AsciiFrame AsciiParser::get_frame(int i) {
    if (i >= frames.size())
        return {0, 0};
    if (frames[i] == nullptr)
        return {0, 0};

    AVFrame *frame = av_frame_alloc();
    avcodec_send_packet(codec_context, frames[i]);
    avcodec_receive_frame(codec_context, frame);

    int real_height = (frame->height + shrink - 1) / shrink;
    int real_width = (frame->width + shrink - 1) / shrink;

    AsciiFrame gray_frame = AsciiFrame(real_height, real_width);

    int shrink_sum[real_height][real_width];
    memset(shrink_sum, 0, sizeof(shrink_sum));

    for (int i = 0; i < frame->height; i += 1) {
        for (int j = 0; j < frame->width; j += 1) {
            shrink_sum[i / shrink][j / shrink] += *(frame->data[0] + i * frame->width + j);
        }
    }
    int border = 256 / alphabet.size();
    int counter = 0;
    for (int i = 0; i < real_height; i += 1) {
        for (int j = 0; j < real_width; j += 1) {
            gray_frame.str[counter++] = alphabet[shrink_sum[i][j] / (shrink * shrink * border)];
        }
        gray_frame.str[counter++] = '\n';
    }
    return gray_frame;
}

void AsciiParser::start() {
    start_parsing(file_name);
}

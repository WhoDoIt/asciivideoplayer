#include <iostream>
#include <chrono>
#include <thread>
extern "C"
{
    #include <libavformat/avformat.h>
}

int shrink = 15;
char char_colors[] = " .,:;ox%#@";

int open_input_media_file(AVFormatContext** format_context, const char *file_name) {
    *format_context = avformat_alloc_context();
    if (!*format_context) {
        av_log(NULL, AV_LOG_ERROR, "Couldn't allocate memory for the input");
        return EXIT_FAILURE;
    }
    avformat_open_input(format_context, file_name, NULL, NULL);
    avformat_find_stream_info(*format_context,  NULL);
    return EXIT_SUCCESS;
}

void print_gray_frame(AVFrame *frame) {
    int real_height = (frame->height + shrink - 1) / shrink;
    int real_width = (frame->width + shrink - 1) / shrink;
    int **gray_frame = new int*[real_height];
    for (int i = 0; i < real_height; i += 1) {
        gray_frame[i] = new int[real_width];
        for (int j = 0; j < real_width; j += 1) {
            gray_frame[i][j] = 0;
        }
    }
    for (int i = 0; i < frame->height; i += 1) {
        for (int j = 0; j < frame->width; j += 1) {
            gray_frame[i / shrink][j / shrink] += *(frame->data[0] + i * frame->width + j);
        }
    }
    int border = 256 / 10;
    std::system("clear");
    for (int i = 0; i < real_height; i += 1) {
        for (int j = 0; j < real_width; j += 1) {
            printf("%c", char_colors[gray_frame[i][j] / (shrink * shrink * border)]);
        }
        printf("\n");
    }
    fflush(stdout);
}

int main(int arg_count, char* args[]) {
    AVFormatContext *format_context = NULL;
    open_input_media_file(&format_context, args[1]);
    for (int i = 0; i < format_context->nb_streams; i += 1) {
        AVCodecParameters *codec_parameters = format_context->streams[i]->codecpar;
        if (codec_parameters->codec_type != AVMEDIA_TYPE_VIDEO) {
            continue;
        }
        AVCodec *codec = avcodec_find_decoder(codec_parameters->codec_id);
        AVCodecContext *codec_context = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codec_context, codec_parameters);
        avcodec_open2(codec_context, codec, NULL);

        AVPacket* packet = av_packet_alloc();
        AVFrame* frame = av_frame_alloc();

        while (av_read_frame(format_context, packet) >= 0) {
            if (packet->stream_index != format_context->streams[i]->index)
                continue;
            avcodec_send_packet(codec_context, packet);
            avcodec_receive_frame(codec_context, frame);
            print_gray_frame(frame);

            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 25));
        }

        return EXIT_SUCCESS;
    }

    av_log(NULL, AV_LOG_ERROR, "Couldn't find video stream in file");
}

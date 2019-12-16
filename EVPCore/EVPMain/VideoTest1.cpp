#include <stdio.h>

extern "C"  
{  
#include <libavformat/avformat.h>  
}; 

int main()
{
    printf("Hello World\n");

    char * inputFile = "/Users/yuqiaomiao/Video/1280_720.mp4";
    char * outputFile = "/Users/yuqiaomiao/Video/1280_720__miaomiao.mp4";

    av_register_all();

    AVFormatContext * formatCtx = NULL;
    int ret = avformat_open_input(&formatCtx, inputFile, 0, 0);
    if(ret){
        return -1;
    }

    ret = avformat_find_stream_info(formatCtx, 0);
    if(ret){
        return -1;
    }

    printf("===========Input Information==========\n");
    av_dump_format(formatCtx, 0, inputFile, 0);
    printf("======================================\n");

    AVFormatContext * outFormatCtx = NULL;
    avformat_alloc_output_context2(&outFormatCtx, NULL, NULL, outputFile);



    for (int i=0;i<formatCtx->nb_streams;i++) {
        AVStream * inStream = formatCtx->streams[i];
        AVStream * outStream = avformat_new_stream(outFormatCtx, inStream->codec->codec);

        avcodec_copy_context(outStream->codec, inStream->codec);

        
    }

    if (avio_open(&outFormatCtx->pb, outputFile, AVIO_FLAG_WRITE) < 0) {
        printf( "Could not open output file '%s'", outputFile);
    }

    if (avformat_write_header(outFormatCtx, NULL) < 0) {
        printf( "Error occurred when opening output file\n");
    }

    printf("==========Output Information==========\n");
    av_dump_format(outFormatCtx, 0, outputFile, 1);
    printf("======================================\n");

    AVPacket pkt;
    while (av_read_frame(formatCtx, &pkt) >= 0)
    {
        pkt.pts = av_rescale_q_rnd(pkt.pts, formatCtx->streams[pkt.stream_index]->time_base, outFormatCtx->streams[pkt.stream_index]->time_base, AV_ROUND_NEAR_INF);
        pkt.dts = av_rescale_q_rnd(pkt.dts, formatCtx->streams[pkt.stream_index]->time_base, outFormatCtx->streams[pkt.stream_index]->time_base, AV_ROUND_NEAR_INF);
        pkt.duration = av_rescale_q(pkt.duration,formatCtx->streams[pkt.stream_index]->time_base, outFormatCtx->streams[pkt.stream_index]->time_base);
        
        av_interleaved_write_frame(outFormatCtx, &pkt);
        av_free_packet(&pkt);
        // printf("PTS:%lld\n", pkt.pts);
    }

    av_write_trailer(outFormatCtx);

    avio_close(outFormatCtx->pb);

    return 0;
}
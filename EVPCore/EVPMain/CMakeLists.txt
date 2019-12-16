include_directories (../)
include_directories (./)

include_directories (../3rdpart/mac/ffmpeg-4.1.4/include)

set(CMAKE_EXE_LINKER_FLAGS
    "-framework AudioToolbox -framework CoreGraphics -framework CoreMedia -framework Cocoa -framework VideoToolbox -framework AVFoundation -framework Security -framework CoreFoundation -framework CoreVideo -framework OpenGL -framework AppKit -framework CoreImage"
)

add_executable(
    EVPMain
    VideoTest1.cpp
    )

target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libavcodec.a)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libavformat.a)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libavfilter.a)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libavdevice.a)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libavutil.a)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libswresample.a)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/ffmpeg-4.1.4/lib/libswscale.a)
target_link_libraries (EVPMain bz2)
target_link_libraries (EVPMain z)
target_link_libraries (EVPMain lzma)
target_link_libraries (EVPMain iconv)
target_link_libraries (EVPMain ${CMAKE_SOURCE_DIR}/3rdpart/mac/x264/lib/libx264.a)
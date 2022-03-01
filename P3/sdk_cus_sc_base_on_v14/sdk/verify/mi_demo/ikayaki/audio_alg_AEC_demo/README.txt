audio_alg_AEC_demo使用说明:

（1）编译：（开发平台上运行）
    1.进入mi_demo/source目录，如：cd /Home/voli.wu/alkaid/sdk/verify/mi_demo/source
    2.make audio_alg_AEC_demo
    3.生成可执行文件在sdk/verify/mi_demo/out/demo/app目录，如：cd /Home/voli.wu/alkaid/sdk/verify/mi_demo/out/demo/app
    4.生成可执行文件：
        prog_audio_alg_AEC_demo
（2）运行：
    如果源代码宏 #define IN_PARAMETER 0
        ./prog_audio_alg_AEC_demo [Output files and paths]
    如果源代码宏 #define IN_PARAMETER 1
        ./prog_audio_alg_AEC_demo  [Enter files1 and paths] [Enter files2 and paths]  [Output files and paths]

    例如：
        ./prog_audio_alg_AEC_demo  ./output.wav

注：
    (1)在sdk/verify/mi_demo/source/audio_alg_AEC_demo有音频文件用于测试
    (2)audio_alg_AED_demo/audio_alg_APC_demo/audio_alg_APC_ANR_demo/audio_alg_APC_EQ_demo/audio_alg_APC_AGC_demo/audio_alg_SSL_demo/audio_alg_BF_demo/audio_alg_SRC_demo 编译、运行方法类似。

cmake_minimum_required (VERSION 3.20)

project (Miriyaki-XT
    VERSION 1.0.0
    LANGUAGES C CXX
)

add_subdirectory (dpf)

include_directories (
    source/
    resource/
)

set (SRC_CORE
    source/cEnvelope.cpp
    source/cFilter.cpp
    source/cGlobals.cpp
    source/cGlobFilter.cpp
    source/cLFO.cpp
    source/cModulation.cpp
    source/cOscillator.cpp
    source/cParameter.cpp
    source/cVoice.cpp
    source/cWaveform.cpp
    resource/MirWavetableData.cpp
)

set (SRC_PRESETS
    source/presets.cpp
    source/presets0.cpp
)

dpf_add_plugin (${PROJECT_NAME}
    TARGETS vst2 vst3 lv2 clap
    FILES_DSP
        source/mirsynth.cpp
        source/mirsynthDPF.cpp
        source/mirsynthproc.cpp
        ${SRC_CORE}
        ${SRC_PRESETS}
    FILES_COMMON
        source/functions.cpp
        source/modulationConstants.cpp
)

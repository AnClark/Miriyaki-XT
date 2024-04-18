#include "mirsynth.h"

void MirSynth::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints = kParameterIsAutomatable;

    // Fallback to classic VST 2.4 param range (0.0 ~ 1.0), to fit with Cetone's own param handlers.
    parameter.ranges.min = 0.0f;
    parameter.ranges.max = 1.0f;
    parameter.ranges.def = getParameter(index);

    // Must set parameter.symbol, this is the unique ID of each parameter.
    // If not set, you can neither save presets nor reset to factory default, in VST3 and CLAP!
    char buff[256];
    getParameterName(index, buff);
    parameter.symbol = String(buff).replace(' ', '_').replace('.', '_');
    parameter.name = String(buff);

#if 0
    switch (index) {
    case pClipState:
    case pGlideState:
        parameter.hints |= kParameterIsBoolean;
        break;
    }
#endif
}

float MirSynth::getParameterValue(uint32_t index) const
{
	return this->getParameter(index);
}

void MirSynth::setParameterValue(uint32_t index, float value)
{
	this->setParameter(index, value);
}

void MirSynth::activate()
{
	this->resume();
}

void MirSynth::run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount)
{
	this->processEvents(midiEvents, midiEventCount);
	this->processReplacing((float**) inputs, outputs, frames);
}

void MirSynth::bufferSizeChanged(int newBufferSize)
{
	this->setBlockSize(newBufferSize);
}

void MirSynth::sampleRateChanged(double newSampleRate)
{
	this->setSampleRate(newSampleRate);
}

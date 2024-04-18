// Trieda

#ifndef __mirsynth__
#define __mirsynth__
#include "cVoice.h"
#include "cOscillator.h"
#include "cLFO.h"
#include "cModulation.h"
#include "cGlobals.h"
#include "DistrhoPlugin.hpp"
//#include "../vst2.x/audioeffectx.h"
//#include "cMirEditor.h"
#include "cGlobFilter.h"

//------------------------------------------------------------------------------------------
// MirSynthProgram
//------------------------------------------------------------------------------------------
class MirSynthProgram
{
friend class MirSynth;
public:
	MirSynthProgram ();
	~MirSynthProgram () {}

private:
	float params[kNumParams];
	char name[kVstMaxProgNameLen+1];
};

//------------------------------------------------------------------------------------------
// VstXSynth
//------------------------------------------------------------------------------------------
class MirSynth : public DISTRHO::Plugin
{
public:
	// ------------------------------------------------------------------------
	// Constructor / Destructor

	MirSynth ();
	~MirSynth ();

	// ------------------------------------------------------------------------
	// DISTRHO Plugin interface

	// ---------------------------------------
	// Information

	/**
		Get the plugin label.@n
		This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
	*/
	const char* getLabel() const noexcept override
	{
		return DISTRHO_PLUGIN_NAME;
	}

	/**
		Get an extensive comment/description about the plugin.@n
		Optional, returns nothing by default.
	*/
	const char* getDescription() const override
	{
		return "A subtractive VST synth";
	}

	/**
		Get the plugin author/maker.
	*/
	const char* getMaker() const noexcept override
	{
		return DISTRHO_PLUGIN_BRAND;
	}

	/**
		Get the plugin license (a single line of text or a URL).@n
		For commercial plugins this should return some short copyright information.
	*/
	const char* getLicense() const noexcept override
	{
		return "GPLv3";
	}

	/**
		Get the plugin version, in hexadecimal.
		@see d_version()
	*/
	uint32_t getVersion() const noexcept override
	{
		return d_version(1, 0, 0);
	}

	/**
		Get the plugin unique Id.@n
		This value is used by LADSPA, DSSI and VST plugin formats.
		@see d_cconst()
	*/
	int64_t getUniqueId() const noexcept override
	{
		return d_cconst('t', 's', 't', '2');
	}

	// ---------------------------------------
	// Init

	void initParameter(uint32_t index, Parameter& parameter) override;

	// ---------------------------------------
	// Internal data

	float getParameterValue(uint32_t index) const override;
	void  setParameterValue(uint32_t index, float value) override;

	// ---------------------------------------
	// Audio/MIDI Processing

	void activate() override;
	void run(const float** inputs, float** outputs, uint32_t frames, const MidiEvent* midiEvents, uint32_t midiEventCount) override;

	// ---------------------------------------
	// Callbacks

	void bufferSizeChanged(int newBufferSize);
	void sampleRateChanged(double newSampleRate) override;

	// ------------------------------------------------------------------------
	// Former VST 2.4 Plugin interfaces.
	// DPF will call them on demand.

	virtual void processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames);
	//virtual VstInt32 processEvents (VstEvents* events);
	virtual VstInt32 processEvents(const DISTRHO::MidiEvent* events, uint32_t eventCount);	// Apply DPF MIDI events instead

	// TODO: Implement factory program support!
	virtual void setProgram (VstInt32 program);
	virtual void setProgramName (const char* name);	// Use const char* to suppress "ISO C++ forbids converting a string constant to 'char*'" warning
	virtual void getProgramName (char* name);
	virtual bool getProgramNameIndexed (VstInt32 category, VstInt32 index, char* text);

	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index) const;
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);

	virtual void setSampleRate (float sampleRate);
	virtual void setBlockSize (VstInt32 blockSize);
	virtual void resume();
	
	//virtual bool getOutputProperties (VstInt32 index, VstPinProperties* properties);	// Not used by DPF
		
	virtual bool getEffectName (char* name);
	virtual bool getVendorString (char* text);
	virtual bool getProductString (char* text);
	[[maybe_unused]] virtual VstInt32 getVendorVersion ();
	[[maybe_unused]] virtual VstInt32 canDo (char* text);

	[[maybe_unused]] virtual VstInt32 getNumMidiInputChannels ();
	[[maybe_unused]] virtual VstInt32 getNumMidiOutputChannels ();


	// ------------------------------------------------------------------------
	// Preset loaders

	void defaultPresets();
	void defaultPresets2();
	void defaultPresets3();
	/*void defaultPresets4();
	void defaultPresets5();
	void defaultPresets6();
	void defaultPresets7();
	void defaultPresets8();
	void defaultPresets9();
	void defaultPresets10();*/

	// ------------------------------------------------------------------------
	// Synth parameter controllers

	void setOctave(VstInt32 oscId, float value);
	void setCoarse(VstInt32 oscId, float value);
	void setFine(VstInt32 oscId, float value);
	void setOscLevel(VstInt32 oscId, float value);
	void setOscPan(VstInt32 oscId, float value);
	void setOscSync(VstInt32 oscId, float value);
	void setOscWaveform(VstInt32 oscId, float value);

	void setEnvAttack(VstInt32 envId, float value);
	void setEnvDecay(VstInt32 envId, float value);
	void setEnvSustain(VstInt32 envId, float value);
	void setEnvTime(VstInt32 envId, float value);
	void setEnvRelease(VstInt32 envId, float value);

	void setLfoRange(VstInt32 lfoId, float value);
	void setLfoRate(VstInt32 lfoId, float value);
	void turnOnLfoRateInterpolation(VstInt32 lfoId);

	void setLfoPhaseShift(VstInt32 lfoId, float value);
	void setLfoDelay(VstInt32 lfoId, float value);
	void setLfoFade(VstInt32 lfoId, float value);
	void setLfoWaveform(VstInt32 oscId, float value);

	void setFilterCutoff(VstInt32 oscId, float value);
	void setFilterQ(VstInt32 oscId, float value);
	void setFilterKeyFollow(VstInt32 oscId, float value);
	void setFilterMix(VstInt32 oscId, float value);
	void setFilterType(VstInt32 oscId, float value);
	void setFilterRouting(float value);
	void setModSrc(VstInt32 index, float value);
	void setModDst(VstInt32 index, float value);
	void setModAmt(VstInt32 index, float value);


	
private:

	cGlobals *globals;

	cVoice* voices[MAX_POLYPHONY];
#if 0	// AnClark MOD: I prefer fixed size of out buffers, as there're only 2 channels!
	float *out_buffer;
	float *voice_buffer;
#else
	float out_buffer[2];
	float voice_buffer[2];
#endif
	cLFO *lfo[4];
	cGlobFilter *filter[2];

	MirSynthProgram* programs;
	VstInt32 channelPrograms[16];

	VstInt32 curProgram;	// Seems like a global VST 2.4 variable provided by Steinberg (?)

	VstInt32 playingCount;

	[[maybe_unused]] void initProcess ();
	//void fillProgram (VstInt32 channel, VstInt32 prg, MidiProgramName* mpn); // Not really used by DPF
};

#endif

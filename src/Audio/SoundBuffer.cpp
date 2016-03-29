/*
************************************
* Copyright (C) 2016 ByteForge
* SoundBuffer.cpp
************************************
*/

#include "SoundBuffer.hpp"
#include "../Exception.hpp"
#include <fstream>
using namespace anvil;

//WAV FILE FORMAT
/**
 * Struct that holds the RIFF data of the Wave file.
 * The RIFF data is the meta data information that holds,
 * the ID, size and format of the wave file
 */
struct RIFF_Header 
{
	char chunkID[4];
	long chunkSize;//size not including chunkSize or chunkID
	char format[4];
};

/**
 * Struct to hold fmt subchunk data for WAVE files.
 */
struct WAVE_Format 
{
	char subChunkID[4];
	long subChunkSize;
	short audioFormat;
	short numChannels;
	long sampleRate;
	long byteRate;
	short blockAlign;
	short bitsPerSample;
};

/**
 * Struct to hold the data of the wave file
 */
struct WAVE_Data {
	char subChunkID[4]; //should contain the word data
	long subChunk2Size; //Stores the size of the data block
};
//END WAV FILE FORMAT


SoundBuffer::SoundBuffer() : m_buffer(0)
{
    alGenBuffers(1,&m_buffer);
}

SoundBuffer::~SoundBuffer()
{
    if(m_buffer)
        alDeleteBuffers(1,&m_buffer);
}

bool SoundBuffer::Load(const std::string & path)
{
	std::ifstream fin;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	uint8_t* data;

	fin.open(path, std::ios::binary);
	if (fin.fail())
	{
		return false;
	}
		

	fin.read(reinterpret_cast<char*>(&riff_header), sizeof(RIFF_Header));
	if (std::string(riff_header.chunkID) != "RIFF"&&std::string(riff_header.format) != "WAVE")
		throw AnvilException("Invalid .wav file header: " + path, __FILE__, __LINE__);

	fin.read(reinterpret_cast<char*>(&wave_format), sizeof(WAVE_Format));
	if(std::string(wave_format.subChunkID)!="fmt ")
		throw AnvilException("Invalid .wav file format chunk: " + path, __FILE__, __LINE__);

	if (wave_format.subChunkSize > 16)
		fin.seekg(sizeof(short), std::ios::cur);

	//Read in the the last byte of data before the sound file
	fin.read(reinterpret_cast<char*>(&wave_data), sizeof(WAVE_Data));
	//check for data tag in memory
	if (std::string(wave_data.subChunkID) != "data");
		throw AnvilException("Invalid .wav file data chunk: " + path, __FILE__, __LINE__);

	//Allocate memory for data
	data = new uint8_t[wave_data.subChunk2Size];

	// Read in the sound data into the soundData variable
	if (!fin.read(reinterpret_cast<char*>(data), wave_data.subChunk2Size))
		throw AnvilException("Error loading wave data into chunk: " + path, __FILE__, __LINE__);

	//Now we set the variables that we passed in with the
	//data from the structs
	m_size = wave_data.subChunk2Size;
	m_frequency = wave_format.sampleRate;
	//The format is worked out by looking at the number of
	//channels and the bits per sample.
	if (wave_format.numChannels == 1) 
	{
		if (wave_format.bitsPerSample == 8)
			m_format = AL_FORMAT_MONO8;
		else if (wave_format.bitsPerSample == 16)
			m_format = AL_FORMAT_MONO16;
	}
	else if (wave_format.numChannels == 2) 
	{
		if (wave_format.bitsPerSample == 8)
			m_format = AL_FORMAT_STEREO8;
		else if (wave_format.bitsPerSample == 16)
			m_format = AL_FORMAT_STEREO16;
	}

	alBufferData(m_buffer, m_format, data, m_size, m_frequency);
	fin.close();
	return true;
}

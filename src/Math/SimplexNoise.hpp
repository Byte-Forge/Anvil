/* Copyright (c) 2007-2012 Eliot Eshelman
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

namespace hpse
{
	class SimplexNoise
	{
	public:
		// Multi-octave Simplex noise
		// For each octave, a higher frequency/lower amplitude function will be added to the original.
		// The higher the persistence [0-1], the more of each succeeding octave will be added.
		static float octave_noise_2d(const int octaves, const float persistence, const float scale, const float x, const float y);
		static float octave_noise_3d(const int octaves, const float persistence, const float scale, const float x, const float y, const float z);
		static float octave_noise_4d(const int octaves, const float persistence, const float scale, const float x, const float y, const float z, const float w);

		// Scaled Multi-octave Simplex noise
		// The result will be between the two parameters passed.
		static float scaled_octave_noise_2d(const int octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y);
		static float scaled_octave_noise_3d(const int octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z);
		static float scaled_octave_noise_4d(const int octaves, const float persistence, const float scale, const float loBound, const float hiBound, const float x, const float y, const float z, const float w);

		// Scaled Raw Simplex noise
		// The result will be between the two parameters passed
		static float scaled_raw_noise_2d(const float loBound, const float hiBound, const float x, const float y);
		static float scaled_raw_noise_3d(const float loBound, const float hiBound, const float x, const float y, const float z);
		static float scaled_raw_noise_4d(const float loBound, const float hiBound, const float x, const float y, const float z, const float w);

		// Raw Simplex noise - a single noise value.
		static float raw_noise_2d(const float x, const float y);
		static float raw_noise_3d(const float x, const float y, const float z);
		static float raw_noise_4d(const float x, const float y, const float, const float w);

	private:
		static int perm[512];
		static const int grad3[12][3];
		static const int grad4[32][4];
		static const int simplex[64][4];

		static int fastfloor(const float x);
		static float dot(const int* g, const float x, const float y);
		static float dot(const int* g, const float x, const float y, const float z);
		static float dot(const int* g, const float x, const float y, const float z, const float w);
	};
}
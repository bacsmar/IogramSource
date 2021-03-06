//
// Copyright (c) 2016 - 2017 Mesh Consultants Inc.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


#include "Geomlib_Incenter.h"

#include <Urho3D/Math/Vector3.h>

// Returns the incenter of triangle ABC.
Urho3D::Vector3 Geomlib::Incenter(
	const Urho3D::Vector3& A,
	const Urho3D::Vector3& B,
	const Urho3D::Vector3& C
)
{
	float a = (B - C).Length();
	float b = (C - A).Length();
	float c = (A - B).Length();

	float s = a + b + c;
	if (s == 0.0f) { // use epsilon?
		// all lengths are 0, so A, B, C are all the same point
		return A;
	}

	return (1.0f / s) * (a * A + b * B + c * C);
}
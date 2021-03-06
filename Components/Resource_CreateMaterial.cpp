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


#include "Resource_CreateMaterial.h"

#include <Urho3D/Resource/ResourceCache.h>
#include "IoGraph.h"

#include "Urho3D/Graphics/Technique.h"
#include "Urho3D/Graphics/Material.h"

using namespace Urho3D;

String Resource_CreateMaterial::iconTexture = "Textures/Icons/Resource_CreateMaterial.png";

Resource_CreateMaterial::Resource_CreateMaterial(Urho3D::Context* context) : IoComponentBase(context, 3, 1)
{
	SetName("CreateMaterial");
	SetFullName("Create Material");
	SetDescription("Create a material from parameters");
	SetGroup(IoComponentGroup::DISPLAY);
	SetSubgroup("");

	inputSlots_[0]->SetName("Technique");
	inputSlots_[0]->SetVariableName("Tec");
	inputSlots_[0]->SetDescription("Path to material");
	inputSlots_[0]->SetVariantType(VariantType::VAR_STRING);
	inputSlots_[0]->SetDataAccess(DataAccess::ITEM);
	inputSlots_[0]->SetDefaultValue("Techniques/NoTexture.xml");
	inputSlots_[0]->DefaultSet();

	inputSlots_[1]->SetName("Parameters");
	inputSlots_[1]->SetVariableName("Par");
	inputSlots_[1]->SetDescription("Key-Value pairs of parameters to modify");
	inputSlots_[1]->SetVariantType(VariantType::VAR_VARIANTMAP);
	inputSlots_[1]->SetDataAccess(DataAccess::ITEM);
	inputSlots_[1]->DefaultSet();

	inputSlots_[2]->SetName("Textures");
	inputSlots_[2]->SetVariableName("Tex");
	inputSlots_[2]->SetDescription("Key-Value pairs of tex units and resource paths");
	inputSlots_[2]->SetVariantType(VariantType::VAR_VARIANTMAP);
	inputSlots_[2]->SetDataAccess(DataAccess::ITEM);
	inputSlots_[2]->DefaultSet();

	outputSlots_[0]->SetName("Material");
	outputSlots_[0]->SetVariableName("M");
	outputSlots_[0]->SetDescription("Pointer to material");
	outputSlots_[0]->SetVariantType(VariantType::VAR_PTR);
	outputSlots_[0]->SetDataAccess(DataAccess::ITEM);
}


void Resource_CreateMaterial::SolveInstance(
	const Vector<Variant>& inSolveInstance,
	Vector<Variant>& outSolveInstance
	)
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	String techPath = inSolveInstance[0].GetString();

	Technique* technique = cache->GetResource<Technique>(techPath);

	//create the material
	Material* mat = new Material(GetContext());

	//must have a technique
	if (!technique)
	{
		URHO3D_LOGERROR("Could not load technique.");
		outSolveInstance[0] = mat;
		return;
	}

	//set the technique
	mat->SetNumTechniques(1);
	mat->SetTechnique(0, technique);

	//set the params
	VariantMap params = inSolveInstance[1].GetVariantMap();
	Vector<StringHash> keys = params.Keys();
	auto availableKeys = mat->GetShaderParameters();

	for (int i = 0; i < keys.Size(); i++)
	{
		MaterialShaderParameter mParam;
		if (availableKeys.TryGetValue(keys[i], mParam))
		{
			mParam.value_ = params[keys[i]];
			mat->SetShaderParameter(mParam.name_, mParam.value_);
		}
	}

	//TODO: do we need to manually track these materials and delete the pointers?

	outSolveInstance[0] = mat;

}


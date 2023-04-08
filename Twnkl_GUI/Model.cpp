//
// Twnkl 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
// 
// https://github.com/MaximumOctopus/Twnkl
// 
// 

// represents a collection of objects

#include <iostream>
#include <fstream>

#include "Model.h"
#include "Triangle.h"


Model::Model(std::wstring name) : Object(name)
{
	Name = name;
	Primitive = PrimitiveType::Model;
}


Model::~Model()
{
	
}


void Model::LocalIntersect(Intersections& i, Ray& rt)
{
	if (bounds.Intersects(rt))
	{
		for (int o = 0; o < Objects.size(); o++)
		{
			Objects[o]->Intersects(i, rt);
		}
	}
}


// not used, each triangle's localnormalat is called instead
Quaternion Model::LocalNormalAt(Quaternion& q)
{
	return Quaternion();
}


Trinion Model::VectorsFrom(const std::wstring input, int reference_index)
{
	int ReferenceType = 0;	// 0 = vector index, 1 = texture index, 2 = vector normal
	int mode = 0;
	bool InValue = false;
	int components[3] = { 0, 0, 0 };
	std::wstring temp = L"";

	//std::wcout << L"vf: " << input << L"\n";

	for (int t = 0; t < input.length(); t++)
	{
		if (InValue)
		{
			if (input[t] == L' ' || input[t] == L'/' || t == input.length() - 1)
			{
				//InValue = false;

				if (ReferenceType == reference_index)
				{
					if (temp != L"")
					{
						components[mode] = stoi(temp);
					}
				}

				if (input[t] == L' ')// && temp.empty()) // TO DO
				{
					ReferenceType = 0;
					mode++;
				}
				else if (input[t] == L'/')
				{
					ReferenceType++;
				}			

				temp = L"";
			}
			else if(isdigit(input[t]) || input[t] == L'.' || input[t] == L'-')
			{
				temp += input[t];
			}
		}
		else if (isdigit(input[t]) || input[t] == L'.' || input[t] == L'-')
		{
			InValue = true;

			temp += input[t];
		}

		if (mode > 2)
		{
			break;
		}
	}

	return Trinion(components[0], components[1], components[2]);
}


Quaternion Model::XYZFrom(const std::wstring input)
{
	int mode = 0;
	bool InValue = false;
	double components[3] = { 0, 0, 0 };
	std::wstring temp = L"";

	for (int t = 0; t < input.length(); t++)
	{
		if (InValue)
		{
			if (input[t] == L' ' || t == input.length() - 1)
			{
				InValue = false;

				if (temp != L"")
				{
					components[mode] = stod(temp);
				}

				mode++;
				temp = L"";
			}
			else
			{
				temp += input[t];
			}
		}
		else if (isdigit(input[t]) || input[t] == L'.' || input[t] == L'-')
		{
			InValue = true;

			temp += input[t];
		}

		if (mode > 2)
		{
			break;
		}
	}

	return Quaternion(components[0], components[1], components[2], 0);
}


void Model::Load(std::wstring file_name)
{
	std::wifstream file(file_name);

	if (file)
	{
		FileName = file_name;

		std::wstring s(L"");

		std::vector<Quaternion> Vectors;
		std::vector<Quaternion> VectorNormals;

		while (std::getline(file, s))
		{
			if (s != L"")
			{
				if (s[0] == L'/' || s[0] == L'#')
				{
					// comment, do nothing
				}
				else
				{
					switch (s[0])
					{
					case L'v':
					{
						if (s[1] == L'n')		// vector normals
						{
							VectorNormals.push_back(XYZFrom(s.substr(2) + L" "));
						}
						else					// vectors
						{
							Vectors.push_back(XYZFrom(s.substr(2) + L" "));
						}
						break;	
					}
					case L'f':					// faces
					{
						Trinion points = VectorsFrom(s.substr(2) + L" ", 0);

						Triangle* tringle = new Triangle(L"");

						tringle->Parent = this;

						if (VectorNormals.size() != 0)
						{
							Trinion normals = VectorsFrom(s.substr(2) + L" ", 2);

							// for now, assumes the normals for each point are equal...
							tringle->SetPointsWithNormal(Vectors[points.x - 1], Vectors[points.y - 1], Vectors[points.z - 1],
								VectorNormals[normals.x - 1]);
						}
						else
						{
							tringle->SetPoints(Vectors[points.x - 1], Vectors[points.y - 1], Vectors[points.z - 1]);
						}

						Objects.push_back(tringle);

						SetBounds(tringle);
						
						break;
					}
					}
				}
			}
		}

		file.close();
	}
}


void Model::PostSetup(int index)
{
	for (int t = 0; t < Objects.size(); t++)
	{
		Objects[t]->Material = Material;

		Objects[t]->ID = index;
	}

	bounds.Transform(Transform);
}


void Model::SetBounds(Triangle* tringle)
{
	for (int p = 0; p < 3; p++)
	{
		if (tringle->Points[p].x > bounds.Maximum.x)
		{
			bounds.Maximum.x = tringle->Points[p].x;
		}

		if (tringle->Points[p].y > bounds.Maximum.y)
		{
			bounds.Maximum.y = tringle->Points[p].y;
		}

		if (tringle->Points[p].z > bounds.Maximum.z)
		{
			bounds.Maximum.z = tringle->Points[p].z;
		}

		if (tringle->Points[p].x < bounds.Minimum.x)
		{
			bounds.Minimum.x = tringle->Points[p].x;
		}

		if (tringle->Points[p].y < bounds.Minimum.y)
		{
			bounds.Minimum.y = tringle->Points[p].y;
		}

		if (tringle->Points[p].z < bounds.Minimum.z)
		{
			bounds.Minimum.z = tringle->Points[p].z;
		}
	}
}


std::wstring Model::ToString()
{
	return L"Model: " + std::to_wstring(Objects.size()) + L" triangles.";
}


void Model::ToFile(std::ofstream& ofile)
{
	ofile << Formatting::to_utf8(__SceneChunkObjectModel + L"\n");
	ofile << Formatting::to_utf8(L"name=" + Name + L"\n");
	ofile << Formatting::to_utf8(L"filename=" + FileName + L"\n");
	ofile << Formatting::to_utf8(L"}\n");

	for (int t = 0; t < Transforms.size(); t++)
	{
		Transforms[t].ToFile(ofile);
	}

	Material->ToFile(ofile);
}
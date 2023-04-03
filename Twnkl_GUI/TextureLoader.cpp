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

#include <fstream>
#include <iostream>

#include "TextureLoader.h"


bool TextureLoader::Go(Colour** data, const std::wstring file_name, bool greyscale)
{
	std::ifstream file(file_name);

	if (file)
	{
		int Header = 0;
		std::string Magic = "";
		int Width = 0;
		int Height = 0;
		int MaxValue = 0;

		std::string s("");

		while (Header < 3)
		{
			std::getline(file, s);

			if (s != "")
			{
				if (s[0] == '/' || s[0] == '#')
				{
					// comment, do nothing
				}
				else
				{
					switch (Header)
					{
					case 0:
						Magic = s;
						break;
					case 1:
					{
						auto Space = s.find(L' ');

						if (Space != std::wstring::npos)
						{
							Width = stoi(s.substr(0, Space));
							Height = stoi(s.substr(Space + 1));
						}
						break;
					}
					case 2:
						MaxValue = stoi(s);
						break;
					}

					Header++;
				}
			}
		}

		if (Magic == "P3")			// only supported version of the PPM file spec
		{
			Colour* texture_data = new Colour[Width * Height];

			int x = 0;
			int y = 0;
			std::string temp("");
			double red = 0;
			double green = 0;
			double blue = 0;
			int component = 0;

			while (std::getline(file, s))
			{
				if (s != "")
				{
					if (s[0] == '/' || s[0] == '#')
					{
						// comment, do nothing
					}
					else
					{
						for (int i = 0; i < s.length(); i++)
						{
							if (s[i] == ' ')
							{
								if (temp != "")
								{
									switch (component)
									{
									case 0:
										red = stod(temp);
										break;
									case 1:
										green = stod(temp);
										break;
									case 2:
										blue = stod(temp);
										break;
									}

									if (greyscale)
									{
										double grey = (red * 0.299 + green * 0.587 + blue * 0.114) / (double)MaxValue;

										texture_data[y * Width + x] = Colour(grey, grey, grey);
									}
									else
									{
										texture_data[y * Width + x] = Colour(red / (double)MaxValue, green / (double)MaxValue, blue / (double)MaxValue);
									}

									component++;

									if (component == 3)
									{
										component = 0;

										x++;

										if (x == Width)			// 0 to x - 1
										{
											x = 0;
											y++;
										}
									}

									temp = "";
								}
							}
							else if (isdigit(s[i]))
							{
								temp += s[i];
							}
						}
					}
				}
			}

			*data = texture_data;

			TextureWidth = Width;
			TextureHeight = Height;

			file.close();

			return true;
		}

		file.close();
	}

	return false;
}
#include "TexGen.h"

TexGen::TexGen()
{
	this->texlen = 64;
}

std::vector<int> TexGen::color_values = []
{
	std::vector<int> values(16);
	for (int i = 0; i < 16; ++i)
	{
		values[i] = i + 1;
	}
	return values;
}();

std::vector<int> TexGen::ground_prefix_sums = []
{
	std::vector<int> ground_weights(16);
	for (int i = 0; i < 16 / 2; ++i)
	{
		ground_weights[i] = std::pow((i + 1), 8);
	}
	for (int i = 16 / 2; i < 16; ++i)
	{
		ground_weights[i] = ground_weights[16 - i];
	}

	std::vector<int> prefix_sums = ground_weights;
	for (int i = 1; i < prefix_sums.size(); ++i)
	{
		prefix_sums[i] += prefix_sums[i - 1];
	}
	return prefix_sums;
}();

std::mt19937_64 TexGen::gen64 = []
{
	return std::mt19937_64(std::random_device()());
}();

std::vector<int> TexGen::ground()
{
	std::vector<int> generated_texture(64 * 64);
	std::uniform_int_distribution<int> dist(ground_prefix_sums[0], ground_prefix_sums[ground_prefix_sums.size() - 1]);

	for (int i = 0; i < generated_texture.size(); ++i)
	{
		const auto random_num = dist(gen64);

		// binary search-like algo to find ceiling
		int left = 0;
		int right = ground_prefix_sums.size() - 1;
		while (left < right)
		{
			int mid = (left + right) / 2;
			if (random_num > ground_prefix_sums[mid])
			{
				left = mid + 1;
			}
			else
			{
				right = mid;
			}
		}
		generated_texture[i] = color_values[left];
	}
	return generated_texture;
}

std::vector<int> TexGen::hedge()
{
	int nbox = std::sqrt(64);
	std::vector<int> generated_texture(64 * 64);
	std::uniform_int_distribution<int> dist(0, nbox - 1);
	std::vector<std::pair<int, int>> random_points(64);

	for (int i = 0; i < random_points.size(); ++i)
	{
		random_points[i].first = (i % nbox) * nbox + dist(gen64);
		random_points[i].second = (i / nbox) * nbox + dist(gen64);
	}

	std::vector<std::vector<int>> distances(generated_texture.size(), std::vector<int>(random_points.size()));

	for (int i = 0; i < generated_texture.size(); ++i)
	{
		for (int j = 0; j < random_points.size(); ++j)
		{
			distances[i][j] = std::hypot(random_points[j].first - i % 64, random_points[j].second - i / 64);
		}
		std::sort(distances[i].begin(), distances[i].end());
		generated_texture[i] = (distances[i][1] % 16);
	}

	return generated_texture;
}

// https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
void TexGen::hsv2rgb(int h, int s, int v, int &r, int &g, int &b)
{
	double H = h / 60.0;
	double S = s / 100.0;
	double V = v / 100.0;

	double C = V * S;
	double X = C * (1.0 - std::abs(std::fmod(H, 2.0) - 1.0));
	double M = V - C;

	double R, G, B;
	if (0 <= H && H <= 1)
	{
		R = C;
		G = X;
		B = 0;
	}
	else if (1 < H && H <= 2)
	{
		R = X;
		G = C;
		B = 0;
	}
	else if (2 < H && H <= 3)
	{
		R = 0;
		G = C;
		B = X;
	}
	else if (3 < H && H <= 4)
	{
		R = 0;
		G = X;
		B = C;
	}
	else if (4 < H && H <= 5)
	{
		R = X;
		G = 0;
		B = C;
	}
	else if (5 < H && H <= 6)
	{
		R = C;
		G = 0;
		B = X;
	}

	r = (R + M) * 255.0;
	g = (G + M) * 255.0;
	b = (B + M) * 255.0;
}

void TexGen::actual_visualization_function(std::vector<int> vec, bool hedge)
{
	const int width = TexGen::texlen;
	const int height = TexGen::texlen;

	std::string fileName = "";
	int h, s, v;

	if (hedge)
	{
		fileName = "Models/Hedge/hedge.ppm";
		h = 90 + 10;
		s = 75;
		v = 50 - 17;
	}
	else
	{
		fileName = "Models/Ground/ground.ppm";
		h = 90 - 10;
		s = 75;
		v = 50 - 17;
	}

	std::ofstream image(fileName, std::ofstream::binary);

	image << "P3" << '\n';
	image << width << ' ' << height << '\n';
	image << "255" << '\n';

	int contrast_factor = 1;
	for (int i = 0; i < height * width; i++)
	{
		int r, g, b;
		int h2 = h;
		int s2 = s;
		int v2 = v - vec[i] / contrast_factor;

		hsv2rgb(h2, s2, v2, r, g, b);

		image << r << ' ' << g << ' ' << b << '\n';
	}
	//std::system("explorer test.ppm");
}
void del();

void TexGen::del()
{
	if (remove("Models/Ground/ground.jpg") != 0)
	{
		std::cout << "No ground.jpg\n";
	}
	else
	{
		std::cout << "ground.jpg deleted successfully\n";
	}
	if (remove("Models/Ground/ground.ppm") != 0)
	{
		std::cout << "No ground.ppm\n";
	}
	else
	{
		std::cout << "ground.ppm deleted successfully\n";
	}
	if (remove("Models/Hedge/hedge.jpg") != 0)
	{
		std::cout << "No hedge.jpg\n";
	}
	else
	{
		std::cout << "hedge.jpg deleted successfully\n";
	}
	if (remove("Models/Hedge/hedge.ppm") != 0)
	{
		std::cout << "No hedge.ppm\n";
	}
	else
	{
		std::cout << "hedge.ppm deleted successfully\n";
	}
}
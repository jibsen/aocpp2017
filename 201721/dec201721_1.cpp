//
// Advent of Code 2017, day 21, part one and two
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct RangeHash {
	template<std::ranges::forward_range Range>
	std::size_t operator()(const Range &range) const noexcept
	{
		std::size_t hash = 17;
		for (const auto &elem : range) {
			hash = hash * 37 + std::hash<typename Range::value_type>()(elem);
		}
		return hash;
	}
};

auto split(std::string_view sv, std::string_view delim)
{
	std::vector<std::string_view> res;

	std::string_view::size_type pos = 0;

	for (;;) {
		auto next_delim_pos = sv.find(delim, pos);

		res.push_back(sv.substr(pos, next_delim_pos - pos));

		if (next_delim_pos == std::string_view::npos) {
			break;
		}

		pos = next_delim_pos + delim.size();
	}

	return res;
}

void flip_vertical(std::span<std::string> sp)
{
	std::ranges::reverse(sp);
}

void flip_horizontal(std::span<std::string> sp)
{
	std::ranges::for_each(sp, [](auto &row) { std::ranges::reverse(row); });
}

void transpose(std::span<std::string> sp)
{
	for (int i = 0; i < sp.size(); ++i) {
		for (int j = i + 1; j < sp.size(); ++j) {
			std::swap(sp[i][j], sp[j][i]);
		}
	}
}

void rotate(std::span<std::string> sp)
{
	transpose(sp);
	flip_vertical(sp);
}


using Tile = std::vector<std::string>;

auto read_rules()
{
	std::vector<std::pair<Tile, Tile>> rules;

	std::string from;
	std::string token;
	std::string to;

	while (std::cin >> from >> token >> to) {
		auto from_rows = split(from, "/");

		Tile from_tile;
		from_tile.reserve(from_rows.size());

		for (auto row : from_rows) {
			from_tile.push_back(std::string(row));
		}

		auto to_rows = split(to, "/");

		Tile to_tile;
		to_tile.reserve(to_rows.size());

		for (auto row : to_rows) {
			to_tile.push_back(std::string(row));
		}

		rules.push_back(std::make_pair(std::move(from_tile), std::move(to_tile)));
	}

	return rules;
}

auto make_lookup_from_rules(const std::vector<std::pair<Tile, Tile>> &rules)
{
	std::unordered_map<Tile, Tile, RangeHash> lookup;

	for (const auto &[from, to] : rules) {
		Tile from_alt = from;

		for (auto op : "vhvrvhv") {
			lookup[from_alt] = to;

			switch (op) {
			case 'v':
				flip_vertical(from_alt);
				break;
			case 'h':
				flip_horizontal(from_alt);
				break;
			case 'r':
				rotate(from_alt);
				break;
			}
		}

		lookup[from_alt] = to;
	}

	return lookup;
}

Tile get_subtile(Tile &image, int x, int y, int sub_size)
{
	Tile sub_tile;
	sub_tile.reserve(sub_size);

	for (int dy = 0; dy < sub_size; ++dy) {
		sub_tile.push_back(image[y + dy].substr(x, sub_size));
	}

	return sub_tile;
}

void put_subtile(Tile &image, int x, int y, const Tile &sub_tile)
{
	for (int dy = 0; dy < sub_tile.size(); ++dy) {
		for (int dx = 0; dx < sub_tile.size(); ++dx) {
			image[y + dy][x + dx] = sub_tile[dy][dx];
		}
	}
}

void enhance_image(Tile &image, auto &lookup)
{
	int sub_size = (image.size() % 2) == 0 ? 2 : 3;
	int num_subtiles = image.size() / sub_size;

	Tile new_image;
	new_image.reserve(num_subtiles * (sub_size + 1));

	for (int y = 0; y < num_subtiles * (sub_size + 1); ++y) {
		new_image.push_back(std::string(num_subtiles * (sub_size + 1), '.'));
	}

	for (int y = 0; y < num_subtiles; ++y) {
		for (int x = 0; x < num_subtiles; ++x) {
			auto from = get_subtile(image, x * sub_size, y * sub_size, sub_size);

			auto to = lookup[from];

			put_subtile(new_image, x * (sub_size + 1), y * (sub_size + 1), to);
		}
	}

	image.swap(new_image);
}

int main()
{
	auto rules = read_rules();

	auto lookup = make_lookup_from_rules(rules);

	Tile image = { ".#.", "..#", "###" };

	std::size_t iterations = 0;

	for (; iterations != 5; ++iterations) {
		enhance_image(image, lookup);
	}

	std::cout << std::ranges::count(image | std::views::join, '#') << '\n';

	for (; iterations != 18; ++iterations) {
		enhance_image(image, lookup);
	}

	std::cout << std::ranges::count(image | std::views::join, '#') << '\n';
}

//
// Advent of Code 2017, day 20, part one
//

#include <algorithm>
#include <cstdio>
#include <format>
#include <iostream>
#include <vector>

struct Vec3 {
	int x;
	int y;
	int z;
};

Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs)
{
	return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

struct Particle {
	Vec3 pos;
	Vec3 vel;
	Vec3 acc;
};

auto read_particles()
{
	std::vector<Particle> particles;

	for (;;) {
		Particle p;

		int res = std::scanf(" p=<%d,%d,%d>, v=<%d,%d,%d>, a=<%d,%d,%d>",
			&p.pos.x, &p.pos.y, &p.pos.z,
			&p.vel.x, &p.vel.y, &p.vel.z,
			&p.acc.x, &p.acc.y, &p.acc.z
		);

		if (res != 9) {
			break;
		}

		particles.push_back(p);
	}

	return particles;
}

int manhattan_distance(const Vec3 &t)
{
	return std::abs(t.x) + std::abs(t.y) + std::abs(t.z);
}

int main()
{
	auto particles = read_particles();

	std::cout << std::format("{} particles read\n", particles.size());

	// If each coordinate of the position and velocity is non-decreasing,
	// the particle is never going to get closer to <0,0,0>
	auto is_escaping = [](const Particle &p) {
		return std::abs(p.pos.x + p.vel.x) >= std::abs(p.pos.x)
		    && std::abs(p.pos.y + p.vel.y) >= std::abs(p.pos.y)
		    && std::abs(p.pos.z + p.vel.z) >= std::abs(p.pos.z)
		    && std::abs(p.vel.x + p.acc.x) >= std::abs(p.vel.x)
		    && std::abs(p.vel.y + p.acc.y) >= std::abs(p.vel.y)
		    && std::abs(p.vel.z + p.acc.z) >= std::abs(p.vel.z);
	};

	for (;;) {
		if (std::ranges::all_of(particles, is_escaping)) {
			break;
		}

		for (auto &p : particles) {
			p.vel = p.vel + p.acc;
			p.pos = p.pos + p.vel;
		}
	}

	auto manhattan_less = [](const Particle &lhs, const Particle &rhs) {
		return manhattan_distance(lhs.pos) < manhattan_distance(rhs.pos);
	};

	auto min = std::ranges::min_element(particles, manhattan_less);

	std::cout << std::distance(particles.begin(), min) << '\n';
}

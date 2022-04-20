#include "rtweekend.h"
	
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <chrono>
#include <functional>
#include <iostream>
#include <sstream>
#include <thread>

const int num_threads = std::thread::hardware_concurrency();

color ray_color(const ray& r, const hittable& world, int depth) {
	hit_record rec;

	// If we've exceeded the ray bounce limit, no more light is gathered
	if (depth <= 0)
		return color(0,0,0);

	if (world.hit(r, 0.001, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth-1);
		return color(0,0,0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = color::random() * color::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else if (choose_mat < 0.95) {
					// metal
					auto albedo = color::random(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				} else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

camera default_cam(double aspect_ratio) {

	point3 lookfrom(13,2,3);
	point3 lookat(0,0,0);
	vec3 vup(0,1,0);
	auto vfov = 20;
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	
	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);
	return cam;
}

// Begin Pregen Scenes

hittable_list scene1() {
	
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.1, 0.1, 0.1));
	world.add(make_shared<sphere>(point3(0,-100,0), 100, ground_material));

	auto material_red = make_shared<metal>(color(1.0, 0.0, 0.0), 0.0);
	world.add(make_shared<sphere>(point3(0,1,1), 1.0, material_red));

	auto material_glass = make_shared<dielectric>(1.3);
	world.add(make_shared<sphere>(point3(0,1,-1), 1.0, material_glass));

	auto material_blue = make_shared<lambertian>(color(0.0, 0.0, 1.0));
	world.add(make_shared<sphere>(point3(0,2.70,0), 1.0, material_blue));

	return world;
}

camera cam1(double aspect_ratio) {

	point3 lookfrom(13,0.5,0);
	point3 lookat(0,1.5,0);
	vec3 vup(0,1,0);
	auto vfov = 20;
	auto dist_to_focus = 13.0;
	auto aperture = 0.1;
	
	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);
	return cam;
}

hittable_list scene2() {

	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.1, 0.1, 0.1));
	world.add(make_shared<sphere>(point3(0,-10000,0), 10000, ground_material));

	auto material_red = make_shared<metal>(color(1.0, 0.0, 0.0), 0.05);
	world.add(make_shared<sphere>(point3(0,1,0), 1.0, material_red));

	auto material_orange = make_shared<metal>(color(1.0, 0.65, 0.0), 0.05);
	world.add(make_shared<sphere>(point3(0,1.5,-3), 1.5, material_orange));

	auto material_yellow = make_shared<metal>(color(0.85, 1.0, 0.0), 0.05);
	world.add(make_shared<sphere>(point3(0,2,-7), 2.0, material_yellow));

	auto material_green = make_shared<metal>(color(0.0, 1.0, 0.15), 0.05);
	world.add(make_shared<sphere>(point3(0,2.5,-12), 2.5, material_green));

	auto material_blue = make_shared<metal>(color(0.15, 0.0, 1.0), 0.05);
	world.add(make_shared<sphere>(point3(0,3,-18), 3.0, material_blue));

	auto material_purple = make_shared<metal>(color(0.50, 0.0, 0.50), 0.05);
	world.add(make_shared<sphere>(point3(0,3.5,-25), 3.5, material_purple));

	return world;
}

camera cam2(double aspect_ratio) {

	point3 lookfrom(35,10,25);
	point3 lookat(0,1,-12);
	vec3 vup(0,1,0);
	auto vfov = 20;
	auto dist_to_focus = 50.0;
	auto aperture = 0.1;
	
	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);
	return cam;
}

hittable_list scene3() {

	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.63, 0.32, 0.18));
	world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

	auto s1 = make_shared<lambertian>(color(1.0, 1.0, 1.0));
	world.add(make_shared<sphere>(point3(0,0.2,0), 0.2, s1));

	auto s2 = make_shared<lambertian>(color(0.95, 0.95, 0.95));
	world.add(make_shared<sphere>(point3(-0.5,0.2,-0.5), 0.2, s2));

	auto s3 = make_shared<lambertian>(color(0.9, 0.9, 0.9));
	world.add(make_shared<sphere>(point3(-1.1,0.2,0), 0.2, s3));

	auto s4 = make_shared<lambertian>(color(0.85, 0.85, 0.85));
	world.add(make_shared<sphere>(point3(-1.3,0.2,0.8), 0.2, s4));

	auto s5 = make_shared<lambertian>(color(0.8, 0.8, 0.8));
	world.add(make_shared<sphere>(point3(-1,0.2,1.6), 0.2, s5));

	auto s6 = make_shared<lambertian>(color(0.75, 0.75, 0.75));
	world.add(make_shared<sphere>(point3(-0.3,0.2,2.1), 0.2, s6));

	auto s7 = make_shared<lambertian>(color(0.7, 0.7, 0.7));
	world.add(make_shared<sphere>(point3(0.4,0.2,2.3), 0.2, s7));

	auto s8 = make_shared<lambertian>(color(0.65, 0.65, 0.65));
	world.add(make_shared<sphere>(point3(1.05,0.2,2.2), 0.2, s8));

	auto s9 = make_shared<lambertian>(color(0.6, 0.6, 0.6));
	world.add(make_shared<sphere>(point3(1.8,0.2,2), 0.2, s9));

	auto s10 = make_shared<lambertian>(color(0.55, 0.55, 0.55));
	world.add(make_shared<sphere>(point3(2.5, 0.2, 1.5), 0.2, s10));

	auto s11 = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(3,0.2,0.8), 0.2, s11));

	auto s12 = make_shared<lambertian>(color(0.45, 0.45, 0.45));
	world.add(make_shared<sphere>(point3(3.3,0.2,0), 0.2, s12));

	auto s13 = make_shared<lambertian>(color(0.4, 0.4, 0.4));
	world.add(make_shared<sphere>(point3(3.4,0.2,-0.8), 0.2, s13));

	auto s14 = make_shared<lambertian>(color(0.35, 0.35, 0.35));
	world.add(make_shared<sphere>(point3(3.3,0.2,-1.5), 0.2, s14));

	auto s15 = make_shared<lambertian>(color(0.3, 0.3, 0.3));
	world.add(make_shared<sphere>(point3(3,0.2,-2.2), 0.2, s15));

	auto s16 = make_shared<lambertian>(color(0.25, 0.25, 0.25));
	world.add(make_shared<sphere>(point3(2.6,0.2,-2.9), 0.2, s16));

	auto s17 = make_shared<lambertian>(color(0.2, 0.2, 0.2));
	world.add(make_shared<sphere>(point3(2,0.2,-3.5), 0.2, s17));

	auto s18 = make_shared<lambertian>(color(0.15, 0.15, 0.15));
	world.add(make_shared<sphere>(point3(1.4,0.2,-3.9), 0.2, s18));

	auto s19 = make_shared<lambertian>(color(0.1, 0.1, 0.1));
	world.add(make_shared<sphere>(point3(0.7,0.2,-4.2), 0.2, s19));

	auto s20 = make_shared<lambertian>(color(0.05, 0.05, 0.05));
	world.add(make_shared<sphere>(point3(0,0.2,-4.4), 0.2, s20));

	return world;
}

camera cam3(double aspect_ratio) {

	point3 lookfrom(9.54,13.68,6.84);
	point3 lookat(1,0,-1);
	vec3 vup(-1,0,0);
	auto vfov = 20;
	auto dist_to_focus = 15.0;
	auto aperture = 0.1;
	
	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);
	return cam;
}

// End Pregen Scenes

void render(int start, int end, std::stringstream & out, int image_width, int image_height,
			int samples_per_pixel, int max_depth, camera & cam, hittable_list & world) {


	for (int j = start; j >= end; --j) {
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width-1);
				auto v = (j + random_double()) / (image_height-1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
		write_color(out, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "Block done.\n";
}

int main() {
	
	// Image

	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	// const int samples_per_pixel = 100;
	const int samples_per_pixel = 10;
	const int max_depth = 10;

	// World

	// auto world = random_scene();
	// auto world = scene1();
	// auto world = scene2();
	auto world = scene3();

	// Camera

	// camera cam = default_cam(aspect_ratio);
	// camera cam = cam1(aspect_ratio);
	// camera cam = cam2(aspect_ratio);
	camera cam = cam3(aspect_ratio);

	// Render

	std::cerr << "Rendering with " << num_threads << " threads.\n";

	auto start = std::chrono::high_resolution_clock::now();
	std::thread threads[num_threads];
	std::stringstream streams[num_threads];
	int block_size = image_height/num_threads;

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	int s = image_height - 1;
	for (int i = 0; i < num_threads - 1; ++i, s -= block_size + 1) {
		streams[i] = std::stringstream();
		threads[i] = std::thread(
			render,
			s,
			s - block_size,
			std::ref(streams[i]),
			image_width,
			image_height,
			samples_per_pixel,
			max_depth,
			std::ref(cam),
			std::ref(world)
		);
	}

	threads[num_threads - 1] = std::thread(
		render,
		s,
		0,
		std::ref(streams[num_threads - 1]),
		image_width,
		image_height,
		samples_per_pixel,
		max_depth,
		std::ref(cam),
		std::ref(world)
	);

	for (std::thread & t : threads)
		t.join();

	for (int i = 0; i < num_threads; ++i)
		std::cout << streams[i].str();


	auto end = std::chrono::high_resolution_clock::now();

	std::cerr << "\nDone.\n";
	std::cerr << "Took " 
			  << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() 
			  << " seconds to render.\n";

	return 0;
}

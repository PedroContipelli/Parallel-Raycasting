#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

// BEGIN PREGEN SCENES

// * SCENE 1

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

// * SCENE 2

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

// * SCENE 3

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

	point3 lookfrom(12,8,-4);
	point3 lookat(1,0,-1);
	vec3 vup(-1,0,0);
	auto vfov = 20;
	auto dist_to_focus = 14.0;
	auto aperture = 0.1;
	
	camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus);
	return cam;
}

// END PREGEN SCENES
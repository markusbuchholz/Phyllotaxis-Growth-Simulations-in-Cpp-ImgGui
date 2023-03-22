// Markus Buchholz, 2023

#include <stdafx.hpp>
#include "imgui_helper.hpp"
#include <tuple>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>
#include <thread>
#include <chrono>
//---------------------------------------------------------------

int w = 1000;
int h = 1000;

//---------------------------------------------------------------

struct RGB
{

	float r;
	float g;
	float b;
};

//---------------------------------------------------------------

struct HSV
{
	float h;
	float s;
	float v;
};

//---------------------------------------------------------------

struct Shape
{
	float x;
	float y;
	float color;
};

//---------------------------------------------------------------

int main(int argc, char const *argv[])
{

	std::string title = "Phyllotaxi simulation";
	initImgui(w, h, title);

	bool show_demo_window = true;
	bool show_another_window = false;
	// ImVec4 clear_color = ImVec4(89.0f / 255.0, 88.0f / 255.0, 87.0f / 255.0, 1.00f);
	ImVec4 clear_color = ImVec4(0.0f / 255.0, 0.0f / 0.0, 0.0f / 255.0, 1.00f);
	ImVec4 line_color = ImVec4(255.0f / 255.0, 255.0f / 255.0, 255.0f / 255.0, 1.00f);
	ImVec4 blue_color = ImVec4(0.0f / 255.0, 0.0f / 255.0, 170.0f / 255.0, 1.00f);
	ImVec4 pink_color = ImVec4(179.0f / 255.0, 12.0f / 255.0, 130.0f / 255.0, 1.00f);
	ImVec4 dot_color = ImVec4(255.0f / 255.0, 255.0f / 255.0, 0.0f / 255.0, 1.00f);

	float center_x = w / 2.0;
	float center_y = h / 2.0;
	int n = 0;
	int c = 8;
	float a = 0.0f;
	float r = 0.0f;

	bool flag = true;
	float ang = 0.0f;
	std::vector<Shape> shapePos;

	int counter = 0.0f;

	RGB rgb;
	HSV hsv;

	while (!glfwWindowShouldClose(window) && flag == true)
	{
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = 0;
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_FirstUseEver);
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

		ImGui::Begin("Simulation", nullptr, window_flags);
		ImDrawList *draw_list = ImGui::GetWindowDrawList();


		ang = n * 137.5f; //.3 .5 .6
		r = c * std::sqrt(n);

		float xi = r * std::cos(ang) + center_x;
		float yi = r * std::sin(ang) + center_y;
		float d = std::sqrt(std::pow((xi - center_x), 2) + std::pow((yi - center_y), 2));

		shapePos.push_back({xi, yi, d});

		for (auto &c : shapePos)
		{

			hsv = {c.color / 255.0f, 1.0f, 1.0f};
			ImGui::ColorConvertHSVtoRGB(hsv.h, hsv.s, hsv.v, rgb.r, rgb.g, rgb.b);

			ImVec4 pix_color = ImVec4(rgb.r, rgb.g, rgb.b, 1.0f);

			draw_list->AddCircleFilled({c.x, c.y}, 6.0f, ImColor(pix_color));
		}

		n++;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		ImGui::End();

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	termImgui();
	return 0;
}

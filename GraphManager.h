#pragma once
#include <Windows.h>
#include <vector>
#include <string>
namespace graphic_utils {
	struct point2D {
		double x;
		double y;
	};
	typedef double (*func)(double x);
	class GraphManager {
	public:
		GraphManager();
		~GraphManager();
		void draw(HWND hwnd, WPARAM wParam, LPARAM lParam);
		void setFunctions(std::vector<func> functions);
		void setGraphNames(std::vector<std::wstring> graphNames);
		void setPoints(std::vector<point2D> points);
	private:
		std::vector<func> functions;
		std::vector<point2D> points;
		std::vector<std::wstring> graphNames;
		CRITICAL_SECTION drawCritSection;
		CRITICAL_SECTION funcCritSection;
		CRITICAL_SECTION namesCritSection;
		CRITICAL_SECTION pointsCritSection;
	};
}
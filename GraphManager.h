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
		//double getMatrixK();
		//double setMatrixK();
	private:
		//volatile static double matrix_k;
		std::vector<func> functions;
		std::vector<point2D> points;
		std::vector<std::wstring> graphNames;
		volatile double step;
		volatile double interval_start;
		volatile double interval_finish;
		//CRITICAL_SECTION kCritSection;
		CRITICAL_SECTION drawCritSection;
		CRITICAL_SECTION funcCritSection;
		CRITICAL_SECTION namesCritSection;
		CRITICAL_SECTION pointsCritSection;
	};
}
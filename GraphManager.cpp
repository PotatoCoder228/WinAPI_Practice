#include "GraphManager.h"
#include <iostream>

namespace graphic_utils {

	/**
	* Критическая секция != мьютексу
	* Мьютекс - объект ядра и глобален
	* Критическая секция работает в виде структуры и позволяет лишь в нужных случаях вызывать мьютекс
	* Поэтому мы должны выделить под неё память в куче и потом высвобождать
	* Критическая секция работает быстрее, так как системные вызовы используют большое количество
	* процессорных инструкций
	*/

	/*
	double GraphManager::getMatrixK() {
		
	}
	double GraphManager::setMatrixK() {
		
	}
	*/

	GraphManager::GraphManager():interval_start(-5), interval_finish(5), step(0.001) {
		InitializeCriticalSection(&(this->drawCritSection));
		InitializeCriticalSection(&(this->funcCritSection));
		InitializeCriticalSection(&(this->pointsCritSection));
		InitializeCriticalSection(&(this->namesCritSection));
		//InitializeCriticalSection(&(this->kCritSection));
		//this->matrix_k = 1;
	}
	GraphManager::~GraphManager() {
		DeleteCriticalSection(&(this->drawCritSection));
		DeleteCriticalSection(&(this->funcCritSection));
		DeleteCriticalSection(&(this->pointsCritSection));
		DeleteCriticalSection(&(this->namesCritSection));
	}

	static void rotateAxesFromGraph(double& x, double& y) {
		double buf = x;
		x = y;
		y = buf;
	}

	static void rotateAxesToGraph(double& x, double& y) {
		double buf = x;
		x = y;
		y = buf;
	}

	static double getRectWidth(RECT& rect) {
		return rect.right - rect.left;
	}

	static double getRectHeight(RECT& rect) {
		return rect.bottom - rect.top;
	}

	static double getAxisSize(RECT& rect) {
		return (rect.right >= rect.bottom) ? rect.right : rect.bottom;
	}

	static void drawFunction(HDC hdc, RECT& rect, func function) {
		double width = getRectWidth(rect);
		double height = getRectHeight(rect);
		double x_start = 0.8 * height;
		double y_start = 0.2 * width;
		POINT pt;
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(100, 0, 0));
		SelectObject(hdc, pen);
		MoveToEx(hdc, 0, 0, &pt);
	}

	static void drawAxes(HDC hdc, RECT& rect) {
		double width = getRectWidth(rect);
		double height = getRectHeight(rect);
		double x_start = 0.5*0.8*height;
		double y_start = 0.5*0.2*width;
		rotateAxesFromGraph(x_start, y_start);
		POINT pt;
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(200, 200, 200));
		SelectObject(hdc, pen);
		int size = getAxisSize(rect);
		MoveToEx(hdc, x_start, 0, &pt);
		LineTo(hdc, x_start, size);
		MoveToEx(hdc, 0, y_start, &pt);
		LineTo(hdc, size, y_start);
		DeleteObject(pen);
	}

	void GraphManager::draw(HWND hwnd, WPARAM wParam, LPARAM lParam) {
		//lParam - the low word is a x, the high word is a y
		HDC hdc;
		PAINTSTRUCT ps;
		RECT rect;
		EnterCriticalSection(&(this->drawCritSection));
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		drawAxes(hdc, rect);
		/*
		int width = rect.right - rect.left;
		int height = rect.top - rect.bottom;
		std::string wStr = std::to_string(width);
		std::string hStr = std::to_string(height);
		DrawText(hdc, wStr.c_str(), -1, &rect, DT_CENTER);
		DrawText(hdc, hStr.c_str(), -1, &rect, DT_MODIFYSTRING);
		*/
		EndPaint(hwnd, &ps);
		LeaveCriticalSection(&(this->drawCritSection));
	}

	//сделать PostMessage, для перерисовки после каждого изменения.

	void GraphManager::setFunctions(std::vector<func> functions) {
		EnterCriticalSection(&(this->funcCritSection));
		this->functions = functions;
		LeaveCriticalSection(&(this->funcCritSection));
	}
	void GraphManager::setGraphNames(std::vector<std::wstring> graphNames) {
		EnterCriticalSection(&(this->namesCritSection));
		this->graphNames = graphNames;
		LeaveCriticalSection(&(this->namesCritSection));
	}
	void GraphManager::setPoints(std::vector<point2D> points) {
		EnterCriticalSection(&(this->pointsCritSection));
		this->points = points;
		LeaveCriticalSection(&(this->pointsCritSection));
	}
}
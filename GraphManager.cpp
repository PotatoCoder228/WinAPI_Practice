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

	GraphManager::GraphManager() {
		InitializeCriticalSection(&(this->drawCritSection));
		InitializeCriticalSection(&(this->funcCritSection));
		InitializeCriticalSection(&(this->pointsCritSection));
		InitializeCriticalSection(&(this->namesCritSection));
	}
	GraphManager::~GraphManager() {
		DeleteCriticalSection(&(this->drawCritSection));
		DeleteCriticalSection(&(this->funcCritSection));
		DeleteCriticalSection(&(this->pointsCritSection));
		DeleteCriticalSection(&(this->namesCritSection));
	}

	static void drawAxis(HDC hdc, RECT rect) {
		double x_start = 0.5 * (rect.right - rect.left);
		double y_start = 0.2 * (rect.bottom - rect.top);
		POINT pt;
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(200, 200, 200));
		SelectObject(hdc, pen);
		int size = rect.right;
		if (rect.bottom >= rect.right) {
			size = rect.bottom;
		}
		MoveToEx(hdc, y_start, 0, &pt);
		LineTo(hdc, y_start, size);
		MoveToEx(hdc, 0, x_start, &pt);
		LineTo(hdc, size, x_start);
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
		drawAxis(hdc, rect);
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
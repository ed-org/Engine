#pragma once
#include <Windows.h>

struct Key_keyboard
{
	bool ESC = false,
		q = false,
		w = false,
		e = false,
		r = false,
		t = false,
		y = false,
		u = false,
		i = false,
		o = false,
		p = false,
		a = false,
		s = false,
		d = false,
		f = false,
		g = false,
		h = false,
		j = false,
		k = false,
		l = false,
		z = false,
		x = false,
		c = false,
		v = false,
		b = false,
		n = false,
		m = false,
		Space = false;
}Keys;
void keyboard_time() {
	while (true) {
		GetAsyncKeyState(27) ? Keys.ESC = true : Keys.ESC = false;
		GetAsyncKeyState(81) ? Keys.q = true : Keys.q = false;
		GetAsyncKeyState(87) ? Keys.w = true : Keys.w = false;
		GetAsyncKeyState(69) ? Keys.e = true : Keys.e = false;
		GetAsyncKeyState(82) ? Keys.r = true : Keys.r = false;
		GetAsyncKeyState(84) ? Keys.t = true : Keys.t = false;
		GetAsyncKeyState(89) ? Keys.y = true : Keys.y = false;
		GetAsyncKeyState(85) ? Keys.u = true : Keys.u = false;
		GetAsyncKeyState(73) ? Keys.i = true : Keys.i = false;
		GetAsyncKeyState(79) ? Keys.o = true : Keys.o = false;
		GetAsyncKeyState(80) ? Keys.p = true : Keys.p = false;
		GetAsyncKeyState(65) ? Keys.a = true : Keys.a = false;
		GetAsyncKeyState(83) ? Keys.s = true : Keys.s = false;
		GetAsyncKeyState(68) ? Keys.d = true : Keys.d = false;
		GetAsyncKeyState(70) ? Keys.f = true : Keys.f = false;
		GetAsyncKeyState(71) ? Keys.g = true : Keys.g = false;
		GetAsyncKeyState(72) ? Keys.h = true : Keys.h = false;
		GetAsyncKeyState(74) ? Keys.j = true : Keys.j = false;
		GetAsyncKeyState(75) ? Keys.k = true : Keys.k = false;
		GetAsyncKeyState(76) ? Keys.l = true : Keys.l = false;
		GetAsyncKeyState(90) ? Keys.z = true : Keys.z = false;
		GetAsyncKeyState(88) ? Keys.x = true : Keys.x = false;
		GetAsyncKeyState(67) ? Keys.c = true : Keys.c = false;
		GetAsyncKeyState(86) ? Keys.v = true : Keys.v = false;
		GetAsyncKeyState(66) ? Keys.b = true : Keys.b = false;
		GetAsyncKeyState(78) ? Keys.n = true : Keys.n = false;
		GetAsyncKeyState(77) ? Keys.m = true : Keys.m = false;
		GetAsyncKeyState(32) ? Keys.Space = true : Keys.Space = false;
		Sleep(10);
	}
}
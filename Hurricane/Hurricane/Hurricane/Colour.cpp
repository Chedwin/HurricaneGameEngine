#include "Colour.h"

Colour::Colour(hFLOAT _r, hFLOAT _g, hFLOAT _b, hFLOAT _a) : r(_r), g(_g), b(_b), a(_a)
{
	Normalize();
}

Colour::~Colour() {}

Colour Colour::operator+(const Colour& value) const {
	return Colour(r + value.r, g + value.g, b + value.b, a + value.a);
}

Colour Colour::operator+=(const Colour& value) {
	r += value.r;
	g += value.g;
	b += value.b;
	a += value.a;
	Normalize();
	return *this;
}

Colour Colour::operator-(const Colour& value) const {
	return Colour(r - value.r, g - value.g, b - value.b, a - value.a);
}

Colour Colour::operator-=(const Colour& value) {
	r -= value.r;
	g -= value.g;
	b -= value.b;
	a -= value.a;
	Normalize();
	return *this;
}

Colour Colour::operator*(const hFLOAT& value) const {
	return Colour(r * value, g * value, b * value, a * value);
}

const Colour operator*(const hFLOAT& value, const Colour& _this)
{
	return Colour(_this.r * value, _this.g * value, _this.b * value, _this.a * value);
}

Colour Colour::operator*=(const hFLOAT& value) {
	r *= value;
	g *= value;
	b *= value;
	a *= value;
	Normalize();
	return *this;
}

void Colour::operator=(const Colour& value) {
	r = value.r;
	g = value.g;
	b = value.b;
	a = value.a;
	Normalize();
};

Colour Colour::operator/(const hFLOAT& value) const {
	return Colour(Limit(r / value), g / value, b / value, a / value);
}

Colour Colour::operator/=(const hFLOAT& value) {
	r /= value;
	g /= value;
	b /= value;
	a /= value;
	Normalize();
	return *this;
}

Colour::operator SDL_Color() const
{
	SDL_Color _colour = { b * 255, g * 255, r * 255, a * 255 };
	return _colour;
}

hFLOAT Colour::Limit(const hFLOAT _value) const
{
	return (_value > 1 ? 1 : _value < 0 ? 0 : _value);
}


//Used to keep numbers between 1 and 0.. unused for now
void Colour::Normalize()
{
	/*r = Limit(r);
	g = Limit(g);
	b = Limit(b);
	a = Limit(a);*/
}


/* Factories */
Colour Colour::Black() { return Colour(0, 0, 0, 1); }
Colour Colour::White() { return Colour(1, 1, 1, 1); }
Colour Colour::Gray() { return Colour(0.75f, 0.75f, 0.75f, 1); }
Colour Colour::Transparent() { return Colour(0, 0, 0, 0); }
Colour Colour::Red() { return Colour(1, 0, 0, 1); }
Colour Colour::Green() { return Colour(0, 1, 0, 1); }
Colour Colour::Blue() { return Colour(0, 0, 1, 1); }
Colour Colour::Yellow() { return Colour(1, 1, 0, 1); }
Colour Colour::Cyan() { return Colour(0, 1, 1, 1); }
Colour Colour::Magenta() { return Colour(1, 0, 1, 1); }
Colour Colour::Orange() { return Colour(1, 0.5f, 0, 1); }
Colour Colour::Pink() { return Colour(1, 0, 0.5f, 1); }
Colour Colour::Lime() { return Colour(0.5f, 1, 0, 1); }
Colour Colour::ManganeseBlue() { return Colour(0, 0.5f, 1, 1); }
Colour Colour::SpringGreen() { return Colour(0, 1, 0.5f, 1); }
Colour Colour::Fuchsia() { return Colour(0.5f, 0, 1, 1); }
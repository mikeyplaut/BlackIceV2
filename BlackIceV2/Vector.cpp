#include "Vector.h"
#include <fastmath.h>
//Vector3
vec3_1::vec3_1() {
	this->x = this->y = this->z = 0;
}

vec3_1::~vec3_1() {
	//Memset(&*this, 0, sizeof(*this));
}

vec3_1::vec3_1(float x) {
	this->x = x; this->y = this->z = 0;
}

vec3_1::vec3_1(float x, float y) {
	this->x = x; this->y = y; this->z = 0;
}

vec3_1::vec3_1(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
}

vec3_1::vec3_1(float vec[3]) {
	this->x = vec[0]; this->y = vec[1]; this->z = vec[2];
}

vec3_1 vec3_1::operator()(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
}

vec3_1 vec3_1::operator+(const vec3_1 vec) {
	return vec3_1(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

vec3_1 vec3_1::operator+(const float* vec) {
	return vec3_1(this->x + vec[0], this->y + vec[1], this->z + vec[2]);
}

vec3_1 vec3_1::operator-(const vec3_1 vec) {
	return vec3_1(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

vec3_1 vec3_1::operator-(const float* vec) {
	return vec3_1(this->x - vec[0], this->y - vec[1], this->z - vec[2]);
}

vec3_1 vec3_1::operator*=(const vec3_1 vec) {
	return vec3_1(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

vec3_1 vec3_1::operator*=(const float scalar) {
	return vec3_1(this->x * scalar, this->y * scalar, this->z * scalar);
}

bool vec3_1::operator==(const vec3_1 vec) {
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
}

bool vec3_1::operator==(const float value) {
	return (this->x == value && this->y == value && this->z == value);
}

bool vec3_1::operator!=(const vec3_1 vec) {
	return (this->x != vec.x && this->y != vec.y && this->z != vec.z);
}

bool vec3_1::operator!=(const float value) {
	return (this->x != value && this->y != value && this->z != value);
}

vec3_1::operator float*() {
	return this->convert();
}

float* vec3_1::convert() {
	return (float*)&this[0];
}

void vec3_1::print() {
	//printf("(%v)\n", this->convert());
}
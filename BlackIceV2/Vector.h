#ifndef Vector
#define Vector

template<class T>
class vector {
	T **_data;
	int _capacity;
	int _count;
public:
	vector() {
		_data = (T**)malloc(sizeof(T)*5);
		_capacity = 5;
		_count = 0;
	}
	~vector() {
		free(_data);
		free(&_capacity);
		free(&_count);
	}

	void push(T value) {
		memcpy(_data[_count++], (void*)value, sizeof(T));
	}
	void pop() {
		memset(_data[_count--], 0, sizeof(T));
	}
	int count() {
		return this->_count;
	}
	T &at(int index) {
		return *_data[index];
	}

	T &operator[](int index) {
		if (index > _capacity) {
			return *_data[0];
		}
		return this->at(index);
	}
};
class vec3_1 {
public:
	float x, y, z;

	//constructors
	vec3_1();
	~vec3_1();
	vec3_1(float x);
	vec3_1(float x, float y);
	vec3_1(float x, float y, float z);
	vec3_1(float vect[3]);

	//operators
	vec3_1 operator()(float x, float y, float z);
	vec3_1 operator+(const vec3_1 vec);
	vec3_1 operator+(const float* vec);
	vec3_1 operator-(const vec3_1 vec);
	vec3_1 operator-(const float* vec);
	vec3_1 operator*=(const vec3_1 vec);
	vec3_1 operator*=(const float scalar);
	bool operator==(const vec3_1 vec);
	bool operator==(const float value);
	bool operator!=(const vec3_1 vec);
	bool operator!=(const float value);
	operator float*();

	//functions
	float* convert();
	void print();
};

#endif /* ___VECTOR_H__ */
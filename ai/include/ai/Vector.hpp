#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
public:
    //position
    int x;
    int y;
    //Operators
    bool operator==(const Vector& v) const;
		struct HashFunction {
			size_t operator()(const Vector& v) const;
		};
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;

    int CalculateManHatDistance();
};

extern const Vector DOWN_VECTOR;
extern const Vector UP_VECTOR;
extern const Vector LEFT_VECTOR;
extern const Vector RIGHT_VECTOR;
extern const Vector ZERO_VECTOR;

#endif
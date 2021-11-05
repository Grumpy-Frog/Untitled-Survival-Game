#ifndef MATH_H
#define MATH_H

#include <math.h>

namespace math
{
	class Vector3
	{
	public:
		double x;
		double y;
		double z;


	public:
		Vector3()
		{
			this->x = 0.0;
			this->y = 0.0;
			this->z = 0.0;
		}


		Vector3(double x, double y, double z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		double operator[](unsigned i) const
		{
			try
			{
				if (i == 0)
				{
					return x;
				}
				else if (i == 1)
				{
					return y;
				}
				else if (i == 2)
				{
					return z;
				}
				else
				{
					throw(i);
				}
			}
			catch (int errorIndex) {
				cout << "vector3 has 3 elements (0 <= i <= 2). You are out of range\n";
				cout << "Your given range is: " << errorIndex << endl;
			}
		}

		double& operator[](unsigned i)
		{
			try
			{
				if (i == 0)
				{
					return x;
				}
				else if (i == 1)
				{
					return y;
				}
				else if (i == 2)
				{
					return z;
				}
				else
				{
					throw(i);
				}
			}
			catch (int errorIndex) {
				cout << "vector3 has 3 elements (0 <= i <= 2). You are out of range\n";
				cout << "Your given range is: " << errorIndex << endl;
			}
		}

		void operator+=(const Vector3& v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}

		Vector3 operator+(const Vector3& v) const
		{
			return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
		}

		void operator-=(const Vector3& v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}


		Vector3 operator-(const Vector3& v) const
		{
			return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
		}

		void operator*=(const double value)
		{
			this->x *= value;
			this->y *= value;
			this->z *= value;
		}

		Vector3 operator*(const double value) const
		{
			return Vector3(this->x * value, this->y * value, this->z * value);
		}

		Vector3 componentProduct(const Vector3& vector) const
		{
			return Vector3(this->x * vector.x, this->y * vector.y, this->z * vector.z);
		}

		void componentProductUpdate(const Vector3& vector)
		{
			this->x *= vector.x;
			this->y *= vector.y;
			this->z *= vector.z;
		}

		Vector3 vectorProduct(const Vector3& vector) const
		{
			return Vector3
			(
				this->y * vector.z - this->z * vector.y,
				this->z * vector.x - this->x * vector.z,
				this->x * vector.y - this->y * vector.x
			);
		}


		void operator %=(const Vector3& vector)
		{
			*this = vectorProduct(vector);
		}


		Vector3 operator%(const Vector3& vector) const
		{
			return Vector3
			(
				this->y * vector.z - this->z * vector.y,
				this->z * vector.x - this->x * vector.z,
				this->x * vector.y - this->y * vector.x
			);
		}


		double scalarProduct(const Vector3& vector) const
		{
			return this->x * vector.x + this->y * vector.y + this->z * vector.z;
		}


		double operator *(const Vector3& vector) const
		{
			return this->x * vector.x + this->y * vector.y + this->z * vector.z;
		}


		void addScaledVector(const Vector3& vector, double scale)
		{
			this->x += vector.x * scale;
			this->y += vector.y * scale;
			this->z += vector.z * scale;
		}


		bool operator==(const Vector3& other) const
		{
			return
				(
					this->x == other.x &&
					this->y == other.y &&
					this->z == other.z
					);
		}


		bool operator!=(const Vector3& other) const
		{
			return !(*this == other);
		}


		bool operator<(const Vector3& other) const
		{
			return
				(
					this->x < other.x &&
					this->y < other.y &&
					this->z < other.z
					);
		}

		bool operator>(const Vector3& other) const
		{
			return
				(
					this->x > other.x &&
					this->y > other.y &&
					this->z > other.z
					);
		}


		bool operator<=(const Vector3& other) const
		{
			return
				(
					this->x <= other.x &&
					this->y <= other.y &&
					this->z <= other.z
					);
		}

		bool operator>=(const Vector3& other) const
		{
			return
				(
					this->x >= other.x &&
					this->y >= other.y &&
					this->z >= other.z
					);
		}

		// magnitude(lenght of a vector)
		double magnitude() const
		{
			return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		}

		void normalise()
		{
			double l = magnitude();
			if (l > 0)
			{
				(*this) *= ((double)1) / l;
			}
		}

		Vector3 unit() const
		{
			Vector3 result = *this;
			result.normalise();
			return result;
		}



		void clear()
		{
			x = y = z = 0;
		}

		void invert()
		{
			x = -x;
			y = -y;
			z = -z;
		}

	};
}

#endif // !MATH_H


/// for UML diagram
/*
#ifndef MATH_H
#define MATH_H

#include <math.h>

namespace math
{
	class Vector3
	{
	public:
		double x;
		double y;
		double z;
	public:
		Vector3()
		Vector3(double x, double y, double z)
		double operator[](unsigned i) const
		double& operator[](unsigned i)
		void operator+=(const Vector3& v)
		Vector3 operator+(const Vector3& v) const
		void operator-=(const Vector3& v)
		Vector3 operator-(const Vector3& v) const
		void operator*=(const double value)
		Vector3 operator*(const double value) const
		Vector3 componentProduct(const Vector3& vector) const
		void componentProductUpdate(const Vector3& vector)
		Vector3 vectorProduct(const Vector3& vector) const
		void operator %=(const Vector3& vector)
		Vector3 operator%(const Vector3& vector) const
		double scalarProduct(const Vector3& vector) const
		double operator *(const Vector3& vector) const
		void addScaledVector(const Vector3& vector, double scale)
		bool operator==(const Vector3& other) const
		bool operator!=(const Vector3& other) const
		bool operator<(const Vector3& other) const
		bool operator>(const Vector3& other) const
		bool operator<=(const Vector3& other) const
		bool operator>=(const Vector3& other) const
		double magnitude()
		void normalise()
		Vector3 unit()
		void clear()
		void invert()
	};
}
*/
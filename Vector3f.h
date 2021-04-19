#include <iostream>

#ifndef VECTOR3F_H
#define VECTOR3F_H
#define DEBUG_CONSTRUCTORS

namespace lmh {

    class Vector3f {
    public:
        //CONSTRUCTORS
        Vector3f(const double &x, const double &y, const double &z);

        Vector3f(const Vector3f &vec);

        Vector3f(Vector3f &&vec) noexcept;

        Vector3f() = delete;

        //GETTERS AND SETTERS
        double gX() const;

        double gY() const;

        double gZ() const;

        void sX(const double &x);

        void sY(const double &y);

        void sZ(const double &z);

        //MATHEMATICAL

        double norm() const;

        double dot(const Vector3f &vec) const;

        Vector3f normalize(const Vector3f &vec) const;


        //ASSIGNMENT OPERATORS
        Vector3f &operator=(const Vector3f &vec);

        Vector3f &operator=(Vector3f &&vec) noexcept;


        //OPERATORS
        Vector3f operator+(const Vector3f &vec) const;

        Vector3f &operator+=(const Vector3f &vec);

        Vector3f operator-(const Vector3f &vec) const;

        Vector3f &operator-=(const Vector3f &vec);

        Vector3f operator*(const double &lambda) const;

        Vector3f &operator*=(const double &lambda);

        friend Vector3f operator*(const double &lambda, const Vector3f &vec);

        friend std::ostream &operator<<(std::ostream &stream, const Vector3f &vec);

    private:
        double x, y, z;

    };
}
    lmh::Vector3f operator*(const double &lambda, const lmh::Vector3f &vec);

    std::ostream& operator<<(const std::ostream &stream, const lmh::Vector3f &vec);


#endif
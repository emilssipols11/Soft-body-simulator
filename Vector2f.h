#include <iostream>

#ifndef Vector2f_H
#define Vector2f_H
#define DEBUG_CONSTRUCTORS

namespace lmh {

    class Vector2f {
    public:
        //CONSTRUCTORS
        Vector2f(const double &x, const double &y);

        Vector2f(const Vector2f &vec);

        Vector2f(Vector2f &&vec) noexcept;

        Vector2f() = default;

        //GETTERS AND SETTERS
        double gX() const;

        double gY() const;

        void sX(const double &x);

        void sY(const double &y);


        //MATHEMATICAL

        double norm() const;

        double dot(const Vector2f &vec) const;

        Vector2f normalize(const Vector2f &vec) const;


        //ASSIGNMENT OPERATORS
        Vector2f &operator=(const Vector2f &vec);

        Vector2f &operator=(Vector2f &&vec) noexcept;


        //OPERATORS
        Vector2f operator+(const Vector2f &vec) const;

        Vector2f &operator+=(const Vector2f &vec);

        Vector2f operator-(const Vector2f &vec) const;

        Vector2f &operator-=(const Vector2f &vec);

        Vector2f operator*(const double &lambda) const;

        Vector2f &operator*=(const double &lambda);

        friend Vector2f operator*(const double &lambda, const Vector2f &vec);

        friend std::ostream &operator<<(std::ostream &stream, const Vector2f &vec);

    private:
        double x{}, y{};

    };

    lmh::Vector2f operator*(const double &lambda, const lmh::Vector2f &vec);

    std::ostream &operator<<( std::ostream &stream, const lmh::Vector2f &vec);
}

#endif
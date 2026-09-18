#include <cmath>
#include <cstdio>

int main()
{
    float a, b, c;
    std::printf("Enter a, b and c: ");
    std::scanf("%f %f %f", &a, &b, &c);

    float D = b * b - 4 * a * c;
    if (D < 0)
    {
        std::printf("Equation has no real roots\n");
    }
    else if (D == 0)
    {
        float x = -b / (2 * a);
        std::printf("x1 = x2 = %f\n", x);
    }
    else
    { // D > 0
        float x1, x2;
        x1 = (-b + std::sqrt(D)) / (2 * a);
        x2 = (-b - std::sqrt(D)) / (2 * a);
        std::printf("x1 = %f\nx2 = %f\n", x1, x2);
    }
}

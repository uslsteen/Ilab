#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define TEST(a, b, c, _n_roots, _x1, _x2) assert (SolveSquare (a, b, c, &x1, &x2) == _n_roots && _x1 == x1 && _x2 == x2), x1 = 0, x2 = 0

const double Epsilon = 1e-6;

const int n_coefs = 3;

enum
{
	NO_ROOTS = 0,
	ONE_ROOT = 1,
	TWO_ROOTS = 2,
	INF_ROOTS = -1,
};

void UnitTests(void);

inline int Compare_with_zero(double a);
//! The function for comparing with zero
//! return true or false

inline double Discriminant(double a, double b, double c);
//! The function for finding discriminant
//! @param[in] a coefficient
//! @param[in] b coefficient
//! @param[in] c coefficient
//! @return discriminant

int SolveSquare(double a, double b, double c, double* x1, double* x2);
//! The function for solving a square equation ax2 + bx+ c = 0 //! 
//! @param [in]  a   a‐coefficient 
//! @param [in]  b   b‐coefficient 
//! @param [in]  c   c‐coefficient 
//! @param[out] x1  Pointer to the 1st root 
//! @param[out] x2  Pointer to the 2nd root 

int SolveLinear(double b, double c, double* x1);
//! The function for solving a linear equation bx+ c = 0 //!
//! @param [in]  b   b‐coefficient 
//! @param [in]  c   c‐coefficient 
//! @param[out] x1  Pointer to the root 
//! @return Number of roots 

int main()
{
	UnitTests();

	printf("#Square equation solver\n");

	printf("#Version 1.0, AdamEdition\n");

	double a = NAN, b = NAN, c = NAN, x1 = NAN, x2 = NAN;

	printf("Let's solve ax^2 + bx + c = 0\nEnter a, b, c.\n");

	int NumRead = NAN;

	double coefs[n_coefs];

	coefs[0] = NAN; coefs[1] = NAN; coefs[2] = NAN;

	/* Цикл ввода организована так, чтобы пользователь точно ввел три коэффициента для решения уравнения. 
	В случае его опечатки/умышленного неправильного ввода данных все, что было написано после некорретного типа данных будет стерто и цикл заного попросит ввести коэффициенты. 
	Причем все верно введенные параметры сохраняются, о чем будет свидетельствовать строка "successful input", отображающая уже полученные программой значения a, b, c.
	*/

	for (int i = 0; i < n_coefs; i++) {

		int NumRead = scanf_s("%lf", &coefs[i]);

		if (NumRead != 1) {
			printf("Wrong input! Please, try again!\n");
			i--;
			while (getchar() != '\n');
		}

		printf("[%d]/[%d] successful input.\nAt the moment a = %lf, b = %lf, c = %lf\n", i + 1, n_coefs, coefs[0], coefs[1], coefs[2]);
	}

	a = coefs[0]; b = coefs[1]; c = coefs[2];

	printf("Let's solve it: %lfx^2 + %lfx + %lf = 0\n", a, b, c);

	int n_roots = SolveSquare(a, b, c, &x1, &x2);

	switch (n_roots)
	{
	case NO_ROOTS: printf("The equation has no roots\n");
		break;
	case ONE_ROOT: printf("The equation has one root: x = %.4lf\n", x1);
		break;
	case TWO_ROOTS: printf("The equation has two roots: x1 = %.4lf, x2 = %.4lf\n", x1, x2);
		break;
	case INF_ROOTS: printf("The equation has infinity number of roots\n");
		break;
	default: printf("main(): ERROR: n_roots = %d\n", n_roots);
		break;
	}
	return 0;
}


void UnitTests() {
	double x1 = 0.0, x2 = 0.0;
	TEST(1, -5, 6, 2, 3, 2);
	TEST(1, -3, 2, 2, 2, 1);
	printf("Unit Tests completed\n");
}

int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	assert(isfinite(a));
	assert(isfinite(b));
	assert(isfinite(c));

	assert(x1 != NULL);
	assert(x2 != NULL);

	assert(x1 != x2);

	if (Compare_with_zero(a)) // checking a = 0
	{
		int n_roots1 = SolveLinear(b, c, x1);
		if (n_roots1 == 1)
			return ONE_ROOT;
		else
			return n_roots1;
	}
	else
		if (Compare_with_zero(c)) // checking с = 0
		{
			*x2 = 0;
			int n_roots2 = SolveLinear(a, b, x1);
			if (n_roots2)
				return TWO_ROOTS;
			else
				return n_roots2;
		}
		else
			if (!Compare_with_zero(a)) // checking a != 0
			{
				double d = Discriminant(a, b, c);

				if (Compare_with_zero(d)) // checking d = 0
				{
					*x1 = -b / (2 * a);
					return ONE_ROOT;
				}
				if (d > 0)
				{
					double sqrt_d = sqrt(d);
					*x1 = (-b + sqrt_d) / (2 * a);
					*x2 = (-b - sqrt_d) / (2 * a);
					return TWO_ROOTS;
				}
				else
					if (d < 0)
					{
						return NO_ROOTS;
					}
			}
}
int SolveLinear(double b, double c, double* x1)
{
	if (Compare_with_zero(b) && Compare_with_zero(c)) // checking b = 0 && c = 0
	{
		return INF_ROOTS;
	}
	else
		if (Compare_with_zero(b) && !Compare_with_zero(c)) // checking b = 0 && c != 0
		{
			return NO_ROOTS;
		}
		else
			if (!Compare_with_zero(b))
			{
				*x1 = -c / b;
				return ONE_ROOT;
			}
}
inline int Compare_with_zero(double a)
{
	return (fabs(a - 0) < Epsilon);
}
inline double Discriminant(double a, double b, double c)
{
	return b * b - 4 * a * c;
}

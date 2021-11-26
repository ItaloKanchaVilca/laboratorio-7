#include <iostream>
#include <string>
#include <time.h>

using namespace std;

const string abc = "abcdefghijklmnopqrstuvwxyz().0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ,+-";
int abc_tam = abc.size();

template <typename T>
T mod(T a, T n)
{
	T temp = a / n;
	T r = a - (temp * n);
	if (r < 0)
	{
		r += n;
	}
	return r;
}

template <typename T>
T euclides(T a, T b)
{
	T q, r;
	while (b > 0)
	{
		q = a / b;
		r = a - q * b;
		// A = Q * B + R
		a = b;
		b = r;
	}
	return a;
}

template <typename T>
T euclidesExtendido(T a, T b, T& x, T& y)
{
	T q, r1 = a, r2 = b, r, s1 = 1, s2 = 0, s, t1 = 0, t2 = 1, t;
	while (r2 > 0)
	{
		q = r1 / r2;

		r = r1 - q * r2;
		r1 = r2, r2 = r;

		s = s1 - q * s2;
		s1 = s2, s2 = s;

		t = t1 - q * t2;
		t1 = t2, t2 = t;
	}
	x = s1;
	y = t1;
	return r1;
}

template<typename T>
T inversa(T a, T n)
{
	T x, y;
	euclidesExtendido<T>(a, n, x, y);
	return mod<T>(x, n);
}

template <typename T>
class RSA
{
	T q, p, n, phi_n, e, d;
	T clave_privada[2];
public:
	T clave_publica[2];
	RSA(T q = 17, T p = 43)
	{
		this->q = q;
		this->p = p;
		n = q * p;
		phi_n = (q - 1) * (p - 1);
		srand(time(NULL));
		e = mod<t>(rand(), phi_n);
		while (euclides<T>(e, phi_n) != 1)
		{
			e = mod<T>(rand(), phi_n);
		}
		d = inversa<T>(e, phi_n);
		clave_privada[0] = n;
		clave_privada[1] = d;
		clave_publica[0] = n;
		clave_publica[1] = e;
	}
	T cifrar(string mensaje, T publica[2])
	{
		T q = expmod(abc.find(mensaje), publica[1], publica[0]);
		return q;
	}
	string descifrar(T txt)
	{
		T temp = expmod(txt, d, n);
		string D;
		D = abc[temp];
		return D;
	}
};

int main()
{
	RSA<int> fernando;
}
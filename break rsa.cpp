#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <gmpxx.h>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Please specify the file name.\n";
        return 0;
    }

    std::vector<mpz_class> ciphertext;
    {
        std::fstream fs;
        fs.open(argv[1], std::fstream::in);
        std::string line;
        while (std::getline(fs, line)) {
            ciphertext.push_back(mpz_class(line.c_str(), 16));
        }
    }

    // Public key.
    mpz_class n, a;
    n.set_str("a65db2074039053f9980a4d06884cc7c8cd72e3bd2e883e8f75c1f17", 16);
    a.set_str("35ef8e080e741222ddd5256b9f2e2144c32e2fb1d909f5ae160805", 16);
    mpz_class f1, f2;
    f1.set_str("3889923060761232077444551752098261", 10);
    f2.set_str("4504043963017591265757550206945083", 10);

    mpz_class phi_n = (f1 - 1) * (f2 - 1);

    mpz_class b;
    mpz_powm(b.get_mpz_t(), a.get_mpz_t(), mpz_class(-1).get_mpz_t(), phi_n.get_mpz_t());

    for (auto& x : ciphertext) {
        mpz_class d;
        mpz_powm(d.get_mpz_t(), x.get_mpz_t(), b.get_mpz_t(), n.get_mpz_t());

        std::vector<char> str;
        while (d > 0) {
            mpz_class temp = d & 0xff;
            str.push_back(temp.get_ui());
            d >>= 8;
        }

        for (int i = str.size() - 1; i >= 0; i--) {
            std::cout << str[i];
        }
    }

    return 0;
}
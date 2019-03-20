#include <iostream>
#include <fstream>
#include <vector>
#include <iosfwd>
#include <algorithm>
#include <iterator>
#include <unordered_map>


void solution();

void naive_solution();

int main()
{
    std::ifstream in;

    in = std::ifstream{"../input.txt"};
    std::cin.rdbuf(in.rdbuf());
    naive_solution();
    std::cout << std::endl;

    in = std::ifstream{"../input.at.scale.txt"};
    std::cin.rdbuf(in.rdbuf());
    naive_solution();
    std::cout << std::endl;

    in = std::ifstream{"../input.txt"};
    std::cin.rdbuf(in.rdbuf());
    solution();
    std::cout << std::endl;

    in = std::ifstream{"../input.at.scale.txt"};
    std::cin.rdbuf(in.rdbuf());
    solution();
    std::cout << std::endl;

    in = std::ifstream{"../input.at.scale.2.txt"};
    std::cin.rdbuf(in.rdbuf());
    solution();
    std::cout << std::endl;

    return 0;
}


void naive_solution()
{
    int N;
    std::cin >> N;
    std::vector<int> a(N);
    copy_n(std::istream_iterator<int>(std::cin), N, begin(a));

    size_t min = N + 1;

    for (auto it = std::begin(a); it != std::end(a); ++it)
    {
        const auto v = *it;
        for (auto it2 = it + 1; it2 != std::end(a); ++it2)
        {
            const auto v2 = *it2;
            if (v == v2)
            {
                size_t d = std::distance(it, it2);
                min = std::min(min, d);
            }
        }
    }

    if (N + 1 == min)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << min;
    }

//    is_sorted_until
//    iter_swap
//    make_reverse_iterator
//    find_if
//    is_sorted

}

void solution()
{
    int N;
    std::cin >> N;
    std::vector<int> a(N);
    copy_n(std::istream_iterator<int>(std::cin), N, begin(a));

    int min = N + 1;

    std::unordered_map<int, int> m;
    for (auto it = std::begin(a); it != std::end(a); ++it)
    {
        auto v = *it;
        int indice_destro = std::distance(std::begin(a), it);
        if (m.count(v))
        {
            int indice_sinistro = m.at(v);
            min = std::min(min, indice_destro - indice_sinistro);
        }
        else
        {
            m[v] = indice_destro;
        }
    }

    if (N + 1 == min)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << min;
    }
}
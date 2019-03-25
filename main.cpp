#include <bits/stdc++.h>

void solution();
void naive_solution();
void solution_memory_saving();

inline int parseLine(char *line)
{
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char *p = line;
    while (*p < '0' || *p > '9')
    { p++; }
    line[i - 3] = '\0';
    i = atoi(p);
    return i;
}

inline int getVmSizeinKB()
{
    FILE *file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, "VmSize:", 7) == 0)
        {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

inline int getVmRSSinKB()
{
    FILE *file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL)
    {
        if (strncmp(line, "VmRSS:", 6) == 0)
        {
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int main()
{
    std::ifstream in;

//    in = std::ifstream{"../input.txt"};
//    std::cin.rdbuf(in.rdbuf());
//    naive_solution();
//    std::cout << std::endl;

    in = std::ifstream{"../input.txt"};
    std::cin.rdbuf(in.rdbuf());
    solution_memory_saving();
    std::cout << std::endl;

//    in = std::ifstream{"../input.at.scale.txt"};
//    std::cin.rdbuf(in.rdbuf());
//    naive_solution();
//    std::cout << std::endl;

//    in = std::ifstream{"../input.txt"};
//    std::cin.rdbuf(in.rdbuf());
//    solution();
//    std::cout << std::endl;
//
//    in = std::ifstream{"../input.at.scale.txt"};
//    std::cin.rdbuf(in.rdbuf());
//    solution();
//    std::cout << std::endl;
//
//    in = std::ifstream{"../input.at.scale.2.txt"};
//    std::cin.rdbuf(in.rdbuf());
//    solution();
//    std::cout << std::endl;

    in = std::ifstream{"../input.at.scale.2.txt"};
    std::cin.rdbuf(in.rdbuf());
    solution_memory_saving();
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

    std::cerr << getVmRSSinKB() << std::endl;
}

void solution_memory_saving()
{
    std::vector<int> inverse(100000, -1);
    int N;
    std::cin >> N;
    std::vector<int> a(N);

    copy_n(std::istream_iterator<int>(std::cin), N, begin(a));

    int min = N + 1;

    for (auto it = 0; it<a.size(); ++it)
    {
        auto v = a[it];
        if (inverse[v]>=0)
        {
            int indice_sinistro = inverse[v];
            min = std::min(min, it - indice_sinistro);
            inverse[v] = it;
        }
        else
        {
            inverse[v] = it;
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

    std::cerr << getVmRSSinKB() << std::endl;
}

#include <iostream>    
#include <fstream>    
#include <vector>      
#include <algorithm>   
#include <iterator> 

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " input_file\n";
        return 1;
    }

    ifstream in(argv[1]);
    if (!in) {
        cerr << "Cannot open input file: " << argv[1] << "\n";
        return 1;
    }

    // Chitaem N, a, b
    long long N;
    long long a, b;
    if (!(in >> N >> a >> b)) {
        cerr << "Bad input header (expect N a b)\n";
        return 1;
    }

    // Chitaem stroku iz N chisel v vektor orig
    vector<long long> orig;
    orig.reserve((size_t)max(0LL, N));
    for (long long i = 0; i < N; ++i) {
        long long x;
        if (!(in >> x)) {
            cerr << "Not enough numbers in second line (expected " << N << ")\n";
            return 1;
        }
        orig.push_back(x);
    }

    // 1) Vyvod iskhodnogo massiva
    cout << "Ishodnyy massiv:\n";
    copy(orig.begin(), orig.end(), ostream_iterator<long long>(cout, " "));
    cout << "\n\n";

    // 2) Massiv v diapazone [a, b] (udalyaem chisla, ne lezhashchie v [a,b])
    vector<long long> in_range = orig;
    auto out_of_range_pred = [&](long long x) {
        return (x < a) or (x > b);
    };

    /*
    bool out_of_range_pred(long long x) {
        return (x < a) or (x > b);
    }
    */
    // remove_if + erase
    auto new_end = remove_if(in_range.begin(), in_range.end(), out_of_range_pred);
    in_range.erase(new_end, in_range.end());

    cout << "Massiv v diapazone [" << a << ", " << b << "]:\n";
    for (size_t i = 0; i < in_range.size(); i++) {
        cout << in_range[i] << " ";
    }
    cout << "\n\n";

    // 3) Nayti maksimum (pervoe vkhozhdenie), zatem nayti pervyy chetnyy element, sleduyushchiy za maksimumom,
    //    i isklyuchit' ego (esli nayden)
    bool excluded = false;
    long long excluded_value = 0;
    long long excluded_pos1based = -1; // pozitsiya v in_range do udaleniya (1-based)

    if (!in_range.empty()) {
        auto it_max = max_element(in_range.begin(), in_range.end());
        // nayti pervyy chetnyy element posle it_max
        auto it_search = find_if(next(it_max), in_range.end(), [](long long x) {
            return (x % 2 == 0);
        });

        if (it_search != in_range.end()) {
            excluded = true;
            excluded_value = *it_search;
            excluded_pos1based = distance(in_range.begin(), it_search) + 1; // 1-based
            in_range.erase(it_search); // udaliaem element
        }
    }

    cout << "Massiv posle isklyucheniya (esli isklyuchali):\n";
    copy(in_range.begin(), in_range.end(), ostream_iterator<long long>(cout, " "));
    cout << "\n\n";

    if (excluded) {
        cout << "Isklyuchennyy element: pozitsiya (v massive v diapazone, 1-based) = "
             << excluded_pos1based << ", znachenie = " << excluded_value << "\n\n";
    } else {
        cout << "Isklyuchennyy element: ne nayden (nichego ne udaleno)\n\n";
    }

    // 4) Kolichestvo polozhitel'nykh i otritsatel'nykh chisel v poluchivshemsya (posle isklyucheniya) massive
    auto positive_pred = [](long long x) { return x > 0; };
    auto negative_pred = [](long long x) { return x < 0; };

    long long cnt_positive = count_if(in_range.begin(), in_range.end(), positive_pred);
    long long cnt_negative = count_if(in_range.begin(), in_range.end(), negative_pred);

    cout << "Kolichestvo polozhitelnykh chisel: " << cnt_positive << "\n";
    cout << "Kolichestvo otritsatelnykh chisel: " << cnt_negative << "\n";

    return 0;
}
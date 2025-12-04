#include <iostream>
#include <variant>
#include <cmath>
#include <utility>
#include <optional>
#include <string>

using QuadraticResult = std::variant<std::monostate, double, std::pair<double,double>>;

// solveQuadratic reshaet kvadratnoe uravnenie ax^2 + bx + c = 0
// vozvraschaet std::variant: monostate (net realnykh korney),
// double (odin koren), ili pair<double,double> (dva kornya)
QuadraticResult solveQuadratic(double a, double b, double c) {
    const double eps = 1e-12; // malenkaya pogreshnost' dlya sravneniy s nul'em
    if (std::abs(a) < eps) { // esli a ~= 0 -> lineynoe uravnenie
        if (std::abs(b) < eps) return std::monostate{}; // b ~= 0 -> net resheniy ili beskonechno mnog; my vozvraschaem monostate
        return -c / b; // odin koren dlya lineynogo uravneniya
    }
    double D = b*b - 4*a*c; // diskriminant
    if (D < -eps) return std::monostate{}; // otricatel'nyy -> net realnykh korney
    if (std::abs(D) <= eps) return -b / (2*a); // odin dvoynoy koren
    double s = std::sqrt(D); // kvadratnyy koren diskriminanta
    return std::make_pair((-b + s) / (2*a), (-b - s) / (2*a)); // dva kornya
}

// RootVisitor: posetitelskaya struktura dlya vyvoda rezultata
struct RootVisitor {
    void operator()(std::monostate) const { std::cout << "Net deystvitelnykh korney"; } // net real'nykh korney
    void operator()(double r) const { std::cout << "Odin koren: x = " << r << '\n'; } // odin koren
    void operator()(const std::pair<double,double>& p) const { std::cout << "Dva kornya: x1 = " << p.first << ", x2 = " << p.second << '\n'; } // dva kornya
};

// parseArgs: proveryaet argv[i] i summyruet tol'ko polnost'yu chislovye stroki
// vozvraschaet optional<double>: esli net chisel -> nullopt
std::optional<double> parseArgs(int argc, char* argv[]) {
    std::optional<double> sum; // pustoy optional - esli ne naydeno chisel
    for (int i = 1; i < argc; ++i) {
        try {
            size_t pos = 0;
            std::string s = argv[i];
            double v = std::stod(s, &pos); // stoi stoi provodit pars
            if (pos == s.size()) { // tol'ko esli vsya stroka byla chislom
                if (sum) *sum += v; else sum = v; // nakoplivaem v optional
            }
        } catch (...) { /* propustit nechisovoy argument */ }
    }
    return sum; // nullopt esli ne bylo chisel
}

// prostoy main, pokazivayet rabotu Task1 i Task2
int main(int argc, char* argv[]) {
    // Testy dlya Task1 (kvadratnye uravneniya)
    struct T{double a,b,c; const char* d;};
    T tests[] = {
        {1,-5,6,"x^2 - 5x + 6 = 0"},
        {1,0,-4,"x^2 - 4 = 0"},
        {1,-2,1,"x^2 - 2x + 1 = 0"},
        {1,0,1,"x^2 + 1 = 0"},
        {0,2,-4,"2x - 4 = 0"}
    };

    std::cout << "--- Task1: kvadratnye uravneniya ---"; // zagolovok dlya pervoy chasti
    for (auto const& t : tests) {
        std::cout << "Uravnenie: " << t.d << '\n'; // vyvod opredeleniya uravneniya
        std::visit(RootVisitor{}, solveQuadratic(t.a,t.b,t.c)); // vizit rezultata i vyvod
    }

    // Task2: parse args
    std::cout << "--- Task2: parsig argumentov ---"; // zagolovok dlya vtoroy chasti
    if (auto s = parseArgs(argc, argv)) std::cout << "Summa chislovykh argumentov: " << *s << '\n';
    else std::cout << "Chislovye argumenty ne naideny"; // esli net chisel v argv

    return 0; // vyhod iz programma
}
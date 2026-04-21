#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const std::vector<std::string_view> routes[] = {
    {
        "7_klyuchey", "Sortirovochnaya", "China_town", "Zarechny", "City", "1905_year_square", "Kuybyshevskaya",
        "Sibirskaya", "Siniye_kamni", "Lechebnaya", "Varshavskaya", "Kompressornaya", "Koltsovo"
    },
    {
        "Zelyony_ostrov", "Tatishchevskaya", "Verh_Isetskaya", "Kommunarov_square", "1905_year_square",
        "Teatralnaya", "Vostochnaya", "Vtuzgorodok", "Kamennye_palatki", "University"
    },
    {
        "MEGA", "Metallurgov", "Kraulya", "Central_stadium", "Moskovskaya", "1905_year_square",
        "Shevchenko", "Pionerskaya", "Turbinnaya", "Elmash", "Taganskaya"
    },
    {
        "Akademicheskaya", "Yugo_zapadnaya", "Volgogradskaya", "Posadskaya", "Geologicheskaya", "Teatralnaya",
        "Gagarinskaya", "Komsomolskaya", "Shefskaya", "Ozyornaya", "Italyanskaya", "Kalinovskaya"
    },
    {
        "Sovhoznaya", "Voennaya", "Aviatsionnaya", "Dvorets_sporta", "Geologicheskaya",
        "Kuybyshevskaya", "Vostochnaya", "Gagarinskaya", "Vilonovskaya"
    },
    {
        "Keramicheskaya", "Vtorchermet", "Samolyotnaya", "Botanicheskaya", "Parkovaya", "Mayakovskaya",
        "Oborony_square", "Kuybyshevskaya", "Teatralnaya", "Shevchenko", "Uralskaya", "Zvezda",
        "I_Pyatiletki_square", "Pobedy"
    },
    {
        "Himmash", "Nizhne_Isetskaya", "Uktusskie_Gory", "Shcherbakovskaya", "Botanicheskaya", "Chkalovskaya",
        "Bazhovskaya", "Geologicheskaya", "1905_year_square", "Dinamo", "Uralskaya", "Mashinostroiteley",
        "Uralmash", "Prospekt_Kosmonavtov", "Bakinskih_Komissarov"
    },
    {
        "Moskovskaya", "Kommunarov_square", "City", "Uralskaya", "Pionerskaya", "Gagarinskaya", "Vtuzgorodok",
        "Sibirskaya", "Oborony_square", "Bazhovskaya", "Dvorets_sporta", "Posadskaya", "Moskovskaya"
    }
};

std::vector<std::string_view> stations;

void initialize_stations()
{
    for (const auto& route : routes) {
        for (const auto station : route)
            stations.push_back(station);
    }

    std::sort(stations.begin(), stations.end());
    stations.erase(std::unique(stations.begin(), stations.end()), stations.end());
}

size_t locate_station(std::string_view station)
{
    return std::lower_bound(stations.begin(), stations.end(), station) - stations.begin();
}

unsigned distances[70][70];

void initialize_distances()
{
    constexpr unsigned oo = ~0u >> 1;

    for (size_t i = 0; i < 70; ++i) {
        for (size_t j = 0; j < 70; ++j)
            distances[i][j] = (i == j ? 0 : oo);
    }

    for (const auto& route : routes) {
        for (size_t i = 1; i < route.size(); ++i) {
            const size_t u = locate_station(route[i-1]), v = locate_station(route[i]);
            distances[u][v] = 1;
            distances[v][u] = 1;
        }
    }

    for (size_t k = 0; k < 70; ++k) {
        for (size_t i = 0; i < 70; ++i) {
            for (size_t j = 0; j < 70; ++j)
                distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
        }
    }
}

void test_case()
{
    std::string s, t;
    std::cin >> s >> t;

    std::cout << distances[locate_station(s)][locate_station(t)] << '\n';
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    initialize_stations();
    initialize_distances();

    size_t t;
    std::cin >> t;

    while (t-- > 0)
        test_case();

    return 0;
}

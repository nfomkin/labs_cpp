#include "pugixml.hpp"
#include <math.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <ciso646>
#include <algorithm>
#include <set>
#include <map>

using namespace std;


class Transport
{
private:
    wstring type;
public:
    Transport(wstring current_type_of_vehicle) : type(current_type_of_vehicle) {}

    void max_route(pugi::xml_document& data)
    {
        pugi::xml_node main_node = data.first_child();
        wstring transport;
        wstring route;
        unordered_map<wstring, int> route_stops;
        pair<wstring, int> max_route({ L"none", 0 });
        for (pugi::xml_node node1 = main_node.first_child(); node1; node1 = node1.next_sibling())
        {
            for (pugi::xml_node node2 = node1.first_child(); node2; node2 = node2.next_sibling())
            {
                wstring name = node2.name();
                wstring value = node2.child_value();

                if (name == L"type_of_vehicle")
                {
                    transport = value;
                }

                if (name == L"routes" and transport == type)
                {
                    for (int i = 0; value[i] != '\0'; i++)
                    {
                        if (value[i] == '.' or value[i] == ',' or value[i + 1] == '\0')
                        {
                            route_stops[route] += 1;
                            if (route_stops[route] > max_route.second)
                            {
                                max_route.first = route;
                                max_route.second = route_stops[route];
                            }
                            route = L"";
                        }
                        else
                        {
                            route += value[i];
                        }
                    }
                }
            }
        }
        wcout << L"Route with the most stops: " << max_route.first << endl;
    }

    pair<double, double> make_coordinates(const string& coordinates)
    {
        string latitude;
        string longitude;
        int i;
        for (i = 0; coordinates[i] != ','; i++)
        {
            latitude += coordinates[i];
        }
        i++;
        for (; coordinates[i] != '\0'; i++)
        {
            longitude += coordinates[i];
        }
        return { atof(latitude.c_str()), atof(longitude.c_str()) };
    }

    double distance(pair<double, double> c1, pair<double, double> c2)
    {
        return sqrt(pow(c1.first - c2.first, 2) + pow(c1.second - c2.second, 2));
    }

    void longest_route(pugi::xml_document& data)
    {
        unordered_map<wstring, vector<pair<double, double>> > route_coordinates;
        unordered_map<wstring, double> route_length;
        wstring transport;
        wstring routes;
        wstring cur_route;
        pugi::xml_node main_node = data.first_child();
        for (pugi::xml_node node1 = main_node.first_child(); node1; node1 = node1.next_sibling())
        {
            for (pugi::xml_node node2 = node1.first_child(); node2; node2 = node2.next_sibling())
            {
                wstring name = node2.name();
                wstring value = node2.child_value();

                if (name == L"type_of_vehicle")
                    transport = value;

                if (name == L"routes" and transport == type)
                {
                    routes = value;
                }

                if (name == L"coordinates" and transport == type)
                {
                    string coordinates(value.begin(), value.end());
                    pair<double, double> Crd = make_coordinates(coordinates);
                    for (int i = 0; routes[i] != '\0'; i++)
                    {
                        if (routes[i] == '.' or routes[i] == ',' or routes[i + 1] == '\0')
                        {
                            route_coordinates[cur_route].push_back(Crd);
                            route_length.insert({ cur_route, 0 });
                            cur_route = L"";
                        }
                        else
                        {
                            cur_route += routes[i];
                        }

                    }
                }

            }
        }

        pair<wstring, double> max = { L"none", 0 };
        for (auto route : route_coordinates) {
            {
                wstring name_route = route.first;
                vector<pair<double, double>>& arr = route.second;
                for (int i = 0; i < arr.size() - 1; i++)
                {
                    route_length[name_route] += distance(arr[i], arr[i + 1]);
                    if (route_length[name_route] > max.second)
                    {
                        max.first = name_route;
                        max.second = route_length[name_route];
                    }
                }
            }
        }
        wcout << L"The longest route: " << max.first << endl;
    }

    void max_street(pugi::xml_document& data)
    {
        pugi::xml_node main_node = data.first_child();
        unordered_map<wstring, int> streets;
        wstring transport;
        pair<wstring, int> max = { L"none", 0 };
        for (pugi::xml_node node1 = main_node.first_child(); node1; node1 = node1.next_sibling())
        {
            for (pugi::xml_node node2 = node1.first_child(); node2; node2 = node2.next_sibling())
            {
                wstring name = node2.name();
                wstring value = node2.child_value();
                if (name == L"type_of_vehicle")
                {
                    transport = value;
                }

                else if (name == L"name_stopping" and transport == type)
                {
                    streets[value]++;
                    if (streets[value] > max.second)
                    {
                        max.first = value;
                        max.second = streets[value];
                    }
                }
            }
        }
        wcout << L"The street with max stops: " << max.first << endl;
    }
};

int main()
{
    pugi::xml_document data;
    data.load_file("data.xml");
    Transport a(L"Автобус");
    a.max_route(data);
    a.longest_route(data);
    a.max_street(data);
    return 0;
}
